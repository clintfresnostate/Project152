// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Project_152.h"
#include "Project_152GameMode.h"
#include "Project_152Character.h"

AProject_152GameMode::AProject_152GameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = AProject_152Character::StaticClass();	
}
