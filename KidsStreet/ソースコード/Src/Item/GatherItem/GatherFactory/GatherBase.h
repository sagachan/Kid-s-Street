//���W�A�C�e���p���N���X
//���łɑ��݂���^�C�v�ɓK�p���ꂽ�A�C�e���̊��N���X
//��:�����S��Gather�N���X�Ȃ�

#pragma once

class CGatherBase
{
public:
	CGatherBase();
	virtual ~CGatherBase();


	//������
	virtual void Init() = 0;
	//�ǂݍ���
	virtual void Load() = 0;
	//�ݒ�
	virtual void Set() = 0;
	//���t���[���Ăԏ���
	virtual void Step() = 0;
	//�`��
	virtual void Draw() = 0;
	//�㏈��
	virtual void Fin() = 0;
};