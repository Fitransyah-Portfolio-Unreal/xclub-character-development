// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class GAME_CLUBX_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item | Basic Setting")
	class USphereComponent* CollisionVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item | Basic Setting")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Basic Setting")
	class UParticleSystemComponent* IdleParticleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Basic Setting")
	class UParticleSystem* OverlapParticle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Behaviour Setting")
	float RotationRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | Behaviour Setting")
	bool bIdleParticleActive;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | Behaviour Setting")
	bool bOverlapParticleActive;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | Behaviour Setting")
	bool bRotate;
	UFUNCTION()
	virtual void OnOverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
