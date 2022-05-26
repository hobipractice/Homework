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

	// ������ ã�°̴ϴ�.
	// Ŭ���̾�Ʈ�� �� ��� ���� �̴ϴ�.
	TSubclassOf<AClientMonster> Monster = PGameMode->GetMonsterClass(0);

	if (nullptr == Monster
		|| false == Monster->IsValidLowLevel())
	{
		UE_LOG(ClientLog, Error, TEXT("%S(%u) > Monster SubClass Is nullptr"), __FUNCTION__, __LINE__);
		return;
	}

	// �� ���Ͱ� �������� �ʾ�.
	if (false == PGameMode->IsRegist(Message_->DmgObjectIndex))
		return;

	AActor* actor = PGameMode->GetGameObject(Message_->DmgObjectIndex);
	if (actor != nullptr)
	{
		AClientMonster* mon = Cast<AClientMonster>(actor); //Cast ����

		if (mon != nullptr)
			mon->SetClientDamage(Message_->DamagedValue);
	}

	//PGameMode->ObjectPushMessage(Message_->DmgObjectIndex, Message_);
}
