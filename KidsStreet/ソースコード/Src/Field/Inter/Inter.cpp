//Inter.cpp
//�����_�N���X

#include "Inter.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../Player/PlayerManager.h"
#include "../../Enemy/EnemyManager.h"

//�t�B�[���h�֘A
namespace
{
	const VECTOR	FIELD_POS = VGet(-20.0f, -1.0f, 0.0f);				//�t�B�[���h�̍��W
	const int		FIELD_D = 36;									//�t�B�[���h�̉��s
	const float		INTER_RADIUS = 50.0f;							//�����_�Ƃ��ĔF�߂Ă���L��
	
}

//�R���X�g���N�^
CInter::CInter()
{
	Init();
}

//�f�X�g���N�^
CInter::~CInter()
{
	Fin();
}


void CInter::Init()
{
	for (int interNum = 0; interNum < INTER_MAX_NUM; interNum++){
		interInfo_[interNum] = { 0 };
	}
	frmHndl_ = 0;
	for (int carNum = 0; carNum < INTER_MAX_NUM; carNum++){
		interInfo_[carNum] = { 0 };
	}
}


void CInter::Set()
{
	//�����_�̐����������_���\���̂�����
	//true�̕����͐i�ނ��Ƃ��\
	InterInfo setType[INTER_MAX_NUM]
	{
		{1,0,0,1},
		{1,0,1,0},
		{1,1,1,0},
		{1,1,0,1},
		{1,1,1,0},
		{1,1,1,1},
		{1,0,0,1},
		{0,1,0,1},
		{1,1,1,1},
		{0,1,1,0},
		{0,1,0,1},
		{0,1,1,1},
		{0,1,1,0},
		{1,1,0,1},
		{1,1,1,0},
		{1,0,1,0},
		{1,0,0,1}
	};

	//�f�[�^���R�s�[
	for (int arrayNum = 0; arrayNum < INTER_MAX_NUM; arrayNum++)
	{
		interInfo_[arrayNum].front = setType[arrayNum].front;
		interInfo_[arrayNum].back = setType[arrayNum].back;
		interInfo_[arrayNum].right = setType[arrayNum].right;
		interInfo_[arrayNum].left = setType[arrayNum].left;
	}
}


void CInter::Load()
{
	frmHndl_ = MV1LoadModel("Data/Map/Inter/mapInterBone.x");
	
	//�}�b�v�̍��W
	MV1SetPosition(frmHndl_, FIELD_POS);
}

void CInter::Delete()
{

}


void CInter::Fin()
{
	//if (m_handle[0] != 0)
	//{
	//	//Delete���Ă�ł���
	//	Delete();
	//}
}


void CInter::InterManager()
{
	CEnemyManager* enemyManager = CEnemyManager::GetInstance();		 
	
	int interMaxNum = MV1GetFrameNum(frmHndl_),trueNum = 0;
	bool interFlg = true;
	VECTOR Check[INTER_BONE_MAX_NUM] = {0};

	//�Ԃ̐��̕����������_�����m�F����
	for (int carNum = 0; carNum < APPEAR_CAR_NUM; carNum++)
	{
		CEnemy* car = enemyManager->GetEnemy(carNum);

		trueNum = 0;

		//�����_�������Ƀ`�F�b�N���Ă���
		for (int interNum = 0; interNum < interMaxNum; interNum++)
		{

			//���̎Ԃ������_�������J�n���Ă��Ȃ��Ȃ�
			if (!car->GetInterFlg())
			{
				//�����_�ԍ�����̎��ɂ������肵�Ȃ��Ă����̂ŁA��̎��̂ݒʂ�悤�ɂ���
				if (interNum % INTER_BW)
				{

					//���Q�Ƃ���Ă���ԍ��̎Ԃ̈ʒu���������Ƃ��Ċ֐����Ă�
					CheckComeInter(car->GetPosition(), interNum,trueNum, carNum);
					trueNum++;
				}
			}
		}
	}
	
	//�����_�������Ƀ`�F�b�N���Ă���
	for (int interNum = 0; interNum < interMaxNum; interNum++)
	{
		Check[interNum] = MV1GetFramePosition(frmHndl_, interNum);
	}

	//�Ԃ̐��̕����������_�����m�F����
	for (int carNum = 0; carNum < APPEAR_CAR_NUM; carNum++)
	{
		CEnemy* car = enemyManager->GetEnemy(carNum);

		if (car->GetInterFlg())
		{
			//�����_���o�Ă�Ȃ�interFlg��܂�
			CheckOutInter(car->GetPosition(), car->GetInterNum(), carNum);
		}
	}
}



//�Ԃ������_�ɓ����Ă��邩�ǂ������m�F����A���������Ă���Ȃ�dirInfo�̎g�p�t���O�𗧂Ă�B
//���̏����͎g�p�t���O�������Ă���Ƃ��͒ʂ�Ȃ�
void CInter::CheckComeInter(VECTOR carPos,int frmNum,int interNum,int carNum)
{
	CEnemy* car = CEnemyManager::GetInstance()->GetEnemy(carNum);

	VECTOR frmPos = MV1GetFramePosition(frmHndl_, frmNum);

	//�͈͌v�Z���g���Č����_�ɓ����Ă��邩�ǂ����𔻒肷��Ax��z�������͈͓��ɂ���ꍇ�Ɍ���A
	if (CMyMath::RadiusCheck(carPos.x, INTER_RADIUS, frmPos.x)&&
		CMyMath::RadiusCheck(carPos.z, INTER_RADIUS, frmPos.z))
	{
		//�����_�̏������J�n����t���O��true�ɂ��āA�����_�����ɕK�v�Ȍ����_�ԍ���Ώۂ̎ԃN���X�ɓn��
		car->SetInterFlg(true);
		car->SetInterNum(frmNum);

		//�Ԃ̐i�ސ�𔻒肷��
		JudgeInter(carPos, interNum, carNum);
	}
}


