// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAIController.h"
#include "AICharacterBase.h"
#include "BehaviorTree/BehaviorTree.h"

AMainAIController::AMainAIController()
{
	BTComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
	BBComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard Component"));
}

void AMainAIController::OnPossess(APawn * InPawn)
{
	if (InPawn != nullptr) {
		auto Character = Cast<AAICharacterBase>(InPawn);

		if (Character && Character->BehaviorTree)
		{
			BBComp->InitializeBlackboard(*Character->BehaviorTree->BlackboardAsset);
			TargetKeyID = BBComp->GetKeyID("Target"); //Key in black board.
			BTComp->StartTree(*Character->BehaviorTree);
		}
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("AI is getting no Pawn"));
	}
}
