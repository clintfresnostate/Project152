// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Project_152.h"
#include "Project_152GameMode.h"
#include "Engine.h"
#include "Project_152Character.h"
#include "CombatGrid.h"
#include "ParentCombatCharacter.h"

AProject_152GameMode::AProject_152GameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = AProject_152Character::StaticClass();

	//Levels in order starting from level 1
	ExperienceBrackets.Add(0); //1
	ExperienceBrackets.Add(100); //2
	ExperienceBrackets.Add(300); //3
	ExperienceBrackets.Add(600); //4
	ExperienceBrackets.Add(1000); //5
	ExperienceBrackets.Add(1500); //6
	ExperienceBrackets.Add(2100); //7
	ExperienceBrackets.Add(2800); //8
	ExperienceBrackets.Add(3700); //9
	ExperienceBrackets.Add(4700); //10
	ExperienceBrackets.Add(5800); //11
	ExperienceBrackets.Add(7000); //12
	ExperienceBrackets.Add(8300); //13
	ExperienceBrackets.Add(9700); //14
	ExperienceBrackets.Add(11200); //15
	ExperienceBrackets.Add(12800); //16
	ExperienceBrackets.Add(14500); //17
	ExperienceBrackets.Add(16300); //18
	ExperienceBrackets.Add(18200); //19

	//Non-Linear Jump in Last Level
	ExperienceBrackets.Add(21000); //20
}
/*
void AProject_152GameMode::StartCombat(TArray<AParentCombatCharacter*> CharactersInCombat, ACombatGrid* GridRef)
{
	//Temp Variables we need
	int32 HighestSpeed = 0;
	//int32 IndexSave;
	int32 TurnIncrementer = 0;
	//Final and temp Array Used to Sort the Characters
	TArray <AParentCombatCharacter*> TempCharactersInCombat = CharactersInCombat;
	TArray <AParentCombatCharacter*> ArrangedCharactersInCombat;

	//Sorting by highest Speed goes first
	//Each iteration removes the highest and adds it to the new array
	
	
	while (TempCharactersInCombat.Num() > 0)
	{
		for (int32 i = 0; i < TempCharactersInCombat.Num(); i++)
		{
			
			if (TempCharactersInCombat[i]->GetSpeedStat() > HighestSpeed)
			{
				HighestSpeed = TempCharactersInCombat[i]->GetSpeedStat();
				IndexSave = i;
			}
			
		}
		ArrangedCharactersInCombat.Add(TempCharactersInCombat[IndexSave]);
		if ((IndexSave > 0) & TempCharactersInCombat.Contains(TempCharactersInCombat[IndexSave]))
		{
			TempCharactersInCombat.RemoveAt(IndexSave);
		
		}
		IndexSave = -1;
		HighestSpeed = 0;
	}
	
	//While loop to loop through turns until combat is over
	while (bInCombat)
	{
		if (bDo)
		{
			CharactersInCombat[TurnIncrementer]->TakeTurn();
			bDo = false;
			bInCombat = false;
		}
	}
}
*/
void AProject_152GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bInCombat)
	{
		CharactersInCombat[TurnIncrement % CharactersInCombat.Num()]->SetTurnIndicatorVisible();
		if (CharactersInCombat[TurnIncrement % CharactersInCombat.Num()]->CurrentHealthStat <= 0)
		{
			//TurnIncrement++;
			//bTakeTurn = false;
			bNextTurn = true;
		}
		if (bTakeTurn)
		{
			CharactersInCombat[TurnIncrement % CharactersInCombat.Num()]->TakeTurn();
			bTakeTurn = false;
		}
		if (bNextTurn)
		{
			CharactersInCombat[TurnIncrement % CharactersInCombat.Num()]->NumberOfTilesCanMove = CharactersInCombat[TurnIncrement % CharactersInCombat.Num()]->MovementRange;
			CharactersInCombat[TurnIncrement % CharactersInCombat.Num()]->RefreshMoves(CharactersInCombat[TurnIncrement % CharactersInCombat.Num()]->NumberofMovesPerTurn, CharactersInCombat[TurnIncrement % CharactersInCombat.Num()]->NumberOfAttacksPerTurn);
			CharactersInCombat[TurnIncrement % CharactersInCombat.Num()]->SetTurnIndicatorHidden();
			TurnIncrement++;
			if (!CharactersInCombat[TurnIncrement % CharactersInCombat.Num()]->bIsHumanPlayer)
			{
				CharactersInCombat[TurnIncrement % CharactersInCombat.Num()]->TakeTurn();
			}
			bNextTurn = false;
		}
	}
}
void AProject_152GameMode::WinExecution_Implementation()
{

}
void AProject_152GameMode::LossExecution_Implementation()
{

}
void AProject_152GameMode::ProcessWin(int32 InputExperience, int32 Currencytoadd)
{
	AProject_152Character* MyCharTemp;
	MyCharTemp = Cast<AProject_152Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	TArray<int32> ItemIdArray;
	ItemIdArray.Empty();

	/*
	for (int i = 0; i < CharactersInCombat.Num(); i++)
	{
		if (CharactersInCombat[i]->bIsHumanPlayer)
		{
			ItemIdArray.Add(CharactersInCombat[i]->ItemId);
			//CharactersInCombat[i]->AddExperience(InputExperience);
		}
	}
	
	for (int i = 0; i < ItemIdArray.Num(); i++)
	{
		for (int j = 0; j < MyCharTemp->ParentCombatCharacterInventoryArray.Num(); j++)
		{
			if (MyCharTemp->ParentCombatCharacterInventoryArray[j].ItemID == ItemIdArray[i])
			{
				MyCharTemp->ParentCombatCharacterInventoryArray[j].Experience += InputExperience;
				CheckForLevelUP(MyCharTemp->ParentCombatCharacterInventoryArray[j]);
			}
		}
	}
	*/
	for (int k = 0; k < MyCharTemp->ParentCombatCharacterInventoryArray.Num(); k++)
	{
		MyCharTemp->ParentCombatCharacterInventoryArray[k].Experience += InputExperience;
		CheckForLevelUP(MyCharTemp->ParentCombatCharacterInventoryArray[k], k);
	}

	MyCharTemp->Currency += Currencytoadd;

}
void AProject_152GameMode::CheckForLevelUP(FInventoryItemStruct ItemIn, int32 arrayindex)
{
	AProject_152Character* MyCharTemp;
	MyCharTemp = Cast<AProject_152Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int32 CurrentLevel = ItemIn.Level;
	int32 TempNewLevel = 0;

	for (int i = 0; i < ExperienceBrackets.Num(); i++)
	{
		if (ItemIn.Experience < ExperienceBrackets[i])
		{
			TempNewLevel = i;
			break;
		}

	}
	if ((TempNewLevel - CurrentLevel) > 0)
	{
		FString newstring = FString::FromInt(TempNewLevel);
		GEngine->AddOnScreenDebugMessage(0, 5.5f, FColor::Red, newstring);
		for (int j = 0; (j < (TempNewLevel - CurrentLevel)); j++)
		{
			//GEngine->AddOnScreenDebugMessage(0, 5.5f, FColor::Red, FString("AddingLevel"));
			MyCharTemp->ParentCombatCharacterInventoryArray[arrayindex].Level++;
		}
	}
}