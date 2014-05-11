#include "include\core\MenuSystem.h"
#include "include\handler\InputHandler.h"
#include "include\common\Properties.h"

#include "CEGUI\WindowManager.h"
#include "CEGUI\System.h"
#include "CEGUI\Window.h"
#include "CEGUI\GUIContext.h"
#include "CEGUI\SchemeManager.h"
#include "CEGUI\CEGUI.h"
#include "OIS\OIS.h"

MenuSystem::MenuSystem(InputHandler *inputHandler) {
	mInputHandler = inputHandler;
	mIsActive = true;
	mCommand = Properties::MenuCommand::CANCLE;
	initialize();
}

MenuSystem::~MenuSystem() {
}

void MenuSystem::initialize() {
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	CEGUI::WindowManager &windowManager = CEGUI::WindowManager::getSingleton();
	CEGUI::Window *root = windowManager.createWindow("DefaultWindow", "root");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root);
	CEGUI::Window *mainWindow = windowManager.createWindow("TaharezLook/FrameWindow", "mainWindow");
	root->addChild(mainWindow);
	mainWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0.0f), CEGUI::UDim(0.25f, 0.0f)));
	mainWindow->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0.0f), CEGUI::UDim(0.5f, 0.0f)));
	mainWindow->setText("Tank Battle");

	CEGUI::Window *newEasyGameButton = windowManager.createWindow("TaharezLook/Button", "newEasyGame");
	newEasyGameButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0.0f), CEGUI::UDim(0.25f, 0.0f)));
	newEasyGameButton->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0.0f), CEGUI::UDim(0.1f, 0.0f)));
	newEasyGameButton->setText("New Game(Easy)");
	newEasyGameButton->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&MenuSystem::onNewEasyGame, this)); 
	mainWindow->addChild(newEasyGameButton);

	CEGUI::Window *newHardGameButton = windowManager.createWindow("TaharezLook/Button", "newHardGame");
	newHardGameButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0.0f), CEGUI::UDim(0.5f, 0.0f)));
	newHardGameButton->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0.0f), CEGUI::UDim(0.1f, 0.0f)));
	newHardGameButton->setText("New Game(Hard)");
	newHardGameButton->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&MenuSystem::onNewHardGame, this)); 
	mainWindow->addChild(newHardGameButton);

	CEGUI::Window *quitButton = windowManager.createWindow("TaharezLook/Button", "quitButton");
	quitButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0.0f), CEGUI::UDim(0.75f, 0.0f)));
	quitButton->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0.0f), CEGUI::UDim(0.1f, 0.0f)));
	quitButton->setText("Quit");
	quitButton->subscribeEvent(CEGUI::PushButton::EventMouseClick, CEGUI::Event::Subscriber(&MenuSystem::onQuit, this)); 
	mainWindow->addChild(quitButton);
}

void MenuSystem::think(float time) {
	CEGUI::System::getSingleton().injectTimePulse(time);
	injectMouseMove(mInputHandler->getMouseState());
	if (!mInputHandler->isMouseDown(OIS::MB_Left) && mInputHandler->wasMouseDown(OIS::MB_Left)) {
		injectMouseClicked(OIS::MB_Left);
	}
	if (mInputHandler->isMouseDown(OIS::MB_Right)) {
		injectMouseClicked(OIS::MB_Right);
	}
}

void MenuSystem::activate() {
	CEGUI::Window *mainWindow = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("mainWindow");
	mainWindow->show();
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
	mIsActive = true;
}

void MenuSystem::deactivate() {
	CEGUI::Window *mainWindow = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("mainWindow");
	mainWindow->hide();
	mIsActive = false;
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
	mCommand = Properties::MenuCommand::CANCLE;
}

void MenuSystem::injectMouseMove(const OIS::MouseState &mouseState) {
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(mouseState.X.rel, mouseState.Y.rel);
}

void MenuSystem::injectMouseClicked(OIS::MouseButtonID mouseButton) {
	CEGUI::MouseButton ceguiMouseButton;
	switch (mouseButton)
    {
    case OIS::MB_Left:
        ceguiMouseButton = CEGUI::LeftButton;
 
    case OIS::MB_Right:
        ceguiMouseButton = CEGUI::RightButton;
    default:
        ceguiMouseButton = CEGUI::LeftButton;
    }
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonClick(ceguiMouseButton);
}

bool MenuSystem::isActive() const {
	return mIsActive;
}

bool MenuSystem::onQuit(const CEGUI::EventArgs& eventArgs) {
	//deactivate();
	mCommand = Properties::MenuCommand::QUIT;
	return true;
}

bool MenuSystem::onNewEasyGame(const CEGUI::EventArgs& eventArgs) {
	//deactivate();
	mCommand = Properties::MenuCommand::NEWGAME_EASY;
	return true;
}

bool MenuSystem::onNewHardGame(const CEGUI::EventArgs& eventArgs) {
	mCommand = Properties::MenuCommand::NEWGAME_HARD;
	return true;
}

Properties::MenuCommand MenuSystem::getCommand() const {
	return mCommand;
}