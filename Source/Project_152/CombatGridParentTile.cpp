// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_152.h"
#include "CombatGridParentTile.h"


// Sets default values
ACombatGridParentTile::ACombatGridParentTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GridTile->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void ACombatGridParentTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACombatGridParentTile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
//Called When Spawning Tile and used to set its index
void ACombatGridParentTile::SetGridIndex(int32 index)
{
	GridTileIndex = index;

}

