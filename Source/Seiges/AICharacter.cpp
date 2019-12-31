// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "MainAIController.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	AMainAIController* Controller = Cast<AMainAIController>(GetController());
	Controller->SetOwnedCharacter(this);
}

void AAICharacter::Jump()
{
	ACharacter::Jump();
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	///Simple movement ai
	/*auto StartPos = GetActorLocation();
	FVector PlayerPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	FVector Direction = PlayerPos - StartPos;
	Direction.Normalize();

	SetActorLocation(StartPos + Direction);
*/
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

