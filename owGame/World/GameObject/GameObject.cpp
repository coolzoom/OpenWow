#include "stdafx.h"

// General
#include "GameObject.h"


GameObject::GameObject(const std::shared_ptr<M2>& M2Object)
	: CM2_Base_Instance(M2Object)
{
}

GameObject::~GameObject()
{
}