#pragma once

enum class MessageId 
{
	Login,
	CreateCharacter,
	SelectCharacter,
	ClientToReady,
	UDPConnectResult,
	LevelMoveReply,
	RankRequest,
	PlayerAttack,
	LoginResult,
	CharacterCreateResult,
	CharacterSelectResult,
	LevelMove,
	UDPReadyOK,
	SectionInsertResult,
	ServerDestroy,
	PlayerDestroy,
	ObjectDestroy,
	CharacterList,
	PlayersUpdate,
	MonsterUpdate,
	UserRankWindowData,
	MonsterDamaged,
	Chat,
	PlayerUpdate,
	MAX
};