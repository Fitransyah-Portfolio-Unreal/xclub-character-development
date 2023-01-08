// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	CollisionVolume->SetSphereRadius(75, true);
	RootComponent = CollisionVolume;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	Mesh->SetupAttachment(GetRootComponent());

	IdleParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IdleParticleComponent"));
	IdleParticleComponent->SetupAttachment(GetRootComponent());

	RotationRate = 45.f;

	bIdleParticleActive = false;
	bOverlapParticleActive = false;
	bRotate = false;
}


// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverLapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AItem::OnOverlapEnd);

	if (!bIdleParticleActive)
	{
		IdleParticleComponent->Deactivate();
	}
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotate)
	{
		FRotator InitialRotation = GetActorRotation();
		InitialRotation.Yaw += DeltaTime * RotationRate;
		SetActorRotation(InitialRotation);
	}
}

void AItem::OnOverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//FString Name = GetActorNameOrLabel();
	//FString OtherName = OtherActor->GetActorLabel();
	//UE_LOG(LogTemp, Warning, TEXT("%s begin overlapped by: %s"), *Name, *OtherName );

	AMainCharacter*  MainChar = Cast<AMainCharacter>(OtherActor);
	if (MainChar)
	{
		if (OverlapParticle && bOverlapParticleActive)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticle, GetActorLocation(), FRotator(0.f), true, EPSCPoolMethod::None, true);
		}
	}
}

void AItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//FString Name = GetActorNameOrLabel();
	//FString OtherName = OtherActor->GetActorLabel();
	//UE_LOG(LogTemp, Warning, TEXT("%s end overlapped by: %s"), *Name, *OtherName);
}