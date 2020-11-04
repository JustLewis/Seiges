// Fill out your copyright notice in the Description page of Project Settings.


#include "StructureControlled.h"
#include "Kismet/KismetMathLibrary.h"

AStructureControlled::AStructureControlled() : AStructuresBase()
{

}

void AStructureControlled::Activate()
{
	AStructuresBase::Activate();

	bIsActive = true;
}

void AStructureControlled::MakeStructureInactive()
{
	bIsActive = false;
}

void AStructureControlled::BeginPlay()
{
	Super::BeginPlay();

	ProjectileSpawner = FindComponentByClass<UProjectileSpawnLocation>();
	if (ProjectileSpawner == nullptr) {	UE_LOG(LogTemp, Error, TEXT("Projectile spawner is missing from %s"), *GetNameSafe(this));}

	if (!GetWorld()) { UE_LOG(LogTemp, Error, TEXT("Unable to get world in structure: %s"), *GetNameSafe(this)); return; }
	if (!GetWorld()->GetFirstPlayerController()) { UE_LOG(LogTemp, Error, TEXT("Unable to get first player controller in structure: %s"), *GetNameSafe(this)); return; }

	//Target = GetWorld()->GetFirstPlayerController()->GetPawn();

	//TargetLocation = Target->GetActorLocation();
	
}

void AStructureControlled::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsActive)
	{
		if (Target != nullptr)
		{
			TargetLocation = Target->GetActorLocation();
			if (ProjectileSpawner != nullptr) { ProjectileSpawner->SetFiring(true); }
		}

		FRotator TargetDirection = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
		
		SetActorRotation(FRotator(0.0f,TargetDirection.Yaw,0.0f), ETeleportType::None);
	}
}
