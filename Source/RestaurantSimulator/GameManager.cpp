// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Event = false;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	CounterNPC = 0;
	Money = 0;
	OrderLenght = 0;
	MaxNpc = 6;
	DailyNpcSpawn = MaxNpc;
	NewDay = false;
	DayCounter = 1;
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	EventFunctions(DayCounter);
	
	CountDownTimer -= DeltaTime * 300;

	if(CounterNPC >= 2)
	{
		CountDownTimer = 1000.0f;
	}
	
	if (NpcSpawn != nullptr && CountDownTimer <= 0 && DailyNpcSpawn > 0 && Event == true)
	{
		NpcSkeletalMesh = SkeletalMeshs[FMath::RandRange(0,SkeletalMeshs.Num() - 1)];
		GetWorld()->SpawnActor<AActor>(NpcSpawn, GetActorLocation() , GetActorRotation(), SpawnParams);
		CountDownTimer = 1000.0f;
		CounterNPC++;
		DailyNpcSpawn--;
	}
}

void AGameManager::NewDayFunction()
{
	MaxNpc += 1;
	DailyNpcSpawn = MaxNpc;
	UE_LOG(LogTemp, Warning, TEXT("New Day!!!!"));
	NewDay = false;
}

bool AGameManager::EndOfDay(int NpcCounter, int dailyNpc)
{
	if(dailyNpc <= 0 && NpcCounter <= 0)
	{
		NewDay = true;
	}
	
	return NewDay;
}

void AGameManager::EventFunctions(int Day)
{
	switch (Day)
	{
		case 1:
			if(CounterNPC <= 0 && Event == false)
			{
				Event = true;
				NpcSkeletalMesh = EventSkeletalMeshs[0];
				EventNpc = GetWorld()->SpawnActor<AActor>(NpcSpawn, GetActorLocation() , GetActorRotation(), SpawnParams);
				CounterNPC++;
				EventNpc->Destroy();
				CounterNPC--;
			}
		break;
	}
}




