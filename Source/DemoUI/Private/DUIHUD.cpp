#include "DUIHUD.h"

void ADUIHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateAndAddRootWidget();
}

void ADUIHUD::CreateAndAddRootWidget()
{
	// Create root widget if type is valid.
	if (!RootWidget || RootWidget->GetClass() != RootWidgetType)
	{
		RootWidget = CreateWidget<UDUIUIManagerWidget>(GetOwningPlayerController(), RootWidgetType);
	}

	// Add root widget to root of viewport.
	if (RootWidget)
	{
		RootWidget->AddToPlayerScreen();
	}
}

void ADUIHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RemoveRootWidget();

	Super::EndPlay(EndPlayReason);
}

void ADUIHUD::RemoveRootWidget()
{
	// Remove root widget from viewport.
	if (RootWidget)
	{
		RootWidget->RemoveFromParent();
	}
}
