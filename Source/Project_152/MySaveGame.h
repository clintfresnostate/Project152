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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
		AProject_152Character* mainPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
		FString SaveSlotName = "TEST";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
		int32 UserIndex = 0;

	UMySaveGame();
};

