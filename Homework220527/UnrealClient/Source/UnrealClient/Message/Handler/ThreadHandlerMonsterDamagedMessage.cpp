#include "ThreadHandlerMonsterDamagedMessage.h"
#include "Kismet/GameplayStatics.h"
#include "../../Global/ClientGameInstance.h"
#include "../../Play/PlayGameMode.h"
#include "../../UnrealClient.h"
#include "../../Play/ClientMonster.h"
#include "../../Global/ClientBlueprintFunctionLibrary.h"
#include "../../Play/ObjectMessageComponent.h"

void ThreadHandlerMonsterDamagedMessage::Start()
{
	APlayGameMode* PGameMode = Cast<APlayGameMode>(UGameplayStatics::GetGameMode(World_));

	if (nullptr == PGameMode
		|| false == PGameMode->IsValidLowLevel())
	{
		UE_LOG(ClientLog, Error, TEXT("%S(%u) > GameMode Is nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	// 프리팹 찾는겁니다.
	// 클라이언트가 다 들고 있을 겁니다.
	TSubclassOf<AClientMonster> Monster = PGameMode->GetMonsterClass(0);

	if (nullptr == Monster
		|| false == Monster->IsValidLowLevel())
	{
		UE_LOG(ClientLog, Error, TEXT("%S(%u) > Monster SubClass Is nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	// 이 몬스터가 존재하지 않아.
	if (false == PGameMode->IsRegist(Message_->DmgObjectIndex))
		return;

	AActor* actor = PGameMode->GetGameObject(Message_->DmgObjectIndex);
	if (actor != nullptr)
	{
		AClientMonster* mon = Cast<AClientMonster>(actor); //Cast 진행

		if (mon != nullptr)
			mon->SetClientDamage(Message_->DamagedValue);
	}

	//PGameMode->ObjectPushMessage(Message_->DmgObjectIndex, Message_);
}
