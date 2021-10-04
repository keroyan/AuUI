# What's AuUI

** Project is not finished **

**AuUI**, an abbreviation for "Actual Understandable User Interface" is a graphical user interface framework to help you build your projects quicker and easier. 
It's built on top of [ImGui](https://github.com/ocornut/imgui) with additional features to make it easier for a beginner to create softwares using ImGui.

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

## What does this project use

- To Draw?
  - It uses *DirectX* to draw all it's elements e.g Text, Checkboxes
- To Create Window?
  - It uses *Windows API* to make a basic Window
- Made in?
  - Plain *C++*

## Why?

I created this project to help people make good designs while not investing time in creating the elements they desire.
I want to help developers spend more time on the program's quality than the quality of the library. Moreover, with the community's help, we can create a powerful Graphical User Interface Framework that will help developers make powerful programs such as Game Engines and other kinds of programs. Hopefully, you understand that this project is for good intentions only.
