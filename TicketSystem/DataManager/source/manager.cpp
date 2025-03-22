#include "pch.h"

static std::unique_ptr<MySQL::Connector> ctor;

namespace Manager
{
	
	MySQL::Connector* GetSQL()
	{
		return ctor.get();
	}
	bool Init(const std::string& host, const std::string& user, const std::string& pass)
	{
		ctor = std::make_unique<MySQL::Connector>(host, user, pass);
		return ctor->Connect();
	}
	bool Release()
	{
		ctor.reset();
		return true;
	}
}