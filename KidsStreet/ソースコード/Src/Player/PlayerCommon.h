#pragma once
#include "DxLib.h"
namespace
{
	const VECTOR PLAYER_HP_POS = VGet(700.0f, 655.0f, 0.0f);
	const float PLAYER_UI_END_POS_X = 1350.0f;
	const float PLAYER_UI_END_POS_Y = 1975.0f;
	const VECTOR ORIGIN_HP_POS = 
		VGet(PLAYER_HP_POS.x + PLAYER_UI_END_POS_X, PLAYER_HP_POS.y + PLAYER_UI_END_POS_Y, 0.0f );

	
	const float PLAYER_W = 4.0f;			//プレイヤーの横幅
	const float PLAYER_H = 4.0f;			//プレイヤーの高さ
	const float PLAYER_D = 4.0f;			//プレイヤーの奥行き
	const VECTOR PLAYER_COL = VGet(PLAYER_W, PLAYER_H, PLAYER_D);
}