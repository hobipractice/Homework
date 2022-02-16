#include <iostream>
#include <regex>
#include <string>

using namespace std;

class GameServerString
{
public:
	//                 "오늘은 정말 힘들었다"                  "오늘은"          "어제는"
	static void Replace(std::string& _Text, const std::string& _Prev, const std::string& _Next, int _Count = 1);

	// "ffasdfsdafdas" "cccc"
	static void Insert(std::string& _Text, int _Index, const std::string& _InsertText);

	// ReMove
	static void Remove(std::string& _Text, const std::string& _DeleteText);

	// ' '
	static void TrimRemove(std::string& _Text);

	// 한글이 섞여있어도.
	static void ToUpper(std::string& _Text);

};


int main()
{
	string str1 = "오늘은 정말 힘들었다 오늘은 아니다 어제는 오늘은";
	GameServerString::Replace(str1, "오늘은", "어제는");
	cout << str1 << endl;

	string str2 = "ffasdfsdafdas";
	GameServerString::Insert(str2, 2, "cccc");
	cout << str2 << endl;

	string str3 = "ffasdfsdafdas";
	GameServerString::Remove(str3, "f");
	cout << str3 << endl;


	string str4 = "ff asd    fsd af das";
	GameServerString::TrimRemove(str4);
	cout << str4 << endl;

	string str5 = "ff asd    fsd af das";
	GameServerString::ToUpper(str5);
	cout << str5 << endl;

}

void GameServerString::Replace(std::string& _Text, const std::string& _Prev, const std::string& _Next, int _Count)
{
	_Text = regex_replace(_Text, regex(_Prev), _Next);
	//int answer = 0;
	//size_t found; 
	//while ((found = _Text.find(_Prev)) != string::npos)
	//{ 
	//	answer++;
	//	/*if (_Count < answer)
	//		break;*/
	//	_Text = _Text.substr(found + 1); 
	//}

	//int a = 0;

}

void GameServerString::Insert(std::string& _Text, int _Index, const std::string& _InsertText)
{
	if (_Text.size() < _Index)
		return;

	_Text.insert(_Index, _InsertText);
}

void GameServerString::Remove(std::string& _Text, const std::string& _DeleteText)
{
	_Text = regex_replace(_Text, regex(_DeleteText), "");
}

void GameServerString::TrimRemove(std::string& _Text)
{
	_Text = regex_replace(_Text, regex(" "), "");
}

void GameServerString::ToUpper(std::string& _Text)
{
	for (int i = 0; i < _Text.size(); i++)
	{
		_Text[i] = toupper(_Text[i]);
	}
}
