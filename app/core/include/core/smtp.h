#pragma once

namespace SMTP
{
	class Request
	{
		// smtp server address
		std::string smtpAddr;
		// sender email and pass
		Entity::User sender;
	public:
		// set smtp sender email and app passsword
		void SetSender(const Entity::User& sender);
		// set smtp server address
		void SetServer(const std::string& smtpAddr);
		// send email to all receivers
		void Send(const std::vector<std::string>& receiversEmail, const std::string& subject, const std::string& body) const;
		void SendAsync(const std::vector<std::string>& receiversEmail, const std::string& subject, const std::string& body) const;	

		Request(const Entity::User& sender, const std::string& smtpAddr);
		Request() = default;
	};

	// send a msg to all users if emailList is empty, else to a group of users
	void NotifyUsers(const std::string& subject, const std::string& msg, std::vector<std::string> emailList ={});
}