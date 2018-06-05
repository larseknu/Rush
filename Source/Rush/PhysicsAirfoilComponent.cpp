// Fill out your copyright notice in the Description page of Project Settings.

#include "PhysicsAirfoilComponent.h"


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
}

void UPhysicsAirfoilComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsActive || GetAttachParent())
		return;
	
	FVector WorldForce = LiftForce * GetComponentTransform().TransformVectorNoScale(FVector(0.f, 0.f, 1.f));

	UPrimitiveComponent* BasePrimComp = Cast<UPrimitiveComponent>(GetAttachParent());
	if (BasePrimComp)
		BasePrimComp->AddForceAtLocation(WorldForce, GetComponentLocation(), NAME_None);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor(255, 198, 128), FString::Printf(TEXT("WorldForce %s"), *WorldForce.ToString()));
}

void UPhysicsAirfoilComponent::SetLiftForce(float LiftForce) 
{
	this->LiftForce = LiftForce;
}

float UPhysicsAirfoilComponent::GetLiftForce()
{
	return LiftForce;
}