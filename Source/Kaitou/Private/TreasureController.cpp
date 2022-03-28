// Fill out your copyright notice in the Description page of Project Settings.


#include "TreasureController.h"
#include "PlayerBindTreasure.h"
#include "Misc/OutputDeviceNull.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
// Sets default values for this component's properties
UTreasureController::UTreasureController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	scorePoint = 100;
	getTime = 2.0f;
	TreasureType = ETreasureState::T_SHOWCASE;

	WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(TEXT("/Game/Image/TreasureUI"))).LoadSynchronous();
	
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	//RootComponent = Scene;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	SphereComp->SetupAttachment(Scene);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &UTreasureController::OnOverlapEnd);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &UTreasureController::OnOverlapBegin);
	// ...

	
}


// Called when the game starts
void UTreasureController::BeginPlay()
{
	Super::BeginPlay();
	// ...
}


// Called every frame
void UTreasureController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	switch (TreasureType)
	{
		case ETreasureState::T_GOAL:
			
			break;
		case ETreasureState::T_HAND:
			if (IsFirst) {
				Hand();
				IsFirst = false;
			}
			break;
		case ETreasureState::T_SHOWCASE:

			break;
	}
	// ...
}
void UTreasureController::Hand() {
	UE_LOG(LogTemp, Warning, TEXT("%s: inHand!"), __FUNCTIONW__);

	ATreasureManager* TM = Cast<ATreasureManager>(treasureManger);
	TM->SetTreasureImage(true, treasureNumber);
	//SetImage(true, treasureNumber);
	GetOwner()->SetActorHiddenInGame(true);
}


void UTreasureController::StartTimer(float time) {

	// 第3引数：デリゲートとして渡す関数
	// 第4引数：遅延させる秒数
	// 第5引数：処理をループさせるか
	// 第5引数：開始時間を遅延させる秒数
	//GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UTreasureController::GetTreasure, 0.2f, false);
}
void UTreasureController::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
#if 0
	// Handleに登録されたTimerの解放
	timerManager.ClearTimer(timerHandle);
#endif
	// このActorが所有するタイマーの解放
	timerManager.ClearAllTimersForObject(this);
}
void UTreasureController::GetTreasure() {

	UE_LOG(LogTemp, Warning, TEXT("%s: Hit!"), __FUNCTIONW__);
}

void UTreasureController::SetTreasreUI(UTreasureWidget* T_Widget){
	Widget = T_Widget;
}
void UTreasureController::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Overlapした際に実行したいイベント
	if (OtherActor->ActorHasTag("Player")) {
		isHitting = true;
		UActorComponent* comp = OtherActor->GetComponentByClass(UPlayerBindTreasure::StaticClass());

		UPlayerBindTreasure* player = Cast<UPlayerBindTreasure>(comp);
		if (player) {
			UE_LOG(LogTemp, Warning, TEXT("%s: check!"), __FUNCTIONW__);
			player->HitTreasure(isHitting, treasureNumber);
		}

		//GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UTreasureController::GetTreasure, 0.2f, false);
	}

}
void UTreasureController::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player")) {
		isHitting = false;
		UPlayerBindTreasure* player = Cast<UPlayerBindTreasure>(OtherActor);
		if (player) {
			player->HitTreasure(isHitting, treasureNumber);
		}
	}
}
