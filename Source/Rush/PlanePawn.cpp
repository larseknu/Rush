// Fill out your copyright notice in the Description page of Project Settings.

#include "PlanePawn.h"


// Sets default values
APlanePawn::APlanePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

