// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawner.h"
//#include "Engine.h" //massive header... Shouldn't need this

#include "Engine/World.h"
#include "MainAIController.h"
#include "EngineUtils.h"

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

	//https://wiki.unrealengine.com/Iterators:_Object_%26_Actor_Iterators,_Optional_Class_Scope_For_Faster_Search
	for (TActorIterator<AStructureToDefend> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AStructureToDefend* Structure = Cast<AStructureToDefend>(*ActorItr);

		if (Structure) 
		{
			UE_LOG(LogTemp, Warning, TEXT("Found structure %s "), *Structure->GetName())
			AActor* StructureActor = Cast<AActor>(Structure);

			if (StructureActor)
			{
				UE_LOG(LogTemp, Warning, TEXT("Structure was cast to Actor successfully."));
				PlayerBase = StructureActor;
			}
		}

	}

	if (World)
	{	//World is fine, VS is just silly.
		World->GetTimerManager().SetTimer(BotSpawnTimerHandle, this, &AAISpawner::SpawnBot, 1.0f, true, TimeBetweenSpawns);
	}
}

void AAISpawner::SpawnBot()
{
	if (BotCount < BotMaxCount)
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
		AMainAIController* ActorController = Cast<AMainAIController>(ActorSpawned->GetController());

		if (ActorController)
		{
			ActorController->Target = PlayerBase;
		}
		BotCount++;
	}
	else if (BotCount >= BotMaxCount)
	{
		//stops timer calling this function.
		GetWorld()->GetTimerManager().ClearTimer(BotSpawnTimerHandle);
		
		//Destroying this creates a tonne of nuisence in the debugger. #
		//"The requested operation could not be completed because the actor has invalid flags. (AISpawnerBP)"
		//Won't destroy for now.

		//ConditionalBeginDestroy();
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



