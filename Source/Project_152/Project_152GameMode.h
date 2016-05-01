// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/GameMode.h"
#include "CombatGrid.h"
#include "ParentCombatCharacter.h"
#include "Project_152GameMode.generated.h"

// The GameMode defines the game being played. It governs the game rules, scoring, what actors
// are allowed to exist in this game type, and who may enter the game.
//
// This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of Project_152Character

UCLASS(minimalapi)
class AProject_152GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AProject_152GameMode();

	//This will start the combat. Pass through the characters involved and which grid its on
//	UFUNCTION(BlueprintCallable, Category = Combat)
//		void StartCombat(TArray<AParentCombatCharacter*> CharactersInCombat, ACombatGrid* GridRef);

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		bool bInCombat = false;

	//Set this when units are spawned. Keeps track of all the actors/characters in combat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		TArray<AParentCombatCharacter*> CharactersInCombat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		ACombatGrid* GridRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		int32 TurnIncrement = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		bool bTakeTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		bool bNextTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		bool bDoneWithMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		bool bDoneWithAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
		int32 UniqueItemID = 0;

	UFUNCTION(BlueprintNativeEvent, Category = WinCondition)
		void WinExecution(); // Dummy event

	UFUNCTION(BlueprintNativeEvent, Category = WinCondition)
		void LossExecution(); // Dummy event 
};
