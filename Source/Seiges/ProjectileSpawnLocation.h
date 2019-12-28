// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BaseProjectile.h"
#include "ProjectileSpawnLocation.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SEIGES_API UProjectileSpawnLocation : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectileSpawnLocation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	TSubclassOf<class ABaseProjectile> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float SprayAmount;

	UFUNCTION(BlueprintCallable, Category = Projectile)
	void SpawnProjectileWithVelocity(float VelocityIn);

	void SetFiring(bool ValueIn);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool bIsFiring;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
