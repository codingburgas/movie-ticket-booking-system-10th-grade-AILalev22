#pragma once

namespace Core
{
	// set global handles and variables, execute startup functions
	bool Init(const std::string& host, const std::string& user, const std::string& pass);
	// free global handles,execute cleanup functions
	bool Release();
}