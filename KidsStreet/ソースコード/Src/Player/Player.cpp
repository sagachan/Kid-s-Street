#include "Player.h"
#include "../Common.h"
#include <math.h>
#include "../Library/MyMath/MyMath.h"
#include "../Library/Input/Input.h"
#include "../Camera/CameraManager.h"
#include "../Enemy/EnemyManager.h"
#include "../Item/UseItem/ItemManager.h"
#include "../Library/Animation/Animation.h"
#include "../Field/FieldManager.h"
#include "../Item/GatherItem/GatherFactory/GatherManager.h"
#include "../Item/ItemCommon.h"
#include "../UI/GameUIManager.h"
#include "../Library/Sound/Sound.h"
#include "../Collision/CollisionManager.h"
#include "../Library/LibraryCommon.h"
#include "../Scene/SaveScene/SaveScene.h"

namespace
{
	//�v���C���[�֘A
	const VECTOR PLAYER_START_POS = VGet(5.0f, 1.0f, 250.0f);	//�v���C���[�̍��W
	const VECTOR PLAYER_CONTINUE_POS = VGet(-1500.0f, 1.0f, 1700.0f);	//�v���C���[�̍��W
	const VECTOR PLAYER_CONTINUE_ROT = VGet(0.0f, 4.8f, 0.0f);	//�v���C���[�̉�]


	const float PLAYER_SPD = 0.2f;			//�v���C���[�̈ړ����x
	const float PLAYER_ADDSPD = 0.8f;		//�v���C���[���s���x
	const float PLAYER_JUMP_POWER = 0.5f;	//�v���C���[�̃W�����v��
	const float PLAYER_G_POWER = 0.5;		//�v���C���[�ɂ�����d�͂̋����ݒ�i���̐��l�͉��j
	const bool  HIT_INIT_FLG = false;		//�v���C���[�ɊO������ύX�\�ȓ����蔻��t���O�̏����l
	const int	PLAYER_HP = 100;			//�v���C���[�̗̑�
	const float CLEAR_LINE = -1600.0f;		//�N���A���C��

	const float PLAYER_R = 2.0f;			//�v���C���[�̔��a
	const VECTOR COL_RADIUS = VGet(2.0f, 2.0f, 2.0f);

	//��ʔ͈͊֘A
	const float RANGE_MAX_WIDTH = 14.0f;	//�����̍ő�͈�
	const float RANGE_MIN_WIDTH = -14.0f;	//�����̍ŏ��͈�
	const float RANGE_MAX_HEIGHT = 12.0f;	//�c���̍ő�͈�
	const float RANGE_MIN_HEIGHT = -12.0f;	//�c���̍ő�͈�

	//�W�����v�֘A
	const float ORIGIN_POS = 0.0f;			//���_���W
	const float PLAYER_JUMP_TIME = 0.35f;	//�v���C���[�̔�Ԏ���
	const float PLAYER_JUMP_VAL = 0.0f;		//�W�����v��
	const float GRAVITY = 0.3f;				//�d��
	const float JUMP_CHARGE = 10.0f;		//�W�����v���̗��ߍd������
	const float JUMP_LANDING = 40.0f;		//�W�����v��̒��n�d������

	//�A�j���[�V�����֘A
	const int THROW_FRM = 25;
	const int RELOAD_FRM = 10;
	const int ATTACK_FRM = 15;
	const float ATTACK_RAD = 10.0f;
	const int ATTACK_DMG = 5;
}




