//UI�p���N���X

#pragma once

class CUIBase
{
public:
	CUIBase();
	virtual ~CUIBase();

	virtual void Init() = 0;			//������
	virtual void Load() = 0;			//�ǂݍ���
	virtual void Set() = 0;				//�ݒ�
	virtual void Step() = 0;			//���t���[���Ăԏ���
	virtual void Draw() = 0;			//�`��
	virtual void Fin() = 0;				//�㏈��
};