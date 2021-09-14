// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/Handle/EventHandleBase.h"

#include "Serialization/BufferArchive.h"

UEventHandleBase::UEventHandleBase()
{
	EventType = EEventType::Multicast;
	
	Execute_Reset(this);
}

bool UEventHandleBase::Filter_Implementation(UObject* InOwner, const FName InFuncName)
{
	return true;
}

void UEventHandleBase::Fill_Implementation(const TArray<FParameter>& InParameters)
{
	
}

void UEventHandleBase::Reset_Implementation()
{
	
}
