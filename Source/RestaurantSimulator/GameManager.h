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
	
	FActorSpawnParameters SpawnParams;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int CounterNPC;
	
	int Money;
	int OrderLenght;
	int MaxNpc;
	int DayCounter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int DailyNpcSpawn;

	UFUNCTION(BlueprintCallable, Category = "NewDay")
		void NewDayFunction();

	UFUNCTION(BlueprintCallable, Category = "EndOfDay")
		bool EndOfDay(int NpcCounter, int dailyNpc);

	UFUNCTION()
		void EventFunctions(int Day);

	UPROPERTY(EditAnywhere)
		TArray<USkeletalMesh*> SkeletalMeshs;

	UPROPERTY(EditAnywhere)
	TArray<USkeletalMesh*> EventSkeletalMeshs;

	USkeletalMesh* NpcSkeletalMesh;
	
	bool Event;
	bool NewDay;

	AActor* EventNpc;
	
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
