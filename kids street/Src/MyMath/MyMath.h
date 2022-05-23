#ifndef __MYMATH_H__
#define __MYMATH_H__

#include "DxLib.h"

//ベクトルの初期化マクロ定義
#define ZERO_VECTOR VGet(0.0f, 0.0f, 0.0f)

class CMyMath {
public:
	

	////ベクトルや行列の計算処理をまとめたクラス////

	//２点間の距離を求める（２Ｄ）
	static float GetDistance(float x1, float y1, float x2, float y2);

	//pos1からpos2までの距離を計算する
	static float GetDistance(VECTOR pos1, VECTOR pos2);

	//変位ベクトルの作成
	static VECTOR VecCreate(VECTOR start, VECTOR end);

	//pos1からpos2方向の回転地を返す
	static VECTOR GetRot(VECTOR pos1, VECTOR pos2);

	//ベクトルの長さを求める
	static float VecLong(VECTOR vec);

	//ベクトルの加算
	static VECTOR VecAdd(VECTOR vec1, VECTOR vec2);

	//ベクトルの減算
	static VECTOR VecSub(VECTOR vec1, VECTOR vec2);

	//ベクトルの正規化
	static VECTOR VecNormalize(VECTOR vec);

	//ベクトルのスカラー倍
	static VECTOR VecScale(VECTOR vec, float scale);

	//ベクトルの内積
	static float VecDot(VECTOR vec1, VECTOR vec2);

	//ベクトルの外積（２Ｄ）
	static float VecCross2D(VECTOR vec1, VECTOR vec2);
	//ベクトルの外積（３Ｄ）
	static VECTOR VecCross(VECTOR vec1, VECTOR vec2);


	//回転値を０～２πの値にする
	static float RadianNormalize(float rad);


	//単位行列を取得する
	static MATRIX GetIdentityMatrix();

	//平行移動行列を取得する
	static MATRIX GetTranslateMatrix(VECTOR move);

	//拡縮行列を取得する
	static MATRIX GetScaleMatrix(VECTOR scale);

	//Ｘ軸回転行列を取得する
	static MATRIX GetPitchMatrix(float rad);

	//Ｙ軸回転行列を取得する
	static MATRIX GetYawMatrix(float rad);

	//Ｚ軸回転行列を取得する
	static MATRIX GetRollMatrix(float rad);

	//引数で渡された２つの行列を足し算する
	static MATRIX MatAdd(MATRIX mat1, MATRIX mat2);

	//引数で渡された２つの行列を引き算する
	static MATRIX MatSub(MATRIX mat1, MATRIX mat2);

	//引数で渡された行列をスカラー倍する
	static MATRIX MatScale(MATRIX mat, float scale);

	//引数で渡された２つの行列の掛け算を行う
	static MATRIX MatMult(MATRIX mat1, MATRIX mat2);

	//行列×ベクトルを行う（変換計算）
	static VECTOR MatTransform(MATRIX mat, VECTOR vec);

	//行列転置を行う
	static MATRIX MatTranspose(MATRIX mat);

	//ポリゴンの法線ベクトル
	static VECTOR GetPolygonNormalVec(VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);

	//面の方程式から床の高さを計算
	static float GetTriangleHeightXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	// 平面上の壁の高さを計算
	static float GetTriangleHeightXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);
	// 平面上の壁の高さを計算
	static float GetTriangleHeightYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC);


	static float Abs(float val);

	//originの+-rad分の範囲内にtargetがあるならtrueを返す計算(VECTOR)
	static bool RadiusCheck(VECTOR origin, float rad, VECTOR target);

	//originの+-rad分の範囲内にtargetがあるならtrueを返す計算(float)
	static bool RadiusCheck(float origin, float rad, float target);

};

#endif
