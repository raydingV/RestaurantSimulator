// Fill out your copyright notice in the Description page of Project Settings.


#include "Npc.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ANpc::ANpc()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsMoving = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	
	RootComponent = SkeletalMesh;
	
}

// Called when the game starts or when spawned
void ANpc::BeginPlay()
{
	Super::BeginPlay();

	Pawn = Cast<APlayerControllerPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerControllerPawn::StaticClass()));
	PawnClass = Cast<APlayerControllerPawn>(Pawn);

	GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
	GameManagerClass = Cast<AGameManager>(GameManager);

	SkeletalMesh->SetSkeletalMesh(GameManagerClass->NpcSkeletalMesh);
	
	TargetLocation = FVector3d(260, 820, 35);
	
	if(GameManagerClass->CounterNPC >= 1)
	{
		TargetLocation = FVector3d(TargetLocation.X + 150, 820, 35);
	}

	OrderFoodTag = FMath::RandRange(0, GameManagerClass->UnlockMeat);
	BreadOrPlate = FMath::RandRange(0,1);

	UE_LOG(LogTemp, Error, TEXT("%d"), BreadOrPlate);
	
	TargetRotation = FRotator3d(0,90,0);
	SetActorRotation(TargetRotation);

	OrderReady = false;

	switch (GameManagerClass->OrderLenght)
	{
		case 1:
			FoodOrder[0] = true;
			UE_LOG(LogTemp, Error, TEXT("Case1"));
			break;

		case 2:
			for(int i = 0; i < FoodOrder.Num() - 3; i++)
			{
				TrueOrFalse = FMath::RandRange(0,1);
				if(TrueOrFalse == 1)
				{
					FoodOrder[i] = true;	
				}
				else
				{
					FoodOrder[i] = false;
				}
			}
			if(BreadOrPlate == 0)
			{
				FoodOrder.Last() = false;
			}
			UE_LOG(LogTemp, Error, TEXT("Case2"));
			FoodOrder[0] = true;
			break;

		case 3:
			for(int i = 0; i < FoodOrder.Num() - 1; i++)
			{
				TrueOrFalse = FMath::RandRange(0,1);
				if(TrueOrFalse == 1)
				{
					FoodOrder[i] = true;	
				}
				else
				{
					FoodOrder[i] = false;
				}
			}
		UE_LOG(LogTemp, Error, TEXT("Case3"));
		if(OrderFoodTag == 0)
		{
			FoodOrder[0] = true;
			FoodOrder[5] = false;
		}
		else
		{
			FoodOrder[5] = true;
			FoodOrder[0] = false;
		}
		if(BreadOrPlate == 0)
		{
			FoodOrder.Last() = false;
		}
		break;

		case 4:
		for(int i = 0; i < FoodOrder.Num(); i++)
		{
			TrueOrFalse = FMath::RandRange(0,1);
			if(TrueOrFalse == 1)
			{
				FoodOrder[i] = true;	
			}
			else
			{
				FoodOrder[i] = false;
			}
		}
		UE_LOG(LogTemp, Error, TEXT("Case3"));
		if(OrderFoodTag == 0)
		{
			FoodOrder[0] = true;
			FoodOrder[5] = false;
		}
		else
		{
			FoodOrder[5] = true;
			FoodOrder[0] = false;
		}
		if(BreadOrPlate == 0)
		{
			FoodOrder.Last() = false;
		}
		break;
	}
	
}

// Called every frame
void ANpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(GameManagerClass->CounterNPC == 1)
	{
		TargetLocation = FVector3d(260, 820, 35);
	}

	OldLocation = GetActorLocation().X;

	CurrentLocation = GetActorLocation();
	
	if(CurrentLocation.X >= TargetLocation.X)
	{
		Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
		NewLocation = CurrentLocation + (Direction * 300 * DeltaTime);
		SetActorLocation(NewLocation);	
	}
	
	if(OldLocation >= GetActorLocation().X && OldLocation >= TargetLocation.X + 10)
	{
		IsMoving = true;
	}
	else
	{
		IsMoving = false;
	}

	if(GetActorLocation().X <= 270 && GameManagerClass->NpcCanOrder == true && GameManagerClass->Event == true)
	{
		if(BreadOrPlate == 0)
		{
			GameManagerClass->GetFoodNames.Add(FText::FromString("Wrap with"));
		}
		else
		{
			GameManagerClass->GetFoodNames.Add(FText::FromString("On Plate with"));
		}
	
		for (int i = 0; i < FoodOrder.Num(); i++)
		{
			if(FoodOrder[i] == true)
			{
				GameManagerClass->GetFoodNames.Add(FoodNames[i]);

			}
		}

		GameManagerClass->NpcCanOrder = false;
	}

}

void ANpc::OrderTake()
{
	for(int i = 0; i < FoodOrder.Num(); i++)
	{
		if(GameManagerClass->ControlIngredients[i] == FoodOrder[i])
		{
			OrderReady = true;
		}
		else
		{
			OrderReady = false;
			UE_LOG(LogTemp, Error, TEXT("OrderReady = false"));
			break;
		}
	}

	if(PawnClass->FoodTag == BreadOrPlate)
	{
		UE_LOG(LogTemp, Error, TEXT("FoodTag is True"));
	}
	
	if(PawnClass->takeAway == false && GameManagerClass->eventNpcInteraction == true && OrderReady == true && PawnClass->FoodTag == BreadOrPlate)
	{
		GameManagerClass->Money += 100;
		UE_LOG(LogTemp, Warning, TEXT("%d"), GameManagerClass->Money);

		
		TArray<AActor*> ChildActors;
		PawnClass->foodObject->GetAttachedActors(ChildActors);
		
		for (AActor* ChildActor : ChildActors)
		{
			ChildActor->Destroy();
		}

		for (int i = 0; i < GameManagerClass->ControlIngredients.Num(); i++)
		{
			GameManagerClass->ControlIngredients[i] = false;
		}
		
		PawnClass->foodObject->Destroy();
		
		PawnClass->CountFood--;
		GameManagerClass->CounterNPC--;
		GameManagerClass->GetFoodNames.Empty();
		GameManagerClass->GetFoodNames.SetNum(0);
		GameManagerClass->NpcOrderQutoe = FText::FromString("");
		GameManagerClass->NpcCanOrder = true;
		this->Destroy();
	}
}

bool ANpc::IsNpcMoving()
{
	return IsMoving;
}



