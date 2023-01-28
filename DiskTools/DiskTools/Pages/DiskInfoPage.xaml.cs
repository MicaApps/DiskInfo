using DiskTools.ViewModels;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;
using DiskInfoLibWinRT;
using Syncfusion.UI.Xaml.Gauges;

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
            get
            {
                if (ViewModel.LibInstance.Info.Count == 0)
                {
                    //无管理员权限时的示例数据
                    var info = new DiskInfoLibWinRT.AtaSmartInfo();
                    info.Firmware = "2BQEXM7";
                    info.SerialNumber = "S4EVNF0N402289K";
                    info.Interface = "NVM Express";
                    info.CurrentTransferMode = "PCIe 3.0 x4 | PCIe 3.0 x4";
                    info.DriveMap = "C:";
                    info.Features = "S.M.A.R.T";
                    info.HostReads = 1234;
                    info.HostWrites = 5678;
                    info.Rotation = 0;
                    info.PowerOnCount = 1170;
                    info.PowerOnTime = 10886;
                    info.Standard = "NVM Express 1.3";

                    //填充假attribute
                    for (int i = 0; i<15; ++i)
                    {
                        info.Attributes.Add(
                            new SmartAttribute()
                            {
                                Id = "01",
                                Name = "Some attribute",
                                RawValue = "000000000050",
                                Threshold = "50"
                            });
                    }
                    return info;
                }
                else
                    return ViewModel.LibInstance.Info[0];
            }
        }

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
    }
}
