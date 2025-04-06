// Builder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <memory>
#include "database.h"
#include "user.h"
#include "process.h"
#include "manager.h"
#include "error.h"
#include "auth.h"
int main()
{
     MySQL::Init("tcp://127.0.0.1:3306", "root", "root1234!!??");
    auto sql = MySQL::GetSQL();
  sql->SetDB("dataticket");

    std::cout << Auth::SignUser({ "yahoo1@gmail.com","pass12345" });
    MySQL::Release();
}


