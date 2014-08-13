inline HWND Window::GetWindowHandle()
{
	return mhtWin;
}

void inline Window::SetTitle(const char * pctitle)
{
	SetWindowText(mhtWin, pctitle);
}