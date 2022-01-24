// GameClientApp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <thread>
#include <vector>
#include <mutex>
#include <conio.h>
#include <functional>
#include <assert.h>

#include <WinSock2.h>
#include <Windows.h> // 아래쪽에 놔야 합니다.
#include <WS2tcpip.h> // inet_pton 함수를 사용하기 위한 헤더
#include <thread>
#include <memory>
#include <vector>
#include <mutex>

#pragma comment (lib, "ws2_32") // 서버통신용 구현이 들어있는 라이브러리

#include <iostream>

#include <string>
std::mutex Lock;

std::thread RecvThread;

bool Check = true;

std::string str;

bool End = false;
void RecvFunc(SOCKET _SessionSocket)
{

	while (Check)
	{
		char Buffer[1024];

		int Result = recv(_SessionSocket, Buffer, sizeof(Buffer), 0);

		if (SOCKET_ERROR == Result)
		{
			return;
		}

		if (End == true)
			continue;

		int len = sizeof(Buffer) / sizeof(Buffer[0]);

		for (int i = 0; i < len; i++)
		{
			//std::cout << Buffer[i] << std::endl;

			if (Buffer[i] == '\0')
				break;

			if (Buffer[i] == '!')
			{
				End = true;
				std::cout << "문제획득!!" << std::endl;
			}


			str.append(1, Buffer[i]);
		}

	}

}

int main()
{
	WSADATA wsa;

	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		std::cout << "WSAStartup Error" << std::endl;
	}

	SOCKET SessionSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == SessionSocket)
	{
		return 0;
	}

	std::cout << "IP주소를 입력해주세요" << std::endl;
	std::string Ip;
	std::string Port;
	std::cin >> Ip;

	if ("Q" == Ip
		|| "q" == Ip)
	{
		Ip = "127.0.0.1";
	}
	else if ("w" == Ip
		|| "W" == Ip)
	{
		Ip = "58.150.30.210";
	}

	SOCKADDR_IN Add = { 0, };
	Add.sin_family = AF_INET;
	Add.sin_port = htons(30001);
	if (SOCKET_ERROR == inet_pton(AF_INET, Ip.c_str(), &Add.sin_addr))
	{
		return 0;
	}
	int Len = sizeof(SOCKADDR_IN);

	if (SOCKET_ERROR == connect(SessionSocket, (const sockaddr*)&Add, Len))
	{
		std::cout << "연결이 종료되었습니다." << std::endl;

		return 0;
	}

	std::cout << "커넥트 성공." << std::endl;

	std::cout << "문제 받는중.." << std::endl;

	RecvThread = std::thread(RecvFunc, SessionSocket);

	//int Result = send(SessionSocket, Buffer, sizeof(Buffer), 0);

	while (true)
	{
		std::string In;

		// Lock.lock();

		std::cin >> In;

		if (In == "q" || In == "Q")
		{
			//TCP면 포핸드 쉐이크를 다 깔끔하게 맞춰줍니다.
			closesocket(SessionSocket);
			Check = false;
			RecvThread.join();
			Sleep(1);
			return 0;
		}

		if (In == "a" || In == "A")
		{
			std::cout << str << std::endl;

			std::string Answer;
			std::cin >> Answer;

			char Buffer[1024] = {};
			//char Buffer[1024] = { "작업자:TCP" };
			memcpy_s(Buffer, sizeof(Buffer), Answer.c_str(), Answer.size());
			int Result = send(SessionSocket, Buffer, sizeof(Buffer), 0);
		}

		Sleep(1);
	}
	_getch();
}
