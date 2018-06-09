#include "stdafx.h"

// General
#include "M2.h"

M2::M2(cstring name) :
	m_Loaded(false),
	m_FileName(name),
	m_UniqueName(""),
	// Loops and sequences
	m_IsAnimated(false),
	// Bones
	m_HasBones(nullptr),
	m_AnimBones(false),
	m_IsBillboard(false),
	// Vertices
	m_ContainGeom(false),
	// Colors and textures
	m_AnimTextures(false),
	// Misc
	m_HasMisc(false),
	// My types
	m_Animator(nullptr)
{
	//Log::Info("M2[%s]: Loading...", m_FileName.c_str());

	// Replace .M2 with .M2
	if (m_FileName.back() != '2')
	{
		m_FileName[m_FileName.length() - 2] = '2';
		m_FileName[m_FileName.length() - 1] = '\0';
		m_FileName.resize(m_FileName.length() - 1);
	}
}

M2::~M2()
{
	Log::Info("M2[%s]: Unloading...", m_FileName.c_str());
}

//

void M2::drawModel()
{
	if (!m_ContainGeom)
	{
		return;
	}

	_Render->TechniquesMgr()->m_Model->Bind();
	_Render->TechniquesMgr()->m_Model->SetPVW();

	for (auto it : m_Skins)
	{
		it->Draw();
	}

	_Render->TechniquesMgr()->m_Model->Unbind();
}

void M2::Update(double _time, double _dTime)
{
	if (!m_Loaded)
	{
		return;
	}


	if (m_IsAnimated)
	{
		if (m_IsBillboard)
		{
			animate(m_Animator->getSId(), m_Animator->getCurrentTime(_time), _time);
		}
		else
		{
			if (!animcalc)
			{
				animate(m_Animator->getSId(), m_Animator->getCurrentTime(_time), _time);
				animcalc = true;
			}
		}
	}
}

void M2::Render()
{
	if (!m_Loaded)
	{
		return;
	}

	// Cull bounging box
	BoundingBox aabb = m_Bounds;
	aabb.transform(_Pipeline->GetWorld());
	if (_CameraFrustum->_frustum.cullBox(aabb))
	{
		return;
	}

	if (m_IsAnimated)
	{
		// draw ribbons
		for (auto it : m_RibbonEmitters)
		{
			it.draw();
		}

#ifdef MDX_PARTICLES_ENABLE
		// draw particle systems
		for (uint32 i = 0; i < m_Header.particle_emitters.size; i++)
		{
			particleSystems[i].draw();
		}
#endif
	}

	drawModel();
}

void M2::animate(uint16 _animationIndex, uint32 _time, uint32 globalTime)
{
	if (m_HasBones)
	{
		for (uint32 i = 0; i < m_Header.bones.size; i++)
		{
			m_Bones[i].SetNeedCalculate();
		}

		for (uint32 i = 0; i < m_Header.bones.size; i++)
		{
			m_Bones[i].calcMatrix(m_Bones.data(), _animationIndex, _time, globalTime);
		}
	}

	/*for (uint32 i = 0; i < m_Header.lights.size; i++)
	{
	if (m_Lights[i].getBoneIndex() >= 0)
	{
	m_Lights[i].tpos = m_Bones[m_Lights[i].getBoneIndex()].getTransformMatrix() * m_Lights[i].pos;
	m_Lights[i].tdir = m_Bones[m_Lights[i].getBoneIndex()].getRotateMatrix() * m_Lights[i].dir;
	}
	}*/


	for (auto it : m_RibbonEmitters)
	{
		it.setup(_animationIndex, _time, globalTime);
	}

#ifdef MDX_PARTICLES_ENABLE
	for (uint32 i = 0; i < m_Header.particle_emitters.size; i++)
	{
		// random time distribution for teh win ..?
		int pt = (animtime + (int)(tmax*particleSystems[i].tofs)) % tmax;
		particleSystems[i].setup(_animationIndex, _time);
	}
#endif

	if (m_AnimTextures)
	{
		for (uint32 i = 0; i < m_Header.textureTransforms.size; i++)
		{
			m_TexturesTransform[i].calc(_animationIndex, _time, globalTime);
		}
	}

	if (m_HasMisc)
	{
		for (uint32 i = 0; i < m_Header.textureWeights.size; i++)
		{
			m_TextureWeights[i].calc(_animationIndex, _time, globalTime);
		}
	}

	for (auto it : m_Colors)
	{
		it.calc(_animationIndex, _time, globalTime);
	}
}

//

void M2::lightsOn(uint32 lbase)
{
	/*if (!m_Loaded)
	{
		return;
	}

	// setup lights
	for (uint32 i = 0, l = lbase; i < m_Header.lights.size; i++)
	{
		m_Lights[i].setup(_time, l++);
	}*/
}

void M2::lightsOff(uint32 lbase)
{
	/*if (!m_Loaded)
	{
		return;
	}*/

	for (uint32 i = 0, l = lbase; i < m_Header.lights.size; i++)
	{
		//glDisable(l++);
	}
}

void M2::updateEmitters(float dt)
{
	if (!m_Loaded)
	{
		return;
	}

#ifdef MDX_PARTICLES_ENABLE
	for (uint32 i = 0; i < m_Header.particle_emitters.size; i++)
	{
		particleSystems[i].update(dt);
	}
#endif
}
