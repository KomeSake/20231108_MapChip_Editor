#include "Player.h"

Player::Player()
{
	Initial();
}

void Player::Initial()
{
	_pos = { 640 / 2,780 / 2 };
	_width = 60;
	_height = 64;
	_sprite = LoadRes::_spriteListTemplate;
	_color = WHITE;

	_hp = 10;
}

void Player::Move(char keys[])
{
	//チェックするために、一旦書いてある
	if (keys[DIK_W]) {
		_pos.y += 20;
	}
	if (keys[DIK_S]) {
		_pos.y -= 20;
	}
	if (keys[DIK_A]) {
		_pos.x -= 20;
	}
	if (keys[DIK_D]) {
		_pos.x += 20;
	}
}

void Player::Collide()
{
}

void Player::Show()
{
	FrameTexture(_pos.x, _pos.y, _sprite, 0, _color);
}

void Player::IsDead()
{
	if (_hp < 0) {

	}
}
