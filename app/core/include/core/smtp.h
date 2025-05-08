#pragma once

namespace SMTP
{
	class Request
	{
		// smtp server address
		std::string server;
		// sender email and pass
		Entity::User sender;
	public:
		void SetSender(const std::string& email, const std::string& password);
		void SetServer(const std::string& serverAddr);
		void Send(const std::string& receiverEmail, const std::string& subject, const std::string& body);

		Request(const std::string& emailSender, const std::string& passwordSender, const std::string& serverAddr);
		Request() = default;
	};
}