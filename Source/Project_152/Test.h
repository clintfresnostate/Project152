// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

#include "Test.generated.h"


UCLASS()
class PROJECT_152_API ATest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATest();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//IMPLEMENT_SIMPLE_AUTOMATION_TEST(ATest, "Windows.SetResolution", ATF_Game)
	
};
