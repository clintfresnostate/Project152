// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "InventoryItem.h"
#include "CombatGrid.h"
#include "ParentCombatCharacter.generated.h"

/**
 * 
 */
class UTextRenderComponent;

UCLASS()
class PROJECT_152_API AParentCombatCharacter : public APaperCharacter
{
	GENERATED_BODY()
		// This class is the default character for Project_152, and it is responsible for all
		// physical interaction between the player and the world.
		//
		//   The capsule component (inherited from ACharacter) handles collision with the world
		//   The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
		//   The Sprite component (inherited from APaperCharacter) handles the visuals

		UTextRenderComponent* TextComponent;
		virtual void Tick(float DeltaSeconds) override;

	protected:

		//Initialize Arrow Component
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UArrowComponent* BaseOfCharacterArrow;

		// The animation to play while running around
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* RunningAnimation;

		// The animation to play while idle (standing still)
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* IdleAnimation;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* DownAnimation;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* AttackAnimation;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* DownIdleAnimation;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* UpAnimation;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* UpIdleAnimation;

		/** Called to choose the correct animation to play based on the character's movement state */
		void UpdateAnimation();

		/** Called for side to side input */
		void MoveRight(float Value);
		void MoveDown(float Value);
		void UpdateCharacter();


		// APawn interface
		virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
		// End of APawn interface

		//Inventory, Array of FInventoryItemStructs
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
			TArray<FInventoryItemStruct> InventoryArray;


		//Drops the item
		UFUNCTION(BlueprintCallable, Category = Inventory)
			void DropItem(FInventoryItemStruct Item);

		/* Don't Need this quite yet
		//Uses the item and calls the blueprint event
		UFUNCTION(BlueprintCallable, Category = Inventory)
			void UseItem(FInventoryItemStruct Item);
		*/

		//Updates our Inventory UI
		UFUNCTION(BlueprintNativeEvent, Category = Inventory)
			void RefreshInventory(); // Dummy event that notifies the UI that our inventory has been updated

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory)
			bool bIsWithinItemRange;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory)
			AInventoryItem* FocusedItem; // Item that is within our radius

		UFUNCTION(BlueprintCallable, Category = Inventory)
			void SetWithinItemRadius(bool bIsInRadius, AInventoryItem* Item);

		UFUNCTION(BlueprintCallable, Category = Inventory)
			void UpdateInventory();
		
		/*   GRID MOVEMENT   */
		UFUNCTION(BlueprintCallable, Category =GridMovement)
			void MoveToPosition();

		UFUNCTION(BlueprintCallable, Category = GridMovement)
			int32 GetGridNum(FVector InputPosition, TArray<FVector> WorldGridRef);
			
		UFUNCTION(BlueprintCallable, Category = GridMovement)
		TArray<FVector> GetLocationOfTilesWithinOneUnit(int32 GridNum, TArray<FVector> WorldGridRef, ACombatGrid* CombatGridRef);

		

		
		
	public:
		AParentCombatCharacter();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
			FVector StartingSpawnLocation;

		

		//Variables for Movement
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridMovement)
			int32 ForLoopVariable;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridMovement)
			float Speed;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridMovement)
			float heightoffset;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridMovement)
			FVector InitialLocation;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridMovement)
			bool bUseDiagonals = true;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridMovement)
			float X_Direction = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridMovement)
			float Y_Direction = 0;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridMovement)
			TArray<int32> PathwayPoints;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridMovement)
			bool bInMovement = false;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridMovement)
			bool bEnableUpdate = true;
		//Grid Movement
		UFUNCTION(BlueprintCallable, Category = GridMovement)
			void FaceRight();
		UFUNCTION(BlueprintCallable, Category = GridMovement)
			void FaceDown();
		UFUNCTION(BlueprintCallable, Category = GridMovement)
			void FaceLeft();
		UFUNCTION(BlueprintCallable, Category = GridMovement)
			void FaceUp();

		//Sprite Rotation Variables
		//FOR RIGHT FACING SPRITE. Set these once Blueprint is created.
		FRotator MoveRightRotation = FRotator(0, 0, -45);
		FRotator MoveLeftRotation = FRotator(0, 180, 45);


		ACombatGrid* CombatGrid;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grid)
			int32 TestGridNum;

		// Need to set this ref to the World Grid or else the character wont know which grid to apply to
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridMovement)
			TArray<FVector> WorldGridRef;

		UFUNCTION(BlueprintNativeEvent, Category = GridMovement)
			void MoveToGridEvent();


		//Adds the item to the inventory given its FInventoryItemStruct or "data"
		UFUNCTION(BlueprintCallable, Category = Inventory)
			void GiveItem(FInventoryItemStruct Item);


		/*   COMBAT   */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
			int32 NumberOfAttacksRemaining = 1;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
			int32 NumberOfMovesRemaining = 1;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
			bool bIsAttacking = false;
		UFUNCTION(BlueprintCallable, Category = Combat)
			void TakeTurn();
		
	


		/*  STATS  */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
			int32 SpeedStat;
		//Used to grab the speed stat
		int32 GetSpeedStat(void);


		/* TEST Variables for Later Implementation*/
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
			bool bChooseMove = false;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
			int32 MoveToChosenPosition;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
			bool bChooseAttack;
	
};
