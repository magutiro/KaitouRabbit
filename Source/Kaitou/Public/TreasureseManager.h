// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include <TreasureController.h>
#include "TreasureseManager.generated.h"

UCLASS()
class KAITOU_API ATreasureseManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreasureseManager();
	//Treasureクラス（宝）を格納するリスト
	UPROPERTY(EditAnywhere, Category = "Treasure")
		TArray<AActor*> treasureList;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetTreasureState(int T_Number);

};
