// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsDragComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUSH_API UPhysicsDragComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPhysicsDragComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnRegister() override;
	
	/** The calculated drag factor of the component */
	UPROPERTY(Category = Physics, BlueprintReadOnly)
		float DragFactor;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
