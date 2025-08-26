// Copyright Epic Games, Inc. All Rights Reserved.


#include "OW_RPG_PrototypePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Interaction/OW_Hightlightable.h"
#include "Items/Components/OW_ItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Public/Widgets/HUD/OW_HUDWidget.h"


AOW_RPG_PrototypePlayerController::AOW_RPG_PrototypePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	TraceLength = 1000.0;
	ItemTraceChannel = ECC_GameTraceChannel1;
}	

void AOW_RPG_PrototypePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TraceForIntem();
}

void AOW_RPG_PrototypePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Contexts
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultIMCs)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(PrimaryInteractAction,ETriggerEvent::Started, this, &AOW_RPG_PrototypePlayerController::PrimaryInteract);
	
	CreateHUDWidget();
}

void AOW_RPG_PrototypePlayerController::PrimaryInteract()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,                         // Key (-1 para generar una nueva)
			5.0f,                      // Tiempo que se mostrará el mensaje (5 segundos)
			FColor::Green,             // Color del texto
			TEXT("Interacción Primaria Activada!")  // Mensaje a mostrar
		);
	}

}

void AOW_RPG_PrototypePlayerController::CreateHUDWidget()
{
	if (!IsLocalPlayerController()) return;
	HUDWidget = CreateWidget<UOW_HUDWidget>(this, HUDWidgetClass);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
	}
}

void AOW_RPG_PrototypePlayerController::TraceForIntem()
{
	if (!IsValid(GEngine)|| !IsValid(GEngine->GameViewport))
	{
		return;
	}
	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D ViewportCenter = ViewportSize / 2.0f;

	FVector TraceStart;
	FVector Forward;
	
	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportCenter,TraceStart, Forward))
	{
		return;
	}
	
	const FVector TraceEnd = TraceStart + Forward * TraceLength;
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ItemTraceChannel);
	
	LastActor = ThisActor;
	ThisActor = HitResult.GetActor();

	if (!ThisActor.IsValid())
	{
		if (IsValid(HUDWidget))
		{
			HUDWidget->HidePickupMessage();
		}
	}
	
	if (ThisActor == LastActor)
	{
		return;
	}
	
	if (ThisActor.IsValid())
	{
		if (UActorComponent* Highlightable = ThisActor->FindComponentByInterface(UOW_Hightlightable::StaticClass()); IsValid(Highlightable))
		{
			IOW_Hightlightable::Execute_Higthlight(Highlightable);
		}
		UOW_ItemComponent* ItemComponent = ThisActor->FindComponentByClass<UOW_ItemComponent>();
		if (!IsValid(ItemComponent))
		{
			return;
		}
		if (IsValid(HUDWidget))
		{
			HUDWidget->ShowPickupMessage(ItemComponent->GetPickupMessage());
		}
		if (GEngine)
		{
			// FString ActorName = ThisActor->GetActorNameOrLabel();
			// FString Message = FString::Printf(TEXT("Se está rastreando un nuevo actor: %s"), *ActorName);
			// GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,Message);
		}
	}
	if (LastActor.IsValid())
	{

		if (UActorComponent* Highlightable = LastActor->FindComponentByInterface(UOW_Hightlightable::StaticClass()); IsValid(Highlightable))
		{
			IOW_Hightlightable::Execute_UnHigthlight(Highlightable);
		}
		
		// FString ActorName = LastActor->GetActorNameOrLabel();
		// FString Message = FString::Printf(TEXT("last actor: %s"), *ActorName);
		// GEngine->AddOnScreenDebugMessage(1,5.0f,FColor::Red,Message);
	}
}