//�R���X�g���N�^
CPlayer::CPlayer()
{
	Init();
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{
	Fin();
}



//������
void CPlayer::Init()
{
	jump_time_ = 0.0f;				//�W�����v�̎���
	hit_flg_ = HIT_INIT_FLG;		//�����蔻��t���O������
	hp_ = 0;
	state_ = PLAYER_INIT;			//��ԁi�X�e�[�^�X�j
	old_state_ = PLAYER_INIT;		//�O���[�v��ԁi�X�e�[�^�X�j
	forward_ = { 0.0f };			//�v���C���[�̌����x�N�g���i�[
}



//�ǂݍ��݁i���[�h�j
void CPlayer::Load()
{
	//���f���ǂݍ���
	hndl_ = MV1LoadModel("Data/Player/Player.x");

	CSound::LoadSE(CSound::SE_FOOT);
}



//�e�ϐ��Ȃǂɏ����l��ݒ�i�Z�b�g�j
void CPlayer::Set()
{
	pos_ = PLAYER_START_POS;

	CSaveScene* save = CSaveScene::GetInstance();
	if (!save->GetBossFlg()){
		pos_ = PLAYER_CONTINUE_POS;
		rot_ = PLAYER_CONTINUE_ROT;
	}

	rad_ = PLAYER_R;			//���a
	state_ = PLAYER_STAND;			//�X�e�[�^�X
	hp_ = PLAYER_HP;
	MV1SetupCollInfo(hndl_);

	//�����蔻��𐶐�
	CCollisionManager* collision = CCollisionManager::GetInstance();
	colData_.pos_			= pos_;
	colData_.cubeRad_		= COL_RADIUS;
	colData_.useFlg_		= true;
	colData_.myList_		= COL_CHECK_PLAYER;
	colData_.type_.pawn_	= CHECK_BOX_HIT;
	colData_.type_.static_	= CHECK_BOX_NONE;
	colData_.type_.dynamic_ = CHECK_BOX_NONE;
	colData_.object_		= OBJECT_PAWN;
	colData_.shapeCol_		= SHAPE_CUBE;

	colNum_ = collision->CreateCol(&colData_);
}


//�v���C���[�������蔻��̉e�����󂯂鏈��
void CPlayer::HitSet()
{
	pos_.x = oldPos_.x;
	pos_.z = oldPos_.z;
}


//�v���C���[�������蔻��̉e�����󂯂邩�ǂ������t���O�ŊǗ�����I�[�o�[���[�h
void CPlayer::HitSet(bool flg)
{
	hit_flg_ = flg;
}

void CPlayer::AddDamage(int dmg)
{
	hp_ -= dmg;
}




//���t���[���Ăԏ����i����j
void CPlayer::Step()
{
	//�v���C���[�̗̑͂�0��菭�Ȃ��Ȃ�
	if (hp_ < 0){
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_OVER);
	}

	// ���݃A�j�����I��������
	end_animFlg_ = IsEndAnim();

	//�v���C���[�ɏ�ɏd�͂�������
	pos_.y -= GRAVITY;
	//�v���C���[�̈ړ��O�̍��W���L�^
	oldPos_ = pos_;
	
	move_ = { 0 };

	//�O���ɗD��x���������͏���������ꍇ�͒ʂ�Ȃ�
	if(!CGameUIManager::GetInstance()->GetInputFlg())
		StepInput();
	
	//�v���C���[�̍��W�x�N�g��
	pos_ = CMyMath::VecAdd(pos_, move_);
	
	StatesSet();

	//�O������ύX���s���������蔻��
	if (hit_flg_ == true)
	{
		HitSet();
		//�g�p����Ƃɖ߂�
		HitSet(HIT_INIT_FLG);
	}

	frm_int_++;

	Hit();

	CEnemyManager* enemyManager = CEnemyManager::GetInstance();
	if (enemyManager->GetSceneFlg() && CLEAR_LINE > pos_.x)
	{
		//�Q�[���N���A�V�[���֕ύX
		CSceneManager::GetInstance()->ChangeScene(CSceneManager::SCENE_ID_GAME_CLEAR);
	}
}


//�X�V
void CPlayer::Update()
{
	//�A�j���[�V�����X�V
	CAnim3D::UpdateAnim();

	//�v���C���[�̉�]
	MV1SetRotationXYZ(hndl_, rot_);

	//�v���C���[�̍��W
	MV1SetPosition(hndl_, pos_);

	MV1RefreshCollInfo(hndl_);

	oldRot_ = rot_;

	//�����蔻��֌W�X�V
	CCollisionManager::GetInstance()->SetUpdateColInfo(colNum_, pos_, colData_.useFlg_);
}

void CPlayer::Hit()
{
	//�v���C���[�ɏ������W������̂�h������
	//�v���C���[�ƃ^�[�Q�b�g�̓����蔻��̓^�[�Q�b�g���ōs��
}


//�`��
void CPlayer::Draw()
{
	//�v���C���[�̕`��
	MV1DrawModel(hndl_);
}


//�폜
void CPlayer::Delete()
{
	//�v���C���[���f���폜
	MV1DeleteModel(hndl_);

	//�폜������0�������Ă���
	hndl_ = 0;
}


