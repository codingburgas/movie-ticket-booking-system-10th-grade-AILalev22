#include "pch.h"
#include "smtp.h"
#include <curl/curl.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include "utils.h"

namespace SMTP
{

    std::string EmailMsg(const std::vector<std::string>& toList, const std::string& from, const std::string& cc,const std::string& subject, const std::string& body)
    {
        std::string id = "<" + std::to_string(rand() % INT_MAX) + "@gmail.com>"; // unique email id

        std::string toCombined; // combined email list
        for (size_t i = 0; i < toList.size(); i++)
        {
            toCombined += toList[i];
            if (i < toList.size() - 1)
                toCombined += ", ";
        }
        std::string message =
            "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n"
            "To: " + toCombined + "\r\n"
            "From: " + from + "\r\n"
            "Cc: " + cc + "\r\n"
            "Message-ID: " + id + "\r\n"
            "Subject: " + subject + "\r\n"
            "\r\n" +
            body + "\r\n";

        return message;
    }

    struct stru 
    {
        size_t readed;
        std::string payload;
    };

    static size_t PayloadSrc(char* ptr, size_t size, size_t nmemb, void* userp)
    {
        if (!ptr || !userp)
            return 0;

        size_t room = size * nmemb;
        if (room == 0)
            return 0;

        stru* upload_ctx = (stru*)userp;

        size_t remaining = upload_ctx->payload.size() - upload_ctx->readed;
        size_t len = (remaining < room) ? remaining : room;

        memcpy(ptr, upload_ctx->payload.data() + upload_ctx->readed, len);
        upload_ctx->readed += len;

        return len;
    }

    ///////////////////
    Request::Request(const Entity::User& sender, const std::string& smtpAddr)
    {
        this->sender.email = sender.email;
        this->sender.password = sender.password;
        this->smtpAddr = smtpAddr;
    }
    void Request::SetSender(const std::string& email, const std::string& password)
    {
        sender.email = email;
        sender.password = password;
    }
    void Request::SetServer(const std::string& smtpAddr)
    {
        this->smtpAddr = smtpAddr;
    }
    void Request::SendThread(const std::vector<std::string>& receiversEmail,const std::string& subject,const std::string& body)
    {
        CURL* curl;
        CURLcode res = CURLE_OK;
        struct curl_slist* recipients = nullptr;
        stru ctx; // upload context

        std::srand(std::time(0));

        ctx.readed = 0;
        ctx.payload = EmailMsg(receiversEmail, sender.email, "", subject, body); // get email msg

        curl = curl_easy_init();
        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, nullptr);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, nullptr);

            curl_easy_setopt(curl, CURLOPT_USERNAME, sender.email.c_str());
            curl_easy_setopt(curl, CURLOPT_PASSWORD, sender.password.c_str());

            curl_easy_setopt(curl, CURLOPT_URL, smtpAddr.c_str());
            curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

            curl_easy_setopt(curl, CURLOPT_MAIL_FROM, sender.email.c_str());

            for (const auto& email : receiversEmail)
            {
                recipients = curl_slist_append(recipients, email.c_str()); // add all recipients to slist
            }

            curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
            curl_easy_setopt(curl, CURLOPT_READFUNCTION, PayloadSrc);
            curl_easy_setopt(curl, CURLOPT_READDATA, &ctx);
            curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

            curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
            {              
                Utils::DbgMsg("error curl_easy_perform(): %s\n", curl_easy_strerror(res)); // dbg curl err if send fails
            }

            curl_slist_free_all(recipients);
            curl_easy_cleanup(curl);
        }
    }

    static std::unique_ptr<SMTP::Request> req;

    void Request::Send(const std::vector<std::string>& receiversEmail, const std::string& subject, const std::string& body)
    {
        std::thread t(&Request::SendThread, this, receiversEmail, subject, body);
        t.detach(); // run thread independetly
    }

    void NotifyUsers(const Entity::User& sender,const std::string& smtpAddr,const std::string& subject, const std::string& msg)
    {
        std::vector<std::string> lsEmail; // list with all emails
        if (Select::SelectAllUsersEmail(lsEmail) == Error::SUCCESSFUL) // if list with emails is available
        {
            req = std::make_unique<SMTP::Request>(sender, smtpAddr);
            req->Send(lsEmail, subject, msg);
        }
    }
}
