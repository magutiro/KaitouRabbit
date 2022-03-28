// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "TreasureWidget.h"
#include "TreasureManager.h"
#include "TreasureController.generated.h"

UENUM(BlueprintType)
enum class ETreasureState : uint8
{
	T_SHOWCASE UMETA(DisplayName = "Showcase"),
	T_HAND     UMETA(DisplayName = "Hand in Player"),
	T_GOAL     UMETA(DisplayName = "Goal Completed"),
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class KAITOU_API UTreasureController : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Treasure")
		int scorePoint;
	UPROPERTY(EditAnywhere, Category = "Treasure")
		float getTime;
	UPROPERTY(EditAnywhere, Category = "Treasure")
		int treasureNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* Scene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* SphereComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTreasureWidget* Widget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Treasure")
		ETreasureState TreasureType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Treasure")
		AActor* treasureManger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Treasure")
		TSubclassOf<class UUserWidget> WidgetClass;
	bool isHitting;
	bool isGet;
	bool IsFirst = true;
	//FTimerManager& timerManager = GetWorld()->GetTimerManager();
	//↑なぜかエディタがクラッシュするため解除不可
	UTreasureController();
private:
	FTimerHandle timerHandle;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void StartTimer(float time);
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
	virtual void GetTreasure();
	virtual void Hand();
	//UFUNCTION(Category = "MyFunc")
		//void SetTreasreUI();
	UFUNCTION(BlueprintCallable, Category = "MyFunc")
		void SetTreasreUI(UTreasureWidget* T_Widget);
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintImplementableEvent, Category = "Treasure|UI|SetImage")
		void SetImage(bool isView, int T_Number);
};
