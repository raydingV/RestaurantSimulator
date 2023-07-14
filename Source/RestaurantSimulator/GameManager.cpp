
// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

// Sets default values
AGameManager::AGameManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Event = true;

	// 
	DayCounter = 1;
	Currency = 100;
	
	Health = 3;
	UnlockMeat = 0;
	
	Profit = 0;
	OrderLenght = 1;
	
	MaxNpc = 6;
	CounterNPC = 0;
	DailyNpcSpawn = MaxNpc;

	GameOver = false;
	GameOverSpawn = false;
	
	NewDay = false;
	FireDay = false;
	
	eventNpcInteraction = true;
	OptionDialogueContinue = false;

	NpcCanOrder = true;
	GetFireEventOne = true;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CountDownTimer -= DeltaTime * 300;
	
	if(Health <= 0)
	{
		GameOver = true;
	}
	else
	{
		if(Currency <= 0)
		{
			GameOver = true;
		}
		else if(Currency >= 0)
		{
			GameOver = false;
		}
	}
	
	if (CountDownTimer <= 0)
	{
		EventFunctions(DayCounter);
		
		GameOverFunction(GameOver);	
	}
	
	if (CounterNPC >= 2)
	{
		CountDownTimer = 1000.0f;
	}

	if (NpcSpawn != nullptr && CountDownTimer <= 0 && DailyNpcSpawn > 0 && Event == true && Health > 0)
	{
		SpawnNPC(NULL, true, false);
		CountDownTimer = 1000.0f;
	}

	if(NewDay == true && DayCounter == 5 && OptionDialogueChoose == true && GameOver == false)
	{
		FireDay = true;
	}
	
	dayText = FString::Printf(TEXT("Day %d"), DayCounter + 1);

	CurrencyText = FText::Format(FText::FromString("{0} $"), FText::AsNumber(Currency));

	if(Health <= 0)
	{
		HealthBarTexture = HealthBarTextureArray[0];
	}
	else
	{
		HealthBarTexture = HealthBarTextureArray[Health];
	}
}

void AGameManager::SpawnNPC(int MeshNpcArrayValue, bool Random, bool IsEventNpc)
{
	if(Random == true)
	{
		NpcSkeletalMesh = SkeletalMeshs[FMath::RandRange(0, SkeletalMeshs.Num() - 1)];	
	}
	else
	{
		NpcSkeletalMesh = EventSkeletalMeshs[MeshNpcArrayValue];
	}

	if(IsEventNpc == true)
	{
		EventNpc = GetWorld()->SpawnActor<AActor>(NpcSpawn, GetActorLocation(), GetActorRotation(), SpawnParams);	
	}
	else
	{
		GetWorld()->SpawnActor<AActor>(NpcSpawn, GetActorLocation(), GetActorRotation(), SpawnParams);
	}
	
	CounterNPC++;
	DailyNpcSpawn--;
	UE_LOG(LogTemp, Error, TEXT("DailyNpc: %d"), DailyNpcSpawn);
}

void AGameManager::NewDayFunction()
{
	if(MaxNpc < 8)
	{
		MaxNpc += 1;	
	}
	
	DailyNpcSpawn = MaxNpc;
	UE_LOG(LogTemp, Error, TEXT("New Day!!!!"));
	NewDay = false;
	DayCounter++;
}

bool AGameManager::EndOfDay(int NpcCounter, int dailyNpc)
{
	if (dailyNpc <= 0 && NpcCounter <= 0)
	{
		NewDay = true;
	}
	return NewDay;
}

void AGameManager::DialogueReset()
{
	NpcDialogue.Empty();
	NpcDialogue.SetNum(0);
	OptionChooseDialogue1.Empty();
	OptionChooseDialogue1.SetNum(0);
	OptionChooseDialogue2.Empty();
	OptionChooseDialogue2.SetNum(0);
	OptionChooseDialogue3.Empty();
	OptionChooseDialogue3.SetNum(0);
	Option1.Empty();
	Option1.SetNum(0);
	Option2.Empty();
	Option2.SetNum(0);
	Option3.Empty();
	Option3.SetNum(0);
}


