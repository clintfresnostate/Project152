// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_152.h"
#include "CombatGrid.h"

ACombatGrid::ACombatGrid()
{
	FVector();
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//GridFloor = CreateDefaultSubobject<UStaticMesh>(TEXT("Grid"));
	//GridFloor->AddToRoot;

	//get Reference to the world
	UWorld* const WorldReference = GetWorld();

	//Set spawn Param necessary to fulfill spawn inputs
	FActorSpawnParameters SpawnParam;

	//Set Spawn Rotation necessary to fulfill spawn inputs
	FRotator SpawnRotation;

	
	
}

// Called when the game starts or when spawned
void ACombatGrid::BeginPlay()
{
	Super::BeginPlay();

	//Get Location of Actor at beginning of Play
	OffsetVectorLocation = GetActorLocation();

	//Generating the Grid
	ArrayLastIndex = MaxX*MaxY - 1;
	for (int i = 0; i <= ArrayLastIndex; i++)
	{
		VectorSpawnLoc.X = i / MaxY*GridTileSize;
		VectorSpawnLoc.Y = i % MaxY*GridTileSize;
		VectorSpawnLoc.Z = 0.0f;

		//Add the Vector Point to the Array
		GridArray.Add(VectorSpawnLoc);

		//initialize grid with item type (0 = Openspace)
		GridType.Add(0);
	}

	//Convert the Local Space to World Coordinates in Ue4 editor
	WorldLocArray = ConvertToWorldCoord(GridArray);


	/*Not Using this due to Grid Image Change Which Allowed Points to already be in the middle*/
	//Convert the corners of the tiles to the midpoint
	//GridArray = ConvertToMidPoints(GridArray);

	
}

// Called every frame
void ACombatGrid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
//This will convert the points starting from the NorthWest Corner to the mid point of each tiles.
//Input is the Array of Vectors. Returns the new grid coordinates. ONLY DO ONCE. Adds offset values to each vector.
TArray<FVector> ACombatGrid::ConvertToMidPoints(TArray< FVector > GridArray)
{
	FVector VectorHolder;
	TArray<FVector> ArrayHolder;
	if (bCanConvertToMidPoints == true)
	{

		for (int i = 0; i <= ArrayLastIndex; i++)
		{
			VectorHolder.X = GridArray[i].X + GridTileSize;
			VectorHolder.Y = GridArray[i].Y + GridTileSize;
			VectorHolder.Z = 0.0f;

			ArrayHolder.Add(VectorHolder);
		}
		bCanConvertToMidPoints = false;
		return ArrayHolder;
	}
	else
	{
		return GridArray;
	}
}
//Returns Conversion of a array of vectors to world location. Use ONLY ONCE-it adds offset values to each vector.
TArray<FVector> ACombatGrid::ConvertToWorldCoord(TArray< FVector > GridArray)
{
	FVector VectorHolder;
	TArray<FVector> ArrayHolder;
	for (int i = 0; i <= ArrayLastIndex; i++)
		{
			VectorHolder.X = GridArray[i].X *GridScale + OffsetVectorLocation.X;
			VectorHolder.Y = GridArray[i].Y *GridScale + OffsetVectorLocation.Y;
			VectorHolder.Z = 0.0f;

			ArrayHolder.Add(VectorHolder);

		}
	return(ArrayHolder);
}
//Returns the World Grid Locations
TArray<FVector> ACombatGrid::GetWorldGridArray()
{
	return WorldLocArray;
}
int32 ACombatGrid::GetMaxY()
{
	return MaxY;
}
int32 ACombatGrid::GetMaxX()
{
	return MaxX;
}

//Used for input for a mouse to click and choose which grid tiles to move to
//Use only After WORLDLOCARRAY has been created
int32 ACombatGrid::GetGridNum(FVector InputPosition)
{

	//Vector Magnitude Variable to Find closest point
	FVector VectorDifference;
	FVector SmallestVectorMag;
	//Initialize Index to be negative so we can check it later if its not on the grid
	int32 index = -1;
	bool bOutOfBounds=false;

	if (bMouseIsOnGrid)
	{
		index = 0;
		VectorDifference.X = WorldLocArray[0].X - InputPosition.X;
		VectorDifference.Y = WorldLocArray[0].Y - InputPosition.Y;
		float MagnitudeInit = FMath::Sqrt(FMath::Pow(VectorDifference.X, 2) + FMath::Pow(VectorDifference.Y, 2));	

		//For Each Loop. Getting the points closest to our vector by comparing their differences' magnitude
		for (int i = 0; i < WorldLocArray.Num(); i++)
		{				
			VectorDifference.X = WorldLocArray[i].X - InputPosition.X;
			VectorDifference.Y = WorldLocArray[i].Y - InputPosition.Y;

			float Magnitude = FMath::Sqrt(FMath::Pow(VectorDifference.X, 2) + FMath::Pow(VectorDifference.Y, 2));
			if (Magnitude < MagnitudeInit)
			{
					MagnitudeInit = Magnitude;
					index = i;
			}
		}
	}
	return index;

}
