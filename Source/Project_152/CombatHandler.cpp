// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_152.h"
#include "CombatHandler.h"


// Sets default values
ACombatHandler::ACombatHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACombatHandler::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACombatHandler::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

