using DiskTools.ViewModels;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;
using DiskInfoLibWinRT;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskTools.Pages
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class DiskInfoPage : Page
    {
        public string ID = string.Empty;

        internal DiskInfoViewModel Provider;

        //public DiskInfo.DiskInfo info = new DiskInfo.DiskInfo();
        public DiskInfoLibWinRT.Class instance = new Class();

        public DiskInfoPage() => InitializeComponent();

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            if (e.Parameter is string id)
            {
                ID = id;
                Provider = new DiskInfoViewModel(id);
            }
            DataContext = Provider;
        }
    }
}
