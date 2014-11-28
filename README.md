how_to_create_dll
========
Visual StudioでDLLとEXEを作る時の自己流お作法のメモ。

設定の目的
========
* DLLのビルド→EXEのビルド→実行 の流れをスムーズにする。
  * ビルド時の出力ファイルをDLL,EXE共に同じディレクトリに出力
  * 依存関係を設定しておくことで、test_exeをビルドする前にtest_dllをビルドするように設定しておく。
* DLLの名前を変えておくことで、デバッグ・リリースビルドを見分けやすくする。
  * デバッグビルドとリリースビルドのDLLを混ぜると危険…
* バイナリでのライブラリ配布を容易にする。
  * includeディレクトリにヘッダを出力する。
  * libディレクトリにインポートライブラリを出力する。

ディレクトリ構成
========
<pre>
  how_to_create_dll/
    |
    +--- bin/       DLL,EXEなどの出力場所
    |
    +--- include/   test_dllのインクルードファイルを出力
    |
    +--- lib/       test_dllのインポートライブラリ(*.lib)を出力
    |
    +--- src/       ソースコード
           |
           +--- how_to_create_dll.sln  プロジェクトをまとめているソリューションファイル
           |
           +--- test_exe/              test_dllを使用するEXEのプロジェクト
           |
           +--- test_dll/              簡単なDLLを出力するプロジェクト
</pre>

プロジェクトの設定
========

全般
--------

* 出力ディレクトリ
  * $(ProjectDir)/../../bin/
* 中間ディレクトリ
  * $(ProjectDir)/../../_obj/$(ProjectName)/$(Configuration)/
* ターゲット名
  * デバッグのみ $(ProjectName)D を設定しておく。
* ビルドログファイル
  * $(ProjectDir)/../../../_obj/$(ProjectName)/$(Configuration)/$(MSBuildProjectName).log

デバッグ
--------

* 作業ディレクトリ
  * $(TargetDir)

C++
--------

* 追加のインクルードディレクトリ
  * $(ProjectDir)/../../include/

リンカー
--------

* 出力ファイル 
  * $(OutDir)$(TargetName)$(TargetExt)
* 追加のライブラリディレクトリ
  * $(ProjectDir)/../../lib/

DLLを作成するときの設定
--------
* リンカー -> 詳細設定 -> インポートライブラリ
  * $(ProjectDir)../../lib/$(TargetName).lib

* ビルドイベント -> ビルド後イベント -> コマンドライン
  * call _copy_headers.bat
  * ※ビルド成功時にヘッダファイルをincludeディレクトリへコピーする

test_dll.h, test_dll.cppのメモ
========

test_dll.h
--------

<pre>
#pragma once

// ここを定義しておくのがミソ。
// ライブラリ利用時にtest_dll.hをインクルードするとインポートライブラリをリンクするように設定
#ifdef LIB_TEST_DLL_EXPORTS
    #define LIB_TEST_DLL_API __declspec(dllexport)
#else
    #define LIB_TEST_DLL_API __declspec(dllimport)
    #ifdef _DEBUG
        #pragma comment(lib, "test_dllD.lib")
    #else
        #pragma comment(lib, "test_dll.lib")
    #endif
#endif

class LIB_TEST_DLL_API TestDllAPI
{
public:
    TestDllAPI();
    virtual ~TestDllAPI();

    void test_function(const int &val);
};
</pre>

test_dll.cpp
--------

<pre>
#include "stdafx.h"

#define LIB_TEST_DLL_EXPORTS   ←ここを定義しておくのがミソ。__declspec(dllexport)に切り替える
#include "test_dll.h"

LIB_TEST_DLL_API TestDllAPI::TestDllAPI()
{
}

LIB_TEST_DLL_API TestDllAPI::~TestDllAPI()
{
}

LIB_TEST_DLL_API void TestDllAPI::test_function(const int &val)
{
	printf("TestDllAPI::test_function() : val=%d\n", val);
}
</pre>
