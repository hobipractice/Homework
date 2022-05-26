#pragma once
#include <GameServerCore\ThreadHandlerBase.h>
#include "ClientToServer.h"
#include "ServerAndClient.h"
#include "ServerToClient.h"

// 용도 : 
// 분류 :
// 첨언 : 
class ThreadHandlerPlayerAttackMessage  final : public ThreadHandlerBase<PlayerAttackMessage>
{
private: // Member Var

public: // Default
	ThreadHandlerPlayerAttackMessage();
	~ThreadHandlerPlayerAttackMessage();

	ThreadHandlerPlayerAttackMessage(const ThreadHandlerPlayerAttackMessage& _Other) = delete;
	ThreadHandlerPlayerAttackMessage(ThreadHandlerPlayerAttackMessage&& _Other) noexcept;

protected:
	ThreadHandlerPlayerAttackMessage& operator=(const ThreadHandlerPlayerAttackMessage& _Other) = delete;
	ThreadHandlerPlayerAttackMessage& operator=(ThreadHandlerPlayerAttackMessage&& _Other) = delete;

private:

public: // Member Function
	void Start() override;
};

