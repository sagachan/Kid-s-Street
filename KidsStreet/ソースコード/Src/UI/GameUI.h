//GameUI.h
//UI�̃x�[�X�ƂȂ�N���X
#include "DxLib.h"
#pragma once

//UI�̃x�[�X�ƂȂ�N���X
class CGameUI
{
public:
	CGameUI();
	virtual ~CGameUI();

public:
	virtual void Init(float posX, float posY) = 0;	//������
	virtual void Load(const char* file_path) = 0;		//�ǂݍ���
	virtual void Step() = 0;							//�X�e�b�v
	virtual void Draw() = 0;							//�`��
	virtual void Delete() = 0;							//�폜
	virtual void Fin() = 0;								//�㏈��

	void SetPosX(float posX) { posX_ = posX; }	//�w���W�ݒ�
	void SetPosY(float posY) { posY_ = posY; }	//�x���W�ݒ�

	float GetPosX()const { return posX_; }	//�w���W�擾
	float GetPosY()const { return posY_; }	//�x���W�擾

	void SetSize(int size) { size_ = size; }
	void SetEndPos(VECTOR pos) { endPos_ = pos; }
	

	void SetDrawFlg(bool flg) { drawFlg_ = flg; }
	bool GetDrawFlg() { return drawFlg_; }

protected:
	float	posX_;	//�w���W
	float	posY_;	//�x���W
	int		size_;
	VECTOR endPos_;
	bool	drawFlg_;	//�`��t���O
};