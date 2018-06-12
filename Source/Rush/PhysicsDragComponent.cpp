// Fill out your copyright notice in the Description page of Project Settings.

#include "PhysicsDragComponent.h"
#include "PlanePawn.h"


// Sets default values for this component's properties
UPhysicsDragComponent::UPhysicsDragComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;

}


// Called when the game starts
void UPhysicsDragComponent::BeginPlay()
{
	Super::BeginPlay();

	SetActive(true);
	
}

void UPhysicsDragComponent::OnRegister()
{
	Super::OnRegister();

	APlanePawn *Owner = Cast<APlanePawn>(GetOwner());
	DragFactor = Owner->GetMaxThrust() / (Owner->GetMaxSpeed() * Owner->GetMaxSpeed());

}


// Called every frame
void UPhysicsDragComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsActive || !GetAttachParent())
		return;

	UPrimitiveComponent* BasePrimComp = Cast<UPrimitiveComponent>(GetAttachParent());
	if (!BasePrimComp)
		return;

	FVector Velocity = BasePrimComp->GetPhysicsLinearVelocity(NAME_None);
	FVector DragForce = DragFactor * Velocity.Size() * Velocity.Size() * (-Velocity.GetSafeNormal());

	BasePrimComp->AddForceAtLocation(DragForce, BasePrimComp->GetCenterOfMass(), NAME_None);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor(255, 198, 128), FString::Printf(TEXT("DragLocation %s DragRotation %s"), *GetComponentTransform().GetLocation().ToString(), *GetComponentTransform().GetRotation().GetUpVector().ToString()));
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor(255, 198, 128), FString::Printf(TEXT("DragForce %s"), *DragForce.ToString()));
	}
	
}

