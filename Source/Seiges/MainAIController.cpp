// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAIController.h"
//#include "BehaviorTree/BehaviorTree.h"
#include "AICharacter.h"
#include "StructureToDefend.h"

AMainAIController::AMainAIController()
{
	BehaviorComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior componenet"));
	BlackBoardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard Component"));

}

void AMainAIController::OnPossess(APawn * InPawn)
{
	
	Super::OnPossess(InPawn);


	AAICharacter* ControlledCharacter = Cast<AAICharacter>(InPawn);

	if (InPawn != nullptr)
	{
		BlackBoardComponent->InitializeBlackboard(*(ControlledCharacter->BehaviorTree->BlackboardAsset));//Hope this works
		TargetKeyID = BlackBoardComponent->GetKeyID("TheTarget");
		BehaviorComponent->StartTree(*(ControlledCharacter->BehaviorTree)); //This is a weird use of pointers. 
	}
	else {
		UE_LOG(LogTemp,Error,TEXT("InPawn is Nullptr"))
	}

}

void AMainAIController::Jump()
{
	if (OwnedCharacter) 
	{
	OwnedCharacter->Jump();
	}
}

void AMainAIController::SetOwnedCharacter(ACharacter * CharacterIn)
{
	if (CharacterIn) 
	{
		OwnedCharacter = CharacterIn;
	}
}

//UBlackboardComponent * AMainAIController::GetBlackBoard()
//{
//	return BlackBoardComponent;
//}
