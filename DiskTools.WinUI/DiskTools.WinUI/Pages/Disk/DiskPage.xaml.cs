using DiskTools.WinUI.Navigation.Model;
using DiskTools.WinUI.Pages.Disk.Detail;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;

namespace DiskTools.WinUI.Pages.Disk
{
    public sealed partial class DiskPage : Page
    {
        private DiskPageViewModel viewModel = new();
        public DiskPage()
        {
            this.InitializeComponent();
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            if (e.Parameter is DiskModel diskModel)
            {
                viewModel.DiskModel= diskModel;
            }
        }

        private void ListView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (ItemList.SelectedItem is ListViewItem item && item.Content is string content && viewModel.DiskModel != null)
            {
                switch(content)
                {
                    case "Overview":
                        DiskInfoContent.Navigate(typeof(OverviewPage), viewModel.DiskModel);
                        break;

                }
            }
        }
    }
}
