// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlideDoor.generated.h"

UCLASS()
class GAME_CLUBX_API ASlideDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlideDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SlideDoor")
	class UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SlideDoor")
	class UStaticMeshComponent* RightDoor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SlideDoor")
	class UStaticMeshComponent* LeftDoor;

	UPROPERTY(BlueprintReadWrite, Category = "SlideDoor")
	FVector InitialRightDoorLocation;

	UPROPERTY(BlueprintReadWrite, Category = "SlideDoor")
	FVector InitialLeftDoorLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlideDoor | Sounds")
	class USoundCue* DoorOpeningSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlideDoor | Sounds")
	class USoundCue* DoorClosingSound;

	FTimerHandle ClosingHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SlideDoor")
	float CloseTime;

	bool bCharNearDoor;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "SlideDoor")
	void SlideOpenRightDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "SlideDoor")
	void SlideCloseRightDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "SlideDoor")
	void SlideOpenLeftDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "SlideDoor")
	void SlideCloseLeftDoor();

	UFUNCTION(BlueprintCallable, Category = "SlideDoor")
	void UpdateRightDoorLocation(float OpenDirection);

	UFUNCTION(BlueprintCallable, Category = "SlideDoor")
	void UpdateLefttDoorLocation(float OpenDirection);

	void CloseDoor();
};
