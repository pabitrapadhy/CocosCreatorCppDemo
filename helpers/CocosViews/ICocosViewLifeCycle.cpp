#include "ICocosViewLifeCycle.h"
#include "CocosView.h"

ICocosViewLifeCycle::ICocosViewLifeCycle() {
	_cocosView = nullptr;
	_isBackButtonEnabled = true;
}

void ICocosViewLifeCycle::preDetachFromScene() { 
	// _cocosView->OnDetachAnimationDone(this);
}

void ICocosViewLifeCycle::removeMessages() {
	// EA::Messaging::IHandler *handler = dynamic_cast<EA::Messaging::IHandler *>(this);
	// if (NULL != handler)
	// {
	// 	EA::GameFoundation::GameMessaging::GetServer().RemoveAllMessagesForHandler(handler);
	// }
}


