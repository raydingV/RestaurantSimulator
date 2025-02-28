// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodObject.h"

#include "PlayerControllerPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFoodObject::AFoodObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AFoodObject::BeginPlay()
{
	Super::BeginPlay();
	pawn = Cast<APlayerControllerPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerControllerPawn::StaticClass()));
	pawnClass = Cast<APlayerControllerPawn>(pawn);
}

// Called every frame
void AFoodObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFoodObject::TakeFood()
{
	if(pawn != nullptr && pawnClass->takeAway)
	{
		// SetActorLocation(FVector3d(pawn->GetActorLocation().X + 100, pawn->GetActorLocation().Y, pawn->GetActorLocation().Z - 30 ));
		this->AttachToActor(pawn, FAttachmentTransformRules::KeepWorldTransform);
		SetActorRelativeLocation(FVector3d(70,-40,-35));
		SetActorRotation(FRotator(0,0,0));
		pawnClass->foodObject = this;
		pawnClass->FoodTag = FoodTag;
		pawnClass->CountFood++;
	}
}

void AFoodObject::ReleaseFood(FKey key)
{
	FString keyPressed = (key.GetDisplayName()).ToString();

	// if(keyPressed == "F")
	// {
	// 	pawnClass->CountFood--;
	//
	// 	this->Destroy();
	// }
}

void AFoodObject::IngredientAdderFunction(AActor* actor, FVector3d newSpawnLocation)
{
	// Ingredient = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	// foodObject.Add(Ingredient);
	// foodObject.Last()->SetStaticMesh(Ingredient->GetStaticMesh());

	actor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	actor->SetActorRelativeLocation(FVector3d(0 + newSpawnLocation.X,0 + newSpawnLocation.Y,0 + newSpawnLocation.Z));
}




