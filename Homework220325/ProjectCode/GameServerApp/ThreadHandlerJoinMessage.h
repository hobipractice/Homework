#pragma once
#include <GameServerNet/TCPSession.h>
#include <GameServerMessage/Messages.h>

class ThreadHandlerJoinMessage final
	: public std::enable_shared_from_this<ThreadHandlerJoinMessage>
{
private: // Member Var
	std::shared_ptr<TCPSession> TCPSession_;

	// �� ��Ŷ
	std::shared_ptr<JoinMessage> JoinMessage_;

	// ó���� ���
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
	// �� �޼����� ó���ϴ� �ܰ�
	void DBCheck();

	// �� �޼����� ó���� �������� ����Ǵ� �Լ�
	void ResultSend();

public: // Member Function
};

