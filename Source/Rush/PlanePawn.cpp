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

	// Create plane mesh component
	PlaneMesh = CreateDefaultSubobject<UPlaneMeshComponent>(TEXT("PlaneMesh"));
	PlaneMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	RootComponent = PlaneMesh;

	// Create a spring arm component for third-person camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
	SpringArm->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 250.0f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;

	// Create the third-person camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ChaseCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->SetRelativeLocation(FVector(-250.0, 0.0f, 0.0f));
	Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 90.f;

	// Create right airfoil component
	RightAirfoil = CreateDefaultSubobject<UPhysicsAirfoilComponent>(TEXT("RightAirfoil"));
	RightAirfoil->SetupAttachment(RootComponent);
	RightAirfoil->SetRelativeLocation(FVector(10.f, 200.f, 0.f));
	RightAirfoil->RegisterComponent();
	
	// Create left airfoil component
	LeftAirfoil = CreateDefaultSubobject<UPhysicsAirfoilComponent>(TEXT("LeftAirfoil"));
	LeftAirfoil->SetupAttachment(RootComponent);
	LeftAirfoil->SetRelativeLocation(FVector(10.f, -200.f, 0.f));
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

	// Create drag component at the center of the plane (also center of mass)
	Drag = CreateDefaultSubobject<UPhysicsDragComponent>(TEXT("Drag"));
	Drag->SetupAttachment(RootComponent);
	Drag->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	Drag->RegisterComponent();

}

// Called when the game starts or when spawned
void APlanePawn::BeginPlay()
{

	// Update the physics properties of the plane mesh
	PlaneMesh->UpdatePhysicsProperties();
	

	// Calculate the lift of the airfoil components to ensure stable flight
	
	float Gravity = abs(GetWorld()->GetGravityZ()) * PlaneMesh->GetMass();
	
	FVector RootPosition = PlaneMesh->GetCenterOfMass() - PlaneMesh->GetComponentTransform().GetLocation();

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

	LeftAirfoil->SetCalibratedLiftForce(LeftLift);
	RightAirfoil->SetCalibratedLiftForce(RightLift);
	RearAirfoil->SetCalibratedLiftForce(RearLift);

	LeftAirfoil->UpdatePhysicsProperties();
	RightAirfoil->UpdatePhysicsProperties();
	RearAirfoil->UpdatePhysicsProperties();
	RudderAirfoil->UpdatePhysicsProperties();
	
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
	Super::Tick(DeltaTime);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor(255, 198, 128), FString::Printf(TEXT("Location %s Rotation %s"), *GetActorTransform().GetLocation().ToString(), *GetActorTransform().GetRotation().GetUpVector().ToString()));
	}

}

// Called to bind functionality to input
void APlanePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("SpeedAxis", this, &APlanePawn::SetThrust);
	PlayerInputComponent->BindAxis("YawAxis", this, &APlanePawn::SetYaw);
	PlayerInputComponent->BindAxis("PitchAxis", this, &APlanePawn::SetPitch);
	PlayerInputComponent->BindAxis("RollAxis", this, &APlanePawn::SetRoll);

	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlanePawn::AddThrust(float Val)
{
	Acceleration += Val;
}

void APlanePawn::AddYaw(float Val)
{
	Yaw += Val;
}

void APlanePawn::AddPitch(float Val)
{
	Pitch += Val;
}

void APlanePawn::AddRoll(float Val)
{
	Roll = Val;
}

void APlanePawn::SetThrust(float Val)
{
	Acceleration = Val;
}

void APlanePawn::SetYaw(float Val)
{
	Yaw = Val;
}

void APlanePawn::SetPitch(float Val)
{
	Pitch = Val;
	LeftAirfoil->SetAngleOfAttack(Pitch);
	LeftAirfoil->SetAngleOfAttack(Pitch);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 25.f, FColor(255, 198, 128), FString::Printf(TEXT("Pitch %f"), Val));
	}
}

void APlanePawn::SetRoll(float Val)
{
	Roll = Val;
}

float APlanePawn::GetStableSpeed()
{
	return StableSpeed;
}

float APlanePawn::GetMaxThrust()
{
	return MaxThrust;
}

float APlanePawn::GetMaxSpeed()
{
	return MaxSpeed;
}