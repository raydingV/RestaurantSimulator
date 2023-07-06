// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "GameFramework/Actor.h"
#include "UnlockFood.generated.h"

UCLASS()
class RESTAURANTSIMULATOR_API AUnlockFood : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnlockFood();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;

	UFUNCTION(BlueprintCallable, Category = "UnlockNewFood")
		void UnlockFood(int day);

	UFUNCTION()
		void DisableActorRecursive(AActor* Actor, bool Hide);

	UPROPERTY(EditAnywhere)
	AActor* GameManager;

	AGameManager* GameManagerClass;
	
	UPROPERTY(EditAnywhere)
		int UnlockDay;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
