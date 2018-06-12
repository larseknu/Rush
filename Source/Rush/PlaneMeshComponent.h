// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/StaticMeshComponent.h"
#include "PlaneMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class RUSH_API UPlaneMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UPlaneMeshComponent();

	void UpdatePhysicsProperties();

protected:
	
};
