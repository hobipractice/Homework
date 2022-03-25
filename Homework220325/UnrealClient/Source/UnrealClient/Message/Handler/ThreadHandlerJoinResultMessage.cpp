#include "ThreadHandlerJoinResultMessage.h"
#include "../../Global/ClientGameInstance.h"
#include "Kismet/GameplayStatics.h"

ThreadHandlerJoinResultMessage::ThreadHandlerJoinResultMessage(std::shared_ptr<JoinResultMessage> _JoinMessage)
	: JoinResultMessage_(_JoinMessage)
{

}

void ThreadHandlerJoinResultMessage::Init(UClientGameInstance* _Inst, UWorld* _World)
{
	Inst_ = _Inst;
	World_ = _World;
}

void ThreadHandlerJoinResultMessage::Start()
{
	if (EGameServerCode::OK == JoinResultMessage_->Code)
	{
		// ȸ������
		UE_LOG(LogTemp, Warning, TEXT("Join Success"));
	}
	else
	{
		// ȸ������ ����
		UE_LOG(LogTemp, Error, TEXT("Join Fail"));
	}
}

