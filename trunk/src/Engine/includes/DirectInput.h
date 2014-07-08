//----------------------------------------------------------------
#ifndef DIRECT_INPUT_H
#define DIRECT_INPUT_H
//----------------------------------------------------------------
#define DIRECTINPUT_VERSION 0x0800
//----------------------------------------------------------------
#include "Input.h"
//----------------------------------------------------------------
#include "d3d9.h"
#include "dinput.h"
//----------------------------------------------------------------
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
//----------------------------------------------------------------
class ENGINE_API DirectInput : public Input
{
public:

    DirectInput (HINSTANCE hInstance, HWND hWnd);
    virtual ~DirectInput ();

    bool init ();
    void deinit ();
    
    // acquire keyboard and mouse
    void acquire ();
    void reacquire ();
    void unacquire ();
	void reset ();

private:

	LPDIRECTINPUT8 m_lpObjectOne;
	LPDIRECTINPUT8 m_lpObjectTwo;
	LPDIRECTINPUTDEVICE8 m_lpKeyboard;
	LPDIRECTINPUTDEVICE8 m_lpMouse;
	DIMOUSESTATE m_kMouseTaken;

	HINSTANCE m_hInstance;
	HWND m_hWnd;
};
//----------------------------------------------------------------
#endif // DIRECT_INPUT_H
//----------------------------------------------------------------