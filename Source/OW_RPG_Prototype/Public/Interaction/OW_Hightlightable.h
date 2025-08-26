// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OW_Hightlightable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UOW_Hightlightable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OW_RPG_PROTOTYPE_API IOW_Hightlightable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	void Higthlight();

	UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
	void UnHigthlight();
};
