#pragma once

namespace Utils
{
	// exit with err msg as quiting
	void Exit();
	// show err message
	void ErrMsg(const std::string& msg,int sec = 0);
	// clear cmd command
	void Clear();
}