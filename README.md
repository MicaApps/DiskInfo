#  ![Frame 30284 (自定义)](https://user-images.githubusercontent.com/6630660/207081052-89642cf8-6a84-456d-9c96-e2db354ff3d6.png) DiskInfo

CrystalDiskInfo is one of the most famous disk health monitoring tools in the world. It is free and open source, and is still actively maintained.

https://github.com/hiyohiyo/CrystalDiskInfo

![image](https://user-images.githubusercontent.com/6630660/212543605-d8d80feb-b7d1-4d63-b528-0e98b1cff968.png)

This project aims at providing a mordern appearance for DiskInfo

![image](https://user-images.githubusercontent.com/6630660/212543495-ffba1279-bf86-4f4e-8568-8b8941edcfed.png)

The new design follow the guide of Fluent Design System，with flexible，adapting layout，and charming visual design

## Build
### Solution Structure
```
DiskTools
    \libs
        DiskInfo ---            The original C++ dll project for getting disk info, where functions are exported as C functions
        DiskInfo.Interop ---    C# interop project to call the C functions from the above dll
        DiskInfoLibWinRT ---    C++/WinRT ports of the above DiskInfo project, to be consumed directly to the main C# project (developing)
    DiskTools ---               The main C# project
```
### WinRT port
The `DiskInfoLibWinRT` is a C++/WinRT project transformed to be able to allowed to call Win32 APIs. 
It's basically using Visual Studio's `Windows Runtime Component` project template, but with additional macros defined and additional library paths added. 
In order to be consumed by the C# project (.NET6), 
- add [this nuget package](https://github.com/microsoft/cswinrt)
- add a project reference to the WinRT component project
and finally add a `PropertyGroup` tag in the `csproj` file.
```xml
<PropertyGroup>
    <CsWinRTIncludes>DiskInfoLibWinRT</CsWinRTIncludes>
    <CsWinRTGeneratedFilesDir>$(OutDir)</CsWinRTGeneratedFilesDir>
</PropertyGroup>
```

## Get From Microsoft Store
https://www.microsoft.com/store/apps/9PLQ8DP73ZDF

## Unknown issues
- Updating data **is** working, but the updates are not reflected on the UI. **Will fix very soon!** (You can see the updates if you restart the app!)
- Debugging for winui3 is not working. For developments' convenience, it normally runs without admin previledges. (This will change when it's publish to store)
- More features coming!

<details>
    <summary>Technology stack and pre-requsite to build</summary>

## Technology Stack

### Document

WinUI3

https://learn.microsoft.com/en-us/windows/apps/winui/winui3/create-your-first-winui3-app

https://learn.microsoft.com/en-us/windows/apps/winui/winui3/

https://apps.microsoft.com/store/detail/winui-3-gallery/9P3JFPWWDZRC

Windows Runtime

https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/intro-to-using-cpp-with-winrt

Windows App SDK

https://learn.microsoft.com/zh-tw/windows/apps/windows-app-sdk/

### Develop Environment

Visual Studio 2022

C++ Desktop Development

Universal C++ Development

Universal C# Development

Windows SDK 22621

### XAML Control Libraries

WinUI3

https://apps.microsoft.com/store/detail/winui-3-gallery/9P3JFPWWDZRC

Microsoft Community Toolkit Lab

https://github.com/CommunityToolkit/Labs-Windows

LiveCharts2

https://github.com/beto-rodriguez/LiveCharts2

Syncfusion WinUI Controls

https://www.syncfusion.com/winui-controls
</details>
