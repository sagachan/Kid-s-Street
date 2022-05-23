#include "MyMath.h"
#include <math.h>



// 点P(x1, y1)から点Q(x2, y2)までの距離を返す
float CMyMath::GetDistance(float x1, float y1, float x2, float y2)
{
	// 点Pから点Qまでの直線を斜辺とする直角三角形を作り、
	// ピタゴラスの定理から斜辺の長さを計算する。
	// ①まずは底辺の長さを計算する
	float a = x2 - x1;

	// ②高さを計算する
	float b = y2 - y1;

	// ③斜辺の2乗の値を計算する
	float double_c = a * a + b * b;

	// ④2乗の値なので平方根を計算して長さとする
	// 　平方根は<math.h>のsqrtf関数で取得できる
	return sqrtf(double_c);
}


//pos1からpos2までの距離を計算する
float CMyMath::GetDistance(VECTOR pos1, VECTOR pos2)
{
	return VecLong(VecCreate(pos1, pos2));
}


//変位ベクトルの作成
VECTOR CMyMath::VecCreate(VECTOR start, VECTOR end)
{
	VECTOR result;

	//各成分で「（終点）ー（始点）」をする
	result.x = end.x - start.x;
	result.y = end.y - start.y;
	result.z = end.z - start.z;

	return result;
}

//pos1からpos2までの向きを返す
VECTOR CMyMath::GetRot(VECTOR pos1, VECTOR pos2)
{
	VECTOR result;

	result = VecCreate(pos1, pos2);
	result = VecNormalize(result);

	return result;

}


//ベクトルの長さを求める
float CMyMath::VecLong(VECTOR vec)
{
	float vec_long = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

	return vec_long;
}


// ベクトルの足し算
VECTOR CMyMath::VecAdd(VECTOR vec1, VECTOR vec2)
{
	VECTOR result;

	// ①各成分を足し算する
	result.x = vec1.x + vec2.x;
	result.y = vec1.y + vec2.y;
	result.z = vec1.z + vec2.z;

	return result;
}


//ベクトルの減算（vec1からvec2を引く)
VECTOR CMyMath::VecSub(VECTOR vec1, VECTOR vec2)
{
	VECTOR result;

	//各成分を引き算する
	result.x = vec1.x - vec2.x;
	result.y = vec1.y - vec2.y;
	result.z = vec1.z - vec2.z;

	return result;
}


//ベクトルの正規化
VECTOR CMyMath::VecNormalize(VECTOR vec)
{
	VECTOR result;
	float vec_long = VecLong(vec);	//ベクトルの長さ

	//各成分の長さで割り正規化する
	result.x = vec.x / vec_long;
	result.y = vec.y / vec_long;
	result.z = vec.z / vec_long;

	return result;
}


//ベクトルのスカラー倍
VECTOR CMyMath::VecScale(VECTOR vec, float scale)
{
	VECTOR result;

	//各成分をスカラー倍する
	result.x = vec.x * scale;
	result.y = vec.y * scale;
	result.z = vec.z * scale;

	return result;
}


