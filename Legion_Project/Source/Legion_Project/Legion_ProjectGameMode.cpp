// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Legion_ProjectGameMode.h"
#include "LegionCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALegion_ProjectGameMode::ALegion_ProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Character/LegionCharacter_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
