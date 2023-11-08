#include <Novice.h>

const char kWindowTitle[] = "LC1B_26_ミヤザキ_ヤマト";

struct Vector2 {
	float x;
	float y;
};
struct Box {
	Vector2 pos;
	Vector2 velocity;
	Vector2 acseraration;
	float radius;
};
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Box player{
		{50,300},
		{5,5},
		{0,0},
		32
	};
	int scene = 0;
	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		switch (scene)
		{
		case 0:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				player.acseraration = player.velocity;
			}
			player.pos.x += player.acseraration.x;
			if (player.pos.x >= 1230) {
				player.acseraration = { 0,0 };
			}
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				scene = 1;
			}
			break;
		case 1:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				player.acseraration.x += 0.1f;
			}
			if (player.acseraration.x != 0) {
				player.acseraration.x += 0.1f;
			}
			player.pos.x += player.acseraration.x;
			if (player.pos.x >= 1230) {
				player.acseraration = { 0,0 };
			}
			if (keys[DIK_RETURN] && !preKeys[DIK_RETURN]) {
				scene = 0;
			}
			break;
		}
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawEllipse((int)player.pos.x, (int)player.pos.y, (int)player.radius, (int)player.radius, 0.0f, 0xffffffff, kFillModeSolid);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
