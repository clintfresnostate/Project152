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