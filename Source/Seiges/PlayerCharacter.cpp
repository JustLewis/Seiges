// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "MainPlayerController.h"
#include "Components/InputComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter working"));
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	if (PlayerInputComponent) {

		PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

		PlayerInputComponent->BindAxis("LookPitch", this, &APlayerCharacter::LookPitch);
		PlayerInputComponent->BindAxis("LookYaw", this, &APlayerCharacter::LookYaw);

		PlayerInputComponent->BindAction("Action",IE_Pressed, this, &APlayerCharacter::TestAction);
		
		EnableInput(Cast<AMainPlayerController>(GetOwner()));

		UE_LOG(LogTemp, Error, TEXT("Setting up input?"));
	}
}

void APlayerCharacter::MoveForward(float speed)
{
	//UE_LOG(LogTemp, Error, TEXT("Moving forward?"));
	if (speed != 0)
	{
		AddMovementInput(GetActorForwardVector(), speed);
	}
}

void APlayerCharacter::MoveRight(float speed)
{
	if (speed != 0)
	{
		AddMovementInput(GetActorRightVector(), speed);
	}
}

void APlayerCharacter::LookPitch(float amount)
{
	AddControllerPitchInput(-amount);
}

void APlayerCharacter::LookYaw(float amount)
{
	AddControllerYawInput(amount);
}

void APlayerCharacter::TestAction()
{
	UE_LOG(LogTemp, Error, TEXT("Pressing action?"));
}