// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "MainPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"

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

	MainCamera = FindComponentByClass<UCameraComponent>();
	if (!MainCamera) { UE_LOG(LogTemp, Error, TEXT("Main Camera is null pionter in %s"), *GetNameSafe(this)); }
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DrawDebugLine(GetWorld(),
		LineTraceStart(),
		LineTraceEnd(),
		FColor::Red,
		false,
		-1.0f,
		1.0f);

	
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

		PlayerInputComponent->BindAction("Action",IE_Pressed, this, &APlayerCharacter::Action);
		PlayerInputComponent->BindAction("AltAction",IE_Pressed, this, &APlayerCharacter::AltAction);
		
		PlayerInputComponent->BindAction("ScrollUp",IE_Pressed, this, &APlayerCharacter::CycleStructureListUp);
		PlayerInputComponent->BindAction("ScrollDown",IE_Pressed, this, &APlayerCharacter::CycleStructureListDown);

		
		EnableInput(Cast<AMainPlayerController>(GetOwner()));

		
	}
	else { UE_LOG(LogTemp, Error, TEXT("Setting up input failed for: %s"), *GetNameSafe(this)); }
}

void APlayerCharacter::MoveForward(float speed)
{
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

void APlayerCharacter::Action()
{
	//FString Text = StructureList[StructureIterator]->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("STructure is %s"), *Text);

	//DrawDebugLine(GetWorld(),
	//	LineTraceStart(),
	//	LineTraceEnd(),
	//	FColor::Red,
	//	false,
	//	-1.0f,
	//	1.0f);
	DrawDebugSphere(GetWorld(), LineTraceHitResult().Location, 5.0f, 10, FColor::Red, false, 3.0f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = NULL;
	
	
	if (StructureList[StructureIterator] == nullptr) { UE_LOG(LogTemp, Error, TEXT("Structure list empty?")); return; }
	GetWorld()->SpawnActor<AStructuresBase>(StructureList[StructureIterator], LineTraceHitResult().Location + FVector(0.0f,0.0f,10.0f), FRotator::ZeroRotator,SpawnParams);

}

void APlayerCharacter::AltAction()
{
	AActor* HitActor = LineTraceHitResult().GetActor();

	if (HitActor)
	{
		TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent DamageEvent(ValidDamageTypeClass);

		HitActor->TakeDamage(1000.0f, DamageEvent, this->GetController(),this);
	}
	else { UE_LOG(LogTemp, Warning, TEXT("Not hit actor")) }
}

void APlayerCharacter::CycleStructureListUp()
{
	StructureIterator++;
	if(!StructureList.IsValidIndex(StructureIterator))
	{
		StructureIterator = 0;
	}
	ChangeActiveStructure();
}

void APlayerCharacter::CycleStructureListDown()
{
	StructureIterator--;
	if (!StructureList.IsValidIndex(StructureIterator))
	{
		StructureIterator = StructureList.Num() - 1; //Last index range
	}
	ChangeActiveStructure();
}

void APlayerCharacter::ChangeActiveStructure()
{
	//doesn't do anything yet.
}

FVector APlayerCharacter::LineTraceStart()
{
	if (MainCamera == nullptr) { return FVector(0.0f); }
	return MainCamera->GetComponentLocation();
}

FVector APlayerCharacter::LineTraceEnd()
{
	if (MainCamera == nullptr) { return FVector(0.0f); }
	return MainCamera->GetComponentLocation() + (MainCamera->GetComponentRotation().Vector() * Reach);
}

FHitResult APlayerCharacter::LineTraceHitResult()
{	
	FHitResult LineTraceHit;
	FCollisionQueryParams CollisionParams (FName(TEXT("")), false, this);

	/*GetWorld()->LineTraceSingleByObjectType(
		LineTraceHit,
		LineTraceStart(),
		LineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		CollisionParams);*/

	GetWorld()->LineTraceSingleByChannel(
		LineTraceHit,
		LineTraceStart(),
		LineTraceEnd(),
		ECollisionChannel::ECC_WorldStatic,
		CollisionParams);

	return LineTraceHit;

}
