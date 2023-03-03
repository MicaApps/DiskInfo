<p align="center">
    <img alt="Icon" src="https://user-images.githubusercontent.com/6630660/207081052-89642cf8-6a84-456d-9c96-e2db354ff3d6.png" align="center"/>
    <h1 align="center"> DiskInfo </h1>
    <p align="center">
        A tool for viewing hard drive information with a modern UI design. 
    </p>
</p>

## Download
<a style="margin-left:24px" href="https://www.microsoft.com/store/productId/9PLQ8DP73ZDF">
    <picture>
        <source media="(prefers-color-scheme: dark)" srcset="https://get.microsoft.com/images/en-us%20light.svg" />
        <source media="(prefers-color-scheme: light)" srcset="https://get.microsoft.com/images/en-us%20dark.svg" />
        <img style="vertical-align:middle" src="https://get.microsoft.com/images/en-us%20dark.svg" alt="Download DiskInfo" />
    </picture>
</a>

## Language
- [中文](README.zh-CN.md)

## Concept
![image](https://user-images.githubusercontent.com/6630660/212543495-ffba1279-bf86-4f4e-8568-8b8941edcfed.png)

## Background
[CrystalDiskInfo](https://github.com/hiyohiyo/CrystalDiskInfo) is one of the most famous disk health monitoring tools in the world. It is free and open source, and is still actively maintained.

<img alt="CrystalDiskInfo" src="https://user-images.githubusercontent.com/6630660/212543605-d8d80feb-b7d1-4d63-b528-0e98b1cff968.png" style="width:30%" />

This project aims at providing a mordern appearance for DiskInfo. The new design follow the guide of [Fluent Design System](https://www.microsoft.com/design/fluent/)，with flexible，adapting layout，and charming visual design.

## Build
### Solution Structure
```
DiskTools
    \libs
        DiskInfoLibWinRT ---    C++/WinRT ports of the above DiskInfo project, to be consumed directly to UI layer (developing).
        DiskToolsTest ---       a library for testing DiskInfoLibWinRT.
        MockDiskInfo ---        Fake DiskInfoLibWinRT reference that provide sample data for UI layer test.
    DiskTools ---               C#/WinUI 3 project that provide the UI layer of DiskInfo.
```
### WinRT port
The `DiskInfoLibWinRT` is a C++/WinRT project transformed to be able to allowed to call Win32 APIs. 
It's basically using Visual Studio's `Windows Runtime Component` project template, but with additional macros defined and additional library paths added. 
In order to be consumed by the C# project (.NET6), 
- add [cs/winrt](https://github.com/microsoft/cswinrt) NuGet package.
- add a project reference to the WinRT component project, finally add a `PropertyGroup` tag in the `csproj` file.
```xml
<PropertyGroup>
    <CsWinRTIncludes>DiskInfoLibWinRT</CsWinRTIncludes>
    <CsWinRTGeneratedFilesDir>$(OutDir)</CsWinRTGeneratedFilesDir>
</PropertyGroup>
```


## Known issues
- Updating data **is** working, but the updates are not reflected on the UI. **Will fix very soon!** (You can see the updates if you restart the app!)
- Debugging for winui3 is not working. For developments' convenience, it normally runs without admin previledges. (This will change when it's publish to store)
- More features coming!

<details>
    <summary>Technology stack and pre-requsite to build</summary>

## Technology Stack

### Documents

- [WinUI 3](https://learn.microsoft.com/en-us/windows/apps/winui/winui3/)

- [Windows Runtime](https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/intro-to-using-cpp-with-winrt)

- [Windows App SDK](https://learn.microsoft.com/zh-tw/windows/apps/windows-app-sdk/)

### Develop Environment

- Visual Studio 2022

- C++ Desktop Development

- Universal Windows Development

- .NET Desktop Development

- Windows SDK 22621

- C++ ATL for latest v143 build tools (x86 & x64)

- C++ MFC for latest v143 build tools (x86 & x64)

### XAML Control Libraries

- [WinUI 3](https://learn.microsoft.com/en-us/windows/apps/winui/winui3)

- [Windows Community Toolkit](https://github.com/CommunityToolkit/WindowsCommunityToolkit)

- [Syncfusion WinUI Controls](https://www.syncfusion.com/winui-controls)
</details>
