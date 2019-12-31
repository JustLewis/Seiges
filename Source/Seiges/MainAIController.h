// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MainAIController.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = AI, BlueprintType, Blueprintable)
class SEIGES_API AMainAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMainAIController();

	virtual void OnPossess(APawn* InPawn) override;
	
	FBlackboard::FKey TargetKeyID;

	//UBlackboardComponent* GetBlackBoard(); //Don't need this

	void Jump();

	void SetOwnedCharacter(ACharacter* CharacterIn);

protected:

	ACharacter* OwnedCharacter;

	UBehaviorTreeComponent* BehaviorComponent;
	UBlackboardComponent* BlackBoardComponent;
	
};
