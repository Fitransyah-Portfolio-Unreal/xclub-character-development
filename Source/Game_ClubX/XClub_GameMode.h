// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainCharacter.h"
#include "XClub_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLUBX_API AXClub_GameMode : public AGameMode
{
	GENERATED_BODY()

	public:
	AXClub_GameMode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	TArray<TSubclassOf<class AMainCharacter>> ArrayOfCharacters;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
	virtual void InitGameState() override;
};