//�㏈��
void CPlayer::Fin()
{
	//Delete���Ă΂�Ă��Ȃ��Ȃ�
	if (hndl_ != 0)
	{
		//�폜���Ă�ł���
		Delete();

	}
}


//���̓X�e�b�v
void CPlayer::StepInput()
{

	CInput* input = CInput::GetInstance();
	CRoad* field = CFieldManager::GetInstance()->GetRoad();
	CItemManager* item_manager = CItemManager::GetInstance();
	//--------------------------------
	//    �v���C���[�̈ړ�����
	//--------------------------------
	float add = PLAYER_SPD;			//�v���C���[�̈ړ����x�ݒ�
	bool calcFlg = false;			//�s��v�Z���s�����ǂ���
	bool inputFlg = false;			//�����Ɉ�������͂������Ȃ�
	oldPos_ = pos_;				//�����O���W��ێ�

	//�����x�N�g�������߂�
	forward_.x = sinf(rot_.y);
	forward_.z = cosf(rot_.y);


	//�_�b�V������
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_LSHIFT))
	{
		add = PLAYER_ADDSPD;
	}

	//�����Ă�������ֈړ�
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_W) && !inputFlg)
	{
		//�����x�N�g����K�؂ȑ傫���E�����ɕύX���č��W�ɉ��Z
		move_.x += forward_.x * add;
		move_.z += forward_.z * add;
		inputFlg = true;
	}
	//���ړ�
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_A) && !inputFlg)
	{
		move_.x -= PLAYER_SPD;
		calcFlg = true;
		inputFlg = true;
	}
	//�E�ړ�
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_D) && !inputFlg)
	{
		move_.x += PLAYER_SPD;
		calcFlg = true;
		inputFlg = true;
	}
	//�����Ă�������Ƃ͋t�ֈړ�
	if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_S) && !inputFlg)
	{
		//�����x�N�g����K�؂ȑ傫���E�����ɕύX���č��W�ɉ��Z
		move_.x -= forward_.x * add;
		move_.z -= forward_.z * add;
		inputFlg = true;
	}

	if (calcFlg)
	{
		//�J�����̌����Ă�������ɐi�ށi���������̈ړ��������ė~�����̂ŁAY����]�l�������Ȃ��j
		MATRIX translate_mat = CMyMath::GetTranslateMatrix(move_);
		MATRIX yaw_mat = CMyMath::GetYawMatrix(rot_.y);
		MATRIX result_mat = CMyMath::MatMult(yaw_mat, translate_mat);

		//�s�񂩂�ړ���̍��W�������擾
		move_ = VGet(result_mat.m[0][3], result_mat.m[1][3], result_mat.m[2][3]);
		move_ = CMyMath::VecNormalize(VGet(move_.x, 0.0f, move_.z));

		move_ = CMyMath::VecScale(move_, PLAYER_SPD);
	}
	
	//�������͑ҋ@�̎�����
	if (state_ == PLAYER_STAND || state_ == PLAYER_WALK || state_ == PLAYER_RUN)
	{
		//�U��
			//F�L�[�������ꂽ���A�C�e������Ɏ����Ă��鎞
		if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_F) &&
			item_manager->GetHold())
		{
			state_ = PLAYER_THROW;
		}

		//�X�y�[�X�L�[�������ꂽ���v���C���[�����݋󒆂ɂ��Ȃ��Ȃ�
		if (CInput::GetInstance()->IsPush(CInput::INPUT_KIND_KEY, KEY_INPUT_SPACE) && field->Is_in_Air() == false)
		{
			//��Ԃ��W�����v�㏸����
			state_ = PLAYER_JUMP;
			jump_time_ = 0.0f;
		}

		
		//�܂��͎������Q�Ƃ��Ă���A�C�e�����܂���ɓ����Ă��Ȃ��ꍇ�͑��U�͂ł��Ȃ��悤�ɂ���
		CItemManager* itemManager = CItemManager::GetInstance();
		CGatherManager* gatherManager = CGatherManager::GetInstance();
		ITEM_KIND item = itemManager->GetItemKind();
		bool* gatherFlg = gatherManager->GetGatherItem();
		bool reloadFlg = false;
		bool attackFlg = false;

		switch (item){
		case ITEM_INIT:break;
		case ERASER:if(gatherFlg[ERASER]) { reloadFlg = true; } break;
		case PENCIL:if(gatherFlg[PENCIL]) { reloadFlg = true; } break;
		case RULER:if (gatherFlg[RULER]) { reloadFlg = true; } break;
		case GLOVE:if (gatherFlg[GLOVE]) { attackFlg = true; } break;
		default:
			break;
		}
		
		//���U
		if (reloadFlg)
		{
			//R�L�[�������ꂽ���A�C�e������ɂ����Ă��Ȃ���
			if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_R) &&
				!item_manager->GetHold())
			{
				state_ = PLAYER_RELOAD;
			}
		}

		//�U��
		if (attackFlg)
		{
			//F�L�[�������ꂽ���O���[�u����ɑI��ł��鎞
			if (input->IsDown(input->INPUT_KIND_KEY, KEY_INPUT_F) &&
				!item_manager->GetHold())
			{
				state_ = PLAYER_ATTACK;
			}
		}
	}
}

