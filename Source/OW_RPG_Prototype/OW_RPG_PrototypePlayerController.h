// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OW_RPG_PrototypePlayerController.generated.h"

class UOW_HUDWidget;
class UInputAction;
class UInputMappingContext;

/**
 *  Basic PlayerController class for a third person game
 *  Manages input mappings
 */
UCLASS(abstract)
class AOW_RPG_PrototypePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AOW_RPG_PrototypePlayerController();

	virtual void Tick(float DeltaSeconds) override;
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditDefaultsOnly, Category ="Inventory")
	TArray<TObjectPtr<UInputMappingContext>> DefaultIMCs;

	/** Primary Interact Action */
	UPROPERTY(EditDefaultsOnly, Category ="Inventory")
	TObjectPtr<UInputAction> PrimaryInteractAction;


	UPROPERTY(EditDefaultsOnly, Category ="Inventory")
	TSubclassOf<UOW_HUDWidget>HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UOW_HUDWidget>HUDWidget;

	UPROPERTY(EditDefaultsOnly, Category ="Inventory")
	double TraceLength;
	
	UPROPERTY(EditDefaultsOnly, Category ="Inventory")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;

	TWeakObjectPtr<AActor> ThisActor;
	TWeakObjectPtr<AActor> LastActor;
	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	void PrimaryInteract();
	void CreateHUDWidget();
	void TraceForIntem();
};
