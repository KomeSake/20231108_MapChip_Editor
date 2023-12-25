#include "MyTools.h"


void MyTools::CheckCameraValume(Vector2 cameraPos, unsigned int screenW, unsigned int screenH)
{
	_cameraPos = cameraPos;
	_screenWidth = float(screenW);
	_screenHeight = float(screenH);
}

int MyTools::MyTimers(int milli, int index)
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

MyTools::Vector2 MyTools::VectorNormalization(float x, float y)
{
	float vectorLength = sqrtf(powf(x, 2) + powf(y, 2));
	if (vectorLength != 0) {
		x = x / vectorLength;
		y = y / vectorLength;
	}
	return Vector2{ x,y };
}

void MyTools::FrameTexture(float x, float y, LoadRes::Sprite sprite, int color)
{
	float screenPosX = x - _cameraPos.x + _screenWidth / 2;
	float screenPosY = (y - _cameraPos.y + _screenHeight / 2 - _screenHeight) * -1;
	Novice::DrawSprite((int)(screenPosX - (float)(sprite.w) / 2), (int)(screenPosY - (float)(sprite.h) / 2), sprite.path, 1, 1, 0, color);
}

void MyTools::FrameTexture(float x, float y, LoadRes::Sprite sprite, float rad, int color)
{
	Vector2 rotated = { (float)sprite.w * -1 / 2,(float)sprite.h / 2 };
	//RotatedPos
	rotated = AditionRule(rotated, -rad);
	//ScreenPos
	rotated = { rotated.x + x ,rotated.y + y };
	rotated = WorldToScreen(rotated.x, rotated.y);

	Novice::DrawSprite((int)rotated.x, (int)rotated.y, sprite.path, 1, 1, rad, color);
}

void MyTools::FrameTexture(float x, float y, map<int, LoadRes::SpriteList> spList, int index, int color)
{
	int arrSprite = spList[index].path;
	int arrW = spList[index].w, arrH = spList[index].h;
	int arrSpriteW = spList[index].listW, arrSpriteH = spList[index].listH;
	int arrX = spList[index].x, arrY = spList[index].y;

	Vector2 pos = WorldToScreen(x, y);
	Novice::DrawSpriteRect((int)(pos.x - (float)(arrW) / 2), (int)(pos.y - (float)(arrH) / 2), arrX, arrY, arrW, arrH, arrSprite, ((float)arrW / (float)arrSpriteW), ((float)arrH / (float)arrSpriteH), 0, color);
}

void MyTools::FrameTexture(float x, float y, map<int, LoadRes::SpriteList> spList, int index, float rad, int color)
{
	int arrSprite = spList[index].path;
	int arrW = spList[index].w, arrH = spList[index].h;
	int arrSpriteW = spList[index].listW, arrSpriteH = spList[index].listH;
	int arrX = spList[index].x, arrY = spList[index].y;

	Vector2 rotated = { (float)spList[index].w * -1 / 2,(float)spList[index].h / 2 };
	rotated = AditionRule(rotated, -rad);
	rotated = { rotated.x + x ,rotated.y + y };
	rotated = WorldToScreen(rotated.x, rotated.y);
	Novice::DrawSpriteRect((int)rotated.x, (int)rotated.y, arrX, arrY, arrW, arrH, arrSprite, ((float)arrW / (float)arrSpriteW), ((float)arrH / (float)arrSpriteH), rad, color);
}
void MyTools::FrameTexture(float x, float y, LoadRes::Sprite sprite, float scaleX, float scaleY, int color)
{
	float screenPosX = x - _cameraPos.x + _screenWidth / 2;
	float screenPosY = (y - _cameraPos.y + _screenHeight / 2 - _screenHeight) * -1;
	Vector2 zoom = { float(sprite.w) / 2 - float(sprite.w) / 2 * scaleX,float(sprite.h) / 2 - float(sprite.h) / 2 * scaleY };
	Novice::DrawSprite((int)(screenPosX - (float)(sprite.w) / 2 + zoom.x), (int)(screenPosY - (float)(sprite.h) / 2 + zoom.y), sprite.path, scaleX, scaleY, 0, color);
}
void MyTools::FrameTexture(float x, float y, LoadRes::Sprite sprite, float scaleX, float scaleY, float rad, int color)
{
	Vector2 zoom = { float(sprite.w) / 2 - float(sprite.w) / 2 * scaleX,float(sprite.h) / 2 - float(sprite.h) / 2 * scaleY };
	Vector2 rotated = { (float)sprite.w * -1 / 2 + zoom.x,(float)sprite.h / 2 - zoom.y };
	//RotatedPos
	rotated = AditionRule(rotated, -rad);
	//ScreenPos
	rotated = { rotated.x + x ,rotated.y + y };
	rotated = WorldToScreen(rotated.x, rotated.y);

	Novice::DrawSprite((int)(rotated.x), (int)(rotated.y), sprite.path, scaleX, scaleY, rad, color);
}

