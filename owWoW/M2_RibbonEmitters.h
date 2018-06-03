#pragma once

// FORWARD BEGIN
class CM2_Part_Bone;
// FORWARD END

struct RibbonSegment
{
	vec3 pos, up, back;
	float len, len0;
};

class CM2_RibbonEmitters
{
public:
	CM2_RibbonEmitters(MDX* _model, IFile* f, const SM2_RibbonEmitter& mta, cGlobalLoopSeq globals);

	void setup(uint32 anim, uint32 time, uint32 _globalTime);

	void draw();

private:
	const MDX*									m_MDX;

	uint32										m_ID;
	const CM2_Part_Bone*						m_Bone;
	vec3										pos;
	vec3										posValue;

	SmartTexturePtr								m_Texture;
	const SM2_Material*							m_Material;

	M2_Animated<vec3>							m_Color;
	M2_Animated<float, short, ShortToFloat>		m_Alpha;
	M2_Animated<float>							m_HeightAbove;
	M2_Animated<float>							m_HeightBelow;
	
	vec4										tcolor;
	float										tabove;
	float										tbelow;
	
	float length;
	float m_EdgesLifeTime;
	int m_EdgesPerSecond;

	list<RibbonSegment> segs;
};