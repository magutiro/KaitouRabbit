// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Image.h"
#include "Math/UnrealMathUtility.h"
#include "TreasureWidget.h"
void UTreasureWidget::NativeConstruct()
{
	Super::NativeConstruct();
	S_Image = Cast<UImage>(GetWidgetFromName("ImageS"));
	R_Image = Cast<UImage>(GetWidgetFromName("ImageR"));
	E_Image = Cast<UImage>(GetWidgetFromName("ImageE"));
	//this->setImage(false, 1);
	//check(this->ImageS);
	//E_Image->SetVisibility(Visibility);
	
}

void UTreasureWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// Œp³Œ³ˆ—
	Super::NativeTick(MyGeometry, InDeltaTime);
	//Image->SetVisibility(Visibility);
	// ...
}

void UTreasureWidget::setImage(bool B_View, int T_Number) {
	ESlateVisibility vi;
	if (B_View) {
		vi = ESlateVisibility::Visible;
	}
	else {
		vi = ESlateVisibility::Hidden;
	}
	if(S_Image != nullptr && R_Image!=nullptr && E_Image!=nullptr){
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