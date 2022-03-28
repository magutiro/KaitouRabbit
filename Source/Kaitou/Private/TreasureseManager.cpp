// Fill out your copyright notice in the Description page of Project Settings.


#include "TreasureseManager.h"

// Sets default values
ATreasureseManager::ATreasureseManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATreasureseManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATreasureseManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATreasureseManager::SetTreasureState(int T_Number)
{
	UActorComponent* comp = treasureList[T_Number]->GetComponentByClass(UTreasureController::StaticClass());

	UTreasureController* treasure = Cast<UTreasureController>(comp);

	treasure->TreasureType = ETreasureState::T_HAND;
}