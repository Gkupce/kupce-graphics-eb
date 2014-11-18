#include <Windows.h>
#include <assert.h>
#include <map>

#include <d3d9.h>
#include <d3dx9.h>

#include "includes\Window.h"
#include "includes\Structs.h"
#include "includes\VertexBuffer.h"
#include "includes\VertexBuffer3D.h"
#include "includes\IndexBuffer3D.h"
#include "includes\Renderer.h"
#include "includes\Camera.h"
#include "includes\Vector3.h"
#include "includes\Quaternion.h"
#include "includes\Material.h"
#include "includes\Light.h"

D3DTRANSFORMSTATETYPE matrixModes[] = {D3DTS_VIEW, D3DTS_WORLD, D3DTS_PROJECTION};
D3DPRIMITIVETYPE primitives[] = {D3DPT_POINTLIST, D3DPT_LINELIST, D3DPT_LINESTRIP, D3DPT_TRIANGLELIST, D3DPT_TRIANGLESTRIP, D3DPT_TRIANGLEFAN};
D3DLIGHTTYPE lightTypes[] = {D3DLIGHT_POINT, D3DLIGHT_SPOT, D3DLIGHT_DIRECTIONAL};

Stu::Engine::Renderer::Renderer()
{
	mulLightAmnt = 0;
	mpoTexVtxBuffer = NULL;
	mpoColorVtxBuffer = NULL;
	mhtDevice = NULL;
	mtClearColor.argb = D3DCOLOR_XRGB(255,255,255);
}

Stu::Engine::Renderer::~Renderer()
{
	if(mpoColorVtxBuffer)
	{
		delete mpoColorVtxBuffer;
		mpoColorVtxBuffer = NULL;
	}

	if(mpoTexVtxBuffer)
	{
		delete mpoTexVtxBuffer;
		mpoTexVtxBuffer = NULL;
	}

	if(mhtDevice)
	{
		IDirect3D9* htDX = NULL;
		mhtDevice->GetDirect3D(&htDX);

		mhtDevice->Release();//documentation says the function will free the pointer, using delete to free the pointer seems to crash the application
		mhtDevice = NULL;

		if(htDX)
		{
			htDX->Release();//same verse as before
			htDX = NULL;
		}
	}
}

bool Stu::Engine::Renderer::Init(Window* poWindow)
{
	D3DDISPLAYMODE tDisplayMode;
	HRESULT tHR = 0;
	IDirect3D9* htDX = NULL;
	D3DPRESENT_PARAMETERS tParams;
	
	htDX = Direct3DCreate9(D3D_SDK_VERSION);
	if(!htDX)
	{
		return true;
	}

	tHR = htDX->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &tDisplayMode);
	if(tHR != D3D_OK)
	{
		return true;
	}

	ZeroMemory(&tParams, sizeof(tParams));
	tParams.BackBufferFormat = tDisplayMode.Format;
	tParams.BackBufferCount = 3; // breaks at >= 4
	tParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	tParams.hDeviceWindow = poWindow->GetWindowHandle(); //care
	tParams.Windowed = true;
	//tParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	tParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE; //solves extreme fps problem (with vsync?)
    tParams.EnableAutoDepthStencil = TRUE;
    tParams.AutoDepthStencilFormat = D3DFMT_D24S8; 
	
	tParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//tParams.Flags = 0;

	tHR = htDX->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
							poWindow->GetWindowHandle(), 
							D3DCREATE_HARDWARE_VERTEXPROCESSING,
							&tParams, &mhtDevice);
	if(tHR != D3D_OK)
	{
		//hardware vertex processing failed, try software vertex processing
		tHR = htDX->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
							poWindow->GetWindowHandle(), 
							D3DCREATE_SOFTWARE_VERTEXPROCESSING,
							&tParams, &mhtDevice);
		if(tHR != D3D_OK)
		{
			assert(true);
			htDX->Release();
			return true;
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//TODO change lighting
	mhtDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	mhtDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	mhtDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	mhtDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	mhtDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	mhtDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	mhtDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//--------------------------------------------------------------

	D3DVIEWPORT9 viewport;
	if(mhtDevice->GetViewport(&viewport) != D3D_OK)
	{
		assert(false);
		throw;
	}
	
	mtViewerPos.x = 0.0f;
	mtViewerPos.y = 0.0f;
	mtViewerPos.z = 200.0f;
	
	mtViewerUp.x = 0.0f;
	mtViewerUp.y = 1.0f;
	mtViewerUp.z = 0.0f;

	SetMatrixMode(Projection);
	LoadIdentity();
	SetMatrixMode(View);
	LoadIdentity();
	SetViewportPosition();
	//(float) viewport.Width, (float) viewport.Height
	D3DXMatrixPerspectiveFovLH(&mtProjectionMat, D3DX_PI/4, 
					(float) viewport.Width/ (float) viewport.Height, 
					1.0f, 5000.0f);
	if(mhtDevice->SetTransform(D3DTS_PROJECTION, &mtProjectionMat) != D3D_OK)
	{
		assert(false);
		throw;
	}

	SetMatrixMode(World);
	LoadIdentity();
	
	return false;
}

