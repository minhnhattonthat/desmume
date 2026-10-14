// QA fork: with --headless the main window is hidden, so a MessageBox owned by it is invisible and blocks the
// emulator forever. Include this after <windows.h>: MessageBox then logs the text to stdout and returns the
// answer that keeps a run going. Without --headless it is the normal Windows MessageBox.
#pragma once
#include <windows.h>

extern bool g_qaHeadless;
int QAMessageBox(HWND hwnd, const char *text, const char *caption, UINT type);

#undef MessageBox
#define MessageBox QAMessageBox
