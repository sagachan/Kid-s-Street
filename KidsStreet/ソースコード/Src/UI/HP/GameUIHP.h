//GameUIHP.h
//HP�N���X

#include "../GameUI.h"
#include "DxLib.h"
//HP�N���X
class CGameUIHP :public CGameUI
{
public:
	CGameUIHP();
	~CGameUIHP();

public:
	void Init(float posX, float posY) override;	//������
	void Load(const char* file_path) override;		//�ǂݍ���
	void Step() override;							//�X�e�b�v
	void Draw() override;							//�`��
	void Delete() override;							//�폜
	void Fin() override;							//�㏈��


private:
	int handle_;	//�摜�n���h��
};