void AGameManager::EventEnd()
{
	Event = true;
	eventNpcInteraction = true;
	CounterNPC = 0;
	DialogueReset();
	EventNpc->Destroy();
}

FText AGameManager::NpcOrderQuoteFunction()
{
	if (Event && GetFoodNames.Num() > 0)
	{
		FString FormattedString;
		
		for (int i = 0; i < GetFoodNames.Num(); i++)
		{
			FString FoodName = GetFoodNames[i].ToString();
			FormattedString += FString::Printf(TEXT(" %s"), *FoodName);
		}

		NpcOrderQutoe = FText::FromString(FormattedString);
	}

	return NpcOrderQutoe;
}

void AGameManager::SpawnText(float Value, bool PositiveValue ,FVector Location, FRotator3d Rotation, FVector Scale, FColor Color)
{
	AActor* textActorObject = GetWorld()->SpawnActor<AActor>(TextObject, Location, Rotation, SpawnParams);
	TextActor = Cast<ATextActor>(textActorObject);
	TextActor->Value = Value;
	TextActor->Scale = Scale;
	TextActor->TextColor = Color;
	TextActor->PositiveValue = PositiveValue;
}

void AGameManager::OrderQuoteReset()
{
	for (int i = 0; i < ControlIngredients.Num(); i++)
	{
		ControlIngredients[i] = false;
	}
	
	GetFoodNames.Empty();
	GetFoodNames.SetNum(0);
	NpcOrderQutoe = FText::FromString("");
	NpcCanOrder = true;
}

void AGameManager::GameOverFunction(bool _GameOver)
{
	if(_GameOver == true && Health >= 0)
	{
		if(DailyNpcSpawn == 1)
		{
			Event = false;
			if(CounterNPC <= 0)
			{
				eventNpcInteraction = false;
				NpcDialogue.Add(FText::FromString("EZIK GAME OVER OLDU HAHA"));
				
				SpawnNPC(0, false, true);
			}
		}
	}

	if(_GameOver == true && Health <= 0 && GameOverNpc == false)
	{
		DailyNpcSpawn = 1;
		if (DailyNpcSpawn == 1)
		{
			Event = false;
			if(CounterNPC <= 0)
			{
				eventNpcInteraction = false;
				NpcDialogue.Add(FText::FromString("EZIK GAME OVER OLDU HAHA"));
				
				GameOverNpc = true;
				SpawnNPC(0, false, true);
			}
		}
	}
}

