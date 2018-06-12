// Fill out your copyright notice in the Description page of Project Settings.

#include "PhysicsAirfoilComponent.h"
#include "PlanePawn.h"


// Sets default values for this component's properties
UPhysicsAirfoilComponent::UPhysicsAirfoilComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;
	
}


// Called when the game starts
void UPhysicsAirfoilComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPhysicsAirfoilComponent::OnRegister()
{
	Super::OnRegister();

	SetActive(true);	

}

void UPhysicsAirfoilComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsActive || !GetAttachParent())
		return;
	
	UPrimitiveComponent* BasePrimComp = Cast<UPrimitiveComponent>(GetAttachParent());
	if (!BasePrimComp)
		return;

	float Coefficient = AngleOfAttack * LiftFactor + LiftBias;

	FVector Velocity = BasePrimComp->GetPhysicsLinearVelocity(NAME_None);
	FVector RelativeVelocity = GetComponentTransform().InverseTransformVectorNoScale(Velocity);
	float RelativeSpeed = RelativeVelocity[0];	

	FVector LiftForce = PlaneFactor * RelativeSpeed * RelativeSpeed * Coefficient * GetComponentTransform().TransformVectorNoScale(FVector(0.f, 0.f, 1.f));

	BasePrimComp->AddForceAtLocation(LiftForce, GetComponentLocation(), NAME_None);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor(255, 198, 128), FString::Printf(TEXT("ComponentLocation %s ComponentRotation %s"), *GetComponentTransform().GetLocation().ToString(), *GetComponentTransform().GetRotation().GetUpVector().ToString()));
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor(255, 198, 128), FString::Printf(TEXT("Velocity %s RelativeSpeed %f"), *Velocity.ToString(), RelativeSpeed));
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor(255, 198, 128), FString::Printf(TEXT("LiftForce %s"), *LiftForce.ToString()));
	}

}

void UPhysicsAirfoilComponent::UpdatePhysicsProperties()
{
	APlanePawn *Owner = Cast<APlanePawn>(GetOwner());
	if (!Owner)
		return;

	PlaneFactor = CalibratedLiftForce / (Owner->GetStableSpeed() * Owner->GetStableSpeed() * Owner->GetMaxSpeed() * Owner->GetMaxSpeed() * LiftBias);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor(255, 198, 128), FString::Printf(TEXT("PlaneFactor %f"), PlaneFactor));
	}
}

void UPhysicsAirfoilComponent::SetCalibratedLiftForce(float LiftForce) 
{
	this->CalibratedLiftForce = LiftForce;
}

float UPhysicsAirfoilComponent::GetCalibratedLiftForce()
{
	return CalibratedLiftForce;
}

void UPhysicsAirfoilComponent::SetAngleOfAttack(float Val)
{
	this->AngleOfAttack = Val;
}

float UPhysicsAirfoilComponent::GetAngleOfAttack()
{
	return AngleOfAttack;
}

float UPhysicsAirfoilComponent::GetLiftFactor()
{
	return LiftFactor;
}

float UPhysicsAirfoilComponent::GetLiftBias()
{
	return LiftBias;
}