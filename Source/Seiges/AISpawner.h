// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AISpawner.generated.h"

UCLASS(Blueprintable)
class SEIGES_API AAISpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISpawner();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Bots)
	TArray<UClass*> BotList;

	UPROPERTY()
	TArray<UClass*> ActiveBotList;

	UPROPERTY(EditAnywhere, BlueprintReadWRite, Category = Bots)
	float TimeBetweenSpawns;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float TimeSinceSpawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
