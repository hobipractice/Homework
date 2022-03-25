#pragma once
#include "CoreMinimal.h"
#include <Memory>
#include "../Messages.h"

// 용도 : 
// 분류 :
// 첨언 : 
class ThreadHandlerJoinResultMessage final
{
private: // Member Var
	class UWorld* World_;
	class UClientGameInstance* Inst_;
	std::shared_ptr<JoinResultMessage> JoinResultMessage_;

public: // Default
	ThreadHandlerJoinResultMessage(std::shared_ptr<JoinResultMessage> _JoinMessage);

	// 이 메세지를 처음 받았을때 실행하는 함수
	void Init(UClientGameInstance* _Inst, UWorld* _World);
	void Start();

};

