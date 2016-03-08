// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_152.h"
#include "ParentCombatCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "CombatGrid.h"
#include "Project_152GameMode.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);
//////////////////////////////////////////////////////////////////////////

/*

PLEASE NOTE THAT THIS CHARACTER IS FOR COMBAT ONLY. MOST OF THE ORIGINAL FUNCTIONALITY BUILT IN HAS BEEN REPLACED TO FIT OUR NEEDS
THE BUILT IN MOVEMENT HAS BEEN OVERRIDDEN. -CH

*/

AParentCombatCharacter::AParentCombatCharacter()
{
	
	// Setup the assets
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> RunningAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> IdleAnimationAsset;
		FConstructorStatics()
			: RunningAnimationAsset(TEXT("/Game/2dSideScroller/Sprites/RunningAnimation.RunningAnimation"))
			, IdleAnimationAsset(TEXT("/Game/2dSideScroller/Sprites/IdleAnimation.IdleAnimation"))
		{
		}
		
	};
	static FConstructorStatics ConstructorStatics;

	RunningAnimation = ConstructorStatics.RunningAnimationAsset.Get();
	IdleAnimation = ConstructorStatics.IdleAnimationAsset.Get();
	GetSprite()->SetFlipbook(IdleAnimation);

	//NECESSARY TO ENABLE TICK FUNCTION
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// 	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarGear"));
	// 	TextComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	// 	TextComponent->SetRelativeLocation(FVector(35.0f, 5.0f, 20.0f));
	// 	TextComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	// 	TextComponent->AttachTo(RootComponent);

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;

}
//////////////////////////////////////////////////////////////////////////
// Animation

void AParentCombatCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeed = PlayerVelocity.Size();

	// Are we moving or standing still?
	UPaperFlipbook* DesiredAnimation = (PlayerSpeed > 0.0f) ? RunningAnimation : IdleAnimation;
	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

void AParentCombatCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
	//UpdateCharacter(); OVERRIDDEN
	//The Following Code Sets the rotation when the actor moves left or right
	if (bEnableUpdate)
	{
		if (bInMovement)
		{
			if (Y_Direction > 0.0f)
			{
				GetSprite()->SetFlipbook(DownAnimation);
			}
			if (Y_Direction < 0.0f)
			{
				GetSprite()->SetFlipbook(UpAnimation);
			}

			if (X_Direction > 0.0f)
			{
				GetSprite()->SetWorldRotation(MoveRightRotation);
				GetSprite()->SetFlipbook(RunningAnimation);
			}
			if (X_Direction < 0.0f)
			{
				GetSprite()->SetWorldRotation(MoveLeftRotation);
				GetSprite()->SetFlipbook(RunningAnimation);
			}
		}
		if (!bInMovement & !bIsAttacking)
		{
			GetSprite()->SetFlipbook(IdleAnimation);
		}
	}
	if (bIsAttacking)
	{
		GetSprite()->SetFlipbook(AttackAnimation);
	}
}


//////////////////////////////////////////////////////////////////////////
// Input

void AParentCombatCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAxis("MoveRight", this, &AParentCombatCharacter::MoveRight);
	InputComponent->BindAxis("MoveDown", this, &AParentCombatCharacter::MoveDown);

}

void AParentCombatCharacter::MoveRight(float Value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}
void AParentCombatCharacter::MoveDown(float Value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
}
void AParentCombatCharacter::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();


}
void AParentCombatCharacter::GiveItem(FInventoryItemStruct Item)
{

	int32 idx = InventoryArray.Find(Item); // Grab the index of the item

	if (!InventoryArray.IsValidIndex(idx)) // If the index is NOT valid it means the item isnt in our inventory / array
	{
		//Then the item can be added!
		InventoryArray.Add(Item);
		RefreshInventory(); // Update our Ui

	}



}

void AParentCombatCharacter::DropItem(FInventoryItemStruct Item)
{

	AInventoryItem* WorldItem = GetWorld()->SpawnActor<AInventoryItem>(Item.ItemClass, GetActorLocation(), FRotator(0, 0, 0)); // Spawn the item in the world
	WorldItem->ItemInfo = Item; // Assign the item info of the newly spawned item in the world to the one we dropped
	int32 idx = InventoryArray.Find(Item); // Grab the index of the item we want to drop


	if (InventoryArray.IsValidIndex(idx)) // Make sure its valid
	{
		if (InventoryArray[idx] == Item) // Make sure the item in our inventory matches the one we want to drop
		{
			InventoryArray.Remove(Item); // Remove it from the array
			RefreshInventory(); // Update our UI
		}
	}




}

