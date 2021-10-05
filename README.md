# What is AuUI

** Project is not finished **

**AuUI**, an abbreviation for "Actual Understandable User Interface" is a graphical user interface framework to help you build your projects quicker and easier. 
It's built on top of [ImGui](https://github.com/ocornut/imgui) with additional features to make it easier to create good designs without working hard to get a specific feature added. 

## Usage/Examples

Getting simple AuUI Window!
```c++
AuUI::BeginWindow();
{
    AuUI::Begin(AuUI::WindowData("Simple Window"));
    {

    }
    AuUI::End();
}
AuUI::EndWindow();
```

BeginWindow is just creating a new frame but instead of three lines of code it's just 1 line and EndWindow is the same as ImGui::EndFrame();
but we don't want to use ImGui namespace as it will look ugly in the code. 
<br></br>
AuUI::Begin() will create the window and just needs only one argument and it's WindowData which is a class that can be used to add a specific size, flags, 
and other information about the window 

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
  - It uses *ImGui* to draw all it's elements e.g Text, Checkboxes
- Made in?
  - Plain *C++*
