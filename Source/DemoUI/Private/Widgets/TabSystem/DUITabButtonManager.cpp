#include "DUITabButtonManager.h"
#include "DUITabButton.h"

void UDUITabButtonManagerWidget::RegisterTabWithContent(UDUITabButton* TabButton, UWidget* TabContent)
{
	TabButtonToContentWidgetMap.Add(TabButton, TabContent);

	TWeakObjectPtr<ThisClass> WeakThis = this;
	TWeakObjectPtr<UDUITabButton> WeakTabButton = TabButton;
	const auto& HandleTabRequestActivateThunk = [WeakThis, WeakTabButton]()
	{
		if (!WeakThis.IsValid() || !WeakTabButton.IsValid())
		{
			return;
		}

		WeakThis->HandleTabRequestActivate(WeakTabButton.Get());
	};
	TabButton->OnTabRequestActivateEvent.AddLambda(HandleTabRequestActivateThunk);

	TryGuaranteeAnActiveTab();
}

void UDUITabButtonManagerWidget::RegisterTabContentSwitcher(UWidgetSwitcher* InTabContentWidgetSwitcher)
{
	ensure(!TabContentWidgetSwitcher.IsValid());
	TabContentWidgetSwitcher = InTabContentWidgetSwitcher;

	TryGuaranteeAnActiveTab();
}

void UDUITabButtonManagerWidget::TryGuaranteeAnActiveTab()
{
	// Attempt to activate first tab if none are active and we have a tab content widget switcher.
	if (!LastActivatedTabButton.IsValid() && TabContentWidgetSwitcher.IsValid())
	{
		TArray<TWeakObjectPtr<UDUITabButton>> RegisteredTabButtons;
		TabButtonToContentWidgetMap.GetKeys(RegisteredTabButtons);

		if (RegisteredTabButtons.IsValidIndex(0))
		{
			SetActiveTab(RegisteredTabButtons[0].Get());
		}
	}
}

void UDUITabButtonManagerWidget::HandleTabRequestActivate(UDUITabButton* ClickedTabButton)
{
	SetActiveTab(ClickedTabButton);
}

void UDUITabButtonManagerWidget::SetActiveTab(UDUITabButton* TabToActivate)
{
	TWeakObjectPtr<UWidget>* const MappedWidget = TabButtonToContentWidgetMap.Find(TabToActivate);
	if (!ensure(MappedWidget && MappedWidget->IsValid()))
	{
		return;
	}

	if (!ensure(TabContentWidgetSwitcher.IsValid()))
	{
		return;
	}

	// Tell the last activated tab that it has been deactivated.
	UDUITabButton* const TabToDeactivate = LastActivatedTabButton.Get();
	if (TabToDeactivate)
	{
		TabToDeactivate->NotifyTabDeactivated();
	}

	// Tell the activated tab that it has been activated.
	TabToActivate->NotifyTabActivated();
	LastActivatedTabButton = TabToActivate;

	// Activate content for this tab button.
	TabContentWidgetSwitcher->SetActiveWidget(MappedWidget->Get());
}
