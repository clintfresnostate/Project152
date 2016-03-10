// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ParentCombatCharacter.h"
#include "BlueLaserRobot.generated.h"

/**
 This Class inherits from ParentCombatCharacter and is used to tailor certain variables and quantities to the robot alone 
 */
UCLASS()
class PROJECT_152_API ABlueLaserRobot : public AParentCombatCharacter
{
	GENERATED_BODY()
	
protected:

	
public:

	UFUNCTION(BlueprintCallable, Category = Attack)
		void AttackWithLaser(FVector SourceLocation, FVector TargetLocation);

	UFUNCTION(BlueprintNativeEvent, Category = Attack)
		void AttackWithLaserEvent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		FVector BeamSourceLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
		FVector BeamTargetLocation = AttackTargetLocation;
};
