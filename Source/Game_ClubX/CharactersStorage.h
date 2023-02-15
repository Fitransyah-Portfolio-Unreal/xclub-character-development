// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharactersStorage.generated.h"

UCLASS()
class GAME_CLUBX_API ACharactersStorage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharactersStorage();

	UPROPERTY(EditDefaultsOnly, Category = "Characters | Lobby")
	TMap<FString, TSubclassOf<class AActor>> LobbyCharMap;

	UPROPERTY(EditDefaultsOnly, Category = "Characters | MainCharacter")
	TMap<FString, TSubclassOf<class AMainCharacter>> MainCharMap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
