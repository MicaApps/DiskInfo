using Microsoft.UI;
using Microsoft.UI.Xaml;
using WinUIEx;

namespace DiskTools.WinUI.Windowing
{
    public partial class BaseWindow : WindowEx
    {
        public BaseWindow()
        {

            Backdrop = new MicaSystemBackdrop();

        }

        protected void UpdateCaptionBar(ElementTheme theme)
        {
            var titleBar = AppWindow.TitleBar;
            if (titleBar != null)
            {
                titleBar.BackgroundColor = Colors.Transparent;
                titleBar.ButtonBackgroundColor = Colors.Transparent;
                titleBar.ButtonInactiveBackgroundColor = Colors.Transparent;

                if (theme == ElementTheme.Light)
                {
                    titleBar.ButtonForegroundColor = Colors.Black;
                    titleBar.ButtonHoverForegroundColor = Colors.Black;
                    titleBar.ButtonHoverBackgroundColor = ColorHelper.FromArgb(10, 00, 00, 00);
                    titleBar.ButtonPressedForegroundColor = ColorHelper.FromArgb(155, 00, 00, 00);
                    titleBar.ButtonPressedBackgroundColor = ColorHelper.FromArgb(6, 00, 00, 00);
                }
                else if (theme == ElementTheme.Dark)
                {
                    titleBar.ButtonForegroundColor = Colors.White;
                    titleBar.ButtonHoverForegroundColor = Colors.White;
                    titleBar.ButtonHoverBackgroundColor = ColorHelper.FromArgb(15, 255, 255, 255);
                    titleBar.ButtonPressedForegroundColor = Colors.White;
                    titleBar.ButtonPressedBackgroundColor = ColorHelper.FromArgb(10, 255, 255, 255);
                }
            }
        }
    }
}
