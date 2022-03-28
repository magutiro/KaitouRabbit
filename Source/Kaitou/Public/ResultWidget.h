// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class KAITOU_API UResultWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "MyFunc")
		void setImage(bool B_View, int T_Number);
private:
	UTexture2D* Tex;
	class UImage* S_Image;
	class UImage* R_Image;
	class UImage* E_Image;
};
