// Fill out your copyright notice in the Description page of Project Settings.

#include "PlaneMeshComponent.h"

UPlaneMeshComponent::UPlaneMeshComponent()
{
	SetSimulatePhysics(true);
}

void UPlaneMeshComponent::UpdatePhysicsProperties() 
{
	FVector CenterOfMass = GetComponentTransform().InverseTransformPositionNoScale(GetCenterOfMass());
	SetCenterOfMass(-CenterOfMass);
	FVector CenterOfMassAfter = GetCenterOfMass() - GetComponentTransform().GetTranslation();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 45.f, FColor(255, 198, 128), FString::Printf(TEXT("CenterOfMassBefore %s CenterOfMassAfter %s"), *CenterOfMass.ToString(), *CenterOfMassAfter.ToString()));
	}
}