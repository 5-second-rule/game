#include <windows.h>

#ifdef _DEBUG
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "game-media/RenderableGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	RenderableGame *game = new RenderableGame(hInstance);
	game->init();
	game->run();
	game->stop();
	delete game;

#ifdef _DEBUG
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;


	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3
	};

	D3D11CreateDevice(
		NULL, //default adapter
		D3D_DRIVER_TYPE_HARDWARE,
		0, //no software device
		createDeviceFlags,
		featureLevels, 4,
		D3D11_SDK_VERSION,
		&device,
		&featureLevel,
		&context
		);
	ID3D11Debug* pDebug;
	HRESULT hr = device->QueryInterface( __uuidof(ID3D11Debug), (void**)&pDebug );
	device->Release();
	pDebug->ReportLiveDeviceObjects( D3D11_RLDO_DETAIL );
	pDebug->Release();

	_CrtDumpMemoryLeaks();
#endif

	return 0;
}

