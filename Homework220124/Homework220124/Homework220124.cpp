// GameClientApp.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//
#include <thread>
#include <vector>
#include <mutex>
#include <conio.h>
#include <functional>
#include <assert.h>

#include <WinSock2.h>
#include <Windows.h> // �Ʒ��ʿ� ���� �մϴ�.
#include <WS2tcpip.h> // inet_pton �Լ��� ����ϱ� ���� ���
#include <thread>
#include <memory>
#include <vector>
#include <mutex>

#pragma comment (lib, "ws2_32") // ������ſ� ������ ����ִ� ���̺귯��

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
				std::cout << "����ȹ��!!" << std::endl;
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

	std::cout << "IP�ּҸ� �Է����ּ���" << std::endl;
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
		std::cout << "������ ����Ǿ����ϴ�." << std::endl;

		return 0;
	}

	std::cout << "Ŀ��Ʈ ����." << std::endl;

	std::cout << "���� �޴���.." << std::endl;

	RecvThread = std::thread(RecvFunc, SessionSocket);

	//int Result = send(SessionSocket, Buffer, sizeof(Buffer), 0);

	while (true)
	{
		std::string In;

		// Lock.lock();

		std::cin >> In;

		if (In == "q" || In == "Q")
		{
			//TCP�� ���ڵ� ����ũ�� �� ����ϰ� �����ݴϴ�.
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
			//char Buffer[1024] = { "�۾���:TCP" };
			memcpy_s(Buffer, sizeof(Buffer), Answer.c_str(), Answer.size());
			int Result = send(SessionSocket, Buffer, sizeof(Buffer), 0);
		}

		Sleep(1);
	}
	_getch();
}
