// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AICharacter.h"
#include "StructureToDefend.h"
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

	//UPROPERTY()
	//TArray<UClass*> ActiveBotList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bots)
	float TimeBetweenSpawns;

	FTimerHandle BotSpawnTimerHandle;

	UFUNCTION()
	void SpawnBot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bots)
	UINT8 BotMaxCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bots)
	AActor* PlayerBase;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int BotCount = 0;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BeginDestroy() override;
};
