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

	UFUNCTION(BlueprintCallable, Category = "MovementControl")
		bool IsNpcMoving();

	UFUNCTION()
		void PatienceOver();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;

	AActor* Pawn;
	AActor* GameManager;

	APlayerControllerPawn* PawnClass;
	AGameManager* GameManagerClass;

	int OrderFoodTag;
	int TrueOrFalse;
	int BreadOrPlate;

	FVector CurrentLocation;
	FVector Direction;
	FVector NewLocation;

	UPROPERTY(EditAnywhere)
	FVector3d ProfitTextLocation;

	UPROPERTY(EditAnywhere)
	FRotator3d ProfitTextRotation;

	UPROPERTY(EditAnywhere)
	FVector ProfitTextScale;

	float OldLocation;

	UPROPERTY(BlueprintReadOnly)
		float PatienceTimer;

	bool IsMoving;

	UPROPERTY(BlueprintReadOnly)
		bool Inline;

	bool OrderReady;

	bool GameOverNpc;

	UPROPERTY(EditAnywhere)
		TArray<bool>FoodOrder;

	UPROPERTY(EditAnywhere)
		TArray<FText>FoodNames;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	FVector TargetLocation;
	
	FRotator TargetRotation;

};