/* Don't Need this Function Just yet
void AParentCombatCharacter::UseItem(FInventoryItemStruct Item)
{
	AInventoryItem* WorldItem = GetWorld()->SpawnActor<AInventoryItem>(Item.ItemClass, GetActorLocation(), FRotator(0, 0, 0)); // Spawn the item in the world
	WorldItem->UseItem(this); // call the blueprint event


}
*/
void AParentCombatCharacter::RefreshInventory_Implementation()
{

}

void AParentCombatCharacter::UpdateInventory()
{
	RefreshInventory();
}

void AParentCombatCharacter::SetWithinItemRadius(bool bIsInRadius, AInventoryItem* Item)
{
	if (bIsInRadius == true) // if we are in the radius
	{
		FocusedItem = Item; // assign our focused item to the one in the radius
		bIsWithinItemRange = true;
	}
	else
	{
		FocusedItem = nullptr; // we are not on the item radius and we dont have a focused item
		bIsWithinItemRange = false; // 
	}
}
void AParentCombatCharacter::MoveToPosition()
{

		if (bInMovement == false)
		{
			//Calling Dummy Function to allow BP to handle the Timeline
			MoveToGridEvent();

			bInMovement = true;
		}
		
}

//Checks Each Possible Movement withint 1 unit and checks to see if its valid. If its valid it adds it to the valid locations for movement.
TArray<FVector> AParentCombatCharacter::GetLocationOfTilesWithinOneUnit(int32 GridNum, TArray<FVector> WorldGridRef, ACombatGrid* TargetGrid)
{
	TArray<FVector> ValidTilesWithin1;
	//If point is valid, add Grid index directly to the RIGHT
	if ((GridNum + TargetGrid->GetMaxY() >= 0)&(GridNum + TargetGrid->GetMaxY() < (WorldGridRef.Num())))
	{
		if (WorldGridRef.Contains(WorldGridRef[GridNum + TargetGrid->GetMaxY()]))
		{
			ValidTilesWithin1.Add(WorldGridRef[GridNum + TargetGrid->GetMaxY()]);
		}
	}
	//If point is valid, add Grid index directly to the LEFT
	if ((GridNum - TargetGrid->GetMaxY() >= 0) & (GridNum - TargetGrid->GetMaxY() < (WorldGridRef.Num())))
	{
		if (WorldGridRef.Contains(WorldGridRef[GridNum - TargetGrid->GetMaxY()]))
		{
			ValidTilesWithin1.Add(WorldGridRef[GridNum - TargetGrid->GetMaxY()]);
		}
	}
	//If point is valid, add Grid index directly UP
	if ((GridNum - 1 >= 0) & (GridNum - 1 < (WorldGridRef.Num())))
	{
		if ((GridNum%TargetGrid->GetMaxY() != 0) & (WorldGridRef.Contains(WorldGridRef[GridNum - 1])))
		{
			ValidTilesWithin1.Add(WorldGridRef[GridNum - 1]);
		}
	}
	//If point is valid, add Grid index directly DOWN
	if ((GridNum + 1 >= 0) & (GridNum + 1 < (WorldGridRef.Num())))
	{
		if (((GridNum+1)%TargetGrid->GetMaxY() != 0) & (WorldGridRef.Contains(WorldGridRef[GridNum + 1])))
		{
			ValidTilesWithin1.Add(WorldGridRef[GridNum + 1]);
		}
	}
	//Diagonal Points
	if (bUseDiagonals)
	{
		//If point is valid, add Grid index directly DOWN & RIGHT
		if ((GridNum + TargetGrid->GetMaxY() + 1 >= 0) & (GridNum + TargetGrid->GetMaxY() + 1 < (WorldGridRef.Num())))
		{
			if (((GridNum+1)%TargetGrid->GetMaxY() != 0) & (WorldGridRef.Contains(WorldGridRef[GridNum + TargetGrid->GetMaxY() + 1])))
			{
				ValidTilesWithin1.Add(WorldGridRef[GridNum + TargetGrid->GetMaxY() + 1]);
			}
		}
		//If point is valid, add Grid index directly DOWN & LEFT
		if ((GridNum - TargetGrid->GetMaxY() + 1 >= 0) & (GridNum - TargetGrid->GetMaxY() + 1 < (WorldGridRef.Num())))
		{
			if (((GridNum+1)%TargetGrid->GetMaxY() != 0) & (WorldGridRef.Contains(WorldGridRef[GridNum - TargetGrid->GetMaxY() + 1])))
			{
				ValidTilesWithin1.Add(WorldGridRef[GridNum - TargetGrid->GetMaxY() + 1]);
			}
		}

		//If point is valid, add Grid index directly UP & RIGHT
		if ((GridNum + TargetGrid->GetMaxY() - 1 >= 0) & (GridNum + TargetGrid->GetMaxY() - 1 < (WorldGridRef.Num())))
		{
			if ((GridNum%TargetGrid->GetMaxY() != 0) & (WorldGridRef.Contains(WorldGridRef[GridNum + TargetGrid->GetMaxY() - 1])))
			{
				ValidTilesWithin1.Add(WorldGridRef[GridNum + TargetGrid->GetMaxY() - 1]);
			}
		}
		//If point is valid, add Grid index directly UP & LEFT
		if ((GridNum - TargetGrid->GetMaxY() - 1 >= 0) & (GridNum - TargetGrid->GetMaxY() - 1 < (WorldGridRef.Num())))
		{
			if ((GridNum%TargetGrid->GetMaxY() != 0) & (WorldGridRef.Contains(WorldGridRef[GridNum - TargetGrid->GetMaxY() - 1])))
			{
				ValidTilesWithin1.Add(WorldGridRef[GridNum - TargetGrid->GetMaxY() - 1]);
			}
		}
	}
	return ValidTilesWithin1;
}
//Returns the current Grid Location
int32 AParentCombatCharacter::GetGridNum(FVector TargetVector, TArray<FVector> WorldGridRef)
{
	//WorldGridRef = CombatGrid->GetWorldGridArray();

	//Vector Magnitude Variable to Find closest point
	FVector VectorDifference;
	FVector SmallestVectorMag;
	//Initialize the Vectors
	int32 index=0;

	if (WorldGridRef.Num() > index)
	{
		VectorDifference.X = WorldGridRef[0].X-TargetVector.X;
		VectorDifference.Y = WorldGridRef[0].Y-TargetVector.Y;
		float MagnitudeInit = FMath::Sqrt(FMath::Pow(VectorDifference.X, 2) + FMath::Pow(VectorDifference.Y, 2));

		//For Each Loop. Getting the points closest to our vector by comparing their differences' magnitude
		for (int i = 0; i < WorldGridRef.Num(); i++)
		{
			VectorDifference.X = WorldGridRef[i].X - TargetVector.X;
			VectorDifference.Y = WorldGridRef[i].Y - TargetVector.Y;

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


//Dummy Events used to interface with Blueprints
void AParentCombatCharacter::MoveToGridEvent_Implementation()
{
	
}

//Make the character face a certain direction
//Updates are disabled so that the facing direction is not changed. Remember to Re-enable.
void AParentCombatCharacter::FaceRight()
{
	bEnableUpdate = false;
	GetSprite()->SetFlipbook(IdleAnimation);
	GetSprite()->SetWorldRotation(MoveRightRotation);
}
void AParentCombatCharacter::FaceDown()
{
	bEnableUpdate = false;
	GetSprite()->SetFlipbook(DownIdleAnimation);
}
void AParentCombatCharacter::FaceLeft()
{
	bEnableUpdate = false;
	GetSprite()->SetFlipbook(IdleAnimation);
	GetSprite()->SetWorldRotation(MoveLeftRotation);
}
void AParentCombatCharacter::FaceUp()
{
	bEnableUpdate = false;
	GetSprite()->SetFlipbook(UpIdleAnimation);
}
int32 AParentCombatCharacter::GetSpeedStat()
{
	return SpeedStat;
}
void AParentCombatCharacter::TakeTurn()
{
	PathwayPoints.Empty();
	if ((NumberOfMovesRemaining > 0)) //& (NumberOfAttacksRemaining>0))
	{
		if (bChooseMove)
		{
			if (NumberOfMovesRemaining > 0)
			{
				//Get the chosen position from the player when they click
				PathwayPoints.Add(GetGridNum(GetActorLocation(),WorldGridRef));
				PathwayPoints.Add(MoveToChosenPosition);
				MoveToPosition();
				NumberOfMovesRemaining--;
			}
			else
			{
				bChooseMove = false;
			}
		}
		if (bChooseAttack)
		{
			if (NumberOfAttacksRemaining > 0)
			{

			}
		}
	}
	else if (!bInMovement & !bIsAttacking)
	{
		//Once the character is out of moves, update the gamemode to increment the turn so that the next player can take a turn
		GetWorld()->GetAuthGameMode<AProject_152GameMode>()->bNextTurn = true;	
	}
}
void AParentCombatCharacter::RefreshMoves(int32 MovementsAdded)
{
	NumberOfMovesRemaining += MovementsAdded;
}

//This is used to keep track of the characters position on the grid. This Allows characters to not overlap. Last known position has to be re set back to its original
void AParentCombatCharacter::UpdatePositionOnGrid(ACombatGrid* CombatGridRef)
{
	int32 CurrentPosition = GetGridNum(GetActorLocation(), WorldGridRef);
	CombatGridRef->GridType[LastKnownPosition] = 0;
	CombatGridRef->GridType[CurrentPosition] = 1;
	LastKnownPosition = CurrentPosition;
}