#include "GameUI.h"

void GameUI::UITexture(float x, float y, LoadRes::Sprite sprite, unsigned int color)
{
	Novice::DrawSprite((int)x, (int)y, sprite.path, 1, 1, 0, color);
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

UI_GameOver::UI_GameOver()
{
	_width = 800;
	_height = 800;
	_pos = { 0,0 };
	_color = WHITE;
	_isRestart = false;
	_isBackMenu = false;
}

void UI_GameOver::UIOpen(Vector2 mousePos, char prekeys[], char keys[])
{
	mousePos;

	Novice::DrawBox(0, 0, 800, 800, 0, 0x832f2690, kFillModeSolid);
	UITexture(_pos.x - 20, _pos.y + 100, LoadRes::_slUI_screenDead, 0, _color);
	UITexture(_pos.x + 400, _pos.y + 100, LoadRes::_slUI_screenDead, 1, _color);

	UITexture(_pos.x + 80, _pos.y + 600, LoadRes::_spUI_restart, _color);

	if (!prekeys[DIK_SPACE] && keys[DIK_SPACE]) {
		_isRestart = true;
	}



	//UITexture(_pos.x + 500, _pos.y + 600, LoadRes::_slUI_screenDead, 2, _color);
	//UITexture(_pos.x + 140, _pos.y + 600, LoadRes::_slUI_screenDead, 3, _color);
	//UITexture(_pos.x + 140 + 50, _pos.y + 600 + 10, LoadRes::_slUI_screenDead, 5, _color);
	//UITexture(_pos.x + 500 + 30, _pos.y + 600 + 10, LoadRes::_slUI_screenDead, 6, _color);
	//if (mousePos.x > _pos.x + 500 && mousePos.x < _pos.x + 500 + 171
	//	&& _pos.y + mousePos.y > 600 && mousePos.y < _pos.y + 600 + 62) {
	//	UITexture(_pos.x + 500, _pos.y + 600, LoadRes::_slUI_screenDead, 4, _color);
	//	if (Novice::IsTriggerMouse(0)) {
	//		_isRestart = true;
	//	}
	//}
	//if (mousePos.x > _pos.x + 140 && mousePos.x < _pos.x + 140 + 171
	//	&& _pos.y + mousePos.y > 600 && mousePos.y < _pos.y + 600 + 62) {
	//	UITexture(_pos.x + 140, _pos.y + 600, LoadRes::_slUI_screenDead, 4, _color);
	//	if (Novice::IsTriggerMouse(0)) {
	//		_isBackMenu = true;
	//	}
	//}
}

UI_Start::UI_Start()
{
	_width = 800;
	_height = 800;
	_pos = { 0,0 };
	_color = WHITE;
	_isStart = false;
}

void UI_Start::UIOpen(char prekeys[], char keys[])
{
	Novice::DrawBox(0, 0, 800, 800, 0, 0xffab9190, kFillModeSolid);
	UITexture(_pos.x + 50, _pos.y + 120, LoadRes::_spUI_title, _color);
	UITexture(_pos.x + 80, _pos.y + 600, LoadRes::_spUI_restart, _color);

	if (!prekeys[DIK_SPACE] && keys[DIK_SPACE]) {
		_isStart = true;
	}
}

UI_Game::UI_Game()
{
	_width = 800;
	_height = 800;
	_pos = { 10,10 };//以左上角的Hp为标准
	_color = WHITE;

	_mapEditorIndex = nothing;
}

void UI_Game::UIOpen(int hp, bool isMapEditor)
{
	int mouseX{}, mouseY{};
	Novice::GetMousePosition(&mouseX, &mouseY);
	if (isMapEditor) {
		UITexture(_pos.x - 10, _pos.y + 100, LoadRes::_spUI_mapEditor, WHITE);

		if (mouseX > 10 && mouseY > 163
			&& mouseX < 58 && mouseY < 208
			&& Novice::IsTriggerMouse(0)) {
			//bg1
			_mapEditorIndex = bg1;
		}
		else if (mouseX > 80 && mouseY > 163
			&& mouseX < 127 && mouseY < 208
			&& Novice::IsTriggerMouse(0)) {
			//box1
			_mapEditorIndex = box1;
		}
		else if (mouseX > 10 && mouseY > 224
			&& mouseX < 58 && mouseY < 272
			&& Novice::IsTriggerMouse(0)) {
			//bg2
			_mapEditorIndex = bg2;
		}
		else if (mouseX > 80 && mouseY > 224
			&& mouseX < 127 && mouseY < 272
			&& Novice::IsTriggerMouse(0)) {
			//box2
			_mapEditorIndex = box2;
		}
		else if (mouseX > 43 && mouseY > 287
			&& mouseX < 92 && mouseY < 334
			&& Novice::IsTriggerMouse(0)) {
			//enemyMother
			_mapEditorIndex = enemyMother;
		}
		else if (mouseX > 20 && mouseY > 355
			&& mouseX < 117 && mouseY < 397
			&& Novice::IsTriggerMouse(0)) {
			//save
		}
		switch (_mapEditorIndex)
		{
		case UI_Game::nothing:
			break;
		case UI_Game::bg1:
			UITexture(17, 185, LoadRes::_spUI_mapEditor_yes, WHITE);
			break;
		case UI_Game::box1:
			UITexture(85, 185, LoadRes::_spUI_mapEditor_yes, WHITE);
			break;
		case UI_Game::bg2:
			UITexture(17, 247, LoadRes::_spUI_mapEditor_yes, WHITE);
			break;
		case UI_Game::box2:
			UITexture(85, 247, LoadRes::_spUI_mapEditor_yes, WHITE);
			break;
		case UI_Game::enemyMother:
			UITexture(55, 310, LoadRes::_spUI_mapEditor_yes, WHITE);
			break;
		}
	}

	UITexture(_pos.x, _pos.y, LoadRes::_spUI_hpBox, _color);
	switch (hp)
	{
	case 10:
		UITexture(_pos.x + 8, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 46, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 84, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 122, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 160, _pos.y + 8, LoadRes::_spUI_hp, _color);
		break;
	case 9:
		UITexture(_pos.x + 8, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 46, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 84, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 122, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 160, _pos.y + 8, LoadRes::_spUI_hp2, _color);
		break;
	case 8:
		UITexture(_pos.x + 8, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 46, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 84, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 122, _pos.y + 8, LoadRes::_spUI_hp, _color);
		break;
	case 7:
		UITexture(_pos.x + 8, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 46, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 84, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 122, _pos.y + 8, LoadRes::_spUI_hp2, _color);
		break;
	case 6:
		UITexture(_pos.x + 8, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 46, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 84, _pos.y + 8, LoadRes::_spUI_hp, _color);
		break;
	case 5:
		UITexture(_pos.x + 8, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 46, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 84, _pos.y + 8, LoadRes::_spUI_hp2, _color);
		break;
	case 4:
		UITexture(_pos.x + 8, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 46, _pos.y + 8, LoadRes::_spUI_hp, _color);
		break;
	case 3:
		UITexture(_pos.x + 8, _pos.y + 8, LoadRes::_spUI_hp, _color);
		UITexture(_pos.x + 46, _pos.y + 8, LoadRes::_spUI_hp2, _color);
		break;
	case 2:
		UITexture(_pos.x + 8, _pos.y + 8, LoadRes::_spUI_hp, _color);
		break;
	case 1:
		UITexture(_pos.x + 8, _pos.y + 8, LoadRes::_spUI_hp2, _color);
		break;
	}
}
