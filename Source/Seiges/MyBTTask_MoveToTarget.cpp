// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_MoveToTarget.h"
#include "MainAIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

EBTNodeResult::Type
UMyBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMainAIController* ControlledAI = Cast<AMainAIController>(OwnerComp.GetAIOwner());

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if(ControlledAI == nullptr) {UE_LOG(LogTemp,Error,TEXT("Move To Target Tasknode Ownercomp cast is null pointer"))}
	else
	{
		AActor* Target = Cast<AActor>(Blackboard->GetValue<UBlackboardKeyType_Object>(ControlledAI->TargetKeyID));
		if (Target)
		{
			ControlledAI->Jump();
			ControlledAI->MoveToActor(Target, 5.0f);
		
			
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}