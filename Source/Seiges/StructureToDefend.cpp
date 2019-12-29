// Fill out your copyright notice in the Description page of Project Settings.


#include "StructureToDefend.h"

// Sets default values
AStructureToDefend::AStructureToDefend()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStructureToDefend::BeginPlay()
{
	Super::BeginPlay();
	Mesh = FindComponentByClass<UStaticMeshComponent>();
	if(Mesh == nullptr){
UE_LOG(LogTemp,Error,TEXT("Main Base does not have static mesh"))}
}

// Called every frame
void AStructureToDefend::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

