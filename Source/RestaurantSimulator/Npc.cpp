
#include "Npc.h"

#include "Kismet/GameplayStatics.h"

ANpc::ANpc()
{
	PrimaryActorTick.bCanEverTick = true;

	IsMoving = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	
	RootComponent = SkeletalMesh;
	
	ProfitTextScale = FVector3d(1,1,1);

	PatienceTimer = 1.0f;

	GameOverNpc = false;
	
}

void ANpc::BeginPlay()
{
	Super::BeginPlay();

	Pawn = Cast<APlayerControllerPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerControllerPawn::StaticClass()));
	PawnClass = Cast<APlayerControllerPawn>(Pawn);

	GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
	GameManagerClass = Cast<AGameManager>(GameManager);

	SkeletalMesh->SetSkeletalMesh(GameManagerClass->NpcSkeletalMesh);

	GameOverNpc = GameManagerClass->GameOverNpc;
	TargetLocation = FVector3d(260, 820, 35);
	
	if(GameManagerClass->CounterNPC >= 1)
	{
		TargetLocation = FVector3d(TargetLocation.X + 150, 820, 35);
	}
	
	TargetRotation = FRotator3d(0,90,0);
	SetActorRotation(TargetRotation);

	OrderInitialize();
}

void ANpc::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(GameManagerClass->CounterNPC == 1)
	{
		TargetLocation = FVector3d(260, 820, 35);
	}//For objects to line up
	
	ToMoveObject(DeltaTime);

	IsMovingFunction();

	if(GetActorLocation().X <= 270 && GameManagerClass->NpcCanOrder == true && GameManagerClass->Event == true)
	{
		OrderToSetQuoteText();
	}

	if((280 <= GetActorLocation().X && GetActorLocation().X <= 430) && GameManagerClass->Event == true)
	{
		PatienceTimer -= DeltaTime / 30.0f;
		Inline = true;
	}
	else if(GetActorLocation().X <= 270 && GameManagerClass->Event == true)
	{
		PatienceTimer -= DeltaTime / 15.0f;
	}

	if(PatienceTimer <= 0 || (GameManagerClass->Health <= 0 && GameOverNpc == false))
	{
		PatienceOver();
	}
}

void ANpc::ToMoveObject(float DeltaTime)
{
	OldLocation = GetActorLocation().X;
	
	CurrentLocation = GetActorLocation();
	
	if(CurrentLocation.X >= TargetLocation.X)
	{
		Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
		NewLocation = CurrentLocation + (Direction * 300 * DeltaTime);
		SetActorLocation(NewLocation);	
	}
}


void ANpc::IsMovingFunction()
{
	if(OldLocation >= GetActorLocation().X && OldLocation >= TargetLocation.X + 10)
	{
		IsMoving = true;
	}
	else
	{
		IsMoving = false;
	}
}


void ANpc::OrderToSetQuoteText()
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


void ANpc::OrderControl()
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
}


void ANpc::OrderTake()
{
	OrderControl();
	
	if(PawnClass->takeAway == false && GameManagerClass->eventNpcInteraction == true && OrderReady == true && PawnClass->FoodTag == BreadOrPlate)
	{
		PawnClass->DestroyFoodObject();
		
		GameManagerClass->OrderQuoteReset();
		
		GameManagerClass->Currency += GameManagerClass->Profit;
		GameManagerClass->SpawnText(GameManagerClass->Profit, true , ProfitTextLocation, ProfitTextRotation, ProfitTextScale, FColor::Green);
		GameManagerClass->Profit = 0;
		
		GameManagerClass->CounterNPC--;
		this->Destroy();
	}
}

bool ANpc::IsNpcMoving()
{
	return IsMoving;
}

void ANpc::PatienceOver()
{
	GameManagerClass->OrderQuoteReset();
	
	GameManagerClass->Health--;
	UE_LOG(LogTemp, Error, TEXT("Health: %d"), GameManagerClass->Health);
	
	GameManagerClass->CounterNPC--;
	this->Destroy();
}

void ANpc::OrderInitialize()
{
	OrderFoodTag = FMath::RandRange(0, GameManagerClass->UnlockMeat);
	BreadOrPlate = FMath::RandRange(0,1);

	UE_LOG(LogTemp, Error, TEXT("%d"), BreadOrPlate);
	
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




