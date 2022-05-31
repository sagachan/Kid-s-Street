//GameUISprite.h
//UIスプライトクラス

#include "GameUI.h"

//UIスプライトクラス
class CGameUISprite :public CGameUI
{
public:
	CGameUISprite();
	~CGameUISprite();

public:
	void Init(float posX, float posY) override;	//初期化
	void Load(const char* file_path) override;		//読み込み
	void Step() override;							//ステップ
	void Draw() override;							//描画
	void Delete() override;							//削除
	void Fin() override;							//後処理

private:
	int handle_;	//画像ハンドル
};