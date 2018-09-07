#include "IShader.h"
#include "DeviceManager.h"


namespace CompEngine
{
	IShader::IShader()
	{
		SetComponentName("IShader");
		filePath = "";
	}

	IShader::~IShader()
	{
	}
	
	void IShader::SetPath(string filePath)
	{
		this->filePath = filePath;
		shader = LoadShader();
	}

	string IShader::GetPath()
	{
		return filePath;
	}

	LPD3DXEFFECT IShader::LoadShader()
	{
		LPD3DXEFFECT ret = NULL;
		LPD3DXBUFFER error = NULL;
		int dwShaderFlags = 0;

		dwShaderFlags = D3DXFX_NOT_CLONEABLE | D3DXSHADER_NO_PRESHADER;

		D3DXCreateEffectFromFile(DeviceMgr->GetDevice(), filePath.c_str(),
			NULL, NULL, dwShaderFlags, NULL, &ret, &error);

		if (!ret && error)
		{
			int size = error->GetBufferSize();
			void *ack = error->GetBufferPointer();

			if (ack)
			{
				char* str = new char[size];
				strcpy(str, (const char*)ack);
				OutputDebugString(str);
				delete[] str;
			}
		}

		return ret;
	}

	LPD3DXEFFECT IShader::GetShader()
	{
		return shader;
	}
}
