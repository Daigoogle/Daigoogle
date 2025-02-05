//	�t�@�C����	�FClass.hxx
//	�@�T�@�v�@	�F
//	��@���@��	�F 
//	 �쐬����	�F
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= �C���N���[�h�K�[�h�� =-=-=
#ifndef _____Class_HXX_____
#define _____Class_HXX_____

// =-=-= �C���N���[�h�� =-=-=
#include "DebugRestriction.hxx"
#include "Object.hxx"
#include "Component.hxx"

class SceneBase : public Object
{
	friend class SceneManager;
public:
	SceneBase();
	virtual ~SceneBase();

	void ReadFile(const std::string& path);

	Location& GetLocation() { return *this; }

	template<typename TypeComp, typename = std::enable_if_t<std::is_base_of_v<Component, TypeComp>>>
	TypeComp* AddSceneComponent()
	{
		std::unique_ptr<TypeComp> pComp(New(TypeComp));
		pComp->m_pBaseObject = this;
		m_SceneComponent = std::move(pComp);
		return m_SceneComponent.get();
	}

	inline virtual void Update() override{}

private:
	void Loading(SceneBase** ppInstantChange);

	bool m_LoadComplete;
	std::unique_ptr<Component> m_SceneComponent;
};

#endif // !_____Class_HXX_____