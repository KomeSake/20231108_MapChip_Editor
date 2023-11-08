#include "Scene.h"

Scene::Scene()
{
	_sceneIndex = Game;
}

void Scene::SceneStart()
{
	UI_playerObj->UIOpen();
}
