// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "StructuresBase.h"
#include "PlayerCharacter.generated.h"

UCLASS(Blueprintable)
class SEIGES_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UCameraComponent* MainCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	TArray<UClass*> StructureList; //TODO May need to force garbage collection at some point.

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float speed);
	void MoveRight(float speed);

	void LookPitch(float amount);
	void LookYaw(float amount);

	void Action();

	FVector LineTraceStart();
	FVector LineTraceEnd();
	FHitResult LineTraceHitResult();

private:
	float Reach = 5000.0f;

};
