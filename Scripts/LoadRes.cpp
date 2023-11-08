#include "LoadRes.h"

void LoadRes::LoadResNovice()
{
	int path = 0;
	int listW = 0, listH = 0;
	int w = 0, h = 0, x = 0, y = 0;

	//こちに宣言した変数を書いてください（以下は３つテンプレート）
	//スライド（リンク、横幅、縦幅）
	_spriteTemplate = { Novice::LoadTexture("./Resources/Textures/Template/sprite.png"),96,96 };

	//スライドシート
	for (int i = 0; i < 5; i++) {
		path = Novice::LoadTexture("./Resources/Textures/Template/sprite_list_character.png");//リンク
		w = 128, h = 128;//一つフレームの横縦幅
		x = i * w, y = 0;//直接にコピペしてください
		listW = 640, listH = 128;//連番動画のシートの横縦幅
		_spriteListTemplate[i] = { path,x,y,w,h,listW,listH };//全部要素をmap容器に入れる
	}

	//スライドシートのUI
	path = Novice::LoadTexture("./Resources/Textures/Template/UI/List.png");//リンク
	listW = 700, listH = 404;//リソースシートの横縦幅
	w = 240, h = 404, x = 0, y = 0;//一番目の横縦幅と左上の座標
	_spriteListTemplate_UI[0] = { path,x,y,w,h,listW,listH };//map容器に入れる
	w = 460, h = 72, x = 240, y = 0;//二番目.....
	_spriteListTemplate_UI[1] = { path,x,y,w,h,listW,listH };
	w = 404, h = 44, x = 240, y = 72;
	_spriteListTemplate_UI[3] = { path,x,y,w,h,listW,listH };
}
