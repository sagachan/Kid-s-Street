//Inter.cpp
//交差点クラス

#include "Inter.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../Player/PlayerManager.h"
#include "../../Enemy/EnemyManager.h"

//フィールド関連
namespace
{
	const VECTOR	FIELD_POS = VGet(-20.0f, -1.0f, 0.0f);				//フィールドの座標
	const int		FIELD_D = 36;									//フィールドの奥行
	const float		INTER_RADIUS = 50.0f;							//交差点として認めている広さ
	
}

//コンストラクタ
CInter::CInter()
{
	Init();
}

//デストラクタ
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
	//交差点の数だけ交差点情報構造体を持つ
	//trueの方向は進むことが可能
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

	//データをコピー
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
	
	//マップの座標
	MV1SetPosition(frmHndl_, FIELD_POS);
}

void CInter::Delete()
{

}


void CInter::Fin()
{
	//if (m_handle[0] != 0)
	//{
	//	//Deleteを呼んでおく
	//	Delete();
	//}
}


void CInter::InterManager()
{
	CEnemyManager* enemyManager = CEnemyManager::GetInstance();		 
	
	int interMaxNum = MV1GetFrameNum(frmHndl_),trueNum = 0;
	bool interFlg = true;
	VECTOR Check[INTER_BONE_MAX_NUM] = {0};

	//車の数の分だけ交差点情報を確認する
	for (int carNum = 0; carNum < APPEAR_CAR_NUM; carNum++)
	{
		CEnemy* car = enemyManager->GetEnemy(carNum);

		trueNum = 0;

		//交差点情報を順にチェックしていく
		for (int interNum = 0; interNum < interMaxNum; interNum++)
		{

			//その車が交差点処理を開始していないなら
			if (!car->GetInterFlg())
			{
				//交差点番号が奇数の時にしか判定しなくていいので、奇数の時のみ通るようにする
				if (interNum % INTER_BW)
				{

					//今参照されている番号の車の位置情報を引数として関数を呼ぶ
					CheckComeInter(car->GetPosition(), interNum,trueNum, carNum);
					trueNum++;
				}
			}
		}
	}
	
	//交差点情報を順にチェックしていく
	for (int interNum = 0; interNum < interMaxNum; interNum++)
	{
		Check[interNum] = MV1GetFramePosition(frmHndl_, interNum);
	}

	//車の数の分だけ交差点情報を確認する
	for (int carNum = 0; carNum < APPEAR_CAR_NUM; carNum++)
	{
		CEnemy* car = enemyManager->GetEnemy(carNum);

		if (car->GetInterFlg())
		{
			//交差点を出てるならinterFlgを折る
			CheckOutInter(car->GetPosition(), car->GetInterNum(), carNum);
		}
	}
}



//車が交差点に入っているかどうかを確認する、もし入っているならdirInfoの使用フラグを立てる。
//この処理は使用フラグが立っているときは通らない
void CInter::CheckComeInter(VECTOR carPos,int frmNum,int interNum,int carNum)
{
	CEnemy* car = CEnemyManager::GetInstance()->GetEnemy(carNum);

	VECTOR frmPos = MV1GetFramePosition(frmHndl_, frmNum);

	//範囲計算を使って交差点に入っているかどうかを判定する、xとzが両方範囲内にある場合に限り、
	if (CMyMath::RadiusCheck(carPos.x, INTER_RADIUS, frmPos.x)&&
		CMyMath::RadiusCheck(carPos.z, INTER_RADIUS, frmPos.z))
	{
		//交差点の処理を開始するフラグをtrueにして、交差点処理に必要な交差点番号を対象の車クラスに渡す
		car->SetInterFlg(true);
		car->SetInterNum(frmNum);

		//車の進む先を判定する
		JudgeInter(carPos, interNum, carNum);
	}
}


