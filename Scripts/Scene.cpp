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
		UI_StartObj->_isStart = false;
		Novice::PlayAudio(LoadRes::_audio_keySpace, 0, 1);

		_sceneIndex = Loading;
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
		UI_GameOverObj->_isRestart = false;
		Novice::PlayAudio(LoadRes::_audio_keySpace, 0, 1);
		_sceneIndex = Loading;
	}
	if (UI_GameOverObj->_isBackMenu) {
		UI_GameOverObj->_isBackMenu = false;
		_sceneIndex = Start;
	}
}
