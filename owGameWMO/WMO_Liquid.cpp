#include "stdafx.h"

// General
#include "WMO_Liquid.h"

CWMO_Liquid::CWMO_Liquid(uint32 _x, uint32 _y) :
	Liquid(_x, _y)
{}

void CWMO_Liquid::CreateFromWMO(IFile* f, WMO_Part_Material* _material, const DBC_LiquidTypeRecord* _liquidType, bool _indoor)
{
	ydir = -1.0f; // Magic for WMO

	initGeometry(DBC_LIQUIDTYPE_Type::lq_river, f);
	//InitTextures((DBC_LIQUIDTYPE_Type)_liquidType->Get_Type());
	InitTextures(DBC_LIQUIDTYPE_Type::lq_river);

	/*if (_indoor)
	{
		m_WaterColorLight = fromRGB(_material->GetDiffuseColor());
		m_WaterColorDark = m_WaterColorLight;
	}
	else
	{
		m_WaterColorLight = _World->EnvM()->m_SkyManager->GetColor(LIGHT_COLOR_RIVER_LIGHT);
		m_WaterColorDark = _World->EnvM()->m_SkyManager->GetColor(LIGHT_COLOR_RIVER_DARK);
	}*/
}