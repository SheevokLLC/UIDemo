#include "DUIHealthBarWidget.h"

void UDUIHealthBarWidget::SetHealthComponentToRepresent(UDUIHealthComponent* const InComponent)
{
	if (ComponentToRepresent == InComponent)
	{
		return;
	}

	HandlePreDifferentHealthComponentToRepresentSetNative();
	ComponentToRepresent = InComponent;
	HandlePostDifferentHealthComponentToRepresentSetNative();
}

void UDUIHealthBarWidget::HandlePreDifferentHealthComponentToRepresentSetNative()
{
	// Unbind OnHitPointsChangedEvent on old component.
	if (ComponentToRepresent.IsValid())
	{
		ComponentToRepresent->OnHitPointsChangedEvent.Remove(HitPointsChangedDelegateHandle);
		HitPointsChangedDelegateHandle.Reset();
	}

	// Notify BP
	HandlePreDifferentHealthComponentToRepresentSetBP();
}

void UDUIHealthBarWidget::HandlePostDifferentHealthComponentToRepresentSetNative()
{
	// Bind OnHitPointsChangedEvent on new component.
	if (ComponentToRepresent.IsValid())
	{
		HitPointsChangedDelegateHandle = ComponentToRepresent->OnHitPointsChangedEvent.AddUObject(this, &ThisClass::HandleHitPointsChangedNative);
	}

	// Notify BP
	HandlePostDifferentHealthComponentToRepresentSetBP();

	// Trigger update of HP.
	HandleHitPointsChangedNative();
}

void UDUIHealthBarWidget::HandleHitPointsChangedNative()
{
	// Notify BP
	HandleHitPointsChangedBP();
}