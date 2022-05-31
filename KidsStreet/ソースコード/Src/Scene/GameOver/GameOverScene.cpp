//GameOverScene.cpp
//�Q�[���I�[�o�[�V�[��

#include "GameOverScene.h"
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


CGameOverScene::CGameOverScene()
{
	Init();
}

CGameOverScene::~CGameOverScene()
{
}

//������
void CGameOverScene::Init()
{
	//UI�Ǘ�����
	CGameUIManager::CreateInstance();
	CGameUIManager* ui_manager = CGameUIManager::GetInstance();
	//�w�i����
	CGameUI* bg = ui_manager->CreateUI(CGameUIManager::UI_TYPE_SPRITE);
	bg->Init(0.0f, 0.0f);
	bg->Load("Data/Title/GameOver_BG.jpg");

	//��������
	CSound::InitSound();
}

//�ǂݍ���
void CGameOverScene::Load()
{
	//���ǂݍ���
	CSound::LoadBGM(CSound::BGM_GAMEOVER);
}

//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
void CGameOverScene::Set()
{
	//���Đ�
	CSound::PlayBGM(CSound::BGM_GAMEOVER);
}

//���t���[���Ăԏ���
void CGameOverScene::Step()
{
	//Enter�L�[�������ꂽ��^�C�g���V�[����
	if (CInput::GetInstance()->IsPush(CInput::INPUT_KIND_KEY, KEY_INPUT_RETURN))
	{
		//�^�C�g���V�[���֕ύX
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_TITLE);
	}

	//UI�Ǘ��X�e�b�v
	CGameUIManager::GetInstance()->Step();
}


//�`��
void CGameOverScene::Draw()
{
	//UI�Ǘ��`��
	CGameUIManager::GetInstance()->Draw();
}


//�㏈��
void CGameOverScene::Fin()
{
	//UI�Ǘ��㏈��
	CGameUIManager::GetInstance()->DeleteAll();
	CGameUIManager::DeleteInstance();

	//���㏈��
	CSound::FinSound();
}