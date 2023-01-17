// Fill out your copyright notice in the Description page of Project Settings.


#include "XClub_GameMode.h"
#include "Kismet/KismetSystemLibrary.h"

AXClub_GameMode::AXClub_GameMode()
{

}

void AXClub_GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AXClub_GameMode::InitGameState()
{
	Super::InitGameState();
}