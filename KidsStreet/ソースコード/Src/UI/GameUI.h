//GameUI.h
//UIのベースとなるクラス
#include "DxLib.h"
#pragma once

//UIのベースとなるクラス
class CGameUI
{
public:
	CGameUI();
	virtual ~CGameUI();

public:
	virtual void Init(float posX, float posY) = 0;	//初期化
	virtual void Load(const char* file_path) = 0;		//読み込み
	virtual void Step() = 0;							//ステップ
	virtual void Draw() = 0;							//描画
	virtual void Delete() = 0;							//削除
	virtual void Fin() = 0;								//後処理

	void SetPosX(float posX) { posX_ = posX; }	//Ｘ座標設定
	void SetPosY(float posY) { posY_ = posY; }	//Ｙ座標設定

	float GetPosX()const { return posX_; }	//Ｘ座標取得
	float GetPosY()const { return posY_; }	//Ｙ座標取得

	void SetSize(int size) { size_ = size; }
	void SetEndPos(VECTOR pos) { endPos_ = pos; }
	

	void SetDrawFlg(bool flg) { drawFlg_ = flg; }
	bool GetDrawFlg() { return drawFlg_; }

protected:
	float	posX_;	//Ｘ座標
	float	posY_;	//Ｙ座標
	int		size_;
	VECTOR endPos_;
	bool	drawFlg_;	//描画フラグ
};