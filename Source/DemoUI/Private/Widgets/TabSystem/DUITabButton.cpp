#include "DUITabButton.h"
#include "Button.h"

void UDUITabButton::NotifyTabActivated()
{
	if (IsActiveTab)
	{
		return;
	}

	IsActiveTab = true;
	HandleIsActiveTabChanged();
}

void UDUITabButton::NotifyTabDeactivated()
{
	if (!IsActiveTab)
	{
		return;
	}

	IsActiveTab = false;
	HandleIsActiveTabChanged();
}

void UDUITabButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (InternalButton)
	{
		InternalButton->OnClicked.AddDynamic(this, &ThisClass::HandleInternalButtonClicked);
	}
}

void UDUITabButton::NativeDestruct()
{
	if (InternalButton)
	{
		InternalButton->OnClicked.RemoveDynamic(this, &ThisClass::HandleInternalButtonClicked);
	}

	Super::NativeDestruct();
}

void UDUITabButton::HandleInternalButtonClicked()
{
	OnTabRequestActivateEvent.Broadcast();
}