//Fade.h
//フェードイン・フェードアウト

#pragma once

//フェードクラス（フェードインやフェードアウトするためのクラス）
//class CFade
//{
//public:
//	//フェードタイプ
//	enum FADE_TYPE
//	{
//		FADE_IN,	//フェードイン
//		FADE_OUT,	//フェードアウト
//	};
//
//	//フェードの色の種類
//	enum FADE_COLOR_KIND
//	{
//		FADE_COLOR_BLACK,	//黒
//		FADE_COLOR_WHITE,	//白
//		FADE_COLOR_RED,		//赤
//		FADE_COLOR_GREEN,	//緑
//		FADE_COLOR_BLUE,	//青
//	};
//
//	//三原色の構造体
//	struct Color
//	{
//		int r;	//赤
//		int g;	//緑
//		int b;	//青
//	};
//
//public:
//	static void StepFade();	//フェードのステップ
//	static void DrawFade();	//フェードの描画
//
//	//フェードの開始処理（引数によって、フェードの種類と色を変えられる）
//	static void StartFade(FADE_TYPE type, FADE_COLOR_KIND color_kind);
//
//	//フェードイン・フェードアウトが開始したかどうか
//	static bool IsFadeStart() { return start_flg_; }
//
//	//フェードイン・フェードアウトが終了したかどうか
//	static bool IsFadeEnd() { return end_flg_; }
//
//private:
//	static void StepFadeIn();	//フェードインを行う関数
//	static void StepFadeOut();	//フェードアウトを行う関数
//
//
//private:
//	static int	blend_param_;	//ブレンドのパラメータ
//	static bool start_flg_;		//開始フラグ
//	static bool end_flg_;		//終了フラグ
//	static FADE_TYPE type_;		//フェードタイプ
//	static Color	color_;		//フェードの色
//};