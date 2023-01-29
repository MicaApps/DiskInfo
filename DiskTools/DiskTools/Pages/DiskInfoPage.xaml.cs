using DiskTools.ViewModels;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;
using DiskInfoLibWinRT;
using Syncfusion.UI.Xaml.Gauges;
using DiskTools.Helpers;

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
        public DiskInfoLibWinRT.AtaSmartInfo Info
        {
            get => ViewModel.LibInstance.Info[0];
        }

        public ViewModel ViewModel { get => viewModel; }
        private ViewModel viewModel = new ViewModel();

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

        private void AppBarButton_Click(object sender, Microsoft.UI.Xaml.RoutedEventArgs e)
        {
            ViewModel.LibInstance.UpdateAll();
        }

        private void SplitButton_Click(SplitButton sender, SplitButtonClickEventArgs args)
        {
            ViewModel.LibInstance.SaveText("");
        }
    }
}