void Stu::Engine::Renderer::StartFrame()
{
	
	mhtDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, mtClearColor.argb, 1.0f, 0);
	mhtDevice->BeginScene();

}

void Stu::Engine::Renderer::EndFrame()
{
	mhtDevice->EndScene();
	mhtDevice->Present(NULL,NULL,NULL,NULL);
}

//--------------------------------------
//matrix stuff

void Stu::Engine::Renderer::LoadIdentity()
{
	D3DXMATRIX tempMat;
	D3DXMatrixIdentity(&tempMat);
	if(mtMatrixMode == D3DTS_VIEW)
	{
		D3DXVECTOR3 eyePos(0,0,-1);
		D3DXVECTOR3 lookPos(0,0,0);
		D3DXVECTOR3 upVector(0,1,0);

		D3DXMatrixLookAtLH(&tempMat, &eyePos, &lookPos, &upVector);
	}

	mhtDevice->SetTransform(mtMatrixMode, &tempMat);


}

void Stu::Engine::Renderer::SetMatrixMode(D3DTRANSFORMSTATETYPE tMatrixMode)
{
	mtMatrixMode = tMatrixMode;
}

void Stu::Engine::Renderer::SetMatrixMode(MatrixMode eMatrixMode)
{
	mtMatrixMode = matrixModes[eMatrixMode];
}

void Stu::Engine::Renderer::SetViewportPosition()
{
	D3DXMATRIX mat;
	D3DXVECTOR3 lookPos;

	lookPos.x = mtViewerPos.x;
	lookPos.y = mtViewerPos.y;
	lookPos.z = 0.0f;

	D3DXMatrixLookAtLH(&mat, &mtViewerPos, &lookPos, &mtViewerUp);
	if(mhtDevice->SetTransform(D3DTS_VIEW, &mat) == D3D_OK)
	{
		mtProjectionMat = mat;
	}
	else
	{
		MessageBox(NULL,"viewport fuck","fuck",MB_OK);
	}
}

void Stu::Engine::Renderer::SetViewportPosition(Stu::Engine::Camera* camera)
{
	D3DXMATRIX mat;
	D3DXVECTOR3 lookPos;
	lookPos = (camera->GetPosition() + camera->GetForward()).getD3DVector();
	mtViewerPos = camera->GetPosition().getD3DVector();
	mtViewerUp = camera->GetUpward().getD3DVector();
	/*
	lookPos.x = mtViewerPos.x;
	lookPos.y = mtViewerPos.y;
	lookPos.z = 0.0f;
	*/
	D3DXMatrixLookAtLH(&mat, &mtViewerPos, &lookPos, &mtViewerUp);
	if(mhtDevice->SetTransform(D3DTS_VIEW, &mat) == D3D_OK)
	{
		mtProjectionMat = mat;
	}
	else
	{
		MessageBox(NULL,"viewport fuck","fuck",MB_OK);
	}
}

void Stu::Engine::Renderer::Translate(float x, float y, float z)
{
	D3DXMATRIX tempMat;

	D3DXMatrixTranslation(&tempMat, x, y, z);

	mhtDevice->MultiplyTransform(mtMatrixMode, &tempMat);
}

void Stu::Engine::Renderer::Scale(float x, float y, float z)
{
	D3DXMATRIX tempMat;

	D3DXMatrixScaling(&tempMat, x, y, z);

	mhtDevice->MultiplyTransform(mtMatrixMode, &tempMat);
}

void Stu::Engine::Renderer::RotateX(float angle)
{
	D3DXMATRIX tempMat;

	D3DXMatrixRotationX(&tempMat, angle);
	
	mhtDevice->MultiplyTransform(mtMatrixMode, &tempMat);
}

void Stu::Engine::Renderer::RotateY(float angle)
{
	D3DXMATRIX tempMat;

	D3DXMatrixRotationY(&tempMat, angle);

	mhtDevice->MultiplyTransform(mtMatrixMode, &tempMat);
}

void Stu::Engine::Renderer::RotateZ(float angle)
{
	D3DXMATRIX tempMat;

	D3DXMatrixRotationZ(&tempMat, angle);

	mhtDevice->MultiplyTransform(mtMatrixMode, &tempMat);
}

