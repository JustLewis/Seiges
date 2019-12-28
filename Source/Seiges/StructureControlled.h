// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructuresBase.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "ProjectileSpawnLocation.h"

#include "StructureControlled.generated.h"

/**
 * 
 */
UCLASS()
class SEIGES_API AStructureControlled : public AStructuresBase
{
	GENERATED_BODY()

public:
	AStructureControlled();

	UProjectileSpawnLocation* ProjectileSpawner;

	APawn* Target;

	FVector TargetLocation;

	virtual void Activate() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	bool bIsActive = false;

};
