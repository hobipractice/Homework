#pragma once
#include "CoreMinimal.h"
#include <Memory>
#include "../Messages.h"

// �뵵 : 
// �з� :
// ÷�� : 
class ThreadHandlerJoinResultMessage final
{
private: // Member Var
	class UWorld* World_;
	class UClientGameInstance* Inst_;
	std::shared_ptr<JoinResultMessage> JoinResultMessage_;

public: // Default
	ThreadHandlerJoinResultMessage(std::shared_ptr<JoinResultMessage> _JoinMessage);

	// �� �޼����� ó�� �޾����� �����ϴ� �Լ�
	void Init(UClientGameInstance* _Inst, UWorld* _World);
	void Start();

};

