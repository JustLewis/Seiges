// Fill out your copyright notice in the Description page of Project Settings.


#include "StructureControlled.h"

AStructureControlled::AStructureControlled()
{
	//AStructuresBase(); //is this correct?
}

void AStructureControlled::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp,Warning,TEXT("Yay I'm a controlled structure and working too!"))
}
