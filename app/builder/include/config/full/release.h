#pragma once

// total halls in each cinema
#define HALLS 4

// total cinemas
#define CINEMAS 2

// row size in each hall
#define ROW_SIZE 16
// col size in each hall
#define COL_SIZE 10

// admin username for app
#define DB_ADMIN_EMAIL "admin1234@gmail.com"

// app database name
#define DB_NAME "dataticket"

// env variables names for db credentials
#define DB_USER_ENV "userAZ"
#define DB_PASS_ENV "passAZ"
#define DB_HOST_ENV "hostAZ"

// env mail.bg credentials used for smtp
#define SMTP_EMAIL_ENV "emailMBG"
#define SMTP_PASS_ENV "passMBG"

// app smtp server
#define SMTP_SERVER "smtps://smtp.mail.bg:465"