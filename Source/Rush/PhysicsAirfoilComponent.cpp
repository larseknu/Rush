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

	// Applied force to the base, so if we don't have one, do nothing.
	if (!bIsActive || GetAttachParent())
		return;
	
	FVector WorldForce = LiftForce * GetComponentTransform().TransformVectorNoScale(FVector(0.f, -1.f, 0.f));

	UPrimitiveComponent* BasePrimComp = Cast<UPrimitiveComponent>(GetAttachParent());
	if (BasePrimComp)
		BasePrimComp->AddForceAtLocation(WorldForce, GetComponentLocation(), NAME_None);
}
