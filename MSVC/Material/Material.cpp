/**
 * \file    Material.cpp
 * \brief   Body of Material class
 * \details Provides tools for handling Cape-Open materials
 * \author  PB
 * \date    2013/12/30
 * \version 0.5
 */
#include "stdafx.h"
#include "Material.h"


Material::Material(ICapeThermoMaterialObject *mat)
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	this->mat = mat;
	mat->AddRef();
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}


Material::~Material(void)
{
	mat->Release();
}
