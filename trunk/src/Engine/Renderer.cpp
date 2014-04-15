#include <Windows.h>
#include <assert.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "includes\Window.h"
#include "includes\Renderer.h"

Stu::Engine::Renderer::Renderer()
{
	mhtDevice = NULL;
	mulClearColor = D3DCOLOR_ARGB(255L,50L,128L,50L);
	//hDX->CreateDevice
}

Stu::Engine::Renderer::~Renderer()
{
	if(mhtDevice)
	{
		IDirect3D9* htDX = NULL;
		mhtDevice->GetDirect3D(&htDX);

		mhtDevice->Release();//documentation says the function will free the pointer, just deleting the pointer seems to crash the application
		mhtDevice = NULL;

		if(htDX)
		{
			htDX->Release();
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
	tParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
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
			delete htDX;
			return true;
		}
	}
	//TODO ?
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