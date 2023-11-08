#include "Camera.h"

Camera::Camera(const int screenW, const int screenH, int bgW, int bgH)
{
	_bgWidth = (float)bgW;
	_bgHeight = (float)bgH;
	_screenWidth = (float)screenW;
	_screenHeight = (float)screenH;

	_pos = { _screenWidth / 2,_screenHeight / 2 };
	_cameraOffset = { 0,0 };
}

void Camera::Move(Vector2 playerPos)
{
	if (playerPos.x >= _screenWidth / 2 && playerPos.x <= _bgWidth - _screenWidth / 2) {
		_pos.x = playerPos.x + _cameraOffset.x;
	}
	if (playerPos.y >= _screenHeight / 2 && playerPos.y <= _bgHeight - _screenHeight / 2) {
		_pos.y = playerPos.y + _cameraOffset.y;
	}
}