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
		TArray<FInventoryItemStruct> SaveInvArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
		TArray<FInventoryItemStruct> SaveCombatCharInvArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
		TArray<FInventoryItemStruct> SaveModInventoryArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
		int32 SaveUniqueItemID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
		int32 SaveCoin;
	///////////////////////////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
		FString SaveSlotName = "TEST";


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
		int32 UserIndex = 0;

	UMySaveGame();
};

