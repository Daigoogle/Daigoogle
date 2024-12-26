#include "AnyUpdateComp.hxx"

AnyUpdateComp::AnyUpdateComp()
{

}

AnyUpdateComp::~AnyUpdateComp()
{

}

bool AnyUpdateComp::Init()
{
	return true;
}

void AnyUpdateComp::Update()
{
	m_Func();
}

void AnyUpdateComp::SetFunc(std::function<void()> func)
{
	m_Func = func;
}