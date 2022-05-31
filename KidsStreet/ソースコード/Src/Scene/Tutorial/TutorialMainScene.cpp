//TutorialScene.cpp
//�^�C�g���V�[��

#include "TutorialMainScene.h"
#include "../SceneManager.h"
#include "../../Library/Input/Input.h"
#include "DxLib.h"
#include <math.h>
#include "../../Common.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../UI/GameUIManager.h"
#include "../../Library/Sound/Sound.h"

namespace
{
	const float TEXT_MAX_SIZE = 1.0f;	//�����̍ő�T�C�Y
	const float TEXT_ADD_SIZE = 0.01f;	//�����̉��Z�����T�C�Y��
	const float TEXT_MOVE_Y = 30.0f;	//������Y���W�ړ���
	
	//�g�`�̊p�x�̕ς��̑����i�T�b�ň���j
	const float WAVE_ANGLE_SPD = (DX_TWO_PI_F / FRAME_RATE) / 5.0f;
}

CTutorialMainScene::CTutorialMainScene()
{
	Init();
}

CTutorialMainScene::~CTutorialMainScene()
{
}

//������
void CTutorialMainScene::Init()
{
	//UI�Ǘ�����
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//�w�i����
	CGameUI* bg = ui_manager->CreateUI(CGameUIManager::UI_TYPE_SPRITE);
	bg->Init(0.0f, 0.0f);
	bg->Load("Data/Title/TutorialMain.png");
}


//�ǂݍ���
void CTutorialMainScene::Load()
{


}


//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
void CTutorialMainScene::Set()
{
	
}


//���t���[���Ăԏ���
void CTutorialMainScene::Step()
{
	CInput* input = CInput::GetInstance();

	if (input->IsPush(input->INPUT_KIND_KEY, KEY_INPUT_RETURN))
	{
		//�v���C�V�[���֕ύX
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_TUTORIAL_ITEM);
	}

	//UI�Ǘ��X�e�b�v
	CGameUIManager::GetInstance()->Step();
}


//�`��
void CTutorialMainScene::Draw()
{
	//UI�Ǘ��`��
	CGameUIManager::GetInstance()->Draw();
}


//�㏈��
void CTutorialMainScene::Fin()
{
	//UI�Ǘ��㏈��
	CGameUIManager::GetInstance()->DeleteAll();
	CGameUIManager::DeleteInstance();
}