void Stu::Engine::Renderer::Rotate(Quaternion baseRot, Vector3 eulerRot)
{
	D3DXMATRIX tempMat, *tempMat2;
	D3DXQUATERNION quaternion(baseRot.x, baseRot.y, baseRot.z, baseRot.w);
	tempMat2 = D3DXMatrixRotationQuaternion(&tempMat, &quaternion);
	mhtDevice->MultiplyTransform(mtMatrixMode, tempMat2);//&tempMat);
	RotateX(eulerRot.x);
	RotateY(eulerRot.y);
	RotateZ(eulerRot.z);
}

bool Stu::Engine::Renderer::Draw(ColorVertex* vertexs, unsigned int vertexCount, DrawPrimitives primitive)
{
	//Create the vertex buffer if it doesn't exist
	if(!mpoColorVtxBuffer)
	{
		//mpoColorVtxBuffer = new VertexBuffer<ColorVertex, D3DFVF_DIFFUSE | D3DFVF_XYZRHW>();
		mpoColorVtxBuffer = new VertexBuffer<ColorVertex, D3DFVF_DIFFUSE | D3DFVF_XYZ>();
		
		if(!mpoColorVtxBuffer)
		{
			return true;
		}
		if(mpoColorVtxBuffer->Create(mhtDevice, false))
		{
			return true;
		}
	}
	mpoColorVtxBuffer->Bind();
	mpoColorVtxBuffer->Draw(vertexs, primitives[primitive], vertexCount);
	return false;
}

bool Stu::Engine::Renderer::Draw(TexVertex* vertexs, unsigned int vertexCount, DrawPrimitives primitive)
{
	//Create the vertex buffer if it doesn't exist
	if(!mpoTexVtxBuffer)
	{
		mpoTexVtxBuffer = new VertexBuffer<TexVertex, D3DFVF_TEX1 | D3DFVF_XYZ>();
		
		if(!mpoTexVtxBuffer)
		{
			return true;
		}
		if(mpoTexVtxBuffer->Create(mhtDevice, false))
		{
			return true;
		}
	}
	mpoTexVtxBuffer->Bind();
	mpoTexVtxBuffer->Draw(vertexs, primitives[primitive], vertexCount);
	return false;
}

bool Stu::Engine::Renderer::Draw(VertexBuffer3D<ColorVertex, COLOR_VERTEX>::Ptr vertexBuffer, IndexBuffer3D::Ptr indexBuffer, 
										DrawPrimitives primitive, Material mat)
{
	BindMaterial(mat);
	mhtDevice->SetVertexShader(NULL);
	mhtDevice->SetFVF(vertexBuffer->GetFVF());
	mhtDevice->SetIndices(indexBuffer->GetIndexBuffer3D());
	vertexBuffer->Draw(primitives[primitive], indexBuffer->GetIndexCount());
	
	return false;
}

bool Stu::Engine::Renderer::Draw(VertexBuffer3D<TexNormalVertex, TEXTURE_NORMAL_VERTEX>::Ptr vertexBuffer, IndexBuffer3D::Ptr indexBuffer, 
										DrawPrimitives primitive, Material mat)
{
	BindMaterial(mat);
	mhtDevice->SetVertexShader(NULL);
	mhtDevice->SetFVF(vertexBuffer->GetFVF());
	mhtDevice->SetIndices(indexBuffer->GetIndexBuffer3D());
	vertexBuffer->Draw(primitives[primitive], indexBuffer->GetIndexCount());
	
	return false;
}

int Stu::Engine::Renderer::LoadTexture(const char* path, Color colorKey, unsigned int& width, unsigned int& height)
{
	LPDIRECT3DTEXTURE9 texture = NULL;
	
	HRESULT hRes = D3DXCreateTextureFromFileEx(
							mhtDevice,				//device
                            path,					//file name
                            D3DX_DEFAULT,			//width
                            D3DX_DEFAULT,			//height
                            D3DX_DEFAULT,			//mip levels
                            NULL,					//usage
                            D3DFMT_UNKNOWN,			//texture color format
                            D3DPOOL_MANAGED,		//memory class
                            D3DX_DEFAULT,			//filter
                            D3DX_DEFAULT,			//mip filter
							colorKey.argb,			//color key
                            NULL,					//source info
                            NULL,					//pallette
                            &texture);				//texture object
	if(!texture)
	{
		return -1;
	}

	D3DSURFACE_DESC Desc;
	texture->GetLevelDesc(0, &Desc);
	height = Desc.Height;
	width = Desc.Width;
	//in which position will the texture be
	int i = moTextureVec.size();
	//put the texture at the end
	moTextureVec.push_back(texture);

	return i;
}

