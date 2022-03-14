// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "WHPlayerController.generated.h"

UENUM(BlueprintType)
enum class ETrackTargetMode : uint8
{
	LocationOnly,
	LocationAndRotation,
	LocationAndRotationAndDistance,
	LocationAndRotationAndDistanceOnce
};

class UModuleNetworkComponent;
/**
 * 
 */
UCLASS()
class WHFRAMEWORK_API AWHPlayerController : public APlayerController
{

private:
	GENERATED_BODY()

public:
	AWHPlayerController();

	//////////////////////////////////////////////////////////////////////////
	/// Components
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class UWidgetInteractionComponent* WidgetInteractionComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class UAudioModuleNetworkComponent* AudioModuleNetComp;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class UCameraModuleNetworkComponent* CameraModuleNetComp;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class UCharacterModuleNetworkComponent* CharacterModuleNetComp;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class UEventModuleNetworkComponent* EventModuleNetComp;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class UMediaModuleNetworkComponent* MediaModuleNetComp;
		
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class UNetworkModuleNetworkComponent* NetworkModuleNetComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class UProcedureModuleNetworkComponent* ProcedureModuleNetComp;

private:
	UPROPERTY(Transient)
	TMap<TSubclassOf<UModuleNetworkComponent>, UModuleNetworkComponent*> ModuleNetCompMap;
public:
	template<class T>
	T* GetModuleNetCompByClass(TSubclassOf<UModuleNetworkComponent> InModuleClass = T::StaticClass())
	{
		if(ModuleNetCompMap.Contains(InModuleClass))
		{
			return Cast<T>(ModuleNetCompMap[InModuleClass]);
		}
		return nullptr;
	}

	//////////////////////////////////////////////////////////////////////////
	/// Defaults
public:	
	virtual void Initialize();
	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	//////////////////////////////////////////////////////////////////////////
	/// Camera Control
	protected:
	UPROPERTY(EditAnywhere, Category = "CameraControl")
	bool bCameraControlAble;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bCameraControlAble == true"), Category = "CameraControl")
	bool bCameraMoveAble;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bCameraControlAble == true"), Category = "CameraControl")
	bool bCameraRotateAble;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bCameraControlAble == true"), Category = "CameraControl")
	bool bCameraZoomAble;

	UPROPERTY(EditAnywhere, Category = "CameraControl")
	float CameraMoveRate;

	UPROPERTY(EditAnywhere, Category = "CameraControl")
	float CameraMoveSmooth;

	UPROPERTY(EditAnywhere, Category = "CameraControl")
	float CameraTurnRate;

	UPROPERTY(EditAnywhere, Category = "CameraControl")
	float CameraLookUpRate;

	UPROPERTY(EditAnywhere, Category = "CameraControl")
	float CameraRotateSmooth;

	UPROPERTY(EditAnywhere, Category = "CameraControl")
	float MinCameraPinch;

	UPROPERTY(EditAnywhere, Category = "CameraControl")
	float MaxCameraPinch;

	UPROPERTY(EditAnywhere, Category = "CameraControl")
	float InitCameraPinch;

	UPROPERTY(EditAnywhere, Category = "CameraControl")
	float CameraZoomRate;

	UPROPERTY(EditAnywhere, Category = "CameraControl")
	float CameraZoomSmooth;

	UPROPERTY(EditAnywhere, Category = "CameraControl")
	float MinCameraDistance;

	UPROPERTY(EditAnywhere, Category = "CameraControl")
	float MaxCameraDistance;

	UPROPERTY(EditAnywhere, Category = "CameraControl")
	float InitCameraDistance;

private:
	UPROPERTY()
	AActor* TrackTargetActor;
	FVector TrackLocationOffset;
	float TrackYawOffset;
	float TrackPitchOffset;
	float TrackDistance;
	ETrackTargetMode TrackTargetMode;

	FVector TargetCameraLocation;
	FRotator TargetCameraRotation;
	float TargetCameraDistance;

