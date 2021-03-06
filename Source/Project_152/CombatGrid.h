// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "GameFramework/Actor.h"
#include "ParentCombatCharacter.h"
#include "CombatGrid.generated.h"

//Have to use forward declaration to avoid circular dependencies


UCLASS()
class PROJECT_152_API ACombatGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACombatGrid();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridProperties)
		float GridScale = 4;

	//Set Tile Size
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridProperties)
		int32 GridTileSize = 100;
	
	UPROPERTY(Editanywhere, BlueprintReadWrite)
		UStaticMeshComponent* GridFloor;

	//Initialize Spawn Ref
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawning)
		TSubclassOf<class ACombatGridParentTile> SpawnRef;

	//Set Grid Dimensions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridProperties)
		int32 MaxX=10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridProperties)
		int32 MaxY=10;

	//Used to check if mouse trace is inbounds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridProperties)
		int32 NWCorner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridProperties)
		int32 SECorner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridProperties)
		bool bMouseIsOnGrid = false;

	//Array of Vectors that INITIALLY holds the grid array without translation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridProperties)
		TArray<FVector> GridArray;

	//Array of Vectors that holds the FINAL grid location after translation into world properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridProperties)
		TArray<FVector> WorldLocArray;

	UFUNCTION(BlueprintCallable, Category = GridProperties)
		int32 GetGridNum(FVector InputPosition);

	UFUNCTION(BlueprintCallable, Category = GridProperties)
		void HandleMods(int32 ModType, AParentCombatCharacter* CharacterToApply, int32 inputStat);

	//Array of ints that store the Data type of each grid tile. To be generated in construction script alongside the grid array.
	//The grid info will be editable in a BP for fast configuration of grid walls/open space etc.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GridProperties)
		TArray<int32> GridType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridProperties)
		TArray<int32> SpawnPoints;


	int32 GetMaxY(void);
	int32 GetMaxX(void);

	//The three human Slots for passing characters through
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CombatInitializer)
		TSubclassOf<AParentCombatCharacter> HumanSlotOne;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CombatInitializer)
		TSubclassOf<AParentCombatCharacter> HumanSlotTwo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CombatInitializer)
		TSubclassOf<AParentCombatCharacter> HumanSlotThree;

	//Three Computer slots for setting up the AI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CombatInitializer)
		TSubclassOf<AParentCombatCharacter> ComputerSlotOne;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CombatInitializer)
		TSubclassOf<AParentCombatCharacter> ComputerSlotTwo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CombatInitializer)
		TSubclassOf<AParentCombatCharacter> ComputerSlotThree;
	/*FUNCTIONS*/

	//convert the corner loc to mid point of each tile. Returns the converted array
	TArray<FVector> ConvertToMidPoints(TArray<FVector>);
	//Convert relative grid loc to world location. Returns the converted array
	TArray<FVector> ConvertToWorldCoord(TArray<FVector>);
	//GetWorldGrid and return it to necessary classes
	TArray<FVector> GetWorldGridArray();

	//Structure to hold the grid information

protected:

	int32 ArrayLastIndex;
	FVector VectorSpawnLoc;
	FVector OffsetVectorLocation;

	//By Default-set to true to enable conversion to midpoints. used to prevet use of convert more than once.
	bool bCanConvertToMidPoints = true;
	bool SetInitialFacing = true;

	

};
