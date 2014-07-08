//----------------------------------------------------------------
#ifndef INPUT_H
#define INPUT_H
//----------------------------------------------------------------
#include "Defines.h"
//----------------------------------------------------------------
//#define Key_Up(key)			getKeyEventUp (unsigned int uiKeyID)
//#define Key_Down(key)		getKeyEventDown (unsigned int uiKeyID)
//#define Key_Pressed(key)	getKeyDown (unsigned int uiKeyID)
//----------------------------------------------------------------
class ENGINE_API Input
{
public:

	enum
	{
		POS_X,
		POS_Y,
		POS_Z
	};

	enum MouseButton
	{
		MB_1,
		MB_2,
		MB_3
	};

	enum KeyState
	{
		KS_NONE,
		KS_DOWN,
		KS_UP
	};
    
	Input ();
    virtual ~Input ();

    virtual bool init () = 0;
    virtual void deinit () = 0;
    
    // Acquire Keyboard and mouse
    virtual void acquire () = 0;
    virtual void reacquire () = 0;
    virtual void unacquire () = 0;

	void getKeyEvent ();
    void setMousePosition (long x, long y, long z);
	void eventClean ();
	virtual void reset ();

	bool getKeyDown (unsigned int uiKeyID);
	bool getKeyEventDown (unsigned int uiKeyID);
	bool getKeyEventUp (unsigned int uiKeyID);

	bool getMouseButton (unsigned int uiButtonID);
	bool getMouseClick (unsigned int uiButtonID);
	long getMouseScrAbsPosX ();
	long getMouseScrAbsPosY ();
	long getMouseScrAbsPosZ ();
	long getMouseRelPosX ();
	long getMouseRelPosY ();
	long getMouseRelPosZ ();

// device state buffers
protected:
	unsigned char m_ucKeyBuffer[256];
	unsigned char m_ucKeyPrevBuffer[256];
	unsigned char m_ucKeyEvent[256];

	long m_lMouseScreenAbsPosition[3];
	long m_lMouseRelPosition[3];
	unsigned char m_ucMouseButton[3];
	bool m_lMouseButtonClick[3];
	bool m_bButtonState[3];

	void update ();
};
//----------------------------------------------------------------
#include "Input.inl"
//----------------------------------------------------------------
#endif // INPUT_H
//----------------------------------------------------------------