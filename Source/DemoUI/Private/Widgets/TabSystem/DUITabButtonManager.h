#pragma once

#include "Blueprint/UserWidget.h"
#include "WidgetSwitcher.h"
#include "DUITabButtonManager.generated.h"

class UDUITabButton;

UCLASS(Abstract)
class UDUITabButtonManagerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterTabWithContent(UDUITabButton* TabButton, UWidget* TabContent);

	UFUNCTION(BlueprintCallable)
	void RegisterTabContentSwitcher(UWidgetSwitcher* TabContentWidgetSwitcher);

	void TryGuaranteeAnActiveTab();

private:
	void HandleTabRequestActivate(UDUITabButton* ClickedTabButton);
	void SetActiveTab(UDUITabButton* TabToActivate);

private:
	TMap<TWeakObjectPtr<UDUITabButton>, TWeakObjectPtr<UWidget>> TabButtonToContentWidgetMap;

	TWeakObjectPtr<UWidgetSwitcher> TabContentWidgetSwitcher;

	TWeakObjectPtr<UDUITabButton> LastActivatedTabButton;
};