// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "XClub_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLUBX_API UXClub_GameInstance : public UGameInstance
{
	GENERATED_BODY()

	public:

	virtual void Init() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	FString SelectedCharacter;	
};
