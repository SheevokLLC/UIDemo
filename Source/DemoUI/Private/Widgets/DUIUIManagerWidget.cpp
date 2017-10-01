#include "DUIUIManagerWidget.h"

void UDUIUIManagerWidget::RequestShowDialog(const FText& Message)
{
	if (!ensure(DialogWidgetType))
	{
		return;
	}

	UDUIDialogWidget* const NewDialogWidget = CreateWidget<UDUIDialogWidget>(GetOwningPlayer(), DialogWidgetType);
	NewDialogWidget->SetMessage(Message);

	const TWeakObjectPtr<ThisClass> WeakThis = this;
	const TWeakObjectPtr<UDUIDialogWidget> WeakDialogWidget = NewDialogWidget;
	const auto& OnRequestCloseDialog = [WeakThis, WeakDialogWidget]()
	{
		if (!WeakThis.IsValid() || !WeakDialogWidget.IsValid())
		{
			return;
		}

		WeakThis->CloseDialog(WeakDialogWidget.Get());
	};
	NewDialogWidget->OnRequestCloseDialogEvent.BindLambda(OnRequestCloseDialog);

	ShowDialog(NewDialogWidget);
}

void UDUIUIManagerWidget::ShowDialog_Implementation(UDUIDialogWidget* DialogWidgetToShow)
{}

void UDUIUIManagerWidget::CloseDialog_Implementation(UDUIDialogWidget* DialogWidgetToClose)
{}