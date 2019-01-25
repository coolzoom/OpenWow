#include "stdafx.h"

// General
#include "ADT_MDX_Instance.h"

// Additional

ADT_MDX_Instance::ADT_MDX_Instance(std::shared_ptr<M2> _mdxObject, const ADT_MDXDef& _placementInfo) :
	CM2_Base_Instance(_mdxObject)
{
	m_UniqueId = _placementInfo.uniqueId;

	// Scene node params
	{
		SetTranslate(_placementInfo.position);
		vec3 rotate = glm::radians(_placementInfo.rotation);
		rotate.x = -rotate.x;
		rotate.y = rotate.y - glm::half_pi<float>();
		SetRotation(vec3(rotate.z, rotate.y, rotate.x));
		SetScale(vec3(static_cast<float>(_placementInfo.scale) / 1024.0f));
		UpdateLocalTransform();
	}

	InitAnimator();
}

ADT_MDX_Instance::~ADT_MDX_Instance()
{
	//Log::Info("ADT_MDX Deleted");
}


//
// SceneNode
//
bool ADT_MDX_Instance::Accept(IVisitor& visitor)
{
	const BasePass& visitorAsBasePass = reinterpret_cast<BasePass&>(visitor);
	const Camera& camera = *(visitorAsBasePass.GetRenderEventArgs().Camera);
	
	const M2_Pass* passAsM2Pass = dynamic_cast<const M2_Pass*>(&visitor);
	if (passAsM2Pass)
	{
		if (m_AlreadyDraw.find(m_UniqueId) != m_AlreadyDraw.end())
		{
			return false;
		}
	}

	/*float distToCamera2D = (camera.GetTranslation() - GetBounds().getCenter()).length() - GetBounds().getRadius();
	if (distToCamera2D > m_QualitySettings.ADT_MCNK_Distance)
	{
		return;
	}*/

	// SceneNode
	if (CM2_Base_Instance::Accept(visitor))
	{
		if (passAsM2Pass)
		{
			m_AlreadyDraw.insert(m_UniqueId);
		}
		return true;
	}

	return false;
}

//
std::set<uint32> ADT_MDX_Instance::m_AlreadyDraw;
void ADT_MDX_Instance::reset()
{
	m_AlreadyDraw.clear();
}