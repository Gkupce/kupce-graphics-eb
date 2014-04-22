#include <Windows.h>
#include <assert.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "includes\Window.h"
#include "includes\Structs.h"
#include "includes\VertexBuffer.h"
#include "includes\Renderer.h"

D3DTRANSFORMSTATETYPE matrixModes[] = {D3DTS_VIEW, D3DTS_WORLD, D3DTS_PROJECTION};

Stu::Engine::Renderer::Renderer()
{
	mpoColorVtxBuffer = NULL;
	mhtDevice = NULL;
	mulClearColor = D3DCOLOR_ARGB(255L,50L,128L,50L);
	//hDX->CreateDevice
}

Stu::Engine::Renderer::~Renderer()
{
	if(mpoColorVtxBuffer)
	{
		delete mpoColorVtxBuffer;
		mpoColorVtxBuffer = NULL;
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
	tParams.BackBufferCount = 1;
	tParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	tParams.hDeviceWindow = poWindow->GetWindowHandle(); //care
	tParams.Windowed = true;
	//tParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	tParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE; //solves extreme fps problem (with vsync?)
	tParams.EnableAutoDepthStencil = true;
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

	//TODO understand
	mhtDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//mhtDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	mhtDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	mhtDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	mhtDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
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
	
	D3DXMatrixOrthoLH(&mtProjectionMat, (float) viewport.Width, (float) viewport.Height, -25, 25);
	if( mhtDevice->SetTransform(D3DTS_PROJECTION, &mtProjectionMat) != D3D_OK)
	{
		assert(false);
		throw;
	}

	SetViewportPosition();
	LoadIdentity();
	
	//TODO set viewport and world matrix
	//draw a triangle
	return false;
}

void Stu::Engine::Renderer::StartFrame()
{
	
	mhtDevice->Clear(0, NULL, D3DCLEAR_TARGET, mulClearColor, 1.0f, 0);
	mhtDevice->BeginScene();

}

void Stu::Engine::Renderer::EndFrame()
{
	mhtDevice->EndScene();
	mhtDevice->Present(NULL,NULL,NULL,NULL);
}

void Stu::Engine::Renderer::SetClearColor(int a, int r, int g, int b)
{
	mulClearColor = D3DCOLOR_ARGB(a,r,g,b);
}

//TODO understand

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

void Stu::Engine::Renderer::Translate(float x, float y, float z)
{
	D3DXMATRIX tempMat;

	D3DXMatrixTranslation(&tempMat, x, y, z);

	mhtDevice->MultiplyTransform(mtMatrixMode, &tempMat);
}

void Stu::Engine::Renderer::Scale(float x, float y)
{
	D3DXMATRIX tempMat;

	D3DXMatrixScaling(&tempMat, x, y, 1);

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

//TODO de-hardcode draw primitive
bool Stu::Engine::Renderer::Draw(ColorVertex* vertexs, unsigned int vertexCount)
{
	if(!mpoColorVtxBuffer)
	{
		mpoColorVtxBuffer = new VertexBuffer<ColorVertex, D3DFVF_DIFFUSE | D3DFVF_XYZ>();
		
		if(!mpoColorVtxBuffer)
		{
			return false;
		}
		if(mpoColorVtxBuffer->Create(mhtDevice, false))
		{
			return true;
		}
	}
	mpoColorVtxBuffer->Bind();
	mpoColorVtxBuffer->Draw(vertexs, D3DPT_TRIANGLESTRIP, vertexCount);
}