void CInter::CheckOutInter(VECTOR carPos, int interNum, int carNum)
{
	CRoad* road = CFieldManager::GetInstance()->GetRoad();
	CEnemy* car = CEnemyManager::GetInstance()->GetEnemy(carNum);

	VECTOR frmPos = MV1GetFramePosition(frmHndl_, interNum);

	//�͈͌v�Z���g���Č����_�ɓ����Ă��邩�ǂ����𔻒肷��Ax��z�������͈͓��ɂ���ꍇ�Ɍ���A
	if (CMyMath::RadiusCheck(carPos.x, INTER_RADIUS, frmPos.x) == false ||
		CMyMath::RadiusCheck(carPos.z, INTER_RADIUS, frmPos.z) == false)
	{
		//�����_�̏������J�n����t���O��false�ɂ���
		car->SetInterFlg(false);
		car->SetEndInter(false);
	}
}

//�Ԃ̐i�ސ�𔻒肷��
void CInter::JudgeInter(VECTOR carPos,int interNum, int carNum)
{
	//�����_�����Ɏg�������_���Ɍ��߂������ԍ����i�[����ϐ�(dir)�ƁA�����_���Ɍ��߂��ϐ��ԍ����g���čs�������𔻒肷�邽�߂Ɏg���ϐ�(true)
	int dirNum = 0,trueNum = 0;
	//�����_�󋵂�\�����\���̂̊i�[�p
	bool interFlg[INTER_DIR_NUM];

	CRoad* road = CFieldManager::GetInstance()->GetRoad();
	CEnemy* car = CEnemyManager::GetInstance()->GetEnemy(carNum);


	//�\���̂Ƃ��Ă킩��₷�����Ă������A���̏����Ŏg���ɂ͈����ɂ����̂ŕϐ��z��ɕς���
	interFlg[FRONT] = interInfo_[interNum].front;
	interFlg[BACK] = interInfo_[interNum].back;
	interFlg[RIGHT] = interInfo_[interNum].right;
	interFlg[LEFT] = interInfo_[interNum].left;

	
	//�����_�ɎԂ��������������m�F���Ă��̕����Ƀt���O��܂邱�Ƃœ������ɖ߂�Ȃ��悤�ɂ���
	interFlg[CheckInter(interFlg,carNum)] = false;

	for (int checkNum = 0; checkNum < INTER_DIR_NUM; checkNum++)
	{
		if (interFlg[checkNum])
		{
			//�����_�ɍs�����Ƃ��\�ȕ����̐�
			dirNum++;
		}
	}

	//�����_���ɐi�ޕ����𔻒肷��
	dirNum = GetRand(dirNum -1);


	for (int checkNum = 0; checkNum < INTER_DIR_NUM; checkNum++)
	{
		if (interFlg[checkNum])
		{
			//�i�߂�����̐������烉���_���ɏo�������l�ƍ��v������̂������āA���̕������ԃN���X�ɓn��
			if (trueNum == dirNum)
			{
				VECTOR interPos = MV1GetFramePosition(frmHndl_, car->GetInterNum());
				car->SetInterInfo(checkNum,interPos);
				break;
			}
			//�����_�ɍs�����Ƃ��\�ȕ����̐�
			trueNum++;
		}
	}
}


//�����_�ɎԂ������Ă����p�x���`�F�b�N����
//�����͌����_�̃t���O���擾���Ă���z��A�߂�l�͂��̕ϐ��z�������������Y�����ԍ�
int CInter::CheckInter(bool* inter,int carNum)
{
	CEnemy* car = CEnemyManager::GetInstance()->GetEnemy(carNum);
	
	//�Ԃ茌�Ƃ��ĕԂ����l�ϐ�(0=��A1=���A2=�E�A3=��
	int returnNum = 0;

	////�Ԃ͊�{�I�ɒP������ɂ����i�܂��A�O����W�ƕς����p���炵���i���ł��Ȃ��̂�

	//�����łȂ��Ȃ�c����
	if(car->GetPosition().z != car->GetOldPosition().z)
	{
		//�c�����ł��ォ�炫�Ă��邩�����炫�Ă��邩
		if (0 > car->GetPosition().z - car->GetOldPosition().z){
			returnNum = FRONT;
		}
		else if (0 < car->GetPosition().z - car->GetOldPosition().z){
			returnNum = BACK;
		}
	}
	//�������`�F�b�N
	else if(car->GetPosition().x != car->GetOldPosition().x)
	{
		//�������ł��E���炫�Ă��邩�����炫�Ă��邩
		if (0 > car->GetPosition().x - car->GetOldPosition().x){
			returnNum = RIGHT;
		}
		else if (0 < car->GetPosition().x - car->GetOldPosition().x){
			returnNum = LEFT;
		}
	}
	
	//�ԃN���X�ł��K�v�ɂȂ���Ȃ̂ŁA�ԃN���X�ɓn��
	car->SetJustInter(returnNum);

	return returnNum;
}


//�����_�͈͓n��
float CInter::GetInterRad()
{
	return INTER_RADIUS;
}