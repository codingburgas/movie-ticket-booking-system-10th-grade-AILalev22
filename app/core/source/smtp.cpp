#include "pch.h"
#include "smtp.h"

#define FROM_ADDR "<vscpi_otj@mail.bg>"
#define TO_ADDR   "<pazov44@gmail.com>"
#define CC_ADDR   "<info@example.org>" // optional

#define FROM_MAIL "Sender Person " FROM_ADDR
#define TO_MAIL   "A Receiver " TO_ADDR
#define CC_MAIL   "John CC Smith " CC_ADDR

#include <curl/curl.h>
#include <string.h>
#include <stdio.h>

namespace SMTP {
    static const char* payload_text =
        "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n"
        "To: " TO_MAIL "\r\n"
        "From: " FROM_MAIL "\r\n"
        "Cc: " CC_MAIL "\r\n"
        "Message-ID: <example.1234@domain.com>\r\n"
        "Subject: SMTP example message\r\n"
        "\r\n"
        "This is a test message sent via libcurl and SMTP over SSL.\r\n"
        "Cheers!\r\n";

    struct upload_status {
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

    void Request::Send()
    {
        CURL* curl;
        CURLcode res = CURLE_OK;
        struct curl_slist* recipients = NULL;
        upload_status upload_ctx = { 0 };

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_USERNAME, "vscpi_otj@mail.bg");
            curl_easy_setopt(curl, CURLOPT_PASSWORD, "vscpi_otjvscpi_otjvscpi_otj");

            curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.mail.bg:465");
            curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

            curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM_ADDR);

            recipients = curl_slist_append(recipients, TO_ADDR);
            curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

            curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
            curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
            curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }

            curl_slist_free_all(recipients);
            curl_easy_cleanup(curl);
        }
    }
}
