// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "StructuresBase.h"
#include "Engine/engine.h"

//#include "BaseProjectile.h"
#include "ProjectileSpawnLocation.h"

#include "PlayerCharacter.generated.h"

class MyPlayerState
{
public:
	virtual ~MyPlayerState() {}

	virtual void Activate() {}
	virtual void Deactivate() {}

	virtual MyPlayerState* Action(APlayerCharacter* PlayerIn) { return NULL; }
	virtual MyPlayerState* AltAction(APlayerCharacter* PlayerIn) { return NULL; }
	virtual MyPlayerState* CycleMode(APlayerCharacter* PlayerIn) { return NULL; }
	
	virtual void Rotate(APlayerCharacter* PlayerIn,float amount) {};

	virtual void Tick(APlayerCharacter* PlayerIn) {};

	virtual void ScrollUp(APlayerCharacter* PlayerIn) {}
	virtual void ScrollDown(APlayerCharacter* PlayerIn) {}
};

class WeaponState : public MyPlayerState
{
public:
	WeaponState() { GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Activating weapons", true, FVector2D(3.0f, 3.0f)); }

	~WeaponState() { UE_LOG(LogTemp, Warning, TEXT("Yes I am weapon state being deleted correctly.")) }
	MyPlayerState* Action(APlayerCharacter* PlayerIn) override;
	MyPlayerState* AltAction(APlayerCharacter* PlayerIn) override;
	MyPlayerState* CycleMode(APlayerCharacter* PlayerIn) override;

	void Tick(APlayerCharacter* PlayerIn) override;

private:
	bool bFiring = false;

	//
};

class BuildState : public MyPlayerState
{
public:
	BuildState() { GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Activating Build mode",true,FVector2D(3.0f,3.0f)); }
	~BuildState() { UE_LOG(LogTemp, Warning, TEXT("Yes I am build state being deleted correctly.")) }
	
	MyPlayerState* Action(APlayerCharacter* PlayerIn) override;
	MyPlayerState* AltAction(APlayerCharacter* PlayerIn) override;
	MyPlayerState* CycleMode(APlayerCharacter* PlayerIn) override;

	void Tick(APlayerCharacter* PlayerIn) override;

	void ScrollUp(APlayerCharacter* PlayerIn) override;
	void ScrollDown(APlayerCharacter* PlayerIn) override;

};

class BuildStateSecond : public MyPlayerState
{
public:
	BuildStateSecond() { GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Activated Buildmode part 2", true, FVector2D(3.0f, 3.0f)); }
	~BuildStateSecond() {};
	MyPlayerState* Action(APlayerCharacter* PlayerIn) override;
	MyPlayerState* AltAction(APlayerCharacter* PlayerIn) override;
	MyPlayerState* CycleMode(APlayerCharacter* PlayerIn) override;

	void Rotate(APlayerCharacter* PlayerIn, float amount) override;

};


UCLASS(Blueprintable)
class SEIGES_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:


	UFUNCTION(BlueprintCallable, Category = AIFunctions)
		void SetAITarget() {}; //TODO make this.

	APlayerCharacter();
	~APlayerCharacter();

	UCameraComponent* MainCamera;

	UProjectileSpawnLocation* NozzleLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	TArray<UClass*> StructureList; //TODO May need to force garbage collection at some point.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float SprayAmount;




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

	void Jump();

	void Action();
	void AltAction();

	void ScrollUp();
	void ScrollDown();

	void CycleMode();


	FHitResult LineTraceHitResult();
	UINT GetStructureIterator() { return StructureIterator; }
	void IncrementStuctureIterator(bool bIsPositiveIncrement);
	
	void SetControlledStructure(AStructuresBase* ActorIn);
	AStructuresBase* GetControlledStructure();
	
	bool bRotationEnabled = true;

private:
	float Reach = 5000.0f;
	UINT StructureIterator = 0;
	
	MyPlayerState * ActionState;
	
	AStructuresBase * ControlledStructure = nullptr;
	
	//Needs to be a uproperty to be handled in memory by UEs smart pointers but making it uproperty causes more problems than it solves...
	//UPROPERTY()
	//TArray<MyPlayerState*> StateArray;
	//UINT StateIterator = 0;

	FVector LineTraceStart();
	FVector LineTraceEnd();
	

};

