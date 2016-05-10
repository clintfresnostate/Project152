// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_152.h"
#include "InventoryItem.h"
#include "Project_152Character.h"

void AInventoryItem::UseItem(AProject_152Character* ItemOwner)
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	ItemUsed(ItemOwner); // Call the blueprint event


}
void AInventoryItem::SetSpeed()
{
	ItemInfo.Speed = ItemInfo.Speed + 1;
}

void AInventoryItem::SetInt()
{
	ItemInfo.Intelligence = ItemInfo.Intelligence + 1;
}

void AInventoryItem::SetStr()
{
	ItemInfo.Strength = ItemInfo.Strength + 1;
}

void AInventoryItem::SetStam()
{
	ItemInfo.Stamina = ItemInfo.Stamina + 1;
}

void AInventoryItem::SetHealth()
{
	ItemInfo.Health = ItemInfo.Health + 25;
}

