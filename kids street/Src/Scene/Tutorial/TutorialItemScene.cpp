//TutorialItemScene.cpp
//�^�C�g���V�[��

#include "TutorialItemScene.h"
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
	
}

CTutorialItemScene::CTutorialItemScene()
{
	Init();
}

CTutorialItemScene::~CTutorialItemScene()
{
}

//������
void CTutorialItemScene::Init()
{
	//UI�Ǘ�����
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//�w�i����
	CGameUI* bg = ui_manager->CreateUI(CGameUIManager::UI_TYPE_SPRITE);
	bg->Init(0.0f, 0.0f);
	bg->Load("Data/Title/TutorialItem.png");
}


//�ǂݍ���
void CTutorialItemScene::Load()
{


}


//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
void CTutorialItemScene::Set()
{
	
}


//���t���[���Ăԏ���
void CTutorialItemScene::Step()
{
	CInput* input = CInput::GetInstance();

	if (input->IsPush(input->INPUT_KIND_KEY, KEY_INPUT_RETURN))
	{
		//�v���C�V�[���֕ύX
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_PLAY);
	}

	//UI�Ǘ��X�e�b�v
	CGameUIManager::GetInstance()->Step();

}


//�`��
void CTutorialItemScene::Draw()
{
	//UI�Ǘ��`��
	CGameUIManager::GetInstance()->Draw();
}


//�㏈��
void CTutorialItemScene::Fin()
{
	//UI�Ǘ��㏈��
	CGameUIManager::GetInstance()->DeleteAll();
	CGameUIManager::DeleteInstance();

	//���㏈��
	CSound::FinSound();
}