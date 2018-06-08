// Fill out your copyright notice in the Description page of Project Settings.


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
	PlaneMesh->SetSimulatePhysics(true);
	RootComponent = PlaneMesh;

	// Create right airfoil component
	RightAirfoil = CreateDefaultSubobject<UPhysicsAirfoilComponent>(TEXT("RightAirfoil"));
	RightAirfoil->SetupAttachment(RootComponent);
	RightAirfoil->SetRelativeLocation(FVector(0.f, 200.f, 0.f));
	RightAirfoil->RegisterComponent();
	
	// Create left airfoil component
	LeftAirfoil = CreateDefaultSubobject<UPhysicsAirfoilComponent>(TEXT("LeftAirfoil"));
	LeftAirfoil->SetupAttachment(RootComponent);
	LeftAirfoil->SetRelativeLocation(FVector(0.f, -200.f, 0.f));
	LeftAirfoil->RegisterComponent();

	// Create rear airfoil component
	RearAirfoil = CreateDefaultSubobject<UPhysicsAirfoilComponent>(TEXT("RearAirfoil"));
	RearAirfoil->SetupAttachment(RootComponent);
	RearAirfoil->SetRelativeLocation(FVector(-250.f, 0.f, 0.f));
	RearAirfoil->RegisterComponent();
	
	// Create rudder airfoil component
	RudderAirfoil = CreateDefaultSubobject<UPhysicsAirfoilComponent>(TEXT("RudderAirfoil"));
	RudderAirfoil->SetupAttachment(RootComponent);
	RudderAirfoil->SetRelativeLocation(FVector(-250.f, 0.f, 0.f));
	RudderAirfoil->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	RudderAirfoil->RegisterComponent();

}

// Called when the game starts or when spawned
void APlanePawn::BeginPlay()
{

	// Calculate the lift of the airfoil components to ensure stable flight
	
	float Gravity = abs(GetWorld()->GetGravityZ()) * PlaneMesh->GetMass();
	
	FVector RootPosition = PlaneMesh->GetBodyInstance()->GetCOMPosition() - PlaneMesh->GetComponentTransform().GetLocation();

	FVector LeftPos = LeftAirfoil->GetRelativeTransform().GetTranslation() - RootPosition;
	FVector RightPos = RightAirfoil->GetRelativeTransform().GetTranslation() - RootPosition;
	FVector RearPos = RearAirfoil->GetRelativeTransform().GetTranslation() - RootPosition;
	
	float X1 = LeftPos[0];
	float Y1 = LeftPos[1];
	float X2 = RightPos[0];
	float Y2 = RightPos[1];
	float X3 = RearPos[0];
	float Y3 = RearPos[1];

	float LeftLift = Gravity * (Y2*X3 - Y3*X2) / (Y1*X2 - Y1*X3 + Y2*X3 - Y2*X1 - Y3*X2 + Y3*X1);
	float RightLift = (X3*LeftLift - X1*LeftLift - X3*Gravity) / (X2 - X3);
	float RearLift = Gravity - LeftLift - RightLift;

	LeftAirfoil->SetLiftForce(LeftLift);
	RightAirfoil->SetLiftForce(RightLift);
	RearAirfoil->SetLiftForce(RearLift);
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor(255, 198, 128), FString::Printf(TEXT("RootPos %s LeftPos %s RightPos %s RearPos %s"), *(RootPosition.ToString()), *(LeftPos.ToString()), *(RightPos.ToString()), *(RearPos.ToString())));
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor(255, 198, 128), FString::Printf(TEXT("Mass %f LeftLift %f RightLift %f RearLift %f"), Gravity, LeftLift, RightLift, RearLift));
	}

	Super::BeginPlay();
	
}

// Called every frame
void APlanePawn::Tick(float DeltaTime)
{
	// Update the current speed (not needed?)
	Speed = (GetActorLocation() - PrevPosition) * DeltaTime;
	PrevPosition = GetActorLocation();

	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlanePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

