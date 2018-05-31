// Fill out your copyright notice in the Description page of Project Settings.

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsAirfoilComponent.h"
#include "PlanePawn.h"


// Sets default values
APlanePawn::APlanePawn()
{
 	PrimaryActorTick.bCanEverTick = true;

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		FConstructorStatics() : PlaneMesh(TEXT("/Game/Planes/PlaceholderPlane")) {}
	};
	static FConstructorStatics ConstructorStatics;

	// Create static mesh component
	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh0"));
	PlaneMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	RootComponent = PlaneMesh;

	// Create right wing airfoil component
	RightAirfoil = CreateDefaultSubobject<UPhysicsAirfoilComponent>(TEXT("RightAirfoil"));
	

}

// Called when the game starts or when spawned
void APlanePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlanePawn::Tick(float DeltaTime)
{
	// Update the current speed
	Speed = (GetActorLocation() - PrevPosition) * DeltaTime;
	PrevPosition = GetActorLocation();

	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlanePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

