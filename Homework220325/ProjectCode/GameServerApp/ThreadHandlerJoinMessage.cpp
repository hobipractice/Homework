#include "PreCompile.h"
#include "ThreadHandlerJoinMessage.h"
#include <GameServerBase/GameServerDebug.h>
#include "DBQueue.h"
#include "NetQueue.h"
#include <GameServerBase/GameServerString.h>
#include "GameServerUser.h"
#include <GameServerNet\DBConnecter.h>
#include "UserTable.h"


ThreadHandlerJoinMessage::ThreadHandlerJoinMessage(std::shared_ptr<TCPSession> _TCPSession, std::shared_ptr<JoinMessage> _JoinMessage)
	:TCPSession_(_TCPSession), JoinMessage_(_JoinMessage)
{

}

ThreadHandlerJoinMessage::~ThreadHandlerJoinMessage()
{

}


void ThreadHandlerJoinMessage::Start()
{
	if (nullptr == TCPSession_)
	{
		GameServerDebug::LogError("Login TCPSession Error");
	}
	// Monster나 이런데에다가 넣어줄것이다.


	// 1	A	A
	// 2	B	B
	// 정보를 가지고

	std::string Name = GameServerThread::GetName();

	// TestClass* Test = GameServerThread::GetLocalData<TestClass>();

	JoinResult_.Code = EGameServerCode::JoinError;
	DBQueue::Queue(std::bind(&ThreadHandlerJoinMessage::DBCheck, shared_from_this()));
}



void ThreadHandlerJoinMessage::DBCheck()
{
	std::string Name = GameServerThread::GetName();

	UserTable_SelectIDToUserInfo SelectQuery(JoinMessage_->ID);
	SelectQuery.DoQuery();

	if (nullptr == SelectQuery.RowData)
	{
		// 없으니까 만들어주자
		JoinResult_.Code = EGameServerCode::OK;

		UserTable_InsertUserInfo Query = UserTable_InsertUserInfo(JoinMessage_->ID, JoinMessage_->PW);
		if (false == Query.DoQuery())
		{
			//  쿼리에 문제가 생겼다면 Error
			JoinResult_.Code = EGameServerCode::JoinError;
			GameServerDebug::LogInfo("Join Fail : create ID.");
		}
		else
		{
			GameServerDebug::LogInfo("Join Success!! : " + JoinMessage_->ID);
		}
	}
	else
	{
		JoinResult_.Code = EGameServerCode::JoinError;
		GameServerDebug::LogInfo("Join Fail : Duplicate ID.");

	}

	// INSERT INTO `userver2`.`user` (`ID`, `PW`) VALUES('c', 'c');
	NetQueue::Queue(std::bind(&ThreadHandlerJoinMessage::ResultSend, shared_from_this()));

}

void ThreadHandlerJoinMessage::ResultSend()
{
	std::shared_ptr<GameServerUser> NewUser = std::make_shared<GameServerUser>();
	GameServerString::UTF8ToAnsi(JoinMessage_->ID, NewUser->ID);

	// [TODO] 어떤 용도 인지 확인 필요
	TCPSession_->SetLink(NewUser);

	GameServerSerializer Sr;
	JoinResult_.Serialize(Sr);
	TCPSession_->Send(Sr.GetData());

	GameServerDebug::LogInfo("Join Result Out");
}

