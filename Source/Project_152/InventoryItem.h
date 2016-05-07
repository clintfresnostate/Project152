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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemInfo)
		TSubclassOf<class AParentCombatCharacter> ClassOfCombatChar;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		int32 ItemSlotIndexHolder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		int32 Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		int32 Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		int32 Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		int32 Intelligence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		int32 Experience;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		int32 Level = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		bool isParentCombatCharItem = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemInfo)
		bool isMod = false;

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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		FInventoryItemStruct ItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		bool isParentCombatChar = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		bool isMod = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Item)
		bool bDestroyAfterUse;// Should the item actor be destroyed after it has been used?

	UFUNCTION(BlueprintImplementableEvent)
		void ItemUsed(class AProject_152Character* ItemOwner);

	void UseItem(AProject_152Character* ItemOwner);


};







