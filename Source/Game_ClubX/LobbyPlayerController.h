// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLUBX_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
	public:
	// ------------------------------------------------UI
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "MainWidgets")
	TSubclassOf<class UUserWidget> MainMenuWidget;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "MainWidgets")
	UUserWidget* MainMenu;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "MainWidgets")
	TSubclassOf<UUserWidget> SettingMenuWidget;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "MainWidgets")
	UUserWidget* SettingMenu;

	bool bSettingMenuVisible;

	UFUNCTION(BlueprintCallable)
	void DisplaySettingMenu();
	
	UFUNCTION(BlueprintCallable)
	void RemoveSettingMenu();
	

	void ToggleSettingMenu();

	// ------------------------------------------------Level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Properties")
	class ACharactersStorage* CharStorage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Properties")
	class AActor* PlacementPointActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Properties")
	AActor* ActiveDisplayedActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level Properties")
	FString ActiveDisplayedActorName;

	UFUNCTION(BlueprintCallable)
	void SetFirstActor();

	UFUNCTION(BlueprintCallable)
	void SetActiveDisplayerdActor(FString NewActiveDisplayedActor);

	UFUNCTION(BlueprintCallable)
	void DestroyActiveDisplayedActor();



	protected:
	virtual void BeginPlay() override;
};
