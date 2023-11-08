#include "GameUI.h"

void GameUI::UITexture(float x, float y, int sprite, unsigned int color)
{
	Novice::DrawSprite((int)x, (int)y, sprite, 1, 1, 0, color);
}

void GameUI::UITexture(float x, float y, std::map<int, LoadRes::SpriteList> sprite, int index, unsigned int color)
{
	int arrSprite = sprite[index].path;
	int arrW = sprite[index].w, arrH = sprite[index].h;
	int arrX = sprite[index].x, arrY = sprite[index].y;
	int arrSpriteW = sprite[index].listW, arrSpriteH = sprite[index].listH;
	Novice::DrawSpriteRect((int)x, (int)y, arrX, arrY, arrW, arrH, arrSprite, ((float)arrW / (float)arrSpriteW), ((float)arrH / (float)arrSpriteH), 0, color);
}

void GameUI::UIAnimation(float x, float y, std::map<int, LoadRes::SpriteList> sprite, float angle, int frameTime, int index)
{
	if (FrameTimers(frameTime, index)) {
		_frameAniIndex[index]++;
	}
	if (_frameAniIndex[index] > (int)sprite.size() - 1 || _frameAniIndex[index] < 0) {
		_frameAniIndex[index] = 0;
	}
	int arrSprite = sprite[_frameAniIndex[index]].path;
	int arrW = sprite[_frameAniIndex[index]].w, arrH = sprite[_frameAniIndex[index]].h;
	int arrX = sprite[_frameAniIndex[index]].x, arrY = sprite[_frameAniIndex[index]].y;
	int arrSpriteW = sprite[_frameAniIndex[index]].listW, arrSpriteH = sprite[_frameAniIndex[index]].listH;
	Novice::DrawSpriteRect((int)x, (int)y, arrX, arrY, arrW, arrH, arrSprite, ((float)arrW / (float)arrSpriteW), ((float)arrH / (float)arrSpriteH), angle, WHITE);
}

int GameUI::MyTimers(int milli, int index)
{
	if (!_isTimeOpen[index]) {
		_timeStart[index] = clock();
		_isTimeOpen[index] = true;
	}
	_timeEnd[index] = clock();
	if (_timeEnd[index] - _timeStart[index] > milli) {
		_isTimeOpen[index] = false;
		return 1;
	}
	return 0;
}

int GameUI::FrameTimers(int milli, int index)
{
	if (!_frame_isTimeOpen[index]) {
		_frame_timeStart[index] = clock();
		_frame_isTimeOpen[index] = true;
	}
	_frame_timeEnd[index] = clock();
	if (_frame_timeEnd[index] - _frame_timeStart[index] > milli) {
		_frame_isTimeOpen[index] = false;
		return 1;
	}
	return 0;
}

UI_player::UI_player()
{
	_pos = { 0,0 };
	_width = 0;
	_height = 0;
	_color = WHITE;
}

void UI_player::UIOpen()
{
}
