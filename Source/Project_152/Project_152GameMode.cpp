// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Project_152.h"
#include "Project_152GameMode.h"
#include "Project_152Character.h"
#include "CombatGrid.h"
#include "ParentCombatCharacter.h"

AProject_152GameMode::AProject_152GameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = AProject_152Character::StaticClass();	
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
			CharactersInCombat[TurnIncrement % CharactersInCombat.Num()]->RefreshMoves(1, 1);
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
				MyCharTemp->ParentCombatCharacterInventoryArray[j].Experience += InputExperience;
		}
	}
	
	MyCharTemp->Currency += Currencytoadd;

}