using DiskTools.WinUI.Windowing;
using Microsoft.UI.Windowing;

namespace DiskTools.WinUI
{

    public sealed partial class MainWindow : BaseWindow
    {

        public MainWindow()
        {
            this.InitializeComponent();

            //Setup title bar
            var titleBar = AppWindow.TitleBar;
            titleBar.ExtendsContentIntoTitleBar = true;

            UpdateCaptionBar(Container.ActualTheme);
            Container.ActualThemeChanged += (sender, args) =>
            {
                UpdateCaptionBar(Container.ActualTheme);
            };
        }

        
    }
}
