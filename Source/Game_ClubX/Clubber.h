// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.h"
#include "Clubber.generated.h"

UCLASS()
class GAME_CLUBX_API AClubber : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AClubber();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Clubber")
	class USphereComponent* AgroSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Clubber")
	AMainCharacter* TargetedPlayer;

	FORCEINLINE  AMainCharacter* GetTargetedPlayer() { return TargetedPlayer;}
	FORCEINLINE  void SetTargetedPlayer(AMainCharacter* Target) {TargetedPlayer = Target;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnOverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
