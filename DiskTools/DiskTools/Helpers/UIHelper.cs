using DiskTools.Pages;
using Microsoft.UI.Windowing;
using System;
using WinRT.Interop;

namespace DiskTools.Helpers
{
    public static class UIHelper
    {
        public static bool HasTitleBar = !AppWindowTitleBar.IsCustomizationSupported();
        public static bool TitleBarExtended => HasTitleBar ? MainWindow.ExtendsContentIntoTitleBar : WindowHelper.GetAppWindowForCurrentWindow().TitleBar.ExtendsContentIntoTitleBar;

        public static MainPage MainPage;
        public static MainWindow MainWindow;

        public static int GetActualPixel(this double pixel)
        {
            IntPtr windowHandle = WindowNative.GetWindowHandle(MainWindow);
            int currentDpi = PInvoke.User32.GetDpiForWindow(windowHandle);
            return Convert.ToInt32(pixel * (currentDpi / 96.0));
        }
    }
}
