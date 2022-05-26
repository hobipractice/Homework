// Fill out your copyright notice in the Description page of Project Settings.

#include "ClientPlayCharacter.h"
#include "ClientAnimInstance.h"
#include "../UnrealClient.h"
#include <chrono>
#include "../Message/ClientToServer.h"
#include "../Message/ServerToClient.h"
#include "../Message/ServerAndClient.h"
#include "../Global/ClientGameInstance.h"


UClientAnimInstance::UClientAnimInstance() 
	: Animations_(nullptr)
{

}

void UClientAnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	if (nullptr == Animations_) 
	{
		return;
	}

	Super::NativeUpdateAnimation(_DeltaTime);

	if (false == (*Animations_).Contains(CurrentAnimationType_))
	{
		return;
	}

	UAnimMontage* FindAnimation = (* Animations_)[CurrentAnimationType_];

	if (nullptr == FindAnimation)
	{
		UE_LOG(ClientLog, Error, TEXT("%S(%u) > Animation Is Null"), __FUNCTION__, __LINE__);
	}


	if (true == Montage_IsPlaying(FindAnimation))
	{
		return;
	}

	if (0 != StartFunctions_.size())
	{

		for (auto& Function : StartFunctions_)
		{
			Function(CurrentAnimationType_);
		}
	}


	Montage_Play(FindAnimation);
}

void UClientAnimInstance::ChangeAnimation(ClientAnimationType _Type) 
{
	if (CurrentAnimationType_ == _Type)
	{
		return;
	}

	CurrentAnimationType_ = _Type;
}

void UClientAnimInstance::AnimNotify_End()
{
	if (0 == EndFunctions_.size())
	{
		return;
	}

	for (auto& Function : EndFunctions_)
	{
		Function(CurrentAnimationType_);
	}

	// CurrentAnimationType_ = ClientAnimationType::Idle;
}

void UClientAnimInstance::AnimNotify_Anim_Attack()
{
	APawn* p = TryGetPawnOwner();

	AClientPlayCharacter* clientCharacter = Cast<AClientPlayCharacter>(p);
	if (clientCharacter == nullptr)
		return;

	// 자기 자신이어야만,
	UClientGameInstance* Inst = Cast<UClientGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (nullptr == Inst || false == Inst->IsValidLowLevel())
	{
		return;
	}

	PlayerAttackMessage Msg;

	Msg.Datas.Dir = clientCharacter->GetActorForwardVector();
	Msg.Datas.Pos = clientCharacter->GetActorLocation();
	FQuat RotData = clientCharacter->GetActorQuat();
	Msg.Datas.Rot = FVector4(RotData.X, RotData.Y, RotData.Z, RotData.W);
	Msg.Datas.ObjectIndex = Inst->ObjectIndex;
	Msg.Datas.SectionIndex = Inst->SectionIndex;
	Msg.Datas.ThreadIndex = Inst->ThreadIndex;
	Msg.Datas.SetState(clientCharacter->GetClientAnimInstance()->GetAnimationType());

	auto now = std::chrono::system_clock::now();
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
	auto value = now_ms.time_since_epoch();
	int duration = 500;
	Msg.DurationTimeMs = value.count() + duration;

	GameServerSerializer Sr;

	Msg.Serialize(Sr);
	if (false == Inst->Send(Sr.GetData()))
	{
		int a = 0;
	}
}

void UClientAnimInstance::AddEndFunctionBind(std::function<void(ClientAnimationType)> _BindFunction)
{
	EndFunctions_.push_back(_BindFunction);
}

void UClientAnimInstance::AddStartFunctionBind(std::function<void(ClientAnimationType)> _BindFunction) 
{
	StartFunctions_.push_back(_BindFunction);
}