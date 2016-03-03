// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_152.h"
#include "BlueLaserRobot.h"
#include "ParentCombatCharacter.h"

void ABlueLaserRobot::AttackWithLaser(FVector SourceLocation, FVector TargetLocation)
{
	//Attaching Beam Emitters it much easier in the editor in order to make it look good so this will be a native event

	BeamSourceLocation = SourceLocation;
	BeamTargetLocation = TargetLocation;

	//Check if it can attack
	if (NumberOfAttacksRemaining>0)
	{
		//Call BlueprintNative Event in order to setup the animation
		AttackWithLaserEvent();
		bIsAttacking = true;
	}

}
void ABlueLaserRobot::AttackWithLaserEvent_Implementation()
{

}