#pragma once

#include "Blueprint/UserWidget.h"
#include "Text.h"
#include "DUIDialogWidget.generated.h"


DECLARE_DELEGATE(FDUIOnRequestCloseDialog);

UCLASS(Abstract)
class UDUIDialogWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetMessage(const FText& Message);

	FDUIOnRequestCloseDialog OnRequestCloseDialogEvent;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void HandleDifferentMessageSet();

	UFUNCTION(BlueprintCallable)
	void RequestCloseDialog();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText Message;
};