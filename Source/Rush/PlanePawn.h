// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "Engine/World.h"
#include "PhysicsAirfoilComponent.h"
#include "PhysicsDragComponent.h"
#include "PlaneMeshComponent.h"
#include "PlanePawn.generated.h"

UCLASS()
class RUSH_API APlanePawn : public APawn
{
	GENERATED_BODY()
	
	/** StaticMesh component that will be the visuals for our flying pawn */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UPlaneMeshComponent* PlaneMesh;

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	/** Camera that will be attached to the spring arm for a third person perspective */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;

	/** SCene component for placing the first person camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* InternalCameraBase;

	/** Camera component for the first person perspective */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* InternalCamera;
	
	/** Physics thruster for the propeller */
	UPROPERTY(Category = Physics, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UPhysicsThrusterComponent* Propulsion;

	UPROPERTY(Category = Physics, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UPhysicsAirfoilComponent* LeftAirfoil;

	UPROPERTY(Category = Physics, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UPhysicsAirfoilComponent* RightAirfoil;

	UPROPERTY(Category = Physics, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UPhysicsAirfoilComponent* RearAirfoil;

	UPROPERTY(Category = Physics, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UPhysicsAirfoilComponent* RudderAirfoil;

	UPROPERTY(Category = Physics, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UPhysicsDragComponent* Drag;
	

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

	/** Bound to the left stick vertical axis for a relative control schema */
	void AddThrust(float Val);

	/** Bound to the right stick vertical axis for a relative control schema */
	void AddPitch(float Val);

	/** Bound to the right stick horizontal axis for a relative control schema */
	void AddRoll(float Val);

	/** Bound to the left stick horizontal axis  for a relative control schema */
	void AddYaw(float Val);

	/** Bound to the left stick vertical axis for an absolute control schema */
	void SetThrust(float Val);

	/** Bound to the right stick vertical axis for an absolute control schema */
	void SetPitch(float Val);

	/** Bound to the right stick horizontal axis for an absolute control schema */
	void SetRoll(float Val);

	/** Bound to the left stick horizontal axis  for an absolute control schema */
	void SetYaw(float Val);

	/** The maximum speed of the plane. This controls the wind resistance of the plane */
	UPROPERTY(Category = Physics, EditAnywhere)
		float MaxSpeed = 2000.0f;

	/** The speed at which the plane is stable ([0,1]) */
	UPROPERTY(Category = Physics, EditAnywhere)
		float StableSpeed = 0.7;

	/** The maximum thrust power of the plane */
	UPROPERTY(Category = Physics, EditAnywhere)
		float MaxThrust = 2000.0f;
	
	

	float Acceleration;
	float Pitch;
	float Roll;
	float Yaw;

public:

	float GetStableSpeed();

	float GetMaxThrust();

	float GetMaxSpeed();
	
};
