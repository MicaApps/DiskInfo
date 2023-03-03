<div> 
    <img alt="Icon" src="https://user-images.githubusercontent.com/6630660/207081052-89642cf8-6a84-456d-9c96-e2db354ff3d6.png" style="vertical-align:middle" /> 
    <h1 style="vertical-align:middle;display:inline;margin-left:12px" >DiskInfo</h1> 
    <a style="margin-left:24px" href="ms-windows-store://pdp/?ProductId=9PLQ8DP73ZDF&mode=mini">
        <img style="vertical-align:middle" src="https://get.microsoft.com/images/zh-cn%20dark.svg" alt="下载 DiskInfo" />
    </a>
</div> <br />
 一款拥有现代化 UI 的硬盘信息工具。

 ## 概念图
 ![image](https://user-images.githubusercontent.com/6630660/212543495-ffba1279-bf86-4f4e-8568-8b8941edcfed.png)

 ## 背景
[CrystalDiskInfo](https://github.com/hiyohiyo/CrystalDiskInfo) 是世界上最著名的磁盘健康监视工具之一。它是一款免费且开源的工具，至今仍在积极维护。

![image](https://user-images.githubusercontent.com/6630660/212543605-d8d80feb-b7d1-4d63-b528-0e98b1cff968.png)

本项目旨在提供一个具有现代化视觉体验的磁盘信息工具。新的视觉设计以[Fluent Design System](https://www.microsoft.com/design/fluent/)的设计指导作为参考，提供顺畅的体验和自适应性布局，以及具有魅力的界面设计。

## 构建
### 解决方案结构
```
DiskTools
    \libs
        DiskInfoLibWinRT ---    C++/WinRT层, 提供给UI层使用的磁盘信息(正在开发中)。
        DiskToolsTest ---       DiskInfoLibWinRT的测试库。
        MockDiskInfo ---        假的DiskInfoLibWinRT引用，提供给UI层进行界面测试使用。
    DiskTools ---               C#/WinUI 3 项目，提供了DiskInfo的UI层.
```
### WinRT 层
`DiskInfoLibWinRT` 是一个经过转化后可以调用Win32 API的 C++/WinRT 项目。
它在 Visual Studio 的 `Windows 运行时组件` 项目模板的基础上，添加了额外的宏定义以及库路径。
为了能够在 C# 项目中使用(.NET6),
- 添加 [cs/winrt](https://github.com/microsoft/cswinrt) 的 NuGet 包。
- 在项目中添加该 WinRT 项目的引用，最后在`csproj`文件中添加`PropertyGroup`标签，内容如下：
```xml
<PropertyGroup>
    <CsWinRTIncludes>DiskInfoLibWinRT</CsWinRTIncludes>
    <CsWinRTGeneratedFilesDir>$(OutDir)</CsWinRTGeneratedFilesDir>
</PropertyGroup>
```


## 已知问题
- 数据更新功能正常，但UI层无法正常显示更新后的数据。**该问题即将修复** (在重启应用后你可以看到更新后的数据)
- WinUI 3 无法使用调试功能。为了开发上的方便，默认不使用管理员权限运行。(商店版本发布时会改变这个行为)
- 更多功能即将到来！

<details>
    <summary>技术栈以及构建的前置条件</summary>

## 技术栈

### 文档

- [WinUI 3](https://learn.microsoft.com/en-us/windows/apps/winui/winui3/)

- [Windows Runtime](https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/intro-to-using-cpp-with-winrt)

- [Windows App SDK](https://learn.microsoft.com/zh-tw/windows/apps/windows-app-sdk/)

### 开发环境

- Visual Studio 2022

- 使用 C++ 的桌面开发

- 通用 Windows 平台开发

- .NET 桌面开发

- Windows SDK 22621

- 适用于最新v143 生成工具的 C++ ATL(x86 和 x64)

- 适用于最新v143 生成工具的 C++ MFC(x86 和 x64)

### XAML 控件库

- [WinUI 3](https://learn.microsoft.com/en-us/windows/apps/winui/winui3)

- [Windows Community Toolkit](https://github.com/CommunityToolkit/WindowsCommunityToolkit)

- [Syncfusion WinUI Controls](https://www.syncfusion.com/winui-controls)
</details>
