// ---------- インクルードガード部 ----------
#ifndef _____SCENE_BASE_H_____
#define _____SCENE_BASE_H_____

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//	クラス：SceneBase
//	概要　：各シーンの基底クラス。
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

	void SetIsLoadScene(bool bIsLoad);
	bool GetIsLoadScene();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() {};
	virtual void UnInit() = 0;
private:
	bool m_bIsLoadScene;
};

#endif // !_____SCENE_BASE_H_____