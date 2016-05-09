// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "InventoryItem.h"
#include "NPC.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_152_API ANPC : public APaperCharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shop)
		TArray<FInventoryItemStruct> ItemCapacity;
	UFUNCTION(BlueprintCallable, Category = Shop)
		bool BuyItem(FInventoryItemStruct Item, int32 BuyPrice);
	UFUNCTION(BlueprintCallable, Category = Shop)
		void SellItem(FInventoryItemStruct Item);
};
