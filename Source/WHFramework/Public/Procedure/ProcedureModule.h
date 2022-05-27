// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ProcedureModuleTypes.h"
#include "Base/ProcedureBase.h"
#include "Main/Base/ModuleBase.h"

#include "ProcedureModule.generated.h"

class UProcedureBase;

/**
 * 
 */
UCLASS()
class WHFRAMEWORK_API AProcedureModule : public AModuleBase
{
	GENERATED_BODY()

public:
	// ParamSets default values for this actor's properties
	AProcedureModule();

	//////////////////////////////////////////////////////////////////////////
	/// Module
public:
	#if WITH_EDITOR
	virtual void OnGenerate_Implementation() override;

	virtual void OnDestroy_Implementation() override;
	#endif

	virtual void OnInitialize_Implementation() override;

	virtual void OnPreparatory_Implementation() override;

	virtual void OnRefresh_Implementation(float DeltaSeconds) override;

	virtual void OnPause_Implementation() override;

	virtual void OnUnPause_Implementation() override;

	virtual void OnTermination_Implementation() override;

	//////////////////////////////////////////////////////////////////////////
	/// ProcedureModule
protected:
	/// 自动切换流程 
	UPROPERTY(EditAnywhere, Category = "ProcedureModule")
	bool bAutoSwitch;

public:
	UFUNCTION(BlueprintCallable)
	void SwitchProcedure(UProcedureBase* InProcedure);

	UFUNCTION(BlueprintCallable)
	void SwitchProcedureByIndex(int32 InProcedureIndex);

	template<class T>
	void SwitchProcedureByClass(TSubclassOf<UProcedureBase> InProcedureClass = T::StaticClass())
	{
		SwitchProcedureByClass(InProcedureClass);
	}

	UFUNCTION(BlueprintCallable)
	void SwitchProcedureByClass(TSubclassOf<UProcedureBase> InProcedureClass);

	UFUNCTION(BlueprintCallable)
	void SwitchFirstProcedure();

	UFUNCTION(BlueprintCallable)
	void SwitchLastProcedure();

	UFUNCTION(BlueprintCallable)
	void SwitchNextProcedure();

	UFUNCTION(BlueprintCallable)
	void GuideCurrentProcedure();

	UFUNCTION(BlueprintCallable)
	void ClearAllProcedure();

	//////////////////////////////////////////////////////////////////////////
	/// Procedure Stats
protected:
	/// 初始流程 
	UPROPERTY(VisibleAnywhere, Category = "ProcedureModule|Procedure Stats")
	UProcedureBase* FirstProcedure;
	/// 当前流程 
	UPROPERTY(VisibleAnywhere, Transient, Category = "ProcedureModule|Procedure Stats")
	UProcedureBase* CurrentProcedure;
	/// 流程列表
	UPROPERTY(VisibleAnywhere, Category = "ProcedureModule|Procedure Stats")
	TArray<UProcedureBase*> Procedures;
	UPROPERTY()
	TMap<TSubclassOf<UProcedureBase>, UProcedureBase*> ProcedureMap;

public:
	UFUNCTION(BlueprintPure)
	bool HasProcedureByIndex(int32 InProcedureIndex) const
	{
		if(!InProcedureIndex) return false;

		return Procedures.IsValidIndex(InProcedureIndex);
	}

	template<class T>
	T* GetProcedureByIndex(int32 InProcedureIndex) const
	{
		if(!InProcedureIndex) return nullptr;

		if(HasProcedureByIndex(InProcedureIndex))
		{
			return Cast<T>(Procedures[InProcedureIndex]);
		}
		return nullptr;
	}
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetProcedureByIndex", DeterminesOutputType = "InProcedureIndex"))
	UProcedureBase* K2_GetProcedureByIndex(int32 InProcedureIndex, TSubclassOf<UProcedureBase> InProcedureClass) const;
	
	template<class T>
	bool HasProcedureByClass(TSubclassOf<UProcedureBase> InProcedureClass = T::StaticClass()) const
	{
		if(!InProcedureClass) return false;

		return ProcedureMap.Contains(InProcedureClass);
	}
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "HasProcedureByClass"))
	bool K2_HasProcedureByClass(TSubclassOf<UProcedureBase> InProcedureClass) const;

	template<class T>
	T* GetProcedureByClass(TSubclassOf<UProcedureBase> InProcedureClass = T::StaticClass()) const
	{
		if(!InProcedureClass) return nullptr;

		if(HasProcedureByClass<T>(InProcedureClass))
		{
			return Cast<T>(ProcedureMap[InProcedureClass]);
		}
		return nullptr;
	}
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "GetProcedureByClass", DeterminesOutputType = "InProcedureClass"))
	UProcedureBase* K2_GetProcedureByClass(TSubclassOf<UProcedureBase> InProcedureClass) const;

public:
	/**
	* 获取初始流程
	*/
	UFUNCTION(BlueprintPure)
	UProcedureBase* GetFirstProcedure() const { return FirstProcedure; }
	/**
	* 设置初始流程
	*/
	UFUNCTION(BlueprintCallable)
	void SetFirstProcedure(UProcedureBase* InFirstProcedure) { this->FirstProcedure = InFirstProcedure; }
	/**
	* 获取当前流程
	*/
	UFUNCTION(BlueprintPure)
	UProcedureBase* GetCurrentProcedure() const { return CurrentProcedure; }
	/**
	* 获取流程列表
	*/
	UFUNCTION(BlueprintPure)
	TArray<UProcedureBase*>& GetProcedures() { return Procedures; }
	
	TMap<TSubclassOf<UProcedureBase>, UProcedureBase*>& GetProcedureMap() { return ProcedureMap; }

	//////////////////////////////////////////////////////////////////////////
	/// Editor
public:
	#if WITH_EDITOR
	void GenerateListItem(TArray<TSharedPtr<struct FProcedureListItem>>& OutProcedureListItems);

	void UpdateListItem(TArray<TSharedPtr<struct FProcedureListItem>>& OutProcedureListItems);

	void SetProcedureItem(int32 InIndex, UProcedureBase* InProcedure);
	#endif
};
