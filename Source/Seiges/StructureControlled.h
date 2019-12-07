// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructuresBase.h"
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
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
