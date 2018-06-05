// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"
#include "PhysicsAirfoilComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUSH_API UPhysicsAirfoilComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPhysicsAirfoilComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	
	virtual void OnRegister() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:

	/** The current lift force of the airfoil */
	UPROPERTY(Category = Physics, BlueprintReadOnly)
		float LiftForce;

public:

	void SetLiftForce(float LiftForce);
	float GetLiftForce();
	
	
};
