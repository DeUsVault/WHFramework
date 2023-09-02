// Fill out your copyright notice in the Description page of Project Settings.


#include "Voxel/Voxels/VoxelPlant.h"

UVoxelPlant::UVoxelPlant()
{
	
}

void UVoxelPlant::LoadData(const FString& InData)
{
	Super::LoadData(InData);
}

FString UVoxelPlant::ToData()
{
	return Super::ToData();
}

void UVoxelPlant::OnGenerate(IVoxelAgentInterface* InAgent)
{
	Super::OnGenerate(InAgent);
}

void UVoxelPlant::OnDestroy(IVoxelAgentInterface* InAgent)
{
	Super::OnDestroy(InAgent);
}

void UVoxelPlant::OnAgentHit(IVoxelAgentInterface* InAgent, const FVoxelHitResult& InHitResult)
{
	Super::OnAgentHit(InAgent, InHitResult);
}

void UVoxelPlant::OnAgentEnter(IVoxelAgentInterface* InAgent, const FVoxelHitResult& InHitResult)
{
	Super::OnAgentEnter(InAgent, InHitResult);
}

void UVoxelPlant::OnAgentStay(IVoxelAgentInterface* InAgent, const FVoxelHitResult& InHitResult)
{
	Super::OnAgentStay(InAgent, InHitResult);
}

void UVoxelPlant::OnAgentExit(IVoxelAgentInterface* InAgent, const FVoxelHitResult& InHitResult)
{
	Super::OnAgentExit(InAgent, InHitResult);
}

bool UVoxelPlant::OnAgentAction(IVoxelAgentInterface* InAgent, EVoxelActionType InActionType, const FVoxelHitResult& InHitResult)
{
	switch (InActionType)
	{
		case EVoxelActionType::Action1:
		{
			return Super::OnAgentAction(InAgent, InActionType, InHitResult);
		}
		default: break;
	}
	return false;
}
