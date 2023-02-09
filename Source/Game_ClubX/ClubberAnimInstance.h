// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacter.h"
#include "ClubberAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAME_CLUBX_API UClubberAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	public:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ClubberAnimInstance")
	class APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ClubberAnimInstance")
	class AClubber* Clubber;

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "ClubberAnimInstance")
	void UpdateAnimationProperties();
	
};
