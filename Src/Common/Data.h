#pragma once



class Data
{
public:

	enum class LEVEL
	{
		LEVEL1,
		LEVEL2,
		LEVEL3,
		LEVEL4,
		LEVEL5,
		LEVEL6,
		MAX,
		MARASON,
		VS
	};
	
	//カメラのサイズ
	static constexpr int CAMERA_WIDTH = 150;
	static constexpr int CAMERA_HEIGHT = 150;

	//デフォルトデータ
	static constexpr int DEFAULT_DATA = 2;

	//メンバー関数
	Data(void);
	~Data(void);

	//インスタンスの生成
	//シングルトン化
	static void CreateInstance(void);
	static Data& GetInstance(void);

	void SetDeta(int pos);
	int GetDeta(void);

	//ステージデータを管理する
	void ChangeLevelData(LEVEL Data);
	LEVEL GetStageData(void);

	//マラソンの記録を管理する
	int GetMarasonData();
	void SetMarasonData(int value);

private:

	//マラソン記録
	int marasonData_;

	//変数
	int Data_;

	LEVEL type_;

	//シングルトン化
	static Data* instance_;

	//メンバー関数
	//---------------------------------------
	//コピーコンストラスタ
	Data(const Data& ins);

	void Destory(void);
};

