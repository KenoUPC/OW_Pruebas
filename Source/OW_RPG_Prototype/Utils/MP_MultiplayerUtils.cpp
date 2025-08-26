// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_MultiplayerUtils.h"

void UMP_MultiplayerUtils::PrintLocalNetRole(AActor* Actor)
{
	if (Actor->HasAuthority())
	{
		UE_LOG(LogTemp,Warning,TEXT("Actor [%s] Tiene Autoridad (autohority)!"), *Actor->GetName());
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Actor [%s] No tiene! autoridad (authority)!"), *Actor->GetName());
	}

	
	switch (Actor->GetLocalRole())
	{
	case ROLE_None:
		UE_LOG(LogTemp, Warning, TEXT("[%s] Rol: ROLE_None - El actor no tiene rol de red"), *Actor->GetName());
		break;
        
	case ROLE_SimulatedProxy:
		UE_LOG(LogTemp, Warning, TEXT("[%s] Rol: ROLE_SimulatedProxy - Actor simulado en cliente"), *Actor->GetName());
		break;
        
	case ROLE_AutonomousProxy:
		UE_LOG(LogTemp, Warning, TEXT("[%s] Rol: ROLE_AutonomousProxy - Actor controlado localmente en cliente"), *Actor->GetName());
		break;
        
	case ROLE_Authority:
		UE_LOG(LogTemp, Warning, TEXT("[%s] Rol: ROLE_Authority - Actor con autoridad (generalmente en servidor)"), *Actor->GetName());
		break;
        
	default:
		UE_LOG(LogTemp, Error, TEXT("[%s] Rol desconocido"), *Actor->GetName());
		break;
	}

}

void UMP_MultiplayerUtils::PrintRemoteNetRole(AActor* Actor)
{
	if (Actor->HasAuthority())
	{
		UE_LOG(LogTemp,Warning,TEXT("Actor [%s] Tiene Autoridad (autohority)!"), *Actor->GetName());
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Actor [%s] No tiene! autoridad (authority)!"), *Actor->GetName());
	}

	
	switch (Actor->GetRemoteRole())
	{
	case ROLE_None:
		UE_LOG(LogTemp, Warning, TEXT("[%s] Rol Remote: ROLE_None - El actor no tiene rol de red"), *Actor->GetName());
		break;
        
	case ROLE_SimulatedProxy:
		UE_LOG(LogTemp, Warning, TEXT("[%s] Rol Remote: ROLE_SimulatedProxy - Actor simulado en cliente"), *Actor->GetName());
		break;
        
	case ROLE_AutonomousProxy:
		UE_LOG(LogTemp, Warning, TEXT("[%s] Rol Remote: ROLE_AutonomousProxy - Actor controlado localmente en cliente"), *Actor->GetName());
		break;
        
	case ROLE_Authority:
		UE_LOG(LogTemp, Warning, TEXT("[%s] Rol Remote: ROLE_Authority - Actor con autoridad (generalmente en servidor)"), *Actor->GetName());
		break;
        
	default:
		UE_LOG(LogTemp, Error, TEXT("[%s] Rol Remote desconocido"), *Actor->GetName());
		break;
	}
}
