// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "MainPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"


#pragma region PlayerCharacter

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActionState = nullptr;

}

APlayerCharacter::~APlayerCharacter()
{
	delete ActionState;
	ActionState = 0;
	BeginDestroy();
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	ActionState = new WeaponState;

	MainCamera = FindComponentByClass<UCameraComponent>();
	if (!MainCamera) { UE_LOG(LogTemp, Error, TEXT("Main Camera is null pionter in %s"), *GetNameSafe(this)); }

	NozzleLocation = FindComponentByClass<UProjectileSpawnLocation>();
	if (!NozzleLocation) { UE_LOG(LogTemp, Error, TEXT("NozzleLocation is null pointer in %s"), *GetNameSafe(this)); }
	
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

	ActionState->Tick(this);

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
		
		PlayerInputComponent->BindAction("ScrollUp",IE_Pressed, this, &APlayerCharacter::ScrollUp);
		PlayerInputComponent->BindAction("ScrollDown",IE_Pressed, this, &APlayerCharacter::ScrollDown);

		PlayerInputComponent->BindAction("CycleMode", IE_Pressed, this, &APlayerCharacter::CycleMode);
		
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
	//if (bRotationEnabled) {
		AddControllerPitchInput(-amount);
	//}
}

void APlayerCharacter::LookYaw(float amount)
{
	if (bRotationEnabled)
	{
		AddControllerYawInput(amount);
	}
	ActionState->Rotate(this,amount);
}

void APlayerCharacter::Action()
{
	MyPlayerState * state = ActionState->Action(this);
	if (state != NULL)
	{
		delete ActionState;
		ActionState = state;
	}
	
}

void APlayerCharacter::AltAction()
{
	MyPlayerState * state = ActionState->AltAction(this);
	if (state != NULL)
	{
		delete ActionState;
		ActionState = state;
	}
}

void APlayerCharacter::ScrollUp()
{
	ActionState->ScrollUp(this);
}

void APlayerCharacter::ScrollDown()
{
	ActionState->ScrollDown(this);
}

