// Fill out your copyright notice in the Description page of Project Settings.


#include "StructuresBase.h"
#include "Engine/World.h"
// Sets default values
AStructuresBase::AStructuresBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 100.0f;

}

// Called when the game starts or when spawned
void AStructuresBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("%s has spawned and called Begin play from Base polymorphic class"), *GetNameSafe(this));

	Mesh = FindComponentByClass<UStaticMeshComponent>();
	if (Mesh == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s has no static mesh component for collisions"), *GetNameSafe(this));
		return;
		
	}
	
	Mesh->CanEditSimulatePhysics();
	Mesh->SetSimulatePhysics(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AStructuresBase::Death()
{
	if (Health <= 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s has died"), *GetNameSafe(this)); //This works
		this->Destroy();
	}

}

void AStructuresBase::SettingLocation()
{
	if (GetActorLocation().Z > StartLocation.Z)
	{
		SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, -100.0f));
		return;
	}
	else
	{
		FVector CurrentLoc = GetActorLocation();
		SetActorLocation(FVector(CurrentLoc.X, CurrentLoc.Y, 1.0f));
		bLocationHappy = true;
		return;
	}
}

void AStructuresBase::Activate()
{
	StartLocation = GetActorLocation();
	bLocationHappy = false;
	SetActorLocation(FVector(StartLocation.X,StartLocation.Y,StartLocation.Z + 5000.0f));
	if (Mesh == nullptr)
	{
		return;
	}

	//Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
}

float AStructuresBase::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Health -= DamageAmount;

	Death();
	return DamageAmount;
}


void AStructuresBase::SpawnWithLocationAndRotation(FVector LocationIn, FRotator RotationIn)
{
	UWorld* World = GetWorld();

	if (World) //make sure world is available
	{
		FActorSpawnParameters SpawnParams;
		//SpawnParams.Owner = this; //Leaving this as NULL.

		World->SpawnActor<AStructuresBase>(GetClass(), LocationIn, RotationIn, SpawnParams);

	}
}
// Called every frame
void AStructuresBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bLocationHappy == false) { SettingLocation(); }
	
}

// Called to bind functionality to input
void AStructuresBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

