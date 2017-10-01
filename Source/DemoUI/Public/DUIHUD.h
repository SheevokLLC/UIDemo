#pragma once

#include "GameFramework/HUD.h"
#include "DUIUIManagerWidget.h"
#include "DUIHUD.generated.h"

UCLASS(Abstract)
class ADUIHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	virtual void BeginPlay() override;

private:
	void CreateAndAddRootWidget();
	void RemoveRootWidget();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDUIUIManagerWidget> RootWidgetType;

	UPROPERTY(BlueprintReadOnly)
	UDUIUIManagerWidget* RootWidget;
};