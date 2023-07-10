// Fill out your copyright notice in the Description page of Project Settings.


#include "IngredientActor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AIngredientActor::AIngredientActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	InputEnable = true;
	AnimationFinish = false;
}

// Called when the game starts or when spawned
void AIngredientActor::BeginPlay()
{
	Super::BeginPlay();

	PawnActor = Cast<APlayerControllerPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerControllerPawn::StaticClass()));
	PawnClass = Cast<APlayerControllerPawn>(PawnActor);

	GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));
	GameManagerClass = Cast<AGameManager>(GameManager);
}

// Called every frame
void AIngredientActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(HaveAnimation == true && InputEnable == false)
	{
		PawnClass->InputEnable = InputEnable;

		if(IsDonerAnim == true)
		{
			PawnClass->TargetRotation = FRotator(GetActorRotation().Pitch, -90, GetActorRotation().Roll);
			PawnClass->newRotationSet = true;
		}
		else
		{
			PawnClass->TargetRotation = FRotator(GetActorRotation().Pitch, 90, GetActorRotation().Roll);
			PawnClass->newRotationSet = true;
		}
	}

	if(AnimationFinish == true)
	{
		AnimationFinish = false;
		InputEnable = true;
		PawnClass->InputEnable = InputEnable;
	}
	
	takeAway = PawnClass->takeAway;
	
}

void AIngredientActor::AddInFood()
{
	FoodObjectActor = PawnClass->foodObject;
	GameManagerClass->ControlIngredients[thisFoodTag] = true;

	if(FoodObjectActor != nullptr)
	{
		FoodObjectClass = Cast<AFoodObject>(FoodObjectActor);	
	}

	if(FoodObjectClass != nullptr)
	{
		NewSpawnObject = GetWorld()->SpawnActor<AActor>(IngredientObject, GetActorLocation(), GetActorRotation(), SpawnParameters);
		NewSpawnObject->SetActorScale3D(ScaleSpawn);
		IngredientClass = Cast<AIngredientObject>(NewSpawnObject);
		IngredientClass->Mesh->SetStaticMesh(SpawnMesh);
		FoodObjectClass->IngredientAdderFunction(NewSpawnObject, NewSpawnLocation);

		if(PawnClass->FoodTag == 0)
		{
			NewSpawnObject->SetActorRotation(NewSpawnRotator);
		}
	}
}


