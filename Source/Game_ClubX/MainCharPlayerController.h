// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainCharPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLUBX_API AMainCharPlayerController : public APlayerController
{
	GENERATED_BODY()
	public:
	// Reference to the UMG assets in the editor
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "GameplayWidgets")
	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	// Variable to hold the widget after creating it
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "GameplayWidgets")
	UUserWidget* HUDOverlay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Properties")
	class ACharactersStorage* CharStorage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Properties")
	class AActor* PlacementPointActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Properties")
	class AMainCharacter* ActiveDisplayedCharacter;

	UFUNCTION(BlueprintCallable)
	void SetCharacter(FString SelectedCharacter = "");

	protected:
	virtual void BeginPlay() override;
};
