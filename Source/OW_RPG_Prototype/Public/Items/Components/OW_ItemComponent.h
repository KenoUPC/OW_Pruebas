// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OW_ItemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class OW_RPG_PROTOTYPE_API UOW_ItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOW_ItemComponent();

	FString GetPickupMessage() const{return PickupMessage;}
protected:
	

private:

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FString PickupMessage;
	
};
