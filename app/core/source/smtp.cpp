#include "pch.h"
#include "smtp.h"
#include <curl/curl.h>
#include <string.h>
#include <stdio.h>
#include <thread>

namespace SMTP 
{
    static std::string payload_text_str;
    static const char* payload_text = nullptr;

    std::string EmailMsg(const std::string& to, const std::string& from, const std::string& cc,const std::string& subject,const std::string& body) 
    {
        std::string id = "<" + std::to_string(rand() % INT_MAX) + "@gmail.com>";;
        std::string message =
            "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n"
            "To: " + to + "\r\n"
            "From: " + from + "\r\n"
            "Cc: " + cc + "\r\n"
            "Message-ID: " + id + "\r\n"
            "Subject: " + subject + "\r\n"
            "\r\n" +
            body + "\r\n";

        return message;
    }

    struct upload_status
    {
        size_t bytes_read;
    };

    static size_t payload_source(char* ptr, size_t size, size_t nmemb, void* userp)
    {
        upload_status* upload_ctx = (upload_status*)userp;
        const char* data = &payload_text[upload_ctx->bytes_read];
        size_t room = size * nmemb;

        if (!data || room == 0)
            return 0;

        size_t len = strlen(data);
        if (len > room)
            len = room;

        memcpy(ptr, data, len);
        upload_ctx->bytes_read += len;

        return len;
    }
    Request::Request(const std::string& emailSender, const std::string& passwordSender, const std::string& serverAddr)
    {
        sender.email = emailSender;
        sender.password = passwordSender;
        server = serverAddr;
    }
    void Request::SetSender(const std::string& email, const std::string& password)
    {
        sender.email = email;
        sender.password = password;
    }
    void Request::SetServer(const std::string& serverAddr)
    {
        server = serverAddr;
    }
    void Request::SendThread(const std::string& receiverEmail, const std::string& subject, const std::string& body)
    {
        CURL* curl;
        CURLcode res = CURLE_OK;
        struct curl_slist* recipients = nullptr;
        upload_status upload_ctx = { 0 };

        std::srand(std::time(nullptr));

        payload_text_str = EmailMsg(receiverEmail, sender.email, "", subject, body);
        payload_text = payload_text_str.c_str();

        curl = curl_easy_init();
        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, nullptr);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, nullptr);

            curl_easy_setopt(curl, CURLOPT_USERNAME, sender.email.c_str());
            curl_easy_setopt(curl, CURLOPT_PASSWORD, sender.password.c_str());

            curl_easy_setopt(curl, CURLOPT_URL, server.c_str());
            curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

            curl_easy_setopt(curl, CURLOPT_MAIL_FROM, sender.email.c_str());

            recipients = curl_slist_append(recipients, receiverEmail.c_str());
            curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

            curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
            curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
            curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

            curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
            {
                char msg[256];
                sprintf_s(msg, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res)); // print error str to msg buf
                OutputDebugStringA(msg);
            }

            curl_slist_free_all(recipients);
            curl_easy_cleanup(curl);
        }
    }
    void Request::Send(const std::string& receiverEmail,const std::string& subject,const std::string& body)
    {
        std::thread t(&Request::SendThread, this, receiverEmail, subject, body);
        t.detach();
    }
}
