#pragma once
#include <ctime>
#include "LoadRes.h"
#include "MyBase.h"
class GameUI :
	public MyBase
{
public:
	Vector2 _pos;
	float _width, _height;
	unsigned int _color;
protected:
	//UIの描画関数は左上から描画する
	void UITexture(float x, float y, int sprite, unsigned int color);
	void UITexture(float x, float y, map<int, LoadRes::SpriteList> sprite, int index, unsigned int color);
	void UIAnimation(float x, float y, map<int, LoadRes::SpriteList> sprite, float angle, int frameTime, int index);
	//ストップウォッチ(３０番)
	int MyTimers(int milli, int index);
	clock_t _timeStart[31] = { 0 };
	clock_t _timeEnd[31] = { 0 };
	bool _isTimeOpen[31] = { 0 };
	//アニメーションのための変数
	int FrameTimers(int milli, int index);
	int _frameAniIndex[31] = { 0 };//指定したいフレイムからプレイする(例えば、０フレームから)
	clock_t _frame_timeStart[31] = { 0 };
	clock_t _frame_timeEnd[31] = { 0 };
	bool _frame_isTimeOpen[31] = { 0 };
};

class UI_player :
	public GameUI
{
public:
	UI_player();
	void UIOpen();
};