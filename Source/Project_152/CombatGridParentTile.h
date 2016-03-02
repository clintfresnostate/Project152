// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CombatGridParentTile.generated.h"

UCLASS()
class PROJECT_152_API ACombatGridParentTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACombatGridParentTile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Declare Static Mesh Comp to attach to the root
	UPROPERTY(Editanywhere, BlueprintReadWrite)
		UStaticMeshComponent* GridTile;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = GridProperties)
		int32 GridTileIndex;

	//Function used to Set the tile index
	void SetGridIndex(int32 index);
	
	
};
