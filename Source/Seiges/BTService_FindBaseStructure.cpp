// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindBaseStructure.h"
#include "Engine/World.h"
#include "MainAIController.h"
#include "StructureToDefend.h"


UBTService_FindBaseStructure::UBTService_FindBaseStructure()
{
	bCreateNodeInstance = true;
}

void UBTService_FindBaseStructure::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto AIController = Cast<AMainAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		auto DefendedStructure = AIController->TargetObject;

		OwnerComp.GetBlackboardComponent()->SetValueAsObject("MainTarget"/*AIController->TargetKeyID*/, DefendedStructure);
		UE_LOG(LogTemp, Warning, TEXT("Target has been set for AI"));
	}
}
