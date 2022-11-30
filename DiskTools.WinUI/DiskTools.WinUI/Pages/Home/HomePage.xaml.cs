using Microsoft.UI.Xaml.Controls;
using DiskTools.WinUI.Navigation.Model;
using DiskTools.WinUI.Pages.Disk;

namespace DiskTools.WinUI.Pages.Home
{
    public sealed partial class HomePage : Page
    {

        private HomePageViewModel viewModel = new();

        public HomePage()
        {
            this.InitializeComponent();
        }


        private void NavigationView_SelectionChanged(NavigationView sender, NavigationViewSelectionChangedEventArgs args)
        {
            if (args.SelectedItem is DiskModel diskModel)
            {
                NavigationFrame.Navigate(typeof(DiskPage), diskModel);
            }
            else if (args.IsSettingsSelected)
            {
                //TODO Navigate Setting Page
            }
        }
    }
}
