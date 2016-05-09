//
#pragma once

#include "Project_152Character.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_152_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
		float locationX;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
		float locationY;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
		float locationZ;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
		TArray<FInventoryItemStruct> SaveInvArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
		TArray<FInventoryItemStruct> SaveCombatCharInvArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
		TArray<FInventoryItemStruct> SaveModInventoryArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
		int32 SaveUniqueItemID;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)


	/*
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
		AProject_152Character* mainPlayer;
		*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
		FString SaveSlotName = "TEST";


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
		int32 UserIndex = 0;

	UMySaveGame();
};

