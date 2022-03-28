// Fill out your copyright notice in the Description page of Project Settings.


#include "TreasureManager.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ATreasureManager::ATreasureManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	SphereComp->SetupAttachment(Scene);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &ATreasureManager::OnOverlapEnd);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATreasureManager::OnOverlapBegin);

	WidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(TEXT("/Game/Image/TreasureUI"))).LoadSynchronous();
}

// Called when the game starts or when spawned
void ATreasureManager::BeginPlay()
{
	Super::BeginPlay();
	UTreasureWidget* UserWidget = CreateWidget<UTreasureWidget>(GetWorld(), WidgetClass);
	UserWidget->AddToViewport();
	Widget = UserWidget;
}

// Called every frame
void ATreasureManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATreasureManager::SetTreasureState(int T_Number)
{
	UActorComponent* comp = treasureList[T_Number]->GetComponentByClass(UTreasureController::StaticClass());

	UTreasureController* treasure = Cast<UTreasureController>(comp);
	
	treasure->TreasureType = ETreasureState::T_HAND;
}

void ATreasureManager::SetTreasureImage(bool isView, int T_Numer) {
	Widget->setImage(isView, T_Numer);
}
void ATreasureManager::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Overlapした際に実行したいイベント
	if (OtherActor->ActorHasTag("Player")) {

		for(AActor* actor : treasureList)
		{
			UActorComponent* comp = actor->GetComponentByClass(UTreasureController::StaticClass());
			UTreasureController* treasure = Cast<UTreasureController>(comp);

			if (treasure->TreasureType == ETreasureState::T_HAND) {
				UE_LOG(LogTemp, Warning, TEXT("%s: Hit!"), __FUNCTIONW__);
				treasureCount++;
				treasure->TreasureType = ETreasureState::T_GOAL;
				Widget->setImage(false, treasure->treasureNumber); 
				UMyGameInstance* instance = UMyGameInstance::GetInstance();
				if (instance)
				{
					instance->SetTreasure(true, treasure->treasureNumber);
				}
			}
		}
		if (treasureCount == treasureList.Num()) {
			UGameplayStatics::OpenLevel(this, TEXT("Result"), true);
		}
	}

}
void ATreasureManager::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player")) {
		
	}
}
