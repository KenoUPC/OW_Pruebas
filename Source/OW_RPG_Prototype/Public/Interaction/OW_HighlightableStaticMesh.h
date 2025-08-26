// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OW_Hightlightable.h"
#include "Components/StaticMeshComponent.h"
#include "OW_HighlightableStaticMesh.generated.h"

/**
 * 
 */
UCLASS()
class OW_RPG_PROTOTYPE_API UOW_HighlightableStaticMesh : public UStaticMeshComponent, public IOW_Hightlightable
{
	GENERATED_BODY()

public:
	virtual void Higthlight_Implementation() override;

	virtual void UnHigthlight_Implementation() override;

private:
	UPROPERTY(EditAnywhere, Category = "Interaction")
	TObjectPtr<UMaterialInterface> HighlightMaterial;
};
