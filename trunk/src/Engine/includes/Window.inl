inline HWND Window::GetWindowHandle()
{
	return mhtWin;
}

void inline Window::SetTitle(char * pctitle)
{
	SetWindowText(mhtWin, pctitle);
}