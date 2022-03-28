// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include <TreasureController.h>
#include "TreasureWidget.h"
#include "TreasureManager.generated.h"

UCLASS()
class ATreasureManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreasureManager();

	//Treasureクラス（宝）を格納するリスト
	UPROPERTY(EditAnywhere, Category = "Treasure")
		TArray<AActor*> treasureList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Treasure")
		TSubclassOf<class UUserWidget> WidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Treasure")
		UTreasureWidget* Widget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* Scene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* SphereComp;
	int treasureCount = 0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetTreasureState(int T_Number);
	virtual void SetTreasureImage(bool isView, int T_Number);
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintImplementableEvent, Category = "Treasure|UI|SetImage")
		void SetImage(bool isView, int T_Number);
};
