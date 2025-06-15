#include <windows.h>
#include <string>
#include <iostream>
#include <vector>

#include "core\crypt.h"
#include "core\models.h"
#include "core\misc.h"
#include "core\debug.h"
#include "core\utils.h"
#include "core\matrix.h"
#include "core\smtp.h"
#include "core\database.h"
#include "core\manager.h"

#pragma warning(disable : 4996)
void test1()
{
	byte bytes[SALT_BYTES]; //generated random bytes
	std::string hexBytes;

	Crypt::GenRandom(bytes, SALT_BYTES);	
	Crypt::ByteToHex(bytes, SALT_BYTES, hexBytes);

	byte bytes2[SALT_BYTES];
	Crypt::HexToByte(hexBytes, SALT_BYTES, bytes2);

	for (int i = 0; i < SALT_BYTES; i++)
	{
		if (bytes[i] != bytes2[i])
		{
			std::cout << "bytes are not the same";
			break;
		}
	}
}
void test2()
{
	const std::string str = "hello";

	byte salt[SALT_BYTES]; // hash salt
	Crypt::GenRandom(salt, SALT_BYTES);

	std::string hash;
	Crypt::CalcHash(str, 0, 0, hash); // get sha256 hash without salt

	std::cout << "hash : " << hash << std::endl;

	hash.clear();
	Crypt::CalcHash(str, salt, SALT_BYTES, hash); //get sha256 hash with salt

	std::cout << "hash with salt : " << hash;
}
void test3()
{
	const std::string str = "aaahelloaaa";
	std::string tmp = str; //non const temporary

	Utils::Trim(tmp, "aaa", true); // should leave only "aaaaaa"
	std::cout << tmp << std::endl;

	tmp = str;
	Utils::Trim(tmp, "aaa", false); // should leave only "hello"
	std::cout << tmp;
	
}
void test4()
{
	Matrix::Sparse msparse(3, 3, "x"); // 3 by 3 matrix filled with "x"
	
	msparse.Set(2, 0, "v"); // set value at (2,0) to "v"
	msparse.PrintCols();

	std::string val = msparse.Get(2, 0); // get and print value
	std::cout << std::endl << val;
}
void test5()
{
	auto shRequest = Manager::GetSMTP();
	if (shRequest->GetStatus())
	{
		auto shReqestInstance = shRequest->GetInstance();

		shReqestInstance->Send({ "vovovelev@gmail.com" }, "TestEmail", "Message1");
	}
	else
		std::cout << "ManagerSMTP is not ok";
}
void test6()
{
	auto shSql = Manager::GetSQL();
	if (shSql->GetStatus())
	{
		Entity::User testUser = { "test@gmail.com","Pass1234" };
		std::string rnd;
		for (int i = 0; i < 4; i++)
		{
			rnd += std::to_string(rand() % 10);
		}
		testUser.email.insert(4, rnd);

		std::cout << "Log no reg : " << LogUser(testUser) << std::endl; // print whether login without sign up works
		std::cout << "Reg : " << SignUser(testUser) << std::endl;
		std::cout << "Log with reg : " << LogUser(testUser) << std::endl << std::endl; // print whether login with sign up works

		std::cout << "email: " << testUser.email;
	}
	else
		std::cout << "ManagerSQL is not ok";
}
//init managers and set config
void Init();
Manager::StruConnector dataCtor; // data for db connector
Manager::StruRequest dataReq;//data for smtp request

int main()
{
	Init();

	srand(time(0));
	
	test4();
}
void Init()
{
	char* env[] = 
	{
		getenv("hostAZ"),
		getenv("userAZ"),
		getenv("passAZ"),
		getenv("emailSMTP"),
		getenv("passSMTP"),
		getenv("serverSMTP"),
		getenv("schemaAZ")
	};
	dataCtor.host = env[0] ? env[0] : "";
	dataCtor.user = env[1] ? env[1] : "";
	dataCtor.pass = env[2] ? env[2] : "";

	dataReq.sender.email = env[3] ? env[3] : "";
	dataReq.sender.password = env[4] ? env[4] : "";
	dataReq.smtpAddr = env[5] ? env[5] : "";

	dataCtor.schema = env[6] ? env[6] : "";

	Manager::Init(dataCtor, dataReq);
}

