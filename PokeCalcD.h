
// PokeCalcD.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CPokeCalcDApp:
// このクラスの実装については、PokeCalcD.cpp を参照してください
//

class CPokeCalcDApp : public CWinApp
{
public:
	CPokeCalcDApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CPokeCalcDApp theApp;
