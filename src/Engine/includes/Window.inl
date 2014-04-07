inline HWND Window::GetWindowHandle()
{
	return mhWin;
}

void inline Window::SetTitle(char * title)
{
	SetWindowText(mhWin, title);
}