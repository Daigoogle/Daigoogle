#include "NumSprite2D.h"
#include "BaseObjectManager.h"
#include "PutLog.h"
#include "SceneManager.h"

static const int MAX_DIGIT = 10;

NumSprite2D::NumSprite2D()
	: m_num(nullptr)
	, m_Digit(0)
	, m_Scene(nullptr)
	, m_Color({1.0f,1.0f,1.0f,1.0f})
{
	m_num = new BaseObject[MAX_DIGIT];
	m_Sprite = new Sprite2DComponent * [MAX_DIGIT];

	m_Scene = Singleton<SceneManager>::GetInstance().GetScene();

	if (m_Scene == nullptr)
		Error("Not Setting : m_Scene\n to NumSprite2D");

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		m_num[i] = ObjectManager::Make(m_Scene);
		GetBaseObject().AddChild(m_num[i]);
		m_Sprite[i] = m_num[i].AddComponent<Sprite2DComponent>();
		Transform* transform = m_num[i].GetComponent<Transform>();
		m_Sprite[i]->LoadTexture("Assets/Texture/Num.png");
		m_Sprite[i]->SetUVScale({ 0.1f,1.0f });
		m_Sprite[i]->SetColor({ 0.0f,0.0f,0.0f,0.0f });
		transform->SetLocalPosition({ i * -0.04f,0.0f,0.0f });
		transform->SetLocalScale({ 0.07f,0.17f,0.0f });
	}
}
NumSprite2D::~NumSprite2D()
{

}

void NumSprite2D::Init()
{
	//m_num = new BaseObject[MAX_DIGIT];
	//m_Sprite = new Sprite2DComponent*[MAX_DIGIT];
	////fVec3 DefaltPos = {+330.0f,-200.0f,+10.0f};

	//m_Scene = Singleton<SceneManager>::GetInstance().GetScene();

	//if (m_Scene == nullptr)
	//	Error("Not Setting : m_Scene\n to NumSprite2D");
	Transform* tf = GetBaseObject().GetComponent<Transform>();

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		fVec3 pos = tf->GetWorldPosition();
		pos.x -= i * 0.08f;
		m_num[i].GetComponent<Transform>()->SetLocalPosition(pos);
	}
}
void NumSprite2D::Update()
{

}
void NumSprite2D::UnInit()
{

}

void NumSprite2D::SetScene(SceneBase* pScene)
{
	m_Scene = pScene;
}

void NumSprite2D::SetNum(unsigned int Num)
{
	for (int i = 0; i < MAX_DIGIT; i++)
		m_Sprite[i]->SetColor({1.0f,1.0f,1.0f,0.0f});//“§–¾II

	int cnt = 0, su = Num;
	while (su > 0)
	{
		su /= 10;
		cnt++;
	}
	m_Digit = cnt;
	for (int i = 0; cnt > 0; i++, cnt--)
	{
		int j, Jou = 1;
		for (j = 1; j < cnt; j++, Jou *= 10);
		su = Num / Jou;
		m_Sprite[cnt]->SetUVOffset({su * 0.1f,0.0f});
		m_Sprite[cnt]->SetColor(m_Color);
		Num %= Jou;
	}
}


void NumSprite2D::SetColor(fVec4 color)
{
	m_Color = color;
}