//�A�j���[�V������ԑJ��
void CPlayer::StatesSet()
{
	switch (state_)
	{
	case PLAYER_STAND:FromStand(); break;
	case PLAYER_WALK:FromWalk(); break;
	case PLAYER_RUN:FromRun(); break;
	case PLAYER_JUMP:FromJump(); break;
	case PLAYER_THROW:FromThrow(); break;
	case PLAYER_RELOAD:FromReload(); break;
	case PLAYER_ATTACK:FromAttack(); break;
	}
	
	//�X�e�[�^�X���O�t���ƈႤ�Ȃ�A�j���[�V�����Đ��t���O��������
	if (state_ != old_state_)
	{
		changeFlg_ = true;
		frm_int_ = 0;
	}

	//���t����Ԃ��i�[
	old_state_ = state_;
}

void CPlayer::FromStand()
{
	if (changeFlg_ == true) {
		//�A�j���[�V����
		CAnim3D::RequestLoop(STAND, 1.0f, -1, false);
		//��x�����ǂݍ��܂��悤�ɂ��邽��
		changeFlg_ = false;
		frm_int_ = 0;
	}

	//�O�t���[�������瓮�����Ȃ�
	if (pos_.x != oldPos_.x || pos_.z != oldPos_.z) {
		state_ = PLAYER_WALK;
		changeFlg_ = true;
	}
}

void CPlayer::FromWalk()
{
	//���s��Ԏ��̏�ԑJ��
	if (changeFlg_ == true) {
		//�A�j���[�V����
		CAnim3D::RequestLoop(WALK, 1.0f, -1, false);
		//��x�����ǂݍ��܂��悤�ɂ��邽��
		changeFlg_ = false;
		frm_int_ = 20;
	}

	CInput* input = CInput::GetInstance();
	if (input->IsRelease(input->INPUT_KIND_KEY, KEY_INPUT_LSHIFT))
	{
		state_ = PLAYER_RUN;
		changeFlg_ = true;
	}

	//�����~�܂����Ȃ�ҋ@�ɖ߂�
	if (pos_.x == oldPos_.x && pos_.z == oldPos_.z) {
		state_ = PLAYER_STAND;
		changeFlg_ = true;
	}

	if (frm_int_ == 30)
	{
		CSound::PlaySE(CSound::SE_FOOT);
		frm_int_ = 0;
	}
}

void CPlayer::FromRun()
{
	//���s��Ԏ��̏�ԑJ��
	if (changeFlg_ == true) {
		//�A�j���[�V����
		CAnim3D::RequestLoop(RUN, 2.0f, -1, false);
		//��x�����ǂݍ��܂��悤�ɂ��邽��
		changeFlg_ = false;
		frm_int_ = 5;
	}
	CInput* input = CInput::GetInstance();
	if (input->IsKeep(input->INPUT_KIND_KEY, KEY_INPUT_LSHIFT))
	{
		state_ = PLAYER_WALK;
	}

	if (frm_int_ == 5)
	{
		CSound::PlaySE(CSound::SE_FOOT);
		frm_int_ = 0;
	}
}

