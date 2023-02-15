// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLUBX_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()
	public:
	UPROPERTY(BlueprintReadOnly,Category = "BaseUserWidget Properties")
	class APlayerController* LocalPlayerController;


	bool Initialize() override;

	
};
