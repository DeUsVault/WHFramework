#pragma once

#include "AbilitySystemComponent.h"
#include "Ability/AbilityModuleTypes.h"
#include "Ability/Attributes/VitalityAttributeSetBase.h"

#include "CharacterAttributeSetBase.generated.h"

/**
 * 角色属性集
 */
UCLASS()
class WHFRAMEWORK_API UCharacterAttributeSetBase : public UVitalityAttributeSetBase
{
	GENERATED_BODY()

public:
	UCharacterAttributeSetBase();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame, ReplicatedUsing = OnRep_MoveSpeed, Category = "CharacterAttributes")
	FGameplayAttributeData MoveSpeed;
	GAMEPLAYATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, MoveSpeed)

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame, ReplicatedUsing = OnRep_RotationSpeed, Category = "CharacterAttributes")
	FGameplayAttributeData RotationSpeed;
	GAMEPLAYATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, RotationSpeed)

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame, ReplicatedUsing = OnRep_JumpForce, Category = "CharacterAttributes")
	FGameplayAttributeData JumpForce;
	GAMEPLAYATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, JumpForce)

public:
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION()
	virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed);

	UFUNCTION()
	virtual void OnRep_RotationSpeed(const FGameplayAttributeData& OldRotationSpeed);

	UFUNCTION()
	virtual void OnRep_JumpForce(const FGameplayAttributeData& OldJumpForce);
};
