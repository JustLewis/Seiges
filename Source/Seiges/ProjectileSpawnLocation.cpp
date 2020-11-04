// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpawnLocation.h"

// Sets default values for this component's properties
UProjectileSpawnLocation::UProjectileSpawnLocation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UProjectileSpawnLocation::SpawnProjectileWithVelocity(float VelocityIn)
{
	UWorld * World = GetWorld();
	if (World != NULL)
	{
		const FRotator PlayerRotation = GetComponentRotation();
		const FVector Playerlocation = GetComponentLocation();
		for (size_t i = 0; i < 1; i++) {

			float XOffset = FMath::FRandRange(-SprayAmount, SprayAmount);
			float YOffset = FMath::FRandRange(-SprayAmount, SprayAmount);

			FActorSpawnParameters ActorSpawnParams;
			//ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			World->SpawnActor<ABaseProjectile>(Projectile, Playerlocation /*+
				(PlayerRotation.Vector() * 10.0f)*/, PlayerRotation + FRotator(XOffset, YOffset, 0.0f), ActorSpawnParams);
		}
	}
}

void UProjectileSpawnLocation::SetFiring(bool ValueIn)
{
	bIsFiring = ValueIn;
}

// Called when the game starts
void UProjectileSpawnLocation::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UProjectileSpawnLocation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsFiring) { SpawnProjectileWithVelocity(1000.0f); }
	// ...
}

