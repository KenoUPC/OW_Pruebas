// Fill out your copyright notice in the Description page of Project Settings.


#include "OW_Armor.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Interaction/OW_HighlightableStaticMesh.h"


// Sets default values
AOW_Armor::AOW_Armor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));
	
	HighlightMesh = CreateDefaultSubobject<UOW_HighlightableStaticMesh>(TEXT("HighlightMesh"));
	HighlightMesh->SetupAttachment(RootComponent);
	HighlightMesh->SetIsReplicated(true);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void AOW_Armor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOW_Armor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOW_Armor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ACharacter* OverlappedCharacter = Cast<ACharacter>(OtherActor);
	
	if (HasAuthority() && IsValid(OverlappedCharacter))
	{
		HighlightMesh->AttachToComponent(OverlappedCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,SocketName);
	}
}

