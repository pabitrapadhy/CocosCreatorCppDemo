#pragma once

class CocosView;
class ICocosViewLifeCycle {
public:
	ICocosViewLifeCycle();
	virtual ~ICocosViewLifeCycle() {};

	// setting/getting CocosView
	void			setCocosView(CocosView*	view) { _cocosView = view; }
	CocosView*		getCocosView() { return _cocosView; }

	// attach/detach to scene
	virtual void	attachToScene() { };
	virtual void	detachFromScene() { };

	// pre-attach/post-detach scene
	virtual void	postAttachToScene() { };
	virtual void	preDetachFromScene();

	// lifecycle focus
	virtual void	onLifeCycleFocusLost() { };
	virtual void	onLifeCycleFocusGained() { };

	// load/unload members
	virtual void	loadMembers() { };
	virtual void	unLoadMembers() { };

	// view pushing/popping
	virtual void	onViewPopped() { };
	virtual void	onPopupClosed(std::string sPopupName) { };

	// back button functionality
	virtual bool	onBackButtonPressed() { return false; }
	virtual void	setBackButtonEnabled(bool enabled) { _isBackButtonEnabled = enabled; }
	
	bool handleBackButton() {
		if (_isBackButtonEnabled) return onBackButtonPressed(); 
		else return true;
	}

	// message handling
	void removeMessages();

private:
	CocosView*		_cocosView;
	bool			_isBackButtonEnabled;
};
