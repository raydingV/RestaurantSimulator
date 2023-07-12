// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "TextActor.generated.h"

UCLASS()
class RESTAURANTSIMULATOR_API ATextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATextActor();

	UTextRenderComponent* TextObject;

	FVector TargetLocation;
	FVector CurrentLocation;
	FVector Direction;
	FVector NewLocation;

	float Value;
	FVector Scale;

	FColor TextColor;

	bool PositiveValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
