#include <DxLib.h>
#include "Collision.h"
#include "../MyMath/MyMath.h"

//直方体の当たり判定
// _V1				… 対象AのX,Y,Z座標（モデルの中心座標）
// _W1, _H1, _D1	… 対象AのW,H,D（横幅、高さ、奥行き）
// _V2				… 対象BのX,Y,Z座標（モデルの中心座標）
// _W2, _H2, _D2	… 対象BのW,H,D（横幅、高さ、奥行き）
bool CCollision::IsHitRect(VECTOR v1, float w1, float h1, float d1, VECTOR v2, float w2, float h2, float d2)
{
	if (v1.x + w1 / 2 > v2.x - w2 / 2 &&
		v1.x - w1 / 2 < v2.x + w2 / 2 &&
		v1.y - h1 / 2 < v2.y + h2 / 2 &&
		v1.y + h1 / 2 > v2.y - h2 / 2 &&
		v1.z - d1 / 2 < v2.z + d2 / 2 &&
		v1.z + d1 / 2 > v2.z - d2 / 2)
	{
		return true;
	}

	return false;
}

//球の当たり判定
bool CCollision::IsHitSphere(VECTOR v1, float r1, VECTOR v2, float r2)
{
	if ((r1 + r2) * (r1 + r2) > (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z))
		return true;

	return false;
}

//XY
bool CCollision::IsHitTriangleXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	// 三角形の辺に沿ったベクトル
	VECTOR vecAB = CMyMath::VecCreate(vertexA, vertexB); vecAB.z = 0.0f;
	VECTOR vecBC = CMyMath::VecCreate(vertexB, vertexC); vecBC.z = 0.0f;
	VECTOR vecCA = CMyMath::VecCreate(vertexC, vertexA); vecCA.z = 0.0f;

	//各頂点から対象までのベクトル
	VECTOR vecAP = CMyMath::VecCreate(vertexA, point); vecAP.z = 0.0f;
	VECTOR vecBP = CMyMath::VecCreate(vertexB, point); vecBP.z = 0.0f;
	VECTOR vecCP = CMyMath::VecCreate(vertexC, point); vecCP.z = 0.0f;


	//対応するベクトルどうしで外積を計算する
	VECTOR vecABAP = CMyMath::VecCross(vecAB, vecAP);
	VECTOR vecBCBP = CMyMath::VecCross(vecBC, vecBP);
	VECTOR vecCACP = CMyMath::VecCross(vecCA, vecCP);

	//各外積のZ成分が0以下であれば当たっている
	if (vecABAP.z >= 0 && vecBCBP.z >= 0 && vecCACP.z >= 0)
	{
		return true;
	}

	//反対側も図る
	if (vecABAP.z <= 0 && vecBCBP.z <= 0 && vecCACP.z <= 0)
	{
		return true;
	}

	return false;

}


//XZ
bool CCollision::IsHitTriangleXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	// 三角形の辺に沿ったベクトル
	VECTOR vecAB = CMyMath::VecCreate(vertexA, vertexB); vecAB.y = 0.0f;
	VECTOR vecBC = CMyMath::VecCreate(vertexB, vertexC); vecBC.y = 0.0f;
	VECTOR vecCA = CMyMath::VecCreate(vertexC, vertexA); vecCA.y = 0.0f;

	//各頂点から対象までのベクトル
	VECTOR vecAP = CMyMath::VecCreate(vertexA, point); vecAP.y = 0.0f;
	VECTOR vecBP = CMyMath::VecCreate(vertexB, point); vecBP.y = 0.0f;
	VECTOR vecCP = CMyMath::VecCreate(vertexC, point); vecCP.y = 0.0f;


	//対応するベクトルどうしで外積を計算する
	VECTOR vecABAP = CMyMath::VecCross(vecAB, vecAP);
	VECTOR vecBCBP = CMyMath::VecCross(vecBC, vecBP);
	VECTOR vecCACP = CMyMath::VecCross(vecCA, vecCP);

	//各外積のZ成分が0以下であれば当たっている
	if (vecABAP.y >= 0 && vecBCBP.y >= 0 && vecCACP.y >= 0)
	{
		return true;
	}

	//反対側も図る
	if (vecABAP.y <= 0 && vecBCBP.y <= 0 && vecCACP.y <= 0)
	{
		return true;
	}

	return false;

}

//YZ
bool CCollision::IsHitTriangleYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	// 三角形の辺に沿ったベクトル
	VECTOR vecAB = CMyMath::VecCreate(vertexA, vertexB); vecAB.x = 0.0f;
	VECTOR vecBC = CMyMath::VecCreate(vertexB, vertexC); vecBC.x = 0.0f;
	VECTOR vecCA = CMyMath::VecCreate(vertexC, vertexA); vecCA.x = 0.0f;

	// 各頂点から対象までのベクトル
	VECTOR vecAP = CMyMath::VecCreate(vertexA, point); vecAP.x = 0.0f;
	VECTOR vecBP = CMyMath::VecCreate(vertexB, point); vecBP.x = 0.0f;
	VECTOR vecCP = CMyMath::VecCreate(vertexC, point); vecCP.x = 0.0f;

	// 対応するベクトルどうして外積を計算する
	VECTOR vecABAP = CMyMath::VecCross(vecAB, vecAP);
	VECTOR vecBCBP = CMyMath::VecCross(vecBC, vecBP);
	VECTOR vecCACP = CMyMath::VecCross(vecCA, vecCP);

	// 各外積のX成分が0以下であれば当たっている
	if (vecABAP.x >= 0 && vecBCBP.x >= 0 && vecCACP.x >= 0) {
		return true;
	}
	// 各外積のX成分が0以下であれば当たっている
	if (vecABAP.x <= 0 && vecBCBP.x <= 0 && vecCACP.x <= 0) {
		return true;
	}

	return false;
}