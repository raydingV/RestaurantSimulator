// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class RESTAURANTSIMULATOR_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int CounterNPC;
	
	int Money;
	int OrderLenght;
	int MaxNpc;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int DailyNpcSpawn;

	UFUNCTION(BlueprintCallable, Category = "NewDay")
		void NewDayFunction();

	UFUNCTION(BlueprintCallable, Category = "EndOfDay")
		bool EndOfDay(int DailyNpc, int NpcCounter);

	bool NewDay;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UClass* NpcSpawn;

	float CountDownTimer;

};
