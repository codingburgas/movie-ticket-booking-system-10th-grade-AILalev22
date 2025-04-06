#pragma once

namespace Present
{
	// execute startup functions
	bool Init(const std::string& host, const std::string& user, const std::string& pass);
	// execute release functions
	bool Release();
}