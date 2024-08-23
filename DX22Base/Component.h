#ifndef _____COMPONENT_H_____
#define _____COMPONENT_H_____

class BaseObject;
class BaseObjectInstance;

class Component
{
public:
	Component():m_pSelfInstance(nullptr){}
	virtual ~Component()	{}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void UnInit() = 0;

	BaseObject GetBaseObject();
	void SetBaseObject(BaseObjectInstance* pInstance);

protected:

private:
	BaseObjectInstance* m_pSelfInstance;
};

#endif // !_____COMPONENT_H_____