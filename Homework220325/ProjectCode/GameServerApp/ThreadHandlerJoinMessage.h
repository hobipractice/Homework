#pragma once
#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>

class ThreadHandlerJoinMessage final
	: public std::enable_shared_from_this<ThreadHandlerJoinMessage>
{
private: // Member Var
	std::shared_ptr<TCPSession> TCPSession_;

	// 온 패킷
	std::shared_ptr<JoinMessage> JoinMessage_;

	// 처리한 결과
	JoinResultMessage JoinResult_;

public: // Default
	ThreadHandlerJoinMessage(std::shared_ptr<TCPSession> _TCPSession, std::shared_ptr<JoinMessage> _JoinMessage);
	~ThreadHandlerJoinMessage();

	ThreadHandlerJoinMessage(const ThreadHandlerJoinMessage& _Other) = delete;
	ThreadHandlerJoinMessage(ThreadHandlerJoinMessage&& _Other) noexcept = delete;

	void Start();

protected:
	ThreadHandlerJoinMessage& operator=(const ThreadHandlerJoinMessage& _Other) = delete;
	ThreadHandlerJoinMessage& operator=(ThreadHandlerJoinMessage&& _Other) = delete;

private:
	// 이 메세지를 처리하는 단계
	void DBCheck();

	// 이 메세지가 처리가 끝났을때 실행되는 함수
	void ResultSend();

public: // Member Function
};

