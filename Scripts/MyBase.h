#pragma once
class MyBase
{
	//ここはC++の中にない自作の型を置いてある
	//なので、これら型を使いたいなら、MyBaseクラスに継承してください
public:
	struct Vector2
	{
		float x, y;
	};

	struct Matrix2x2
	{
		float m[2][2];
	};
	struct Matrix3x3
	{
		float m[3][3];
	};
};
