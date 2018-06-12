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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	
	virtual void OnRegister() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:

	/** The calibrated lift force of the airfoil */
	UPROPERTY(Category = Physics, BlueprintReadOnly)
		float CalibratedLiftForce;

	/** The plane coefficient. This is calculated when the component is registered. */
	UPROPERTY(Category = Physics, BlueprintReadOnly)
		float PlaneFactor;

	/** The angle of attack. This value is clamped to [-1,1] */
	UPROPERTY(Category = Physics, BlueprintReadOnly)
		float AngleOfAttack = 0.f;

	/** The lift factor of the airfoil i.e. how many calibrated lift forces to aloow at most (>1.0) */
	UPROPERTY(Category = Physics, EditAnywhere)
		float LiftFactor = 1.7f;

	/** The lift bias i.e. the amount of lift when angle of attack is 0 (<1.0) */
	UPROPERTY(Category = Physics, EditAnywhere)
		float LiftBias = 0.5f;

public:

	UPhysicsAirfoilComponent();

	void UpdatePhysicsProperties();

	void SetCalibratedLiftForce(float LiftForce);
	float GetCalibratedLiftForce();

	void SetAngleOfAttack(float);
	float GetAngleOfAttack();

	float GetLiftFactor();
	float GetLiftBias();
	
	
};
