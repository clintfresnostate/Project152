// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ParentCombatCharacter.h"
#include "GameFramework/Actor.h"
#include "CombatHandler.generated.h"


UCLASS()
class PROJECT_152_API ACombatHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACombatHandler();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
};
