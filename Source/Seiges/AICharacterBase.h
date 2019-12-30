// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacterBase.generated.h"

UCLASS(Blueprintable)
class SEIGES_API AAICharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacterBase();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = AIFunctions)
		class UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintCallable, Category = AIFunctions)
	void SetAITarget() {}; //TODO make this.


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UStaticMeshComponent* Mesh = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
