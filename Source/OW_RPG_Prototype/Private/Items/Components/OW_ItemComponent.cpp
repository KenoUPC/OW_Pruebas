// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Components/OW_ItemComponent.h"


// Sets default values for this component's properties
UOW_ItemComponent::UOW_ItemComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	PickupMessage = FString("E - Recoger");
}


