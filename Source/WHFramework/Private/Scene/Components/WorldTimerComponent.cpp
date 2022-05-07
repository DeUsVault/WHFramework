// Fill out your copyright notice in the Description page of Project Settings.

#include "Scene/Components/WorldTimerComponent.h"

#include "Engine/DirectionalLight.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UWorldTimerComponent::UWorldTimerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	SkyLight = nullptr;
	SunLight = nullptr;

	TimeSeconds = 0.f;
	SecondsOfDay = 300.f;
	SunriseTime = 6.f;
	SunsetTime = 18.f;
	CurrentDay = 0;
	CurrentHour = 0;
	CurrentMinute = 0;
	CurrentSeconds = 0;
}

void UWorldTimerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWorldTimerComponent::SetTimeSeconds(int InTimeSeconds, bool bUpdateTimer /*= true*/)
{
	TimeSeconds = InTimeSeconds;
	if (bUpdateTimer)
	{
		UpdateTimer();
	}
}

void UWorldTimerComponent::UpdateTimer(float DeltaSeconds)
{
	TimeSeconds += DeltaSeconds;

	float RemainSeconds = 0;
	CurrentDay = UKismetMathLibrary::FMod(TimeSeconds, SecondsOfDay, RemainSeconds);

	UpdateLight(RemainSeconds / SecondsOfDay * 360 + 200);

	CurrentHour = UKismetMathLibrary::FMod(TimeSeconds, SecondsOfDay / 24, RemainSeconds);
	CurrentMinute = UKismetMathLibrary::FMod(TimeSeconds, SecondsOfDay / 60, RemainSeconds);
	CurrentSeconds = UKismetMathLibrary::FMod(TimeSeconds, SecondsOfDay / 60 / 60, RemainSeconds);

	TimeSeconds += GetWorld()->GetDeltaSeconds();
}