//ベクトルの内積
float CMyMath::VecDot(VECTOR vec1, VECTOR vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

//ベクトルの外積（２Ｄ）
float CMyMath::VecCross2D(VECTOR vec1, VECTOR vec2)
{
	return vec1.x * vec2.y - vec1.y * vec2.x;
}

//ベクトルの外積（３Ｄ）
VECTOR CMyMath::VecCross(VECTOR vec1, VECTOR vec2)
{
	VECTOR result;

	result.x = vec1.y * vec2.z - vec1.z * vec2.y;
	result.y = vec1.z * vec2.x - vec1.x * vec2.z;
	result.z = vec1.x * vec2.y - vec1.y * vec2.x;

	return result;
}


//回転値を０～２πの値にする
float CMyMath::RadianNormalize(float rad)
{
	float result = rad;
	if (result < 0.0f)
	{
		while (result < 0.0f)
		{
			result += DX_TWO_PI_F;
		}
	}
	else if (result >= DX_TWO_PI_F)
	{
		while (result > DX_TWO_PI_F)
		{
			result -= DX_TWO_PI_F;
		}
	}

	return result;
}


//単位行列を取得する
MATRIX CMyMath::GetIdentityMatrix()
{
	MATRIX result = { 0 };

	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	return result;
}


//平行移動行列を取得する
MATRIX CMyMath::GetTranslateMatrix(VECTOR move)
{
	MATRIX result = { 0 };

	result = GetIdentityMatrix();
	result.m[0][3] = move.x;
	result.m[1][3] = move.y;
	result.m[2][3] = move.z;

	return result;
}


//拡縮行列を取得する
MATRIX CMyMath::GetScaleMatrix(VECTOR scale)
{
	MATRIX result = { 0 };

	result = GetIdentityMatrix();
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;

	return result;
}


//Ｘ軸回転行列を取得する
MATRIX CMyMath::GetPitchMatrix(float rad)
{
	MATRIX result = { 0 };

	result = GetIdentityMatrix();
	result.m[1][1] = cosf(rad);
	result.m[1][2] = -sinf(rad);
	result.m[2][1] = sinf(rad);
	result.m[2][2] = cosf(rad);

	return result;
}


//Ｙ軸回転行列を取得する
MATRIX CMyMath::GetYawMatrix(float rad)
{
	MATRIX result = { 0 };

	result = GetIdentityMatrix();
	result.m[0][0] = cosf(rad);
	result.m[0][2] = sinf(rad);
	result.m[2][0] = -sinf(rad);
	result.m[2][2] = cosf(rad);

	return result;
}


//Ｚ軸回転行列を取得する
MATRIX CMyMath::GetRollMatrix(float rad)
{
	MATRIX result = { 0 };

	result = GetIdentityMatrix();
	result.m[0][0] = cosf(rad);
	result.m[0][1] = -sinf(rad);
	result.m[1][0] = sinf(rad);
	result.m[1][1] = cosf(rad);

	return result;
}


//引数で渡された２つの行列を足し算する
MATRIX CMyMath::MatAdd(MATRIX mat1, MATRIX mat2)
{
	MATRIX result = { 0 };

	//対応する要素同士で足し算
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = mat1.m[i][j] + mat2.m[i][j];
		}
	}

	return result;
}

//引数で渡された２つの行列を引き算する
MATRIX CMyMath::MatSub(MATRIX mat1, MATRIX mat2)
{
	MATRIX result = { 0 };

	//対応する要素同士で引き算
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = mat1.m[i][j] - mat2.m[i][j];
		}
	}

	return result;
}


//引数で渡された行列をスカラー倍する
MATRIX CMyMath::MatScale(MATRIX mat, float scale)
{
	MATRIX result = { 0 };

	//各要素を、スカラー値で掛け算
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = mat.m[i][j] * scale;
		}
	}

	return result;
}


//引数で渡された２つの行列の掛け算を行う
MATRIX CMyMath::MatMult(MATRIX mat1, MATRIX mat2)
{
	MATRIX result = { 0 };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				result.m[i][j] += (mat1.m[i][k] * mat2.m[k][j]);
			}
		}
	}

	return result;
}


//行列×ベクトルを行う（変換計算）
VECTOR CMyMath::MatTransform(MATRIX mat, VECTOR vec)
{
	float work[4] = { 0 };
	float result_buf[4] = { 0 };
	VECTOR result_vec;
	work[0] = vec.x;
	work[1] = vec.y;
	work[2] = vec.z;
	work[3] = 1;
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			result_buf[i] += (mat.m[i][k] * work[k]);
		}
	}

	result_vec.x = result_buf[0];
	result_vec.y = result_buf[1];
	result_vec.z = result_buf[2];

	return result_vec;
}


