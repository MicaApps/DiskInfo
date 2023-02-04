using DiskTools.ViewModels;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;
using DiskInfoLibWinRT;
using Syncfusion.UI.Xaml.Gauges;
using DiskTools.Helpers;
using System;
using DiskTools.Services;
using System.ComponentModel;
using System.Runtime.CompilerServices;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskTools.Pages
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class DiskInfoPage : Page, INotifyPropertyChanged
    {
        public int ID;

        public DiskInfoLibWinRT.AtaSmartInfo Info { get; set; }

        public DiskInfoPage()
        {
            InitializeComponent();
            this.DataContext = this;
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            if (e.Parameter is string id)
            {
                ID = Int32.Parse(id);
                Info = DiskInfoService.Instance.Info[ID];
                OnPropertyChanged("Info");
                if (DetailFrame.Content is OverviewPage page && page != null)
                    page.RefreshData(Info);
            }
        }

        private void Page_Loaded(object sender, Microsoft.UI.Xaml.RoutedEventArgs e)
        {
            DetailFrame.Navigate(typeof(OverviewPage), ID);
        }

        #region INotifyPropertyChanged members

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChangedEventHandler handler = this.PropertyChanged;
            if (handler != null)
            {
                var e = new PropertyChangedEventArgs(propertyName);
                handler(this, e);
            }
        }

        #endregion
    }
}
