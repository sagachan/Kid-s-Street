//TutorialMainScene.h

#pragma once

#include "../SceneBase.h"

//�`���[�g���A���V�[���N���X
class CTutorialMainScene :public CSceneBase
{
public:
	CTutorialMainScene();
	~CTutorialMainScene();

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