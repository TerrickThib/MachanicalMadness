#include "OpeningScene.h"
#include "MainScene.h"
#include "UIText.h"
#include "Engine.h"

void OpeningScene::start()
{
	/// <summary>
	/// Creates all the text for the opening screen
	/// </summary>
	UIText* Title = new UIText(190, 200, "Title", WHITE, 500, 200, 70, "Mechanical\n Madness");
	addUIElement(Title);
	UIText* StartToBegin = new UIText(200,500, "Title", WHITE,300,100, 20, "Press Enter to Begin Testing");
	addUIElement(StartToBegin);
	UIText* Escape = new UIText(200, 550, "Title", RED, 300, 100, 20, "    AN ERR0R H4S OccUR3D\nPLEA$E PUSH ESC to L3aVE!!1");
	addUIElement(Escape);
}

void OpeningScene::update(float deltaTime)
{
	//If the enter key is pressed then start game
	if (Engine::getKeyDown(KEY_ENTER))
	{
		Engine::addScene(new MainScene());
		Engine::setCurrentScene(1);
		Engine::getCurrentScene()->start();
	}
}