void APlayerCharacter::CycleMode()
{
	MyPlayerState * state = ActionState->CycleMode();
	if (state != NULL)
	{
		delete ActionState;
		ActionState = state;
	}
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

	CollisionParams.AddIgnoredActor(ControlledStructure);

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

void APlayerCharacter::IncrementStuctureIterator(bool bIsPositiveIncrement)
{
	if (bIsPositiveIncrement) 
	{
		StructureIterator++;
		if (!StructureList.IsValidIndex(StructureIterator))
		{
			StructureIterator = 0;
			return;
		}
	}
	else
	{
		StructureIterator--;
		if (!StructureList.IsValidIndex(StructureIterator))
		{
			StructureIterator = StructureList.Num() - 1; //Last index range
			return;
		}
	}
}

void APlayerCharacter::SetControlledStructure(AStructuresBase * ActorIn)
{
	ControlledStructure = ActorIn;
}

AStructuresBase * APlayerCharacter::GetControlledStructure()
{
	return ControlledStructure;
}

#pragma endregion

#pragma region WeaponState

MyPlayerState * WeaponState::Action(APlayerCharacter* PlayerIn)
{
	bFiring = true;
	PlayerIn->NozzleLocation->SetFiring(true);
	return nullptr;
}

MyPlayerState * WeaponState::AltAction(APlayerCharacter* PlayerIn)
{
	bFiring = false;
	PlayerIn->NozzleLocation->SetFiring(false);
	return nullptr;
}

MyPlayerState * WeaponState::CycleMode()
{
	return new BuildState;
}

void WeaponState::Tick(APlayerCharacter * PlayerIn)
{
	//if (bFiring)
	//{
	//	//PlayerIn->NozzleLocation->SpawnProjectileWithVelocity(1000.0f);


	//	/*UWorld * World = PlayerIn->GetWorld();
	//	if (World != NULL)
	//	{
	//		const FRotator PlayerRotation = PlayerIn->GetControlRotation();
	//		const FVector Playerlocation = PlayerIn->MainCamera->GetComponentLocation() + FVector(0.0f,50.0f,0.0f);
	//		float SprayAmount = PlayerIn->SprayAmount;
	//		for (size_t i = 0; i < 3; i++) {

	//			float XOffset = FMath::FRandRange(-SprayAmount, SprayAmount);
	//			float YOffset = FMath::FRandRange(-SprayAmount, SprayAmount);

	//			FActorSpawnParameters ActorSpawnParams;
	//			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	//			World->SpawnActor<ABaseProjectile>(PlayerIn->Projectile, Playerlocation +
	//				(PlayerIn->MainCamera->GetComponentRotation().Vector() * 10.0f), PlayerRotation + FRotator(XOffset, YOffset, 0.0f), ActorSpawnParams);
	//		}
	//	}*/
	//}
}


#pragma endregion

#pragma region BuildState

MyPlayerState * BuildState::Action(APlayerCharacter* PlayerIn)
{
	DrawDebugSphere(PlayerIn->GetWorld(), PlayerIn->LineTraceHitResult().Location, 5.0f, 10, FColor::Red, false, 3.0f);

	/*FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = NULL;

	if (PlayerIn->StructureList[PlayerIn->GetStructureIterator()] == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Structure list empty?"));
		return new BuildState; 
	}

	AStructuresBase* ActorSpawned =  PlayerIn->GetWorld()->SpawnActor<AStructuresBase>(
								PlayerIn->StructureList[PlayerIn->GetStructureIterator()],
								PlayerIn->LineTraceHitResult().Location + FVector(0.0f, 0.0f, 1.0f),
								FRotator::ZeroRotator, SpawnParams);
	PlayerIn->SetControlledStructure(ActorSpawned);*/
	
	PlayerIn->bRotationEnabled = false;

	return new BuildStateSecond;
}

MyPlayerState * BuildState::AltAction(APlayerCharacter* PlayerIn)
{
	AActor* HitActor = PlayerIn->LineTraceHitResult().GetActor();

	if (HitActor)
	{
		//Unusual way to deal damage
		TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent DamageEvent(ValidDamageTypeClass);

		HitActor->TakeDamage(1000.0f, DamageEvent, PlayerIn->GetController(), PlayerIn);
	}
	else { UE_LOG(LogTemp, Warning, TEXT("Not hit actor")) }

	return nullptr;
}

MyPlayerState * BuildState::CycleMode()
{
	return new WeaponState;
}

//TODO this is causing a crash.
void BuildState::Tick(APlayerCharacter * PlayerIn)
{
	AStructuresBase* Structure = PlayerIn->GetControlledStructure();
	if (Structure == nullptr)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = NULL;

		if (PlayerIn->StructureList[PlayerIn->GetStructureIterator()] == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Structure list empty?"));//Spam much?
			return;
		}

		AStructuresBase* ActorSpawned = PlayerIn->GetWorld()->SpawnActor<AStructuresBase>(
			PlayerIn->StructureList[PlayerIn->GetStructureIterator()],
			PlayerIn->LineTraceHitResult().Location + FVector(0.0f, 0.0f, 1.0f),
			FRotator::ZeroRotator, SpawnParams);
		PlayerIn->SetControlledStructure(ActorSpawned);
	}
	else
	{
		Structure->SetActorLocation(PlayerIn->LineTraceHitResult().Location, false, nullptr, ETeleportType::None);
	}

}
void BuildState::ScrollUp(APlayerCharacter * PlayerIn)
{
	PlayerIn->IncrementStuctureIterator(true);

	AStructuresBase* Structure = PlayerIn->GetControlledStructure();
	if (!Structure)
	{
		UE_LOG(LogTemp, Error, TEXT("No controlled structure found"));
		PlayerIn->bRotationEnabled = true;
		return;
	}

	PlayerIn->SetControlledStructure(nullptr);

	//Destroy structure
	TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
	FDamageEvent DamageEvent(ValidDamageTypeClass);
	Structure->TakeDamage(1000.0f, DamageEvent, PlayerIn->GetController(), PlayerIn);

}
void BuildState::ScrollDown(APlayerCharacter * PlayerIn)
{
	PlayerIn->IncrementStuctureIterator(true);

	AStructuresBase* Structure = PlayerIn->GetControlledStructure();
	if (!Structure)
	{
		UE_LOG(LogTemp, Error, TEXT("No controlled structure found"));
		PlayerIn->bRotationEnabled = true;
		return;
	}

	PlayerIn->SetControlledStructure(nullptr);

	//Destroy structure
	TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
	FDamageEvent DamageEvent(ValidDamageTypeClass);
	Structure->TakeDamage(1000.0f, DamageEvent, PlayerIn->GetController(), PlayerIn);
}
#pragma endregion

#pragma region BuildStateSecond

MyPlayerState * BuildStateSecond::Action(APlayerCharacter * PlayerIn)
{
	AStructuresBase* Structure = PlayerIn->GetControlledStructure();
	if (Structure != nullptr)
	{
	Structure->Activate();
	}

	PlayerIn->SetControlledStructure(nullptr);
	PlayerIn->bRotationEnabled = true;
	return new BuildState;
}

MyPlayerState * BuildStateSecond::AltAction(APlayerCharacter * PlayerIn)
{
	AStructuresBase* Structure = PlayerIn->GetControlledStructure();
	if (!Structure)
	{
		UE_LOG(LogTemp, Error, TEXT("No controlled structure found"));
		PlayerIn->bRotationEnabled = true;
		return new BuildState;
	}
	
	PlayerIn->SetControlledStructure(nullptr);

	//Destroy structure
	TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
	FDamageEvent DamageEvent(ValidDamageTypeClass);
	Structure->TakeDamage(1000.0f, DamageEvent, PlayerIn->GetController(), PlayerIn);

	PlayerIn->bRotationEnabled = true;
	
	return new BuildState;
}

MyPlayerState * BuildStateSecond::CycleMode()
{
	return new BuildState;
}

void BuildStateSecond::Rotate(APlayerCharacter* PlayerIn,float amount)
{
	AStructuresBase* Structure = PlayerIn->GetControlledStructure();
	if (Structure)
	{
		//Structure->SetActorRotation(FQuat(0, 0, amount / 3, 1));
		Structure->AddActorWorldRotation(FQuat(0, 0, amount / 3, 1), false, nullptr, ETeleportType::None);
		return;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No controlled structure found"));
	}
}

#pragma endregion