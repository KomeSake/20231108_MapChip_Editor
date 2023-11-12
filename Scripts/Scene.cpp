#include "Scene.h"

Scene::Scene()
{
	_sceneIndex = Start;
	UI_StartObj = new UI_Start();
	UI_GameObj = new UI_Game();
	UI_GameOverObj = new UI_GameOver();
}

void Scene::SceneStart(char prekeys[], char keys[])
{
	UI_StartObj->UIOpen(prekeys, keys);
	if (UI_StartObj->_isStart) {
		_sceneIndex = Loading;
		UI_StartObj->_isStart = false;
	}
}

void Scene::SceneGame(int playerHp)
{
	UI_GameObj->UIOpen(playerHp);
}

void Scene::SceneGameOver(int mouseX, int mouseY, char prekeys[], char keys[])
{
	UI_GameOverObj->UIOpen(Vector2{ float(mouseX),float(mouseY) }, prekeys, keys);
	if (UI_GameOverObj->_isRestart) {
		_sceneIndex = Loading;
		UI_GameOverObj->_isRestart = false;
	}
	if (UI_GameOverObj->_isBackMenu) {
		_sceneIndex = Start;
		UI_GameOverObj->_isBackMenu = false;
	}
}
