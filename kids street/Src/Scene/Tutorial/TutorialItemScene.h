//TutorialItemScene.h

#pragma once

#include "../SceneBase.h"

//�`���[�g���A���A�C�e���V�[���N���X
class CTutorialItemScene :public CSceneBase
{
public:
	CTutorialItemScene();
	~CTutorialItemScene();

	//������
	void Init() override;

	//�ǂݍ���
	void Load() override;

	//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
	void Set() override;

	//���t���[���Ăԏ���
	void Step() override;

	//�`��
	void Draw() override;

	//�㏈��
	void Fin() override;

private:

	
};