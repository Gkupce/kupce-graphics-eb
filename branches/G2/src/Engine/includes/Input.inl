//----------------------------------------------------------------
inline bool Input::getKeyDown (unsigned int uiKeyID)
{
	return ((m_ucKeyBuffer[uiKeyID] & 0x80) != 0);
}
//----------------------------------------------------------------
inline bool Input::getKeyEventDown (unsigned int uiKeyID)
{
	return (m_ucKeyEvent[uiKeyID] == KS_DOWN);
}
//----------------------------------------------------------------
inline bool Input::getKeyEventUp (unsigned int uiKeyID)
{
	return (m_ucKeyEvent[uiKeyID] == KS_UP);
}
//----------------------------------------------------------------
inline bool Input::getMouseButton (unsigned int uiButtonID)
{
	return ((m_ucMouseButton[uiButtonID] & 0x80) != 0);
}
//----------------------------------------------------------------
inline bool Input::getMouseClick (unsigned int uiButtonID)
{
	return (m_lMouseButtonClick[uiButtonID]);
}
//----------------------------------------------------------------
inline long Input::getMouseScrAbsPosX ()
{
	return (m_lMouseScreenAbsPosition[0]);
}
//----------------------------------------------------------------
inline long Input::getMouseScrAbsPosY ()
{
	return (m_lMouseScreenAbsPosition[1]);
}
//----------------------------------------------------------------
inline long Input::getMouseScrAbsPosZ ()
{
	return (m_lMouseScreenAbsPosition[2]);
}
//----------------------------------------------------------------
inline long Input::getMouseRelPosX ()
{
	return (m_lMouseRelPosition[0]);
}
//----------------------------------------------------------------
inline long Input::getMouseRelPosY ()
{
	return (m_lMouseRelPosition[1]);
}
//----------------------------------------------------------------
inline long Input::getMouseRelPosZ ()
{
	return (m_lMouseRelPosition[2]);
}
//----------------------------------------------------------------