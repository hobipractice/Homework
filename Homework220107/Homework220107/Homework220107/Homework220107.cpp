// Homework220107.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <regex>
#include <vector>

// 문자열 분리
std::vector<std::string> split(std::string s, std::string pattern = " ")
{
	std::regex re(pattern);
	std::sregex_token_iterator it(s.begin(), s.end(), re, -1), end;
	return std::vector<std::string>(it, end);
}

int main()
{
	std::regex regexIP("(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])");
	std::regex regexIPwithPort("(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5]):[0-9]+");

	std::string Ip;
	int Port = -1;
	while (true)
	{
		std::cout << "IP주소를 입력해주세요" << std::endl;

		// space 받기 위해 getline 사용
		std::getline(std::cin >> std::ws, Ip);

		if ("Q" == Ip || "q" == Ip)
			Ip = "127.0.0.1";

		// 공백 예외처리
		Ip.erase(std::remove_if(Ip.begin(), Ip.end(), isspace), Ip.end());

		if (std::regex_match(Ip, regexIPwithPort)) // IP와 Port 포함 입력시
		{
			std::vector<std::string> splitStr = split(Ip, ":");
			// IP / Port 추출
			if (splitStr.size() == 2)
			{
				Ip = splitStr[0];
				Port = std::stoi(splitStr[1]);

				break;
			}
		}
		else if (std::regex_match(Ip, regexIP)) // IP만 입력시
		{
			std::cout << "Port를 입력해주세요" << std::endl;
			std::cin >> Port;

			break;
		}

		std::cout << "Ip 주소가 잘못되었습니다." << std::endl;
	}

	std::cout << "입력이 완료 되었습니다." << std::endl;
	std::cout << "IP : " << Ip << " PORT : "<< Port << std::endl;

}

