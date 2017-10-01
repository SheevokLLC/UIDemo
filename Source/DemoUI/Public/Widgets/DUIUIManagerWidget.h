#pragma once

#include "Blueprint/UserWidget.h"
#include "DUIDialogWidget.h"
#include "DUIUIManagerWidget.generated.h"

UCLASS(Abstract)
class UDUIUIManagerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RequestShowDialog(const FText& Message);

protected:
	UFUNCTION(BlueprintNativeEvent)
	void ShowDialog(UDUIDialogWidget* DialogWidgetToShow);

	UFUNCTION(BlueprintNativeEvent)
	void CloseDialog(UDUIDialogWidget* DialogWidgetToClose);

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDUIDialogWidget> DialogWidgetType;
};