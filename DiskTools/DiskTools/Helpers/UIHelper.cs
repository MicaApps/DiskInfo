using DiskInfo.Pages;
using Microsoft.UI.Windowing;
using System;
using System.Text;
using WinRT.Interop;

namespace DiskInfo.Helpers
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

        public static string ExceptionToMessage(this Exception ex)
        {
            StringBuilder builder = new StringBuilder();
            builder.Append('\n');
            if (!string.IsNullOrWhiteSpace(ex.Message)) { builder.AppendLine($"Message: {ex.Message}"); }
            builder.AppendLine($"HResult: {ex.HResult} (0x{Convert.ToString(ex.HResult, 16)})");
            if (!string.IsNullOrWhiteSpace(ex.StackTrace)) { builder.AppendLine(ex.StackTrace); }
            if (!string.IsNullOrWhiteSpace(ex.HelpLink)) { builder.Append($"HelperLink: {ex.HelpLink}"); }
            return builder.ToString();
        }
    }
}
