#include "Camera.h"

Camera::Camera(const int screenW, const int screenH, int bgW, int bgH)
{
	_bgWidth = (float)bgW;
	_bgHeight = (float)bgH;
	_screenWidth = (float)screenW;
	_screenHeight = (float)screenH;

	_randomMoveX = 2;
	_randomMoveY = 2;

	_pos = { _screenWidth / 2,_screenHeight / 2 };
	_playerPos = { _screenWidth / 2,_screenHeight / 2 };
	_cameraOffset = { 0,0 };
}

void Camera::Move(Vector2 playerPos)
{
	if (Novice::IsPressMouse(0)) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution dis_moveX(-_randomMoveX, _randomMoveX);
		std::uniform_real_distribution dis_moveY(-_randomMoveY, _randomMoveY);
		_cameraOffset = { dis_moveX(rd),dis_moveY(rd) };
	}
	else {
		_cameraOffset = { 0,0 };
	}
	if (playerPos.x >= _screenWidth / 2 && playerPos.x <= _bgWidth - _screenWidth / 2) {
		_playerPos.x = playerPos.x;
	}
	if (playerPos.y >= _screenHeight / 2 && playerPos.y <= _bgHeight - _screenHeight / 2) {
		_playerPos.y = playerPos.y;
	}

	_pos.x = _playerPos.x + _cameraOffset.x;
	_pos.y = _playerPos.y + _cameraOffset.y;
}