void CInter::CheckOutInter(VECTOR carPos, int interNum, int carNum)
{
	CRoad* road = CFieldManager::GetInstance()->GetRoad();
	CEnemy* car = CEnemyManager::GetInstance()->GetEnemy(carNum);

	VECTOR frmPos = MV1GetFramePosition(frmHndl_, interNum);

	//範囲計算を使って交差点に入っているかどうかを判定する、xとzが両方範囲内にある場合に限り、
	if (CMyMath::RadiusCheck(carPos.x, INTER_RADIUS, frmPos.x) == false ||
		CMyMath::RadiusCheck(carPos.z, INTER_RADIUS, frmPos.z) == false)
	{
		//交差点の処理を開始するフラグをfalseにする
		car->SetInterFlg(false);
		car->SetEndInter(false);
	}
}

//車の進む先を判定する
void CInter::JudgeInter(VECTOR carPos,int interNum, int carNum)
{
	//交差点処理に使うランダムに決めた方向番号を格納する変数(dir)と、ランダムに決めた変数番号を使って行く方向を判定するために使う変数(true)
	int dirNum = 0,trueNum = 0;
	//交差点状況を表した構造体の格納用
	bool interFlg[INTER_DIR_NUM];

	CRoad* road = CFieldManager::GetInstance()->GetRoad();
	CEnemy* car = CEnemyManager::GetInstance()->GetEnemy(carNum);


	//構造体としてわかりやすくしていたが、この処理で使うには扱いにくいので変数配列に変える
	interFlg[FRONT] = interInfo_[interNum].front;
	interFlg[BACK] = interInfo_[interNum].back;
	interFlg[RIGHT] = interInfo_[interNum].right;
	interFlg[LEFT] = interInfo_[interNum].left;

	
	//交差点に車が入った方向を確認してその方向にフラグを折ることで同じ道に戻らないようにする
	interFlg[CheckInter(interFlg,carNum)] = false;

	for (int checkNum = 0; checkNum < INTER_DIR_NUM; checkNum++)
	{
		if (interFlg[checkNum])
		{
			//交差点に行くことが可能な方向の数
			dirNum++;
		}
	}

	//ランダムに進む方向を判定する
	dirNum = GetRand(dirNum -1);


	for (int checkNum = 0; checkNum < INTER_DIR_NUM; checkNum++)
	{
		if (interFlg[checkNum])
		{
			//進める方向の数内からランダムに出した数値と合致するものを見つけて、その方向を車クラスに渡す
			if (trueNum == dirNum)
			{
				VECTOR interPos = MV1GetFramePosition(frmHndl_, car->GetInterNum());
				car->SetInterInfo(checkNum,interPos);
				break;
			}
			//交差点に行くことが可能な方向の数
			trueNum++;
		}
	}
}


//交差点に車が入ってきた角度をチェックする
//引数は交差点のフラグを取得している配列、戻り値はその変数配列を書き換える添え字番号
int CInter::CheckInter(bool* inter,int carNum)
{
	CEnemy* car = CEnemyManager::GetInstance()->GetEnemy(carNum);
	
	//返り血として返す数値変数(0=上、1=下、2=右、3=左
	int returnNum = 0;

	////車は基本的に単一方向にしか進まず、前回座標と変わる方角からしか進入できないので

	//そうでないなら縦方向
	if(car->GetPosition().z != car->GetOldPosition().z)
	{
		//縦方向でも上からきているか下からきているか
		if (0 > car->GetPosition().z - car->GetOldPosition().z){
			returnNum = FRONT;
		}
		else if (0 < car->GetPosition().z - car->GetOldPosition().z){
			returnNum = BACK;
		}
	}
	//横方向チェック
	else if(car->GetPosition().x != car->GetOldPosition().x)
	{
		//横方向でも右からきているか左からきているか
		if (0 > car->GetPosition().x - car->GetOldPosition().x){
			returnNum = RIGHT;
		}
		else if (0 < car->GetPosition().x - car->GetOldPosition().x){
			returnNum = LEFT;
		}
	}
	
	//車クラスでも必要になる情報なので、車クラスに渡す
	car->SetJustInter(returnNum);

	return returnNum;
}


//交差点範囲渡し
float CInter::GetInterRad()
{
	return INTER_RADIUS;
}