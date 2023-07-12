// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TextActor.h"
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

	UPROPERTY(EditAnywhere)
		float Currency;
	
	float Profit;
	
	int OrderLenght;
	int MaxNpc;

	UPROPERTY(EditAnywhere)
		int DayCounter;
	
	int UnlockMeat;

	int Health;

	UPROPERTY(BlueprintReadOnly)
		FString dayText;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int DailyNpcSpawn;

	UFUNCTION(BlueprintCallable, Category = "NewDay")
		void NewDayFunction();

	UFUNCTION(BlueprintCallable, Category = "EndOfDay")
		bool EndOfDay(int NpcCounter, int dailyNpc);

	UFUNCTION(BlueprintCallable, Category = "EventFinish")
		void EventEnd();

	UFUNCTION()
		void EventFunctions(int Day);

	UFUNCTION(BlueprintCallable)
		FText NpcOrderQuoteFunction();

	UFUNCTION()
		void SpawnText(float Value, bool PositiveValue, FVector Location, FRotator3d Rotation, FVector Scale, FColor Color);

	UFUNCTION()
		void GameOverFunction(bool GameOver);
	
	UPROPERTY(EditAnywhere)
		TArray<USkeletalMesh*> SkeletalMeshs;

	UPROPERTY(EditAnywhere)
	TArray<USkeletalMesh*> EventSkeletalMeshs;

	USkeletalMesh* NpcSkeletalMesh;

	UPROPERTY(BlueprintReadWrite)
		bool Event;

	UPROPERTY(BlueprintReadOnly)
		bool NewDay;

	UPROPERTY(BlueprintReadOnly)
		bool eventNpcInteraction;

	UPROPERTY(BlueprintReadWrite)
		bool OptionDialogueContinue;

	UPROPERTY(BlueprintReadWrite)
		bool OptionDialogueChoose;

	UPROPERTY(BlueprintReadWrite)
		bool FireDay;

	UPROPERTY(BlueprintReadWrite)
		bool NpcCanOrder;

	UPROPERTY(EditAnywhere)
	TArray<bool>ControlIngredients;

	UPROPERTY(BlueprintReadWrite)
		bool GetFireEventOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool GameOver;

	bool GameOverSpawn;

	bool GameOverNpc;

	AActor* EventNpc;

	UPROPERTY(BlueprintReadOnly)
		TArray<FText> NpcDialogue;
	
	UPROPERTY(BlueprintReadOnly)
		TArray<FText> OptionChooseDialogue1;
	
	UPROPERTY(BlueprintReadOnly)
		TArray<FText> OptionChooseDialogue2;
	
	UPROPERTY(BlueprintReadOnly)
		TArray<FText> OptionChooseDialogue3;
	
	UPROPERTY(BlueprintReadOnly)
		TArray<FText> Option1;
	
	UPROPERTY(BlueprintReadOnly)
		TArray<FText> Option2;
	
	UPROPERTY(BlueprintReadOnly)
		TArray<FText> Option3;

	UPROPERTY(BlueprintReadOnly)
		TArray<FText> GetFoodNames;

	UPROPERTY(BlueprintReadOnly)
		FText NpcOrderQutoe;

	UPROPERTY(BlueprintReadOnly)
		FText CurrencyText;

	FText lastDialogue;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<UTexture2D*> HealthBarTextureArray;

	UPROPERTY(BlueprintReadOnly)
		UTexture2D* HealthBarTexture;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UClass* NpcSpawn;

	UPROPERTY(EditAnywhere)
		UClass* TextObject;
	
	ATextActor* TextActor;

	float CountDownTimer;
	float DeltaTimeCounter;

};
