// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "NPC.generated.h"
/**
 * 
 */
UCLASS()
class PROJECT_152_API ANPC : public APaperCharacter
{
	GENERATED_BODY()
public:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
		 USphereComponent* ProxSphere;
	// This is the NPC's message that he has to tell us.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
		FString NpcMessage;
	// When you create a blueprint from this class, you want to be
	// able to edit that message in blueprints,
	// that's why we have the EditAnywhere and BlueprintReadWrite
	// properties.
	// The corresponding body of this function is
	// ANPC::Prox_Implementation, __not__ ANPC::Prox()!
	// This is a bit weird and not what you'd expect,
	// but it happens because this is a BlueprintNativeEvent
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
		void Prox_Implementation();
	// you should just simply return from the function
	void ANPC::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent*
		OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &
		SweepResult)
	{
		// if the overlapped actor is not the player,
		// you should just simply return from the function
		if (Cast<APaperCharacter>(OtherActor) == nullptr)
		{
			return;
		}
		APlayerController* PController = GetWorld()-> GetFirstPlayerController();
		if (PController)
		{
			AMyHUD * hud = Cast<AMyHUD>(PController->GetHUD());
			hud->addMessage(Message(NpcMessage, 5.f, FColor::White));
		}
	}


};
