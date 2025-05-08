#pragma once

namespace SMTP
{
	class Request
	{
		// smtp server address
		std::string server;
		// sender email and pass
		Entity::User sender;
		void SendThread(const std::string& receiverEmail, const std::string& subject, const std::string& body);
	public:
		// set smtp sender email and app passsword
		void SetSender(const std::string& email, const std::string& password);
		// set smtp server address
		void SetServer(const std::string& serverAddr);
		// send email using sendthread
		void Send(const std::string& receiverEmail, const std::string& subject, const std::string& body);

		Request(const std::string& emailSender, const std::string& passwordSender, const std::string& serverAddr);
		Request() = default;
	};
}