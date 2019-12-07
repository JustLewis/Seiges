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
	
}

void AStructuresBase::Death()
{
	if (Health <= 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s has died"), *GetNameSafe(this)); //This works
		this->Destroy();
	}




}

float AStructuresBase::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Health -= DamageAmount;

	Death();
	return DamageAmount;
}


//void AStructuresBase::CauseDamage(float DamageIn)
//{
//	Health -= DamageIn;
//	Death();
//}


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
}

// Called to bind functionality to input
void AStructuresBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

