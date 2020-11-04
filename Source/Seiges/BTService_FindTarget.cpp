// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindTarget.h"
#include "MainAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTService_FindTarget::UBTService_FindTarget()
{
	bCreateNodeInstance = true;
}

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AMainAIController* AIController = Cast<AMainAIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		//APawn* TargetActor = GetWorld()->GetFirstPlayerController()->GetPawn();
		AActor* TargetActor = AIController->Target;
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(AIController->TargetKeyID, TargetActor);
		if (TargetActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Ai has choosen target; %s"), *TargetActor->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Ai has null pointer as target"));
		}
	}

}
