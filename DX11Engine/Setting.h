#pragma once
#define SCREEN_WIDTH	(960)			// ウインドウの幅
#define SCREEN_HEIGHT	(540)			// ウインドウの高さ

//目指すFPS。FPSは必ずこれよりも小さくなる
#define DEFAULT_FPS (60.0)

//ログファイルを作るかどうか
#define IS_CREATE_FILE (true)

//入力ログファイルを読み込むかどうか
#define IS_READ_INPUT_FILE (false)

//キャプションを表示するか否か
#define IS_VIEW_CAPTION (true)

//画面の中心(横)
#define SCREEN_CENTER_X (SCREEN_WIDTH/2)
//画面の中心(縦)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT/2)

// ウインドウクラスの名前
#define CLASS_NAME  "GameWindow"       
// ウィンドウ上部のメッセージ
#define WINDOW_NAME "Game" 

#define END_MESSAGE "本当に終了しますか？"
#define END_WINDOW_CAPTION "終了確認"