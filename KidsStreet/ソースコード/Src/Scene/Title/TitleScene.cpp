//TitleScene.cpp
//�^�C�g���V�[��

#include "TitleScene.h"
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

CTitleScene::CTitleScene()
{
	Init();
}

CTitleScene::~CTitleScene()
{
}

//������
void CTitleScene::Init()
{
	//UI�Ǘ�����
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//�w�i����
	CGameUI* bg = ui_manager->CreateUI(CGameUIManager::UI_TYPE_SPRITE);
	bg->Init(0.0f, 0.0f);
	bg->Load("Data/Title/openning.jpg");

	//��������
	CSound::InitSound();
}


//�ǂݍ���
void CTitleScene::Load()
{
	//���ǂݍ���
	CSound::LoadBGM(CSound::BGM_TITLE);
}


//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
void CTitleScene::Set()
{
	//���Đ�
	CSound::PlayBGM(CSound::BGM_TITLE);
}


//���t���[���Ăԏ���
void CTitleScene::Step()
{
	CInput* input = CInput::GetInstance();

	if (input->IsPush(input->INPUT_KIND_KEY, KEY_INPUT_RETURN))
	{
		//�v���C�V�[���֕ύX
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_TUTORIAL_MAIN);
	}


	//UI�Ǘ��X�e�b�v
	CGameUIManager::GetInstance()->Step();
}


//�`��
void CTitleScene::Draw()
{
	//UI�Ǘ��`��
	CGameUIManager::GetInstance()->Draw();
}


//�㏈��
void CTitleScene::Fin()
{
	//UI�Ǘ��㏈��
	CGameUIManager::GetInstance()->DeleteAll();
	CGameUIManager::DeleteInstance();
}