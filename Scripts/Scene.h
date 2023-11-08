#pragma once
#include "GameUI.h"
#include "MyBase.h"
class Scene :
	public MyBase
{
public:
	inline static enum SceneIndex {
		Loading,//ゲーム内容を全体に初期化したいとき、使う
		Start,
		Game,
		GameOver,
	}_sceneIndex;

	Scene();
	void SceneStart();
	void SceneGame();
	void SceneGameOver();


	UI_player* UI_playerObj = new UI_player();
};

