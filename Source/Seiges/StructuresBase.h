// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StructuresBase.generated.h"

/*
	This is a the base class for different types of structures. They are Pawns in case a structure has a turret, future proofing this class.

	The components needed for this class will be assembled in blueprint. (static mesh, camera if needed)
	The functions will all be written in the polymorph class.
*/

UCLASS(Blueprintable)
class SEIGES_API AStructuresBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AStructuresBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = Stats)
	float Health;



	UFUNCTION(BlueprintCallable,Category = StructureFunctions)
	virtual void Death();

	
public:	

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	/*UFUNCTION(BlueprintCallable, Category = StructureFunctions)
		virtual void CauseDamage(float DamageIn);*/

	UFUNCTION(BlueprintCallable, Category = StructureFunctions)
		virtual void SpawnWithLocationAndRotation(FVector LocationIn, FRotator RotationIn);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
