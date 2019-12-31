// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawner.h"
//#include "Engine.h" //massive header... Shouldn't need this

#include "Engine/World.h"


// Sets default values
AAISpawner::AAISpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAISpawner::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (World)
	{	//World is fine, VS is just silly.
		World->GetTimerManager().SetTimer(BotSpawnTimerHandle, this, &AAISpawner::SpawnBot, 1.0f, true, TimeBetweenSpawns);
	}
}

void AAISpawner::SpawnBot()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	if (BotList[0] == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Structure list empty?"));
		return;
	}

	AAICharacter* ActorSpawned = GetWorld()->SpawnActor<AAICharacter>(
									BotList[0],
									GetActorLocation() + FVector(0.0f, 0.0f, -50.0f),
									FRotator::ZeroRotator, SpawnParams);
	BotCount++;
	if (BotCount > 10)
	{
		GetWorld()->GetTimerManager().ClearTimer(BotSpawnTimerHandle);
		//BeginDestroy();
	}
}

// Called every frame
void AAISpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/*TimeSinceSpawn += DeltaTime;
	if (TimeSinceSpawn > TimeBetweenSpawns)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning"))
		TimeSinceSpawn = 0.0f;
	}*/

}

void AAISpawner::BeginDestroy()
{
	
	//GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	

	Super::BeginDestroy();
}



