//BossBattleItem.h
//�{�X��Ɏg���A�C�e������

#include "../GatherBase/GatherItem.h"
#include "../../../ItemCommon.h"
#include "DxLib.h"

class CBossBattleItem :public CGatherItem
{
public:
	CBossBattleItem();
	~CBossBattleItem();

public:
	void Init(VECTOR pos) override;	//������
	void Load(const char* file_path) override;		//�ǂݍ���
	void Step() override;							//�X�e�b�v
	void Draw() override;							//�`��
	void Delete() override;							//�폜
	void Fin() override;							//�㏈��


private:
	int handle_;	//�摜�n���h��
	ITEM_ID id_;
	VECTOR itemRot_;
};