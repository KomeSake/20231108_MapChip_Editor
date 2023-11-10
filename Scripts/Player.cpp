#include "Player.h"

Player::Player()
{
	Initial();
}

void Player::Initial()
{
	_pos = { 32 + 16,32 + 16 };
	_width = 32;
	_height = 32;
	_sprite = LoadRes::_sl_playerRun;
	_color = WHITE;

	_hp = 10;
}

void Player::Move(char keys[])
{
	//チェックするために、一旦書いてある
	if (keys[DIK_W]) {
		_pos.y += 10;
	}
	if (keys[DIK_S]) {
		_pos.y -= 10;
	}
	if (keys[DIK_A]) {
		_pos.x -= 10;
	}
	if (keys[DIK_D]) {
		_pos.x += 10;
	}
}

void Player::Collide()
{
}

void Player::Show()
{
	FrameAnimation(_pos.x, _pos.y, _sprite, 0, _color, 100, 0);
}

void Player::IsDead()
{
	if (_hp < 0) {

	}
}
