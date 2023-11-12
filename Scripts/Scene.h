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
	void SceneStart(char prekeys[], char keys[]);
	void SceneGame();
	void SceneGameOver(int mouseX, int mouseY, char prekeys[], char keys[]);

	UI_Start* UI_StartObj;
	UI_GameOver* UI_GameOverObj;
};

