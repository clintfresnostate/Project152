// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PaperCharacter.h"
#include "InventoryItem.h"
#include "Project_152Character.generated.h"


// This class is the default character for Project_152, and it is responsible for all
// physical interaction between the player and the world.
//
//   The capsule component (inherited from ACharacter) handles collision with the world
//   The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
//   The Sprite component (inherited from APaperCharacter) handles the visuals

class UTextRenderComponent;

UCLASS(config=Game)
class AProject_152Character : public APaperCharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UTextRenderComponent* TextComponent;
	virtual void Tick(float DeltaSeconds) override;
protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	/** Called for side to side input */
	void MoveRight(float Value);
	void MoveDown(float Value);
	void UpdateCharacter();

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	//Inventory, Array of FInventoryItemStructs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
		TArray<FInventoryItemStruct> InventoryArray;

	//Drops the item
	UFUNCTION(BlueprintCallable, Category = Inventory)
		void DropItem(FInventoryItemStruct Item);

	//Uses the item and calls the blueprint event
	UFUNCTION(BlueprintCallable, Category = Inventory)
		void UseItem(FInventoryItemStruct Item);

	//Updates our Inventory UI
	UFUNCTION(BlueprintNativeEvent, Category = Inventory)
		void RefreshInventory(); // Dummy event that notifies the UI that our inventory has been updated

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory)
		bool bIsWithinItemRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory)
		AInventoryItem* FocusedItem; // Item that is within our radius

	UFUNCTION(BlueprintCallable, Category = Inventory)
		void UpdateInventory();
public:
	AProject_152Character();

	//Adds the item to the inventory given its FInventoryItemStruct or "data"
	UFUNCTION(BlueprintCallable, Category = Inventory)
		void GiveItem(FInventoryItemStruct Item);

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION(BlueprintCallable, Category = Inventory)
		void SetWithinItemRadius(bool bIsInRadius, AInventoryItem* Item);


};
