# What's AuUI

** Project is not finished **

**AuUI**, an abbreviation for "Actual Understandable User Interface" is a graphical user interface framework to help you build your projects quicker and easier. 

You might wonder why I chose that name, and the reasoning behind it is that all other frameworks are complicated and harder to understand; that is not the case with AuUI due to it having understandable code and comments that tell you exactly what a specific file does or a line.

## Usage/Examples

Creating Window's are super easy now and will make your code look cleaner instead of having a 200 lines 
of code just to make a window (with Directx)
<br><br>
You can just do the following.
```c++
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    AnUI::Window Window;
    Window.Create(AuUI::WindowData(300, 300, 400, 400, L"Test Window", L"WindowClass1"), WindowProc, hInstance, hPrevInstance, lpCmdLine, nCmdShow);

    MSG msg;
    while (!Window.GetBreakLoop())
    {
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
	{
             TranslateMessage(&msg);
             DispatchMessage(&msg);

	     if (msg.message == WM_QUIT)
                Window.SetBreakLoop(true);
        }

	if (Window.GetBreakLoop())
           break;
      
        // UI Here!
    }

    Window.Destroy();

    return 0;
}
```

  

## Installation

As this project is primarily about simplicity, the installation is also easy; hence do the following.

```bash
  git clone https://github.com/SorryX/AuUI
```

After that, you include all of the files inside "includes" and you are done.
<br>
You can also download the project if you do not want to install "git".

