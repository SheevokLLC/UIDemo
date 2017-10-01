#pragma once

#include "DelegateCombinations.h"
#include "Blueprint/UserWidget.h"
#include "DUITabButton.generated.h"

DECLARE_MULTICAST_DELEGATE(FDUIOnTabRequestActivate)

class UButton;

UCLASS(Abstract)
class UDUITabButton : public UUserWidget
{
	GENERATED_BODY()

public:
	void NotifyTabActivated();
	void NotifyTabDeactivated();

	FDUIOnTabRequestActivate OnTabRequestActivateEvent;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void HandleIsActiveTabChanged();

private:
	UFUNCTION()
	void HandleInternalButtonClicked();

public:
	UPROPERTY(BlueprintReadOnly)
	bool IsActiveTab;

protected:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UButton* InternalButton;
};