// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/World/WorldWidgetComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Widget/WidgetModuleBPLibrary.h"

UWorldWidgetComponent::UWorldWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	UPrimitiveComponent::SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bAutoCreate = true;
	bOrientCamera = true;
	bBindToSelf = true;
	WidgetParams = TArray<FParameter>();
	WidgetPoints = TMap<FName, USceneComponent*>();
	WorldWidget = nullptr;
}

void UWorldWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InitRotation = GetRelativeRotation();

	WidgetPoints.Add(GetFName(), this);
	
	TArray<USceneComponent*> ChildrenComps;
	GetChildrenComponents(false, ChildrenComps);
	for(auto Iter : ChildrenComps)
	{
		if(!WidgetPoints.Contains(Iter->GetFName()))
		{
			WidgetPoints.Add(Iter->GetFName(), Iter);
		}
	}

	if(bAutoCreate)
	{
		CreateWidget();
	}
}

void UWorldWidgetComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	DestroyWidget();
}

void UWorldWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!UGlobalBPLibrary::IsPlaying()) return;
	
	if(bOrientCamera)
	{
		if(const AWHPlayerController* PlayerController = UGlobalBPLibrary::GetPlayerController<AWHPlayerController>(this))
		{
			const FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetComponentLocation(), PlayerController->PlayerCameraManager->GetCameraLocation());
			SetWorldRotation(FRotator(GetComponentRotation().Pitch, TargetRotation.Yaw, GetComponentRotation().Roll));
		}
	}
	else
	{
		SetRelativeRotation(InitRotation);
	}

	if(WorldWidget && WorldWidget->GetWidgetRefreshType() == EWidgetRefreshType::Tick)
	{
		WorldWidget->OnRefresh();
	}
}

#if WITH_EDITOR
bool UWorldWidgetComponent::CanEditChange(const FProperty* InProperty) const
{
	if ( InProperty )
	{
		FString PropertyName = InProperty->GetName();

		if ( PropertyName == GET_MEMBER_NAME_STRING_CHECKED(UWorldWidgetComponent, WidgetClass) )
		{
			return false;
		}

		if ( PropertyName == GET_MEMBER_NAME_STRING_CHECKED(UWorldWidgetComponent, bBindToSelf))
		{
			return Space == EWidgetSpace::Screen;
		}

		if ( PropertyName == GET_MEMBER_NAME_STRING_CHECKED(UWorldWidgetComponent, DrawSize) ||
			 PropertyName == GET_MEMBER_NAME_STRING_CHECKED(UWorldWidgetComponent, bDrawAtDesiredSize) ||
			 PropertyName == GET_MEMBER_NAME_STRING_CHECKED(UWorldWidgetComponent, Pivot) ||
			 PropertyName == GET_MEMBER_NAME_STRING_CHECKED(UWorldWidgetComponent, WidgetParams))
		{
			return Space == EWidgetSpace::World;
		}
	}

	return Super::CanEditChange(InProperty);
}

void UWorldWidgetComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FProperty* Property = PropertyChangedEvent.MemberProperty;

	if(Property && PropertyChangedEvent.ChangeType != EPropertyChangeType::Interactive)
	{
		static FName SpaceName("Space");
		static FName AutoCreateName("bAutoCreate");
		static FName WorldWidgetClassName("WorldWidgetClass");

		auto PropertyName = Property->GetFName();

		if(PropertyName == WorldWidgetClassName)
		{
			if(WorldWidgetClass)
			{
				if(UWorldWidgetBase* DefaultObject = Cast<UWorldWidgetBase>(WorldWidgetClass->GetDefaultObject()))
				{
					DrawSize = FIntPoint(DefaultObject->GetWidgetOffsets().Right - DefaultObject->GetWidgetOffsets().Left, DefaultObject->GetWidgetOffsets().Bottom - DefaultObject->GetWidgetOffsets().Top);
					Pivot = DefaultObject->GetWidgetAlignment();
				}
			}
		}

		if(PropertyName == SpaceName || PropertyName == AutoCreateName || PropertyName == WorldWidgetClassName)
		{
			if(Space == EWidgetSpace::World && bAutoCreate)
			{
				WidgetClass = WorldWidgetClass;
			}
			else
			{
				WidgetClass = nullptr;
			}
		}
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void UWorldWidgetComponent::CreateWidget()
{
	if(!WorldWidget && WorldWidgetClass)
	{
		switch (Space)
		{
			case EWidgetSpace::World:
			{
				SetWidgetClass(WorldWidgetClass);
				break;
			}
			case EWidgetSpace::Screen:
			{
				WorldWidget = UWidgetModuleBPLibrary::CreateWorldWidget<UWorldWidgetBase>(GetOwner(), FVector::ZeroVector, this, &WidgetParams, WorldWidgetClass);
				break;
			}
		}
	}
}

void UWorldWidgetComponent::DestroyWidget()
{
	if(WorldWidget)
	{
		switch (Space)
		{
			case EWidgetSpace::World:
			{
				SetWidgetClass(nullptr);
				break;
			}
			case EWidgetSpace::Screen:
			{
				WorldWidget->Destroy();
				WorldWidget = nullptr;
				break;
			}
		}
	}
}

void UWorldWidgetComponent::SetWidget(UUserWidget* InWidget)
{
	Super::SetWidget(InWidget);

	if(InWidget)
	{
		if(WorldWidget != InWidget)
		{
			WorldWidget = Cast<UWorldWidgetBase>(InWidget);
			if(WorldWidget)
			{
				WorldWidget->OnCreate(GetOwner(), FVector::ZeroVector, this, WidgetParams);
			}
		}
	}
	else if(WorldWidget)
	{
		WorldWidget->OnDestroy();
		WorldWidget = nullptr;
	}
}

USceneComponent* UWorldWidgetComponent::GetWidgetPoint(FName InPointName) const
{
	if(WidgetPoints.Contains(InPointName))
	{
		return WidgetPoints[InPointName];
	}
	return nullptr;
}

