// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoodObject.h"
#include "IngredientObject.h"
#include "PlayerControllerPawn.h"
#include "GameFramework/Actor.h"
#include "GameManager.h"
#include "IngredientActor.generated.h"

UCLASS()
class RESTAURANTSIMULATOR_API AIngredientActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIngredientActor();

	UPROPERTY(EditAnywhere)
	AActor* GameManager;
	AGameManager* GameManagerClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool HaveAnimation;
	
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UStaticMesh* SpawnMesh;

	AActor* FoodObjectActor;
	AFoodObject* FoodObjectClass;

	AActor* PawnActor;
	APlayerControllerPawn* PawnClass;

	FActorSpawnParameters SpawnParameters;
	
	AActor* NewSpawnObject;

	UPROPERTY(EditAnywhere)
	 UClass* IngredientObject;

	AIngredientObject* IngredientClass;

	UFUNCTION(BlueprintCallable, Category = "FoodToIngredient")
		void AddInFood();

	UPROPERTY(EditAnywhere)
		FRotator3d NewSpawnRotator;

	UPROPERTY(EditAnywhere)
		FVector3d NewSpawnLocation;

	UPROPERTY(EditAnywhere)
		FVector3d ScaleSpawn;

	UPROPERTY(EditAnywhere)
		int thisFoodTag;

	UPROPERTY(BlueprintReadWrite)
		bool InputEnable;

	UPROPERTY(BlueprintReadWrite)
		bool AnimationFinish;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
