#pragma once

namespace Core
{
	// set global handles and variables, execute startup functions
	bool Init();
	// free global handles,execute cleanup functions
	bool Release();
}