void AGameManager::EventFunctions(int Day)
{
	switch (Day)
	{
	case 1:
		if(DailyNpcSpawn == 6)
		{
			Event = false;
			if(CounterNPC <= 0)
			{
				eventNpcInteraction = false;
				NpcDialogue.Add(FText::FromString("Oh, welcome! I'm here on the opening day of your new restaurant. I guess now the real competition begins!"));
				NpcDialogue.Add(FText::FromString("I hope you don't try to teach me  about success, that was the biggest mistake your predecessors made. I'll teach you something, small business owner!"));
				OptionChooseDialogue1.Add(FText::FromString("It's a good thought, but you can't go with beauty in the real world. Good luck, you will need it!"));
				OptionChooseDialogue2.Add(FText::FromString("It's a good thought, but you can't go with beauty in the real world. Good luck, you will need it!"));
				Option1.Add(FText::FromString("Everyone has a chance to succeed and I'm here to do the best."));
				Option2.Add(FText::FromString("Competition can help both of us thrive, right?"));
				
				SpawnNPC(0, false, true);
			}
		}
		break;

	case 2:
		if (DailyNpcSpawn == 1 && GameOver == false)
		{
			Event = false;
			if (CounterNPC <= 0)
			{
				eventNpcInteraction = false;
				NpcDialogue.Add(FText::FromString("Dude look, I see the intensity due to the opening day."));
				NpcDialogue.Add(FText::FromString(
					"But don't be too happy, because if everyone who came here had moved on with the money they earned in the first week, they'd all be franchises by now."));
				NpcDialogue.Add(FText::FromString(
					"I have a very good offer. If you don't want to make me your rival, you should accept it."));
				NpcDialogue.Add(FText::FromString(
					"You will close the restaurant at lunch time and I will not bother you again. deal?"));
				OptionChooseDialogue1.Add(
					FText::FromString("Hell no man, be wise. I will let you to think about that."));
				OptionChooseDialogue2.Add(FText::FromString("Would be the biggest mistake of your life"));
				Option1.Add(FText::FromString("I will think about that"));
				Option2.Add(FText::FromString("I WILL SUE YOU!"));

				SpawnNPC(0, false, true);
			}
		}
		break;

	case 3:
		if (DailyNpcSpawn == 6)
		{
			Event = false;
			if (CounterNPC <= 0)
			{
				eventNpcInteraction = false;
				NpcDialogue.Add(FText::FromString("Hello sir, the price of the food seems a little expensive."));
				NpcDialogue.Add(FText::FromString(
					"Do you have a special menu for students? I want to come more often with my friends. 'Cause everywhere is so expensive"));
				OptionChooseDialogue1.Add(FText::FromString("Sir you are rude, you can politely decline."));
				OptionChooseDialogue1.Add(FText::FromString("You never gonna see any student here again."));
				OptionChooseDialogue1.
					Add(FText::FromString("Cause I'm gonna talk to the whole school about you. BYE!"));
				OptionChooseDialogue2.Add(FText::FromString("Thank you sir you are great"));
				OptionChooseDialogue2.Add(
					FText::FromString("Everyone around here is stingy, and thank you again we will come more often."));
				OptionChooseDialogue2.Add(FText::FromString("See you theen!"));
				Option1.Add(FText::FromString("Prices are certain, get out."));
				Option2.Add(FText::FromString("Sure, please come with your friends more often."));

				SpawnNPC(1, false, true);
			}
		}

		if (DailyNpcSpawn == 1 && GameOver == false)
		{
			Event = false;
			if (CounterNPC <= 0)
			{
				eventNpcInteraction = false;
				NpcDialogue.Add(FText::FromString("Howdy partner, I see that things are going well"));
				NpcDialogue.Add(FText::FromString("Don't mind the freak neighborhood, he is just talking trash."));
				NpcDialogue.Add(FText::FromString(
					"Just here to let you know that new products are ready and you can start to use by tomorrow"));
				NpcDialogue.Add(FText::FromString(
					"Now you can prepare more mixed plates. Probably peoples will wish for diffrent combinations."));
				NpcDialogue.Add(FText::FromString("new products and tools will come in the next days."));
				NpcDialogue.Add(FText::FromString("Look yourself very well, See ya!"));

				SpawnNPC(2, false, true);
			}
		}
		break;

	case 4:
		if (DailyNpcSpawn == 5)
		{
			Event = false;
			if (CounterNPC <= 0)
			{
				eventNpcInteraction = false;
				NpcDialogue.Add(FText::FromString("Hello, young man."));
				NpcDialogue.Add(FText::FromString("This place smells really good."));
				NpcDialogue.Add(FText::FromString(
					"Is there an any chance for me to get something. It is really do not matter it could be anything."));
				OptionChooseDialogue1.Add(FText::FromString("OH, you are the best. I really wasn't expecting that."));
				OptionChooseDialogue1.Add(FText::FromString("At these days streets are cold. and peoples are colder"));
				OptionChooseDialogue1.Add(FText::FromString("I am grateful. Take care generous man."));
				OptionChooseDialogue2.
					Add(FText::FromString("I wasn't expecting it anyway, you could have been nicer."));
				OptionChooseDialogue2.Add(FText::FromString("At these days streets are cold. and peoples are colder"));;
				Option1.Add(FText::FromString("Of course man, just take it"));
				Option2.Add(FText::FromString("Get out of here you poor"));

				SpawnNPC(3, false, true);
			}
		}
		break;

	case 5:
		break;

	case 6:
		if (DailyNpcSpawn == 8)
		{
			Event = false;
			if (CounterNPC <= 0 && FireDay == false)
			{
				eventNpcInteraction = false;
				NpcDialogue.Add(FText::FromString(
					"Shhh"));
				NpcDialogue.Add(FText::FromString(
					"Don't make any sound."));
				NpcDialogue.Add(FText::FromString(
					".................."));
				NpcDialogue.Add(FText::FromString(
					"Can I have some ketchup?"));
				OptionChooseDialogue1.Add(FText::FromString("Because I like wires on my neck and ketchup on my stomach"));
				OptionChooseDialogue1.Add(FText::FromString("Give me some ketchup and I make my wires around your neck"));
				OptionChooseDialogue2.Add(FText::FromString("Yes just ketchup."));
				OptionChooseDialogue2.Add(FText::FromString("Because I like wires on my neck and ketchup on my stomach"));
				OptionChooseDialogue2.Add(FText::FromString("Give me some ketchup and I make my wires around your neck"));
				Option1.Add(FText::FromString("Why?"));
				Option1.Add(FText::FromString("Get out man, or I'll call police"));
				Option2.Add(FText::FromString("Just ketchup?"));
				Option2.Add(FText::FromString("Drop your number, I'll call you later."));
		
				SpawnNPC(4, false, true);
			}
		
			if (OptionDialogueContinue)
			{
				if (OptionDialogueChoose)
				{
					lastDialogue = OptionChooseDialogue2.Last();
				}
				else
				{
					lastDialogue = OptionChooseDialogue1.Last();
				}
		
				NpcDialogue.Empty();
				NpcDialogue.SetNum(0);
				NpcDialogue.Add(lastDialogue);
				OptionChooseDialogue1.Empty();
				OptionChooseDialogue1.SetNum(0);
				OptionChooseDialogue2.Empty();
				OptionChooseDialogue2.SetNum(0);
				OptionChooseDialogue1.Add(FText::FromString("You make me sad."));
				OptionChooseDialogue2.Add(FText::FromString("Thanks man."));
				DailyNpcSpawn--;
			}
		}

		if (DailyNpcSpawn == 1 && GameOver == false)
		{
			Event = false;
			if (CounterNPC <= 0)
			{
				eventNpcInteraction = false;
				NpcDialogue.Add(FText::FromString("Howdy partner, It is really good to see you again."));
				NpcDialogue.Add(FText::FromString("I have some good news  for you"));
				NpcDialogue.Add(FText::FromString(
					"I brought drill and meatballs with me and  you can start to use these by tomorrow"));
				NpcDialogue.Add(FText::FromString(
					"Plus, now you have a drink! I am a stupid man didn't even realize drinks are missing."));
				NpcDialogue.Add(FText::FromString("Let me know if anything goes wrong, See ya!"));

				SpawnNPC(2, false, true);
			}
		}
		break;

	case 7:
		if (DailyNpcSpawn == 6)
		{
			Event = false;
			if (CounterNPC <= 0)
			{
				eventNpcInteraction = false;
				NpcDialogue.Add(FText::FromString("Look!"));
				NpcDialogue.Add(FText::FromString("There is no patience left in me. Okey?"));
				NpcDialogue.Add(FText::FromString(
					"I have no patience for restaurants that sell meat."));
				NpcDialogue.Add(FText::FromString("It's officially a corpse shop, you both sell and spin corpses."));
				NpcDialogue.Add(FText::FromString("I hate these places; I will report you to the police."));
				NpcDialogue.Add(FText::FromString("And others with you"));
				OptionChooseDialogue1.Add(FText::FromString("WHAT? did you just expel me?"));
				OptionChooseDialogue1.Add(FText::FromString("You will regret it."));
				OptionChooseDialogue2.Add(FText::FromString("YES I WILL! "));
				OptionChooseDialogue2.Add(FText::FromString("And I about the call police, you will regret it"));;
				Option1.Add(FText::FromString("Miss, I think you should relax and leave."));
				Option2.Add(FText::FromString("Do whatever you want"));

				SpawnNPC(5, false, true);
			}
		}
		break;

	case 8:
		if (DailyNpcSpawn == 8 && GetFireEventOne == false)
		{
			Event = false;
			if (CounterNPC <= 0)
			{
				eventNpcInteraction = false;
				NpcDialogue.Add(FText::FromString("I heard that there been a fire"));
				NpcDialogue.Add(FText::FromString("I wonder why? The security measures here are actually solid."));
				NpcDialogue.Add(FText::FromString("I see that you are very awful at this."));
				NpcDialogue.Add(FText::FromString("Or you don't know how to keep your relation with your associates."));
				NpcDialogue.Add(FText::FromString("HAHAHAHAHA!"));

				SpawnNPC(0, false, true);
			}
		}

		if (DailyNpcSpawn == 4)
		{
			Event = false;
			if (CounterNPC <= 0)
			{
				eventNpcInteraction = false;
				NpcDialogue.Add(FText::FromString("HEY"));
				NpcDialogue.Add(FText::FromString("There is a ghost in my body."));
				NpcDialogue.Add(FText::FromString("Mio padre, Voglio che tu sia piu vicino a me"));
				NpcDialogue.Add(FText::FromString("Ciao"));

				SpawnNPC(4, false, true);
			}
		}
		break;

	case 9:
		if (DailyNpcSpawn == 8)
		{
			Event = false;
			if (CounterNPC <= 0)
			{
				eventNpcInteraction = false;
				NpcDialogue.Add(FText::FromString("Hello sir, sorry to interrupt your business."));
				NpcDialogue.Add(FText::FromString("But we heard that there is many unusual situations in here lately."));
				NpcDialogue.Add(FText::FromString("Is there anything you want to talk about?"));

				OptionChooseDialogue1.Add(FText::FromString("Yes, everybody knows him"));
				OptionChooseDialogue1.Add(FText::FromString("I thought they warned you about him. He been in jail like 4 years because of these situations."));
				OptionChooseDialogue1.Add(FText::FromString("And the thing about; he is not the owner of his restaurant. His father is."));
				OptionChooseDialogue1.Add(FText::FromString("Don't mind him. He just talks. But let us know if something goes wrong."));
				
				OptionChooseDialogue2.Add(FText::FromString("Oh, right."));
				OptionChooseDialogue2.Add(FText::FromString("Actually that's why I am here right now. It is all because of she also sparked an argument on station."));;
				OptionChooseDialogue2.Add(FText::FromString("Just try to act like a normal customer to her."));;
				
				OptionChooseDialogue3.Add(FText::FromString("Wow, I never heard anything like this before"));
				OptionChooseDialogue3.Add(FText::FromString("It might be an interesting situation."));
				OptionChooseDialogue3.Add(FText::FromString("Please call me if you see him again. And..."));
				OptionChooseDialogue3.Add(FText::FromString("Be carefull"));
				
				Option1.Add(FText::FromString("My neighbor, he is always threatening me."));
				Option2.Add(FText::FromString("A woman, She sparked an argument"));
				Option3.Add(FText::FromString("A mysterious man"));

				SpawnNPC(6, false, true);
			}
		}

		if (DailyNpcSpawn == 1 && GameOver == false)
		{
			Event = false;
			if (CounterNPC <= 0)
			{
				eventNpcInteraction = false;
				NpcDialogue.Add(FText::FromString("Howdy partner, It is me again"));
				NpcDialogue.Add(FText::FromString("Yes, I am exactly here for what you are looking for."));
				NpcDialogue.Add(FText::FromString(
					"Now, you are able to sell a rice. People will look for this as a side dish."));
				NpcDialogue.Add(FText::FromString(
				"And man, this rice is a great product. Peoples absolutely like it."));
				NpcDialogue.Add(FText::FromString("See ya!"));

				SpawnNPC(2, false, true);
			}
		}
		break;
	}
}


