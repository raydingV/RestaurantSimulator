// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoodObject.h"
#include "GameFramework/Actor.h"
#include "InteractionActor.generated.h"

UCLASS()
class RESTAURANTSIMULATOR_API AInteractionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionActor();

	AActor* Pawn;

	APlayerControllerPawn* PawnClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	UClass* FoodObject;

	AActor* NewFoodObject;

	AFoodObject* FoodObjectClass;

	UPROPERTY(EditAnywhere)
		UStaticMesh* MeshFood;
	
	UFUNCTION(BlueprintCallable, Category = "FoodMaker")
		void FoodObjectCreate();

	UFUNCTION(BlueprintCallable, Category = "AnimationFood")
	void FoodMakeAnimation();

	UPROPERTY(EditAnywhere)
	int FoodTag;

	UPROPERTY(EditAnywhere)
		FVector3d FoodSpawnLocation;

	UPROPERTY(EditAnywhere)
		FRotator3d FoodSpawnRotation;

};
