using DiskInfo.Helpers;
using Microsoft.UI;
using Microsoft.UI.Xaml;
using System.IO;
using Windows.ApplicationModel;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskInfo
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainWindow : Window
    {
        public BackdropHelper Backdrop;

        public MainWindow()
        {
            UIHelper.MainWindow = this;
            Backdrop = new BackdropHelper(this);
            InitializeComponent();
            SetBackdrop();
            this.GetAppWindowForCurrentWindow().SetIcon("Assets/window_icon.ico");
        }

        private void SetBackdrop()
        {
            BackdropType type = SettingsHelper.Get<BackdropType>(SettingsHelper.SelectedBackdrop);
            Backdrop.SetBackdrop(type);
        }
    }
}