//行列転置を行う
MATRIX CMyMath::MatTranspose(MATRIX mat)
{
	MATRIX result = { 0 };

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[j][i] = mat.m[i][j];
		}
	}

	return result;
}

//ポリゴンの法線ベクトル
VECTOR CMyMath::GetPolygonNormalVec(VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	VECTOR vecAB = VecCreate(vertexA, vertexB);
	VECTOR vecAC = VecCreate(vertexA, vertexC);
	VECTOR vecABAC = VecCross(vecAB, vecAC);
	return VecNormalize(vecABAC);
}

float CMyMath::GetTriangleHeightXZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	//辺に沿ったベクトルABとACを計算
	VECTOR vecAB = VecCreate(vertexA, vertexB);
	VECTOR vecAC = VecCreate(vertexA, vertexC);

	//面法線を計算
	VECTOR vecNorm = VecCross(vecAB, vecAC);
	vecNorm = VecNormalize(vecNorm);

	//平面の方程式から高さ（Y座標を計算）
	float y = (-vecNorm.x * (point.x - vertexA.x) - vecNorm.z * (point.z - vertexA.z) + vecNorm.y * vertexA.y) / vecNorm.y;



	//VECTOR vecNorm = GetPolygonNormalVec(vertexA, vertexB, vertexC);

	//float y = (-vecNorm.x * (point.x - vertexA.x) - vecNorm.z * (point.z - vertexA.z) + vecNorm.y * vertexA.y) / vecNorm.y;

	return y;
}

// 平面上の壁の高さを算出
float CMyMath::GetTriangleHeightXY(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	//辺に沿ったベクトルABとACを計算
	VECTOR vecAB = VecCreate(vertexA, vertexB);
	VECTOR vecAC = VecCreate(vertexA, vertexC);

	//面法線を計算
	VECTOR vecNorm = VecCross(vecAB, vecAC);
	vecNorm = VecNormalize(vecNorm);

	//平面の方程式から高さ（Z座標を計算）
	float z = (-vecNorm.x * (point.x - vertexA.x) - vecNorm.y * (point.y - vertexA.y) + vecNorm.z * vertexA.z) / vecNorm.z;

	return z;
}

// 平面上の壁の高さを計算
float CMyMath::GetTriangleHeightYZ(VECTOR point, VECTOR vertexA, VECTOR vertexB, VECTOR vertexC)
{
	// 辺に沿ったベクトルABとACを計算
	VECTOR vecAB = VecCreate(vertexA, vertexB);
	VECTOR vecAC = VecCreate(vertexA, vertexC);
	// 面法線を計算
	VECTOR vecNorm = VecCross(vecAB, vecAC);
	vecNorm = VecNormalize(vecNorm);
	// 平面の方程式から高さ（Y座標を計算）
	float x = (-vecNorm.y * (point.y - vertexA.y) - vecNorm.z * (point.z - vertexA.z) + vecNorm.x * vertexA.x) / vecNorm.x;

	return x;
}


float CMyMath::Abs(float val)
{
	if (val < 0.0f)
	{
		return -val;
	}

	return val;
}

bool CMyMath::RadiusCheck(VECTOR origin, float rad, VECTOR target)
{
	if (RadiusCheck(origin.x, rad, target.x)&&
		RadiusCheck(origin.y, rad, target.y)&&
		RadiusCheck(origin.z, rad, target.z))
	{
		return true;
	}

	return false;
}

bool CMyMath::RadiusCheck(float origin, float rad, float target)
{
	if (origin + rad > target &&
		origin - rad < target)
	{
		return true;
	}

	return false;
}

bool CMyMath::VectorEqual(VECTOR pos1, VECTOR pos2)
{
	//ベクター型のイコール計算
	if (pos1.x == pos2.x&&pos1.y == pos2.y &&pos1.z == pos2.z)
		return true;

	return false;
}