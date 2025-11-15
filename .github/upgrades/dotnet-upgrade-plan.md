# .NET 8.0 Upgrade Plan

## Execution Steps

Execute steps below sequentially one by one in the order they are listed.

1. Validate that an .NET 8.0 SDK required for this upgrade is installed on the machine and if not, help to get it installed.
2. Ensure that the SDK version specified in global.json files is compatible with the .NET 8.0 upgrade.
3. Upgrade DiskInfoLib\DiskInfoLibWinRT.vcxproj
4. Upgrade DiskInfoLib.Mock\DiskInfoLib.Mock.csproj
5. Upgrade DiskInfoLib.Test\DiskInfoTest.vcxproj
6. Upgrade DiskInfo\DiskInfo.csproj


## Settings

This section contains settings and data used by execution steps.

### Excluded projects

Table below contains projects that do belong to the dependency graph for selected projects and should not be included in the upgrade.

| Project name                                   | Description                 |
|:-----------------------------------------------|:---------------------------:|
| (none)                                         | No projects explicitly excluded |

### Aggregate NuGet packages modifications across all projects

NuGet packages used across all selected projects or their dependencies that need version update in projects that reference them.

| Package Name                         | Current Version     | New Version       | Description                                   |
|:-------------------------------------|:-------------------:|:-----------------:|:----------------------------------------------|
| CommunityToolkit.WinUI               | 7.1.2               |                   | No supported version for .NET 8 discovered; verify replacement or newer major version |
| CommunityToolkit.WinUI.UI            | 7.1.2               |                   | No supported version for .NET 8 discovered; verify replacement or newer major version |
| CommunityToolkit.WinUI.UI.Controls.Markdown | 7.1.2        |                   | No supported version for .NET 8 discovered; verify replacement or newer major version |
| Microsoft.WindowsAppSDK              | 1.2.230313.1        | 1.8.251003001     | Required Windows App SDK update for .NET 8 compatibility |
| Syncfusion.Chart.WinUI               | 20.4.0.54           |                   | No supported version for .NET 8 discovered; check Syncfusion for WinUI 3/.NET 8 support |
| Syncfusion.Gauge.WinUI               | 20.4.0.54           |                   | No supported version for .NET 8 discovered; check Syncfusion for WinUI 3/.NET 8 support |


### Project upgrade details

#### DiskInfoLib\DiskInfoLibWinRT.vcxproj modifications

Project properties changes:
  - Convert the project to an SDK-style project file if possible (ruleId Project.0001).
  - Ensure C++ project remains compatible with C++20 settings and C++/WinRT build targets.

NuGet packages changes:
  - Review and update any package references imported by this native project (CsWinRT build integration) as needed.

Feature upgrades:
  - Migrate any non-SDK MSBuild targets to SDK-style equivalents and update imported targets paths.

Other changes:
  - Ensure Generated CsWinRT files and the `CsWinRTIncludes` usage remain valid after conversion.

#### DiskInfoLib.Mock\DiskInfoLib.Mock.csproj modifications

Project properties changes:
  - Change Target Framework from `net6.0` to `net8.0` (ruleId Project.0002).

NuGet packages changes:
  - Verify compatibility of `MetroLog.Net6` (if referenced) with .NET 8 and replace if needed.

Other changes:
  - Rebuild and fix any API/assembly changes introduced by .NET 8.

#### DiskInfoLib.Test\DiskInfoTest.vcxproj modifications

Project properties changes:
  - Convert the C++ test project to SDK-style project if possible (ruleId Project.0001).

Other changes:
  - Ensure test runner / test adapter used for native tests is compatible with the upgraded toolchain.

#### DiskInfo\DiskInfo.csproj modifications

Project properties changes:
  - Change Target Framework from `net6.0-windows10.0.26100.0` to `net8.0-windows10.0.26100.0` (ruleId Project.0002).

NuGet packages changes:
  - Update `Microsoft.WindowsAppSDK` from `1.2.230313.1` to `1.8.251003001` as recommended by analysis.
  - Review `CommunityToolkit.WinUI`, `CommunityToolkit.WinUI.UI`, and `CommunityToolkit.WinUI.UI.Controls.Markdown` for .NET 8 compatible replacements or later major versions; analysis reported no supported versions found.
  - Review `Syncfusion.Chart.WinUI` and `Syncfusion.Gauge.WinUI` for .NET 8-compatible packages or replacements.

Feature upgrades:
  - Ensure WinUI and Windows App SDK integration is updated to match the newer package versions and any API changes.

Other changes:
  - Re-generate CsWinRT generated files in `obj` folder after project changes.



