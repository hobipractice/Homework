#include "PreCompile.h"
#include "ThreadHandlerPlayerAttackMessage.h"
#include "Windows.h"
#include <chrono>
#include <iostream>

ThreadHandlerPlayerAttackMessage::ThreadHandlerPlayerAttackMessage() 
{

}

ThreadHandlerPlayerAttackMessage::~ThreadHandlerPlayerAttackMessage() 
{

}

ThreadHandlerPlayerAttackMessage::ThreadHandlerPlayerAttackMessage(ThreadHandlerPlayerAttackMessage&& _Other) noexcept
{

}

void ThreadHandlerPlayerAttackMessage::Start()
{
	GameServerDebug::LogInfo("PlayerAttackMessage");

	if (nullptr == Session_)
		GameServerDebug::LogError("TCPSession Error");

	// ����ð�
	auto now = std::chrono::system_clock::now();
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);

	auto value = now_ms.time_since_epoch();
	uint64_t duration = value.count();

	std::cout <<  "duration : " << duration << std::endl;
	std::cout << "Message_->DurationTimeMs :" << Message_->DurationTimeMs << std::endl;

	// �޾ƺ� �ð�
	std::chrono::milliseconds dur(Message_->DurationTimeMs);
	std::chrono::time_point<std::chrono::system_clock> dt(dur);

	if (dt > now)
	{
		GameServerDebug::LogInfo("�����ص� �ǰڳ�");

		ActorWork(Message_->Datas.ThreadIndex, Message_->Datas.SectionIndex, Message_->Datas.ObjectIndex, Message_);
	}
	else
	{
		GameServerDebug::LogInfo("���� ���ϰڱ���...");
	}

}

