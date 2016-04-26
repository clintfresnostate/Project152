// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Project_152.h"
#include "Project_152Character.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/ArrowComponent.h"
#include "Project_152GameMode.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include "MySaveGame.h"



DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);
//////////////////////////////////////////////////////////////////////////
// AProject_152Character

AProject_152Character::AProject_152Character()
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

	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->RelativeRotation = FRotator(0.0f, -90.0f, 0.0f);
	

	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 2048.0f;
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->bAbsoluteRotation = true;
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
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

void AProject_152Character::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeed = PlayerVelocity.Size();

	// Are we moving or standing still?
	UPaperFlipbook* DesiredAnimation = (PlayerSpeed > 0.0f) ? RunningAnimation : IdleAnimation;
	if( GetSprite()->GetFlipbook() != DesiredAnimation 	)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

void AProject_152Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	UpdateCharacter();	
	PlayerControllerRef = GetWorld()->GetFirstPlayerController();
	AProject_152GameMode* GameModeRef = Cast<AProject_152GameMode>(GetWorld()->GetAuthGameMode());

	if (GameModeRef->bInCombat)
	{
		if (GameModeRef->CharactersInCombat[(GameModeRef->TurnIncrement) % (GameModeRef->CharactersInCombat.Num())]->bIsHumanPlayer)
		{
			PlayerControllerRef->bShowMouseCursor = true;
			PlayerControllerRef->bEnableClickEvents = true;
			PlayerControllerRef->bEnableMouseOverEvents = true;

			if (bEnableIndicators)
			{
				SpawnIndicators();
			}
			if (bEnableMovementIndicators)
			{
				SpawnMovementIndicators();
			}
		}
		if (!GameModeRef->CharactersInCombat[(GameModeRef->TurnIncrement) % (GameModeRef->CharactersInCombat.Num())]->bIsHumanPlayer)
		{
			PlayerControllerRef->bShowMouseCursor = false;
			PlayerControllerRef->bEnableClickEvents = false;
			PlayerControllerRef->bEnableMouseOverEvents = false;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProject_152Character::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAxis("MoveRight", this, &AProject_152Character::MoveRight);
	InputComponent->BindAxis("MoveDown", this, &AProject_152Character::MoveDown);

	InputComponent->BindTouch(IE_Pressed, this, &AProject_152Character::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AProject_152Character::TouchStopped);
}

void AProject_152Character::MoveRight(float Value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}
void AProject_152Character::MoveDown(float Value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
}
void AProject_152Character::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AProject_152Character::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AProject_152Character::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();

	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();	
	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 180.0f, 0.0f));
			GetSprite()->SetWorldRotation(FRotator(0.0f, 0.0f, -45.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
			GetSprite()->SetWorldRotation(FRotator(0.0f, 180.0f, 45.0f));
		}
	}
}
void AProject_152Character::GiveItem(FInventoryItemStruct Item)
{

	//int32 idx = InventoryArray.Find(Item); // Grab the index of the item

	if (InventoryArray.Num()<=16) // If the index is NOT valid it means the item isnt in our inventory / array
	{
		//Then the item can be added!
		InventoryArray.Add(Item);
		RefreshInventory(); // Update our Ui

	}

}

void AProject_152Character::DropItem(FInventoryItemStruct Item)
{

	//AInventoryItem* WorldItem = GetWorld()->SpawnActor<AInventoryItem>(Item.ItemClass, GetActorLocation(), FRotator(0, 0, 0)); // Spawn the item in the world
	//WorldItem->ItemInfo = Item; // Assign the item info of the newly spawned item in the world to the one we dropped
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

void AProject_152Character::UseItem(FInventoryItemStruct Item)
{
	AInventoryItem* WorldItem = GetWorld()->SpawnActor<AInventoryItem>(Item.ItemClass, GetActorLocation(), FRotator(0, 0, 0)); // Spawn the item in the world
	WorldItem->UseItem(this); // call the blueprint event


}
void AProject_152Character::RefreshInventory_Implementation()
{

}

void AProject_152Character::UpdateInventory()
{
	RefreshInventory();
}

void AProject_152Character::SetWithinItemRadius(bool bIsInRadius, AInventoryItem* Item)
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
//Dummy Event used to spawn the target indicators
void AProject_152Character::SpawnIndicators_Implementation()
{

}
void AProject_152Character::SpawnMovementIndicators_Implementation()
{

}

/////////////////////////////////////////////////////////////////
// Saving/Loading Character

void AProject_152Character::SaveMainCharacter()
{
	AProject_152Character* newChar = Cast<AProject_152Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//FString PlayerName = TEXT("MainPlayer");
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance->mainPlayer = newChar;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

void AProject_152Character::LoadMainCharacter()
{
	UMySaveGame* LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	LoadGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("I'm sentient...")));
	AProject_152Character* PlayerCharacterToUse = LoadGameInstance->mainPlayer;
	//UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) = PlayerCharacterToUse;
}