#pragma once

namespace Utils
{
	// exit with err msg as quiting
	void Exit();
	// show err message
	void ErrMsg(const std::string& msg,int sec = 0);
	// clear cmd command
	void Clear();
	// trim src bassed on chars string
	// if possible is true only matching characters are left
	// is possible is false characters found in chars string are removed
	void Trim(std::string& src, const std::string& chars,bool possible = true);
}