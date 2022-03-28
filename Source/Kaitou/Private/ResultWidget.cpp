// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultWidget.h"
#include "Components/Image.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
void UResultWidget::NativeConstruct()
{
	Super::NativeConstruct();
	S_Image = Cast<UImage>(GetWidgetFromName("ImageS"));
	R_Image = Cast<UImage>(GetWidgetFromName("ImageR"));
	E_Image = Cast<UImage>(GetWidgetFromName("ImageE"));
	UMyGameInstance* instance = UMyGameInstance::GetInstance();
	if (instance)
	{
		for (int i = 0;i < 3;i++) {
			if (instance->isTreasureGet[i]) {
				setImage(true,i);
				UE_LOG(LogTemp, Warning, TEXT("%s: Hit!"), __FUNCTIONW__);
			}
		}
	}
	
}

void UResultWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// Œp³Œ³ˆ—
	Super::NativeTick(MyGeometry, InDeltaTime);
	// ...
}

void UResultWidget::setImage(bool B_View, int T_Number) {
	ESlateVisibility vi;
	if (B_View) {
		vi = ESlateVisibility::Visible;
	}
	else {
		vi = ESlateVisibility::Hidden;
	}
	if (S_Image != nullptr && R_Image != nullptr && E_Image != nullptr) {
		switch (T_Number) {
		case 0:
			S_Image->SetVisibility(vi);
			break;
		case 1:
			R_Image->SetVisibility(vi);
			break;
		case 2:
			E_Image->SetVisibility(vi);
			break;
		default:
			break;
		}
	}
}