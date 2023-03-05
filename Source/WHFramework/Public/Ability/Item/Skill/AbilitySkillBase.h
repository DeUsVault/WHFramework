// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ability/Item/AbilityItemBase.h"
#include "../../Interfaces/AbilityAttackerInterface.h"
#include "AbilitySkillBase.generated.h"

/**
 * 技能基类
 */
UCLASS()
class WHFRAMEWORK_API AAbilitySkillBase : public AAbilityItemBase, public IAbilityAttackerInterface
{
	GENERATED_BODY()
	
public:	
	AAbilitySkillBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")
	FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")
	float DurationTime;

	UPROPERTY()
	TArray<AActor*> HitTargets;

private:
	FTimerHandle DestroyTimer;

protected:
	virtual int32 GetLimit_Implementation() const override { return 1000; }

	virtual void OnSpawn_Implementation(const TArray<FParameter>& InParams) override;

	virtual void OnDespawn_Implementation(bool bRecovery) override;
	
public:
	virtual void Initialize_Implementation(AAbilityCharacterBase* InOwnerCharacter, const FAbilityItem& InItem = FAbilityItem::Empty) override;
	
public:
	virtual bool CanHitTarget_Implementation(AActor* InTarget) override;

	virtual void OnHitTarget_Implementation(AActor* InTarget, const FHitResult& InHitResult) override;
	
	virtual void ClearHitTargets_Implementation();

	virtual void SetHitAble_Implementation(bool bValue);
};
