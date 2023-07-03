// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "PlayerControllerPawn.h"
#include "GameFramework/Actor.h"
#include "Npc.generated.h"

UCLASS()
class RESTAURANTSIMULATOR_API ANpc : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANpc();
	
	UFUNCTION(BlueprintCallable, Category = "NpcOrderTake")
		void OrderTake();

	AActor* Pawn;
	AActor* GameManager;

	APlayerControllerPawn* PawnClass;
	AGameManager* GameManagerClass;

	int OrderFoodTag;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector TargetLocation;
	FRotator TargetRotation;

};
