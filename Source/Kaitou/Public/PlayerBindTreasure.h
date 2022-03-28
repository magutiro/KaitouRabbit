// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "TreasureManager.h"
#include "PlayerBindTreasure.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KAITOU_API UPlayerBindTreasure : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerBindTreasure();

UPROPERTY(EditAnywhere, Category = "Treasure")
	float DirectLength = 1000.f;
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Treasure")
	ATreasureManager* TM = nullptr;

	bool isGetting = false;

private:
	FTimerHandle timerHandle;
	UInputComponent* InputComponent = nullptr;
	int treasureNumber = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void StartTimer(float time);
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
	//ãﬂÇ≠Ç…Ç†ÇÈïÛÇ©ÇÁåƒÇ—èoÇ≥ÇÍÇÈä÷êî
	virtual void HitTreasure(bool isHitting, int T_Number);
	virtual void GetTreasure();

	virtual void PressF();
	virtual void ReleaseF();
	
};
