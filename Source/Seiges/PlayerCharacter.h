// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "StructuresBase.h"
#include "PlayerCharacter.generated.h"

enum State
{
	StateWeapon,
	StateBuild,
	StateBuildExtended
};


class MyPlayerState
{
public:
	virtual ~MyPlayerState() {};
	virtual void Activate() {}
	virtual void Deactivate() {}

	virtual MyPlayerState* Action() { return NULL; }
	virtual MyPlayerState* AltAction() { return NULL; }
	virtual void CycleUp() {}
	virtual void CycleDown() {}
};

class WeaponState : public MyPlayerState
{
public:
	WeaponState() {};
	~WeaponState() { UE_LOG(LogTemp, Warning, TEXT("Yes I am weapon state being deleted correctly.")) }
	MyPlayerState* Action() override;
	MyPlayerState* AltAction() override;
};

class BuildState : public MyPlayerState
{
public:
	BuildState() {};
	~BuildState() { UE_LOG(LogTemp, Warning, TEXT("Yes I am build state being deleted correctly.")) }
	MyPlayerState* Action() override;
	MyPlayerState* AltAction() override;
};


UCLASS(Blueprintable)
class SEIGES_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	~APlayerCharacter();

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
	void AltAction();

	void CycleStructureListUp();
	void CycleStructureListDown();
	void ChangeActiveStructure();

	

private:
	float Reach = 5000.0f;
	UINT StructureIterator = 0;

	MyPlayerState * ActionState;
	
	
	//Needs to be a uproperty to be handled in memory safely but making it uproperty causes more problems than it solves...
	//UPROPERTY()
	//TArray<MyPlayerState*> StateArray;
	//UINT StateIterator = 0;

	FVector LineTraceStart();
	FVector LineTraceEnd();
	FHitResult LineTraceHitResult();

};

