// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RushGameMode.h"
#include "RushPawn.h"

ARushGameMode::ARushGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = ARushPawn::StaticClass();
}
