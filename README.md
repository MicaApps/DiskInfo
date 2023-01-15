#  ![Frame 30284 (自定义)](https://user-images.githubusercontent.com/6630660/207081052-89642cf8-6a84-456d-9c96-e2db354ff3d6.png) DiskInfo

Aim at providing a mordern appearance for DiskInfo

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
