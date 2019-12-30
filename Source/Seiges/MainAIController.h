// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "StructureToDefend.h"
#include "MainAIController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SEIGES_API AMainAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMainAIController();

	virtual void OnPossess(APawn* InPawn) override;

	FBlackboard::FKey TargetKeyID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIProperties)
	UObject* TargetObject;

private:
	UBehaviorTreeComponent* BTComp;
	UBlackboardComponent* BBComp;
};
