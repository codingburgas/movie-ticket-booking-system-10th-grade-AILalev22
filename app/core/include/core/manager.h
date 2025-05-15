#pragma once

typedef MySQL::Connector CTOR;
typedef SMTP::Request REQ;
namespace Manager
{		
	// connector init data
	struct StruConnector
	{
		std::string host;
		std::string user;
		std::string pass;
		std::string schema;
	};
	// smtp request init data
	struct StruSMTP
	{
		Entity::User sender;
		std::string smtpAddr;
	};

	//general instance manager
	template<class T,class ST>
	class Manager
	{
	protected:
		// managed instance
		std::shared_ptr<T> inst;
		// true if instance is correctly init
		bool isOK;
		// struct with inst data
		ST dataInst;
	public:
		Manager(const ST& data) : isOK(true),dataInst(data)
		{
		}

		// returns manager status
		bool GetStatus()
		{
			return isOK;
		}
		// returns manager instance
		std::shared_ptr<T> GetInstance() { return inst; }
		// init manager func
		virtual void Init() = 0;

		// return init data
		const ST& GetData() { return dataInst; }
	};
	class ManagerSQL : public Manager<CTOR,StruConnector>
	{
	public:
		ManagerSQL(const StruConnector& data) : Manager(data) 
		{
			inst = std::make_shared<CTOR>(dataInst.host, dataInst.user, dataInst.pass);
		}
		void Init();
	};
	class ManagerSMTP : public Manager<REQ, StruSMTP>
	{
	public:
		ManagerSMTP(const StruSMTP& data) : Manager(data) 
		{
			inst = std::make_shared<REQ>(dataInst.sender, dataInst.smtpAddr);
		}
		void Init();
	};

	// get global mysql manager;
	std::shared_ptr<ManagerSQL> GetSQL();
	// get global smtp manager
	std::shared_ptr<ManagerSMTP> GetSMTP();

	// init global managers
	bool Init(const StruConnector& ctorInit, const StruSMTP& smtpInit);
	// release global managers
	void Release();
}