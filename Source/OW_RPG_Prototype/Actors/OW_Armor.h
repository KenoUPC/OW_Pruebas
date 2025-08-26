// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OW_Armor.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UOW_HighlightableStaticMesh;

UCLASS()
class OW_RPG_PROTOTYPE_API AOW_Armor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOW_Armor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UOW_HighlightableStaticMesh> HighlightMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(EditAnywhere,Category = "Item")
	FName SocketName = FName("S_Head"); // Valor por defecto

};
