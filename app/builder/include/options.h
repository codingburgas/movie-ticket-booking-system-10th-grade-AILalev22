#pragma once

namespace Options
{
	// authentication option
	int LogSign(int mode,const std::string& adminEmail);
	// insert movie admin option
	void InsertMovie();
	// delete movie admin option
	void DeleteMovie();
	// insert show admin option
	void InsertShow();
	// delete show admin option
	void DeleteShow();
	// update show admin option
	void UpdateShow();
}