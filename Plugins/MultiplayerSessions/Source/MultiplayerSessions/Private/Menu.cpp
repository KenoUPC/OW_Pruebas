// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/EditableText.h"
#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "WidgetSessionSerch.h"

void UMenu::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch, FString LobbyPath)
{
	PathToLobby = FString::Printf(TEXT("%s?listen"), *LobbyPath);
	NumPublicConnections = NumberOfPublicConnections;
	MatchType = TypeOfMatch;
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsFocusable(true);

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}

	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
		MultiplayerSessionsSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSessions);
		MultiplayerSessionsSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
		MultiplayerSessionsSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
		MultiplayerSessionsSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &ThisClass::OnStartSession);
	}
}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}

	return true;
}

void UMenu::NativeDestruct()
{
	MenuTearDown();
	Super::NativeDestruct();
}

void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel(PathToLobby);
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Red,
				FString(TEXT("Failed to create session!"))
			);
		}
		HostButton->SetIsEnabled(true);
	}
}

void UMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
	if (MultiplayerSessionsSubsystem == nullptr)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("OnFindSessions: Subsystem nulo"));
		return;
	}

	if (GEngine)
	{
		FString Msg = FString::Printf(TEXT("Buscando sesiones... exito: %s, Cantidad: %d"),bWasSuccessful ? TEXT("Si") : TEXT("No"), SessionResults.Num());
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, Msg);
	}

	VerticalSerchs->ClearChildren();

	for (const auto& Result : SessionResults)
	{
		auto Id = Result.GetSessionIdStr();
		FString User = Result.Session.OwningUserName;
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("ID: %s, User: %s"), *Id, *User));

		ChoisesSession = CreateWidget<UWidgetSessionSerch>(GetWorld(), ResourceWidgetClass);
		VerticalSerchs->AddChildToVerticalBox(ChoisesSession);
		ChoisesSession->SetData(FText::FromString(User));
		ChoisesSession->SetSession(Result);
		ChoisesSession->OnButtonSelectSession.AddUObject(this, &ThisClass::SelectSession);


		FString FoundMatchType;
		Result.Session.SessionSettings.Get(FName("KenoTeach"), FoundMatchType);


		/*if (FoundMatchType == MatchType)
		{
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, TEXT("Uniendo a sesión valida..."));
			MultiplayerSessionsSubsystem->JoinSession(Result);
			return;
		}*/
	}

	if (!bWasSuccessful || SessionResults.Num() == 0)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("No se encontraron sesiones validas"));
		JoinButton->SetIsEnabled(true);
	}
}

void UMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	FString ResultStr;
	switch (Result)
	{
	case EOnJoinSessionCompleteResult::Success:
		ResultStr = "Success"; break;
	case EOnJoinSessionCompleteResult::AlreadyInSession:
		ResultStr = "AlreadyInSession"; break;
	case EOnJoinSessionCompleteResult::SessionIsFull:
		ResultStr = "SessionIsFull"; break;
	case EOnJoinSessionCompleteResult::SessionDoesNotExist:
		ResultStr = "SessionDoesNotExist"; break;
	case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
		ResultStr = "CouldNotRetrieveAddress"; break;
	case EOnJoinSessionCompleteResult::UnknownError:
	default:
		ResultStr = "UnknownError"; break;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, FString::Printf(TEXT("Resultado JoinSession: %s"), *ResultStr));
	}
		

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (!Subsystem)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Subsystem no encontrado"));
		return;
	}

	IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
	if (!SessionInterface.IsValid())
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("SessionInterface no valida"));
		return;
	}

	FString Address;
	if (SessionInterface->GetResolvedConnectString(NAME_GameSession, Address))
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Direccion: %s"), *Address));

		APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
		if (PlayerController)
		{
			PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
		}
		else
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("PlayerController nulo"));
			}
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT(""));
		}
			
	}
}

void UMenu::OnDestroySession(bool bWasSuccessful)
{
}

void UMenu::OnStartSession(bool bWasSuccessful)
{
}

void UMenu::HostButtonClicked()
{
	HostButton->SetIsEnabled(false);
	MatchType = NameHost->GetName();

	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->CreateSession(NumPublicConnections, MatchType);
	}
}

void UMenu::JoinButtonClicked()
{
	JoinButton->SetIsEnabled(false);
	if (MultiplayerSessionsSubsystem)
	{
		MultiplayerSessionsSubsystem->FindSessions(10000);
	}
}

void UMenu::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}

void UMenu::SelectSession(const FOnlineSessionSearchResult& SessionResult)
{
	MultiplayerSessionsSubsystem->JoinSession(SessionResult);
}
