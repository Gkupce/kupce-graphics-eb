//----------------------------------------------------------------
#include "includes\DirectInput.h"
//----------------------------------------------------------------
DirectInput::DirectInput (HINSTANCE hInstance, HWND hWnd)
:
m_lpObjectOne(NULL),
m_lpObjectTwo(NULL),
m_lpKeyboard(NULL),
m_lpMouse(NULL),
m_hInstance(hInstance),
m_hWnd(hWnd)
{
	/***/
}
//----------------------------------------------------------------
DirectInput::~DirectInput ()
{
	/***/
}
//----------------------------------------------------------------
bool DirectInput::init ()
{
	// set the cursor value to the current cursor position
	POINT kCursorPos;
	GetCursorPos(&kCursorPos);

	m_lMouseScreenAbsPosition[0] = kCursorPos.x;
	m_lMouseScreenAbsPosition[1] = kCursorPos.y;
	m_lMouseScreenAbsPosition[2] = 0;

	// initialize DirectInput
	static HRESULT hr;

	// direct input keyboard object
	hr = DirectInput8Create( m_hInstance, 
		                DIRECTINPUT_VERSION, 
						IID_IDirectInput8,
						(void**)&m_lpObjectOne, 
						NULL );
    
	if(hr != D3D_OK)
		return false;
	
	// direct input device object
	hr = m_lpObjectOne->CreateDevice( GUID_SysKeyboard, &m_lpKeyboard, NULL );
    
	if(hr != D3D_OK)
		return false;
	
	// set the keyboard data format
	hr = m_lpKeyboard->SetDataFormat(&c_dfDIKeyboard);
    
	if(hr != D3D_OK)
		return false;

	hr = m_lpKeyboard->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
  
	if(hr != D3D_OK)
		return false;
 
	// acquire the keyboard
	m_lpKeyboard->Acquire();		

	// direct input mouse object
	hr = DirectInput8Create( m_hInstance, 
						DIRECTINPUT_VERSION, 
						IID_IDirectInput8,
						(void**)&m_lpObjectTwo,	
						NULL );
    
	if(hr != D3D_OK)
		return false;
	
	// direct input device object
    hr = m_lpObjectTwo->CreateDevice(GUID_SysMouse, &m_lpMouse, NULL);

	if(hr != D3D_OK)
		return false;

	// set the mouse data format
    hr = m_lpMouse->SetDataFormat(&c_dfDIMouse);
	
	if(hr != D3D_OK)
		return false;

	// set the mouse behavior
	hr = m_lpMouse->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	
	if(hr != D3D_OK)
		return false;

	// acquire the mouse
	m_lpMouse->Acquire();

    if(hr != D3D_OK)
		return false;

	return true;
}
//----------------------------------------------------------------
void DirectInput::deinit ()
{
    m_lpKeyboard->Unacquire();  // then unacquire it
    m_lpKeyboard->Release();    // and release it
    m_lpKeyboard = NULL;		// and NULL the pointer
	m_lpObjectOne->Release();		// release the DirectInput Object One
    m_lpObjectOne = NULL;			// and NULL the pointer
    
	m_lpMouse->Unacquire();		// then unacquire it
    m_lpMouse->Release();		// and release it
    m_lpMouse = NULL;			// and NULL the pointer
    m_lpObjectTwo->Release();		// release de DirectInput Object Two
    m_lpObjectTwo = NULL;			// and NULL the pointer
}
//----------------------------------------------------------------
void DirectInput::reacquire ()
{
	// reacquire all the input devices
	//Reset();
	m_lpMouse->Acquire();
	m_lpKeyboard->Acquire();
	acquire();
}
//----------------------------------------------------------------
void DirectInput::unacquire ()
{
	// unacquire all the input devices
	ZeroMemory(&m_ucKeyBuffer, sizeof(m_ucKeyBuffer));
    ZeroMemory(&m_kMouseTaken, sizeof(m_kMouseTaken));
	m_lpMouse->Unacquire();
	m_lpKeyboard->Unacquire();
}
//----------------------------------------------------------------
void DirectInput::acquire ()
{
	// get the keyboard device state
	memcpy(m_ucKeyPrevBuffer, m_ucKeyBuffer, 256);
	ZeroMemory(&m_ucKeyBuffer, sizeof(m_ucKeyBuffer));
	m_lpKeyboard->GetDeviceState(sizeof(m_ucKeyBuffer), &m_ucKeyBuffer);

	// get the mouse device state
    ZeroMemory(&m_kMouseTaken, sizeof(m_kMouseTaken));
    m_lpMouse->GetDeviceState( sizeof(m_kMouseTaken), &m_kMouseTaken);

	// update the mouse absolute position
	m_lMouseScreenAbsPosition[POS_X] += m_kMouseTaken.lX;
	m_lMouseScreenAbsPosition[POS_Y] -= m_kMouseTaken.lY;
	m_lMouseScreenAbsPosition[POS_Z] += m_kMouseTaken.lZ;

	// set the mouse relative position
	m_lMouseRelPosition[POS_X] = m_kMouseTaken.lX;
	m_lMouseRelPosition[POS_Y] = m_kMouseTaken.lY;
	m_lMouseRelPosition[POS_Z] = m_kMouseTaken.lZ;

	// updates the mouse button states
    m_ucMouseButton[MB_1] = m_kMouseTaken.rgbButtons[MB_1] & 0x80;
    m_ucMouseButton[MB_2] = m_kMouseTaken.rgbButtons[MB_2] & 0x80;
    m_ucMouseButton[MB_3] = m_kMouseTaken.rgbButtons[MB_3] & 0x80;

	// update the internal state
	update();
}
//----------------------------------------------------------------
void DirectInput::reset ()
{
	// resets all the devices status buffers
	Input::reset();
	ZeroMemory(&m_kMouseTaken, sizeof(m_kMouseTaken));
}
//----------------------------------------------------------------