	int32 TouchPressedCount;
	FVector2D TouchLocationPrevious;
	float TouchPinchValuePrevious;

	UPROPERTY()
	class USpringArmComponent* CameraBoom;
	
protected:
	virtual void Turn(float InRate);

	virtual void LookUp(float InRate);
	
	virtual void PanH(float InRate);

	virtual void PanV(float InRate);
	
	virtual void Pinch(float InRate);

	virtual void ZoomCam(float InRate);

	virtual void TouchPressed(ETouchIndex::Type InTouchIndex, FVector InLocation);

	virtual void TouchReleased(ETouchIndex::Type InTouchIndex, FVector InLocation);

	virtual void TouchMoved(ETouchIndex::Type InTouchIndex, FVector InLocation);

	virtual void StartInteract(FKey InKey);

	virtual void EndInteract(FKey InKey);

	virtual void TrackTarget(bool bInstant = false);

public:
	UFUNCTION(BlueprintCallable)
	virtual void StartTrackTarget(AActor* InTargetActor, ETrackTargetMode InTrackTargetMode = ETrackTargetMode::LocationAndRotationAndDistanceOnce, FVector InLocationOffset = FVector::ZeroVector, float InYawOffset = 0.f, float InPitchOffset = 0.f, float InDistance = 0.f, bool bInstant = false);

	UFUNCTION(BlueprintCallable)
	virtual void EndTrackTarget();

	UFUNCTION(BlueprintCallable)
	virtual void SetCameraLocation(FVector InLocation, bool bInstant = false);

	UFUNCTION(BlueprintCallable)
	virtual void SetCameraRotation(float InYaw = -1.f, float InPitch = -1.f, bool bInstant = false);

	UFUNCTION(BlueprintCallable)
	virtual void SetCameraDistance(float InDistance = -1.f, bool bInstant = false);

	UFUNCTION(BlueprintCallable)
	virtual void SetCameraRotationAndDistance(float InYaw = -1.f, float InPitch = -1.f, float InDistance = -1.f, bool bInstant = false);

	UFUNCTION(BlueprintCallable)
	virtual void AddCameraMovementInput(FVector InDirection, float InValue);

	UFUNCTION(BlueprintCallable)
	virtual void AddCameraRotationInput(float InYaw, float InPitch);

	UFUNCTION(BlueprintCallable)
	virtual void AddCameraDistanceInput(float InValue);

public:
	UFUNCTION(BlueprintPure)
	bool IsCameraControlAble() const { return bCameraControlAble; }

	UFUNCTION(BlueprintCallable)
	void SetCameraControlAble(bool bInCameraControlAble) { this->bCameraControlAble = bInCameraControlAble; }

	UFUNCTION(BlueprintPure)
	bool IsCameraMoveAble() const { return bCameraMoveAble; }

	UFUNCTION(BlueprintCallable)
	void SetCameraMoveAble(bool bInCameraMoveAble) { this->bCameraMoveAble = bInCameraMoveAble; }

	UFUNCTION(BlueprintPure)
	bool IsCameraRotateAble() const { return bCameraRotateAble; }

	UFUNCTION(BlueprintCallable)
	void SetCameraRotateAble(bool bInCameraRotateAble) { this->bCameraRotateAble = bInCameraRotateAble; }

	UFUNCTION(BlueprintPure)
	bool IsCameraZoomAble() const { return bCameraZoomAble; }

	UFUNCTION(BlueprintCallable)
	void SetCameraZoomAble(bool bInCameraZoomAble) { this->bCameraZoomAble = bInCameraZoomAble; }

	UFUNCTION(BlueprintCallable)
	void SetCameraStates(bool bInCameraControlAble, bool bInCameraMoveAble, bool bInCameraRotateAble, bool bInCameraZoomAble);

	UFUNCTION(BlueprintPure)
	float GetCameraDistance(bool bReally = true);
	
	UFUNCTION(BlueprintPure)
	class USpringArmComponent* GetCameraBoom();
};
