// Fill out your copyright notice in the Description page of Project Settings.


#include "OW_Actor.h"


// Sets default values
AOW_Actor::AOW_Actor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bNetLoadOnClient = true;
	bReplicates = true;
	SetReplicatingMovement(true);
}

// Called when the game starts or when spawned
void AOW_Actor::BeginPlay()
{
	Super::BeginPlay();

	const bool bAuth = HasAuthority();
	const ENetRole LocalRole = GetLocalRole();
}

// Called every frame
void AOW_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

