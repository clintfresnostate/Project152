// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "InventoryItem.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FInventoryItemStruct
{
	GENERATED_BODY()

public:

	// Item class, used to spawn the item in the world when its dropped
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemInfo)
		TSubclassOf<class AInventoryItem> ItemClass;
	// Item Icon that will be displayed in the slot
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemInfo)
		UTexture2D* ItemImage;
	// Text that the item will display as its name
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemInfo)
		FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		FString ActionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		int32 SellPrice;

	bool operator==(FInventoryItemStruct const& Other) const
	{

		if (ItemName != Other.ItemName)
		{

			return false;
		}
		if (ItemClass != Other.ItemClass)
		{

			return false;
		}
		return true;

	}
};
/*
*/

UCLASS(BlueprintType)
class PROJECT_152_API AInventoryItem : public AStaticMeshActor
{
	GENERATED_BODY()
		//AInventoryItem(const FObjectInitializer& ObjectInitializer);

public:



	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
		FInventoryItemStruct ItemInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
		bool bDestroyAfterUse;// Should the item actor be destroyed after it has been used?

	UFUNCTION(BlueprintImplementableEvent)
		void ItemUsed(class AProject_152Character* ItemOwner);

	void UseItem(AProject_152Character* ItemOwner);


};







