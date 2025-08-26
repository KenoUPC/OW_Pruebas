// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/OW_HighlightableStaticMesh.h"

void UOW_HighlightableStaticMesh::Higthlight_Implementation()
{
	SetOverlayMaterial(HighlightMaterial);
}

void UOW_HighlightableStaticMesh::UnHigthlight_Implementation()
{
	SetOverlayMaterial(nullptr);
}
