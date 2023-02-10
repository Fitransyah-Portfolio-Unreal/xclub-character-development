// Fill out your copyright notice in the Description page of Project Settings.


#include "Clubber.h"
#include "Components/SphereComponent.h"

// Sets default values
AClubber::AClubber()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	AgroSphere->SetupAttachment(GetRootComponent());
	AgroSphere->SetSphereRadius(300.f);
	AgroSphere->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
	AgroSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AgroSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);

	TargetedPlayer = nullptr;
	bPlayerIsExist = false;
}

// Called when the game starts or when spawned
void AClubber::BeginPlay()
{
	Super::BeginPlay();
	
	AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &AClubber::OnOverLapBegin);
	AgroSphere->OnComponentEndOverlap.AddDynamic(this, &AClubber::OnOverlapEnd);
}

// Called every frame
void AClubber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AClubber::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AClubber::OnOverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		if (Main)
		{
			SetTargetedPlayer(Main);
			bPlayerIsExist = true;
 
		}
	}
}

void AClubber::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		if (Main)
		{
			bPlayerIsExist = false;
			SetTargetedPlayer(nullptr);

		}
	}
}

