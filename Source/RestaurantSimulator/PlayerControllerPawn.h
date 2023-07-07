// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameManager.h"
#include "PlayerControllerPawn.generated.h"


UCLASS()
class RESTAURANTSIMULATOR_API APlayerControllerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerControllerPawn();

	UFUNCTION(BlueprintCallable, Category = "PlayerInput")
		void CameraInput(float rotation);

	UPROPERTY(EditAnywhere)
		float rotationSpeed;

	AActor* foodObject;

	int FoodTag;

	float currentTime;
	float targetRotationZ;
	
	FRotator NewRotation;
	FRotator StartRotation;
	FRotator TargetRotation;

	bool newRotationSet;
	bool takeAway;

	int CountFood;
	
	AActor* GameManager;
	AGameManager* GameManagerClass;

	bool InputEnable;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
