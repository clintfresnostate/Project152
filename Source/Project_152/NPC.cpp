// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_152.h"
#include "Project_152Character.h"
#include "NPC.h"



bool ANPC::BuyItem(FInventoryItemStruct Item, int32 BuyPrice)
{
	AProject_152Character* MyCharTemp;
	MyCharTemp = Cast<AProject_152Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (MyCharTemp->Currency > BuyPrice)
	{
		if (MyCharTemp->InventoryArray.Num() <= 15)
		{
			MyCharTemp->GiveItem(Item);
			MyCharTemp->Currency -= BuyPrice;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
void ANPC::SellItem(FInventoryItemStruct Item)
{
	AProject_152Character* MyCharTemp;
	MyCharTemp = Cast<AProject_152Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	MyCharTemp->Currency += Item.SellPrice;
	MyCharTemp->InventoryArray.Remove(Item);
}