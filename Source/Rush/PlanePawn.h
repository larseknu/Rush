// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "Engine/World.h"
#include "PhysicsAirfoilComponent.h"
#include "PlanePawn.generated.h"

UCLASS()
class RUSH_API APlanePawn : public APawn
{
	GENERATED_BODY()
	
	/** StaticMesh component that will be the visuals for our flying pawn */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* PlaneMesh;

	
	UPROPERTY(Category = Physics, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UPhysicsThrusterComponent* Propeller;

	UPROPERTY(Category = Physics, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UPhysicsAirfoilComponent* LeftAirfoil;

	UPROPERTY(Category = Physics, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UPhysicsAirfoilComponent* RightAirfoil;

	UPROPERTY(Category = Physics, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UPhysicsAirfoilComponent* RearAirfoil;

	UPROPERTY(Category = Physics, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UPhysicsAirfoilComponent* RudderAirfoil;
	

public:
	// Sets default values for this pawn's properties
	APlanePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Bound to the left stick vertical axis */
	void AddThrust(float Val);

	/** Bound to the right stick vertical axis */
	void AddPitch(float Val);

	/** Bound to the right stick horizontal axis */
	void AddRoll(float Val);

	/** Bound to the triggers */
	void AddYaw(float Val);

private:

	/* The amount of lift provided rear wings comared to the fron wings [0, 1) */
	UPROPERTY(Category = Plane, EditAnywhere)
		float LiftRatio = 0.2f;

	/** The maximum acceleration of the plane */
	UPROPERTY(Category = Plane, EditAnywhere)
		float MaxAcceleration;

	/** The maximum pitch */
	UPROPERTY(Category = Plane, EditAnywhere)
		float MaxPitch;

	/** The maximum roll */
	UPROPERTY(Category = Plane, EditAnywhere)
		float MaxRoll;

	/** The maximum yaw speed */
	UPROPERTY(Category = Plane, EditAnywhere)
		float MaxYaw;

	/** The current speed of the plane */
	UPROPERTY(Category = Physics, VisibleAnywhere)
		FVector Speed;

	float Acceleration;
	float Pitch;
	float Roll;
	float Yaw;

	FVector PrevPosition;
	
};
