using DiskTools.ViewModels;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;
using DiskInfoLibWinRT;
using Syncfusion.UI.Xaml.Gauges;
using DiskTools.Helpers;
using System;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskTools.Pages
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class DiskInfoPage : Page
    {
        
        public int ID;

        public DiskInfoLibWinRT.AtaSmartInfo Info;

        public DiskInfoPage() => InitializeComponent();

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            if (e.Parameter is string id)
            {
                ID = Int32.Parse(id);
            }
            Info = ViewModel.LibInstance.Info[0];
            OverviewPage.Id = ID;
        }

    }
}
