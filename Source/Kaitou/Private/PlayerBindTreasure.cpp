// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBindTreasure.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPlayerBindTreasure::UPlayerBindTreasure()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UPlayerBindTreasure::BeginPlay()
{
	Super::BeginPlay();
	// ...
	TSubclassOf<ATreasureManager> findClass;
	findClass = ATreasureManager::StaticClass();
	TArray<AActor*> emitters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findClass, emitters);

	if (emitters.Num())
	{
		ATreasureManager* emitter = Cast<ATreasureManager>(emitters[0]);
		TM = emitter;
	}
	//CapsuleComp = Cast<UCapsuleComponent>(GetOwner()->GetComponentByClass(UCapsuleComponent::StaticClass()));
	//“ü—Í‚ðŽæ“¾
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("Find", IE_Pressed, this, &UPlayerBindTreasure::PressF);
		InputComponent->BindAction("Find", IE_Released, this, &UPlayerBindTreasure::ReleaseF);
	}
}

void UPlayerBindTreasure::StartTimer(float time) {

	// ‘æ3ˆø”FƒfƒŠƒQ[ƒg‚Æ‚µ‚Ä“n‚·ŠÖ”
	// ‘æ4ˆø”F’x‰„‚³‚¹‚é•b”
	// ‘æ5ˆø”Fˆ—‚ðƒ‹[ƒv‚³‚¹‚é‚©
	// ‘æ5ˆø”FŠJŽnŽžŠÔ‚ð’x‰„‚³‚¹‚é•b”
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UPlayerBindTreasure::GetTreasure, time, false);
}
void UPlayerBindTreasure::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	FTimerManager& timerManager = GetWorld()->GetTimerManager();
#if 0
	// Handle‚É“o˜^‚³‚ê‚½Timer‚Ì‰ð•ú
	timerManager.ClearTimer(timerHandle);
#endif
	// ‚±‚ÌActor‚ªŠ—L‚·‚éƒ^ƒCƒ}[‚Ì‰ð•ú
	timerManager.ClearAllTimersForObject(this);
}
void UPlayerBindTreasure::PressF() {
	UE_LOG(LogTemp, Warning, TEXT("%s: FPRESS!"), __FUNCTIONW__);
	if (isGetting) {
		StartTimer(4.f);
	}
}
void UPlayerBindTreasure::ReleaseF() {
	UE_LOG(LogTemp, Warning, TEXT("%s: FRelease!"), __FUNCTIONW__);
	isGetting = false;


	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	// Handle‚É“o˜^‚³‚ê‚½Timer‚Ì‰ð•ú
	timerManager.ClearTimer(timerHandle);
}


// Called every frame
void UPlayerBindTreasure::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UPlayerBindTreasure::HitTreasure(bool isHitting, int T_Number) {

	treasureNumber = T_Number;
	if (isHitting) {
		isGetting = true;
	}
	else {
		FTimerManager& timerManager = GetWorld()->GetTimerManager();
		// Handle‚É“o˜^‚³‚ê‚½Timer‚Ì‰ð•ú
		timerManager.ClearTimer(timerHandle);
		isGetting = false;
	}

}
void UPlayerBindTreasure::GetTreasure() {
	UE_LOG(LogTemp, Warning, TEXT("%s: GET!"), __FUNCTIONW__);
	TM->SetTreasureState(treasureNumber);
}