bool Stu::Engine::Renderer::BindTexture(int texCode)
{
	assert(moTextureVec.capacity() + 1 > texCode);
	return mhtDevice->SetTexture(0, moTextureVec[texCode]) != D3D_OK;
}

void Stu::Engine::Renderer::UnbindTexture()
{
	mhtDevice->SetTexture(0, NULL);
}


bool Stu::Engine::Renderer::InitVertexBuffer3D(VertexBuffer3D<ColorVertex, COLOR_VERTEX>::Ptr vertexBuffer,
						 bool bDynamic, ColorVertex * pVtxCollection, unsigned int uiVtxCount)
{
	return vertexBuffer->Create(mhtDevice, bDynamic, pVtxCollection, uiVtxCount);
}

bool Stu::Engine::Renderer::InitVertexBuffer3D(VertexBuffer3D<TexNormalVertex, TEXTURE_NORMAL_VERTEX>::Ptr vertexBuffer,
						 bool bDynamic, TexNormalVertex * pVtxCollection, unsigned int uiVtxCount)
{
	return vertexBuffer->Create(mhtDevice, bDynamic, pVtxCollection, uiVtxCount);
}

bool Stu::Engine::Renderer::InitIndexBuffer3D(IndexBuffer3D::Ptr indexBuffer,
						 bool bDynamic, DWORD * pVtxCollection, size_t uiVtxCount)
{
	return indexBuffer->Create(mhtDevice, bDynamic, uiVtxCount, pVtxCollection);
}

bool Stu::Engine::Renderer::BindMaterial(Material mat)
{
	D3DMATERIAL9 dMat = ConvertMaterial(mat);
	
	return mhtDevice->SetMaterial(&dMat) != S_OK;
}

void Stu::Engine::Renderer::UnbindMaterial()
{
	mhtDevice->SetMaterial(NULL);
}

//---------------------------------------------------
D3DCOLORVALUE Stu::Engine::Renderer::ConvertColor(Color col)
{
	D3DCOLORVALUE result;
	result.a = col.part.a /255.0f;
	result.r = col.part.r /255.0f;
	result.g = col.part.g /255.0f;
	result.b = col.part.b /255.0f;

	return result;
}

D3DMATERIAL9 Stu::Engine::Renderer::ConvertMaterial(Material mat)
{
	D3DMATERIAL9 result;
	result.Ambient = ConvertColor(mat.GetAmbient());
	result.Diffuse = ConvertColor(mat.GetDiffuse());
	result.Emissive = ConvertColor(mat.GetEmissive());
	result.Specular = ConvertColor(mat.GetSpecular());
	result.Power = mat.GetSpecPow();

	return result;
}

D3DLIGHT9 Stu::Engine::Renderer::ConvertLight(Light light)
{
	D3DLIGHT9 result;
	result.Ambient = ConvertColor(light.GetAmbient());
	result.Diffuse = ConvertColor(light.GetDiffuse());
	result.Specular = ConvertColor(light.GetSpecular());
	result.Attenuation0 = light.GetAttenuation().x;
	result.Attenuation1 = light.GetAttenuation().y;
	result.Attenuation2 = light.GetAttenuation().z;
	result.Direction = light.GetDirection().getD3DVector();
	result.Falloff = light.GetSpotFalloff();
	result.Phi = light.GetSpotOuterConeRad();
	result.Theta = light.GetSpotInnerConeRad();
	result.Position = light.GetPosition().getD3DVector();
	result.Range = light.GetRange();
	result.Type = lightTypes[light.GetLightType()];

	return result;
}

void Stu::Engine::Renderer::SetLight(Light light)
{
	unsigned long lightToAffect = light.GetLightCode();
	if(lightToAffect == Light::LIGHT_GET_CODE_NONE)
	{
		lightToAffect = Light::GetNewLightCode();
		if(lightToAffect == Light::LIGHT_GET_CODE_NONE)
		{//there are too many lights
			assert(true);
			return;
		}
		light.SetLightCode(lightToAffect);
	}
	D3DLIGHT9 dxLight = ConvertLight(light);
	mhtDevice->SetLight(lightToAffect, &dxLight);
	mhtDevice->LightEnable(lightToAffect, light.IsOn());
}

void Stu::Engine::Renderer::ChangeLightState(Light light)
{
	mhtDevice->LightEnable(light.GetLightCode(), light.IsOn());
}

void Stu::Engine::Renderer::ChangeLightState(Light light, bool state)
{
	mhtDevice->LightEnable(light.GetLightCode(), state);
}