// Fill out your copyright notice in the Description page of Project Settings.


#include "OW_LANMenu.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "EntitySystem/MovieSceneEntityManager.h"
#include "Kismet/GameplayStatics.h"

void UOW_LANMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FInputModeUIOnly InputMode;
	GetOwningPlayer()->SetInputMode(InputMode);
	GetOwningPlayer()->SetShowMouseCursor(true);
	
	
	Button_Host->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	Button_Join->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
}

void UOW_LANMenu::HostButtonClicked()
{
	FInputModeGameOnly InputMode;
	GetOwningPlayer()->SetInputMode(InputMode);
	GetOwningPlayer()->SetShowMouseCursor(false);

	UGameplayStatics::OpenLevelBySoftObjectPtr(this, HostingLevel, true, TEXT("listen"));
}

void UOW_LANMenu::JoinButtonClicked()
{
	FInputModeGameOnly InputMode;
	GetOwningPlayer()->SetInputMode(InputMode);
	GetOwningPlayer()->SetShowMouseCursor(false);

	const FString Address = TextBox_IPAddress->GetText().ToString();

	UGameplayStatics::OpenLevel(this, *Address);
	
}
