// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameButton.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLUBX_API UGameButton : public UUserWidget
{
	GENERATED_BODY()

	protected:

	virtual bool Initialize() override;

	private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ActionButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* DanceButton;

	public:
	UFUNCTION(BlueprintImplementableEvent, Category = "CustomButton")
	void ActionButtonPressed();

	UFUNCTION(BlueprintImplementableEvent, Category = "CustomButton")
	void DanceButtonPressed();

	
};
