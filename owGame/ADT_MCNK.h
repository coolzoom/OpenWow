#pragma once

#include "Map_Headers.h"

// FORWARD BEGIN
class ADT;
// FORWARD END

class ADT_MCNK : public SceneNode
{
public:
	ADT_MCNK(ADT* _parentTile, IFile* _file);

	// ILoadableObject
	bool Load() override;
	bool Delete() override;

	// IRenderable3D
	void PreRender3D() override;
	void Render3D() override;
	void PostRender3D() override;

public:
	const SmartPtr<IFile> m_File;
	const vector<SmartPtr<ADT_TextureInfo>>* m_ParentTextures;
	ADT_MCNK_Header header;

	ADT_MCNK_MCLY mcly[4];

	SmartTexturePtr m_DiffuseTextures[4];
	SmartTexturePtr m_SpecularTextures[4];


	SmartPtr<Liquid_Instance> m_LiquidInstance;

	SmartTexturePtr m_BlendRBGShadowATexture;


	SmartGeomPtr __geom;

	R_Buffer* __ibDefault;
	uint16  m_IndexesCountDefault;

	R_Buffer* __ibLowResolution;
	uint16  m_IndexesCountLowResolution;

	SmartGeomPtr __geomDebugNormals;

	CGroupQuality& m_QualitySettings;
};