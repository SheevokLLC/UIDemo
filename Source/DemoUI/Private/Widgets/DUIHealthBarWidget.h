#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/DUIHealthComponent.h"
#include "WeakObjectPtrTemplates.h"
#include "DUIHealthBarWidget.generated.h"

UCLASS(Abstract)
class UDUIHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetHealthComponentToRepresent(UDUIHealthComponent* const Component);

protected:
	void HandlePreDifferentHealthComponentToRepresentSetNative();
	void HandlePostDifferentHealthComponentToRepresentSetNative();
	void HandleHitPointsChangedNative();

	UFUNCTION(BlueprintImplementableEvent)
	void HandlePreDifferentHealthComponentToRepresentSetBP();
	
	UFUNCTION(BlueprintImplementableEvent)
	void HandlePostDifferentHealthComponentToRepresentSetBP();
	
	UFUNCTION(BlueprintImplementableEvent)
	void HandleHitPointsChangedBP();

protected:
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UDUIHealthComponent> ComponentToRepresent;

private:
	FDelegateHandle HitPointsChangedDelegateHandle;
};