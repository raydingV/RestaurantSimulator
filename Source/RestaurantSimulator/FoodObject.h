// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerPawn.h"
#include "GameFramework/Actor.h"
#include "FoodObject.generated.h"

UCLASS()
class RESTAURANTSIMULATOR_API AFoodObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodObject();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere)
		TArray<UStaticMeshComponent*> foodObject;

	UFUNCTION(BlueprintCallable, Category = "FoodInteraction")
		void TakeFood();

	UFUNCTION(BlueprintCallable, Category = "FoodRelease")
		void ReleaseFood(FKey key);

	UPROPERTY(EditAnywhere)
		AActor* pawn;

	APlayerControllerPawn* pawnClass;

	int FoodTag;
	
	void IngredientAdderFunction(AActor* actor, FVector3d newSpawnLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