void CPlayer::FromJump()
{
	if (changeFlg_ == true)
	{
		//�A�j���[�V����
		CAnim3D::RequestEndLoop(JUMP, 1.15f, -1, false);
		//��x�����ǂݍ��܂��悤�ɂ��邽��
		changeFlg_ = false;
	}

	//�㏸
	pos_.y += PLAYER_JUMP_VAL;
	jump_time_ += 1.0f / FRAME_RATE;

	//�W�����v���Ԃ��߂�����
	if (jump_time_ >= PLAYER_JUMP_TIME)
	{
		jump_time_ = 0.0f;
	}

	//�W�����v���̏������ߍd���ƃW�����v��̒��n�d��
	if (GetAnimFrm() < JUMP_CHARGE ||
		GetAnimFrm() > JUMP_LANDING)
	{
		pos_ = oldPos_;
	}
	//�A�j���[�V�����I�������Ȃ�ҋ@�ɖ߂�
	if (end_animFlg_ == true)
	{
		state_ = PLAYER_STAND;
		changeFlg_ = true;
	}
}
void CPlayer::FromReload()
{
	if (changeFlg_ == true){
		//�A�j���[�V����
		CAnim3D::RequestEndLoop(RELOAD, 1.0f, -1, false);
		//��x�����ǂݍ��܂��悤�ɂ��邽��
		changeFlg_ = false;
	}
	//���̏�Ԃł͓����Ȃ�
	pos_ = oldPos_;
	frm_int_++;

	
	if (frm_int_ == RELOAD_FRM){
		CItemManager* item_manager = CItemManager::GetInstance();
		//�A�C�e������ɂ�
		item_manager->SetHold(true);
	}
	//�A�j���[�V�����I�������Ȃ�ҋ@�ɖ߂�
	if (end_animFlg_ == true){
		state_ = PLAYER_STAND;
	}
}

void CPlayer::FromThrow()
{
	if (changeFlg_ == true){
		//�A�j���[�V����
		CAnim3D::RequestEndLoop(THROW, 1.0f, -1, false);
		//��x�����ǂݍ��܂��悤�ɂ��邽��
		changeFlg_ = false;
		frm_int_ = 0;
	}
	//���̏�Ԃł͓����Ȃ�
	pos_ = oldPos_;
	
	if (frm_int_ == THROW_FRM){
		CItemManager* item_manager = CItemManager::GetInstance();
		//�A�C�e�����肩�痣���
		item_manager->SetHold(false);
		//�A�C�e���𓊂������Ƃ��A�C�e���Ǘ��ɓn��
		item_manager->SetThrowflg(true);
		ITEM_KIND kind = item_manager->GetItemKind();
		CGameUIManager* gameUIManager = CGameUIManager::GetInstance();
		
		//�A�C�e��UI�폜
		switch (kind)
		{
		case ERASER:
			if (item_manager->GetUseNum() == MAX_ERASER - 1)
			gameUIManager->CGameUIManager::DeleteUI(ITEM_ID_ERASER);
			break;
			
		case PENCIL:
			if (item_manager->GetUseNum() == MAX_PENCIL + MAX_ERASER - 1)
			gameUIManager->CGameUIManager::DeleteUI(ITEM_ID_PENCIL);
			break;

			
		case RULER:if (item_manager->GetUseNum() == MAX_RULER + MAX_PENCIL + MAX_ERASER - 1)
			gameUIManager->CGameUIManager::DeleteUI(ITEM_ID_RULER);
			break;
		}
		
	}

	//�A�j���[�V�����I�������Ȃ�ҋ@�ɖ߂�
	if (end_animFlg_ == true){
		state_ = PLAYER_STAND;
	}
}

void CPlayer::FromAttack()
{
	if (changeFlg_ == true) {
		//�A�j���[�V����
		CAnim3D::RequestEndLoop(ATTACK, 1.0f, -1, false);
		//��x�����ǂݍ��܂��悤�ɂ��邽��
		changeFlg_ = false;
		frm_int_ = 0;
	}
	//���̏�Ԃł͓����Ȃ�
	pos_ = oldPos_;

	if (frm_int_ == ATTACK_FRM)
	{
		//�{�X���U���\�͈͓��ɂ��邩
		CBoss* boss = CEnemyManager::GetInstance()->GetBoss();
		VECTOR bossPos = boss->GetPosition();
		if (CMyMath::RadiusCheck(pos_.x, ATTACK_RAD, bossPos.x) &&
			CMyMath::RadiusCheck(pos_.z, ATTACK_RAD, bossPos.z))
		{
			boss->SetColFlg(true);
			boss->Damage(DMG_WEAK);
		}
	}
	//�A�j���[�V�����I�������Ȃ�ҋ@�ɖ߂�
	if (end_animFlg_ == true) {
		state_ = PLAYER_STAND;
	}
}