#include "DUIDialogWidget.h"

void UDUIDialogWidget::SetMessage(const FText& InMessage)
{
	if (Message.IdenticalTo(InMessage))
	{
		return;
	}

	Message = InMessage;
	HandleDifferentMessageSet();
}

void UDUIDialogWidget::RequestCloseDialog()
{
	OnRequestCloseDialogEvent.ExecuteIfBound();
}
