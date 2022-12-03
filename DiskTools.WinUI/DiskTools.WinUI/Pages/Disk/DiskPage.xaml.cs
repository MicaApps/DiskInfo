using DiskTools.WinUI.Navigation.Model;
using DiskTools.WinUI.Pages.Disk.Detail;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;

namespace DiskTools.WinUI.Pages.Disk
{
    public sealed partial class DiskPage : Page
    {
        private DiskPageViewModel VM
        {
            get;
        }
        public DiskPage()
        {
            this.VM = App.GetService<DiskPageViewModel>();  
            this.InitializeComponent();

        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            if (e.Parameter is DiskModel diskModel)
            {
                VM.DiskModel= diskModel;
            }
        }

        private void ListView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (ItemList.SelectedItem is ListViewItem item && item.Content is string content && VM.DiskModel != null)
            {
                switch(content)
                {
                    case "Overview":
                        DiskInfoContent.Navigate(typeof(OverviewPage), VM.DiskModel);
                        break;

                }
            }
        }
    }
}
