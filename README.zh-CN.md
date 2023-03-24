<p align="center">
    <img alt="图标" src="https://user-images.githubusercontent.com/6630660/207081052-89642cf8-6a84-456d-9c96-e2db354ff3d6.png" align="center"/>
    <h1 align="center"> DiskInfo </h1>
    <p align="center">
        一款拥有现代化 UI 的硬盘信息工具。
    </p>
</p>

## 下载
<a style="margin-left:24px" href="https://www.microsoft.com/store/productId/9PLQ8DP73ZDF">
    <picture>
        <source media="(prefers-color-scheme: dark)" srcset="https://get.microsoft.com/images/zh-cn%20light.svg" />
        <source media="(prefers-color-scheme: light)" srcset="https://get.microsoft.com/images/zh-cn%20dark.svg" />
        <img style="vertical-align:middle" src="https://get.microsoft.com/images/zh-cn%20dark.svg" alt="下载 DiskInfo" />
    </picture>
</a>
 

## 概念图
![image](https://user-images.githubusercontent.com/6630660/212543495-ffba1279-bf86-4f4e-8568-8b8941edcfed.png)

## 背景
[CrystalDiskInfo](https://github.com/hiyohiyo/CrystalDiskInfo) 是世界上最著名的磁盘健康监视工具之一。它是一款免费且开源的工具，至今仍在积极维护。

<img alt="CrystalDiskInfo" src="https://user-images.githubusercontent.com/6630660/212543605-d8d80feb-b7d1-4d63-b528-0e98b1cff968.png" style="width:30%" />

本项目旨在提供一个具有现代化视觉体验的磁盘信息工具。新的视觉设计以[Fluent Design System](https://www.microsoft.com/design/fluent/)的设计指导作为参考，提供顺畅的体验和自适应性布局，以及具有魅力的界面设计。

## 构建
### 解决方案结构
```
DiskInfo
    \libs
        DiskInfoLib ---    C++/WinRT层, 提供给UI层使用的磁盘信息(正在开发中)。
        DiskInfoTest ---       DiskInfoLib的测试库。
        MockDiskInfo ---        假的DiskInfoLib引用，提供给UI层进行界面测试使用。
    DiskInfo ---               C#/WinUI 3 项目，提供了DiskInfo的UI层.
```
### WinRT 层
`DiskInfoLib` 用Visual Studio的C++ Windows运行时组件项目模板创建，并添加了额外的宏定义和库路径。
为了能够在 C# 项目中使用(.NET6)，需要
- 添加 [cs/winrt](https://github.com/microsoft/cswinrt) 的 NuGet 包
- 在项目中添加该 WinRT 项目的引用，最后在`csproj`文件中加如下内容
```xml
<PropertyGroup>
    <CsWinRTIncludes>DiskInfoLibWinRT</CsWinRTIncludes>
    <CsWinRTGeneratedFilesDir>$(OutDir)</CsWinRTGeneratedFilesDir>
</PropertyGroup>
```


## 已知问题
- 在管理员权限下WinUI 3项目无法热更新Xaml和调试C++代码，为了开发方便，默认不以管理员权限运行。（在发布商店前会改成必须以管理员权限运行）
- 更多功能即将到来！

<details>
    <summary>技术栈和构建项目的开发环境要求</summary>

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
