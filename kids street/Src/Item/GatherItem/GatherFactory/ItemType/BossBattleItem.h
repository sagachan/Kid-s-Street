//BossBattleItem.h
//ボス戦に使うアイテム処理

#include "../GatherBase/GatherItem.h"
#include "../../../ItemCommon.h"
#include "DxLib.h"

class CBossBattleItem :public CGatherItem
{
public:
	CBossBattleItem();
	~CBossBattleItem();

public:
	void Init(VECTOR pos) override;	//初期化
	void Load(const char* file_path) override;		//読み込み
	void Step() override;							//ステップ
	void Draw() override;							//描画
	void Delete() override;							//削除
	void Fin() override;							//後処理


private:
	int handle_;	//画像ハンドル
	ITEM_ID id_;
	VECTOR itemRot_;
};