void MyTools::FrameTexture(float x, float y, map<int, LoadRes::SpriteList> spList, int index, float scaleX, float scaleY, int color)
{
	int arrSprite = spList[index].path;
	int arrW = spList[index].w, arrH = spList[index].h;
	int arrSpriteW = spList[index].listW, arrSpriteH = spList[index].listH;
	int arrX = spList[index].x, arrY = spList[index].y;

	Vector2 pos = WorldToScreen(x, y);
	Vector2 zoom = { float(arrW) / 2 - float(arrW) / 2 * scaleX,float(arrH) / 2 - float(arrH) / 2 * scaleY };
	Novice::DrawSpriteRect((int)(pos.x - (float)(arrW) / 2 + zoom.x), (int)(pos.y - (float)(arrH) / 2 + zoom.y), arrX, arrY, arrW, arrH, arrSprite, ((float)arrW / (float)arrSpriteW) * scaleX, ((float)arrH / (float)arrSpriteH) * scaleY, 0, color);
}

void MyTools::FrameTexture(float x, float y, map<int, LoadRes::SpriteList> spList, int index, float scaleX, float scaleY, float rad, int color)
{
	int arrSprite = spList[index].path;
	int arrW = spList[index].w, arrH = spList[index].h;
	int arrSpriteW = spList[index].listW, arrSpriteH = spList[index].listH;
	int arrX = spList[index].x, arrY = spList[index].y;

	Vector2 zoom = { float(arrW) / 2 - float(arrW) / 2 * scaleX,float(arrH) / 2 - float(arrH) / 2 * scaleY };
	Vector2 rotated = { (float)spList[index].w * -1 / 2 + zoom.x,(float)spList[index].h / 2 - zoom.y };
	rotated = AditionRule(rotated, -rad);
	rotated = { rotated.x + x ,rotated.y + y };
	rotated = WorldToScreen(rotated.x, rotated.y);
	Novice::DrawSpriteRect((int)(rotated.x), (int)(rotated.y), arrX, arrY, arrW, arrH, arrSprite, ((float)arrW / (float)arrSpriteW) * scaleX, ((float)arrH / (float)arrSpriteH) * scaleY, rad, color);
}

void MyTools::FrameAnimation(float x, float y, map<int, LoadRes::SpriteList> spList, float rad, int color, int frameTime, int playIndex)
{
	if (FrameTimers(frameTime, playIndex)) {
		_frameAniIndex[playIndex]++;
	}
	if (_frameAniIndex[playIndex] > (int)spList.size() - 1 || _frameAniIndex[playIndex] < 0) {
		_frameAniIndex[playIndex] = 0;
	}
	int arrPath = spList[_frameAniIndex[playIndex]].path;
	int arrW = spList[_frameAniIndex[playIndex]].w, arrH = spList[_frameAniIndex[playIndex]].h;
	int arrX = spList[_frameAniIndex[playIndex]].x, arrY = spList[_frameAniIndex[playIndex]].y;
	int arrListW = spList[_frameAniIndex[playIndex]].listW, arrListH = spList[_frameAniIndex[playIndex]].listH;
	Vector2 rotated = { (float)spList[_frameAniIndex[playIndex]].w * -1 / 2,(float)spList[_frameAniIndex[playIndex]].h / 2 };
	rotated = AditionRule(rotated, -rad);
	rotated = { rotated.x + x ,rotated.y + y };
	rotated = WorldToScreen(rotated.x, rotated.y);
	Novice::DrawSpriteRect((int)rotated.x, (int)rotated.y, arrX, arrY, arrW, arrH, arrPath, ((float)arrW / (float)arrListW), ((float)arrH / (float)arrListH), rad, color);
}

void MyTools::FrameAnimation(float x, float y, map<int, LoadRes::SpriteList> spList, float scaleX, float scaleY, float rad, int color, int frameTime, int playIndex)
{
	if (FrameTimers(frameTime, playIndex)) {
		_frameAniIndex[playIndex]++;
	}
	if (_frameAniIndex[playIndex] > (int)spList.size() - 1 || _frameAniIndex[playIndex] < 0) {
		_frameAniIndex[playIndex] = 0;
	}
	int arrPath = spList[_frameAniIndex[playIndex]].path;
	int arrW = spList[_frameAniIndex[playIndex]].w, arrH = spList[_frameAniIndex[playIndex]].h;
	int arrX = spList[_frameAniIndex[playIndex]].x, arrY = spList[_frameAniIndex[playIndex]].y;
	int arrListW = spList[_frameAniIndex[playIndex]].listW, arrListH = spList[_frameAniIndex[playIndex]].listH;
	Vector2 zoom = { float(arrW) / 2 - float(arrW) / 2 * scaleX,float(arrH) / 2 - float(arrH) / 2 * scaleY };
	Vector2 rotated = { (float)spList[_frameAniIndex[playIndex]].w * -1 / 2 + zoom.x,(float)spList[_frameAniIndex[playIndex]].h / 2 - zoom.y };
	rotated = AditionRule(rotated, -rad);
	rotated = { rotated.x + x ,rotated.y + y };
	rotated = WorldToScreen(rotated.x, rotated.y);
	Novice::DrawSpriteRect((int)(rotated.x), (int)(rotated.y), arrX, arrY, arrW, arrH, arrPath, ((float)arrW / (float)arrListW) * scaleX, ((float)arrH / (float)arrListH) * scaleY, rad, color);
}

int MyTools::FrameTimers(int milli, int index)
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

MyTools::Vector2 MyTools::AditionRule(Vector2 pos, float rad)
{
	float aditionX = pos.x * cosf(rad) - pos.y * sinf(rad);
	float aditionY = pos.y * cosf(rad) + pos.x * sinf(rad);
	return Vector2{ aditionX,aditionY };
}

MyTools::Vector2 MyTools::ScreenToWorld(float screenX, float screenY) {
	float worldX = (float)(screenX + _cameraPos.x - _screenWidth / 2);
	float worldY = (float)(screenY * -1 + _cameraPos.y - _screenHeight / 2 + _screenHeight);
	return Vector2{ worldX,worldY };
}

MyTools::Vector2 MyTools::WorldToScreen(float worldPosX, float worldPosY)
{
	float screenPosX = worldPosX - _cameraPos.x + _screenWidth / 2;
	float screenPosY = (worldPosY - _cameraPos.y + _screenHeight / 2 - _screenHeight) * -1;
	return Vector2(screenPosX, screenPosY);
}

float MyTools::SpriteToObjDir(Vector2 dir)
{
	float rad = atan2f(dir.y, dir.x);
	float degree = 180.f / acosf(-1) * rad;
	if (degree < 0) {
		degree += 360;
	}
	degree -= 90;
	rad = -(acosf(-1) / 180 * degree);
	return rad;
}

unsigned int MyTools::ColorInterpolation(unsigned int startColor, unsigned int targetColor, float percent)
{
	uint8_t startAlpha = (startColor >> 24) & 0xFF;
	uint8_t startRed = (startColor >> 16) & 0xFF;
	uint8_t startGreen = (startColor >> 8) & 0xFF;
	uint8_t startBlue = startColor & 0xFF;

	uint8_t targetAlpha = (targetColor >> 24) & 0xFF;
	uint8_t targetRed = (targetColor >> 16) & 0xFF;
	uint8_t targetGreen = (targetColor >> 8) & 0xFF;
	uint8_t targetBlue = targetColor & 0xFF;

	uint8_t currentAlpha = uint8_t(startAlpha + percent * (targetAlpha - startAlpha));
	uint8_t currentRed = uint8_t(startRed + percent * (targetRed - startRed));
	uint8_t currentGreen = uint8_t(startGreen + percent * (targetGreen - startGreen));
	uint8_t currentBlue = uint8_t(startBlue + percent * (targetBlue - startBlue));

	unsigned int returnColor = (currentAlpha << 24) | (currentRed << 16) | (currentGreen << 8) | currentBlue;

	return returnColor;
}