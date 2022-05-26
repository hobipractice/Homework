#pragma once
#include <GameServerBase\GameServerMath.h>
#include "GameServerActor.h"
#include <DirectXCollision.h>
#include <DirectXCollision.inl>
#include <chrono>

enum CollisionCheckType
{
	SPHERE, // ���浹
	AABB, // ȸ������ �ʴ� �ڽ�
	OBB, // ȸ���ϴ� �ڽ� (���� �� 40�� ���� ���̴�)
	MAX,
};

enum CollisionType
{
	NORMAL,
	DAMAGE,
};

class CollisionData 
{
public:
	union 
	{
		// ũ���� x�� ���Ǿ��� �������� �ȴ�.
		DirectX::BoundingSphere Sphere;
		DirectX::BoundingBox AABB;
		DirectX::BoundingOrientedBox OBB;
	};

	CollisionData() 
	{

	}
};

// ���� :
// �ݸ����� ����� �ִ� �༮�� ������ �翬�� ���� ���̰�
class GameServerCollision : public GameServerObjectBase
{
	friend class GameServerActor;
	friend class GameServerSection;

public:
	static bool CollisionCheck(GameServerCollision* _Left, CollisionCheckType _LeftType, GameServerCollision* _Right, CollisionCheckType _RightType);

	static std::function<bool(GameServerCollision*, GameServerCollision*)> CollisionCheckFunction[static_cast<int>(CollisionCheckType::MAX)][static_cast<int>(CollisionCheckType::MAX)];

	static bool SphereToSphere(GameServerCollision* _Left, GameServerCollision* _Right);

public:
	// constrcuter destructer
	GameServerCollision();
	~GameServerCollision();

	// delete Function
	GameServerCollision(const GameServerCollision& _Other) = delete;
	GameServerCollision(GameServerCollision&& _Other) noexcept = delete;
	GameServerCollision& operator=(const GameServerCollision& _Other) = delete;
	GameServerCollision& operator=(GameServerCollision&& _Other) noexcept = delete;

	GameServerSection* GetOwnerSection()
	{
		return OwnerSection;
	}

	GameServerActor* GetOwnerActor()
	{
		return OwnerActor;
	}

	template<typename OwnerType>
	OwnerType* GetOwnerActorConvert()
	{
		return dynamic_cast<OwnerType*>(OwnerActor);
	}


	FVector4 GetScale() 
	{
		return Scale;
	}

	FVector4 GetPivot() 
	{
		return Pivot;
	}

	void SetScale(const FVector4& _Value)
	{
		Scale = _Value;
	}

	void SetPivot(const FVector4& _Value)
	{
		Pivot = _Value;
	}

	void SetGroupIndex(int _Index)
	{
		Index_ = _Index;
	}

	void SetUse(bool _IsUse)
	{
		IsUse_ = _IsUse;
	}

	bool IsUsed()
	{
		return IsUse_;
	}

	void SetDurationTime(uint64_t _duration)
	{
		std::chrono::milliseconds dur(_duration);
		dt = std::chrono::time_point<std::chrono::system_clock>(dur);
		
		durationTime_ = _duration;
	}


	template<typename EnumType>
	bool CollisionCheck(CollisionCheckType _ThisType, EnumType _Order, CollisionCheckType _OtherType)
	{
		return CollisionCheck(_ThisType, static_cast<int>(_Order), _OtherType);
	}

	bool CollisionCheck(CollisionCheckType _ThisType, int _Order, CollisionCheckType _OtherType);


	template<typename EnumType>
	bool CollisionCheckResult(CollisionCheckType _ThisType, EnumType _Order
		, CollisionCheckType _OtherType, std::vector<GameServerCollision*>& _HitResults)
	{
		return CollisionCheckResult(
			_ThisType, static_cast<int>(_Order)
			, _OtherType, _HitResults
		);
	}

	bool CollisionCheckResult(CollisionCheckType _ThisType, int _Order
		, CollisionCheckType _OtherType, std::vector<GameServerCollision*>& _HitResults);

	void CollisionDataUpdate();

	void Death() override;


protected:

private:
	GameServerSection* OwnerSection;
	GameServerActor* OwnerActor;
	FVector4 Scale;
	FVector4 Pivot;

	// �Ⱦ��� ������ �׳� ���ø� ���ٲ���.
	FVector4 Rot;
	int Index_;

	CollisionData CollisionData_;
	uint64_t durationTime_;

	std::atomic<bool> IsUse_;
	std::chrono::time_point<std::chrono::system_clock> dt;


	inline void SetSection(GameServerSection* _OwnerSection)
	{
		OwnerSection = _OwnerSection;
	}

	inline void SetActor(GameServerActor* _Actor) 
	{
		OwnerActor = _Actor;
	}
};

