using DiskInfo.ViewModels;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;
using DiskInfoLibWinRT;
using Syncfusion.UI.Xaml.Gauges;
using DiskInfo.Helpers;
using System;
using DiskInfo.Services;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using DiskInfo.Controls;
using Windows.Media.Playback;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskInfo.Pages
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class DiskInfoPage : Page, INotifyPropertyChanged
    {
        public int ID;
        public DiskInfoLibWinRT.AtaSmartInfo Info { get; set; }
        public List<DiskInfoPageListItem> NaviList { get; set; }
        private int backdropIndex;

        public int BackdropIndex {
            get { return backdropIndex; }
            set { 
                backdropIndex = value;
                OnPropertyChanged();
            }
        }

        public DiskInfoPage()
        {
            InitializeComponent();
            this.DataContext = this;
            
        }

        private void Backdrop_BackdropTypeChanged(BackdropHelper sender, object args) {
            UpdateBackdropIndex();
        }

        private void UpdateBackdropIndex() {
            switch(UIHelper.MainWindow.Backdrop.Backdrop) {
                case BackdropType.Mica:
                    BackdropIndex = 0;
                    break;
                case BackdropType.MicaAlt:
                    BackdropIndex = 0;
                    break;
                case BackdropType.DesktopAcrylic:
                    BackdropIndex = 1;
                    break;
                case BackdropType.DefaultColor:
                    BackdropIndex = 2;
                    break;
                default:
                    BackdropIndex = 2;
                    break;
            }
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            if (e.Parameter is string id)
            {
                ID = Int32.Parse(id);
                Info = DiskInfoService.Instance.Info[ID];
                NaviList = new List<DiskInfoPageListItem>();
                NaviList.Add(new DiskInfoPageListItem("概述", null));
                NaviList.Add(new DiskInfoPageListItem("[05] 重新分配扇区数", Info.ReallocatedSectorsData));
                NaviList.Add(new DiskInfoPageListItem("[09] 通电时间", Info.PowerOnHoursData));
                NaviList.Add(new DiskInfoPageListItem("[0C] 通电次数", Info.PowerCycleData));
                NaviList.Add(new DiskInfoPageListItem("[C2] 温度", Info.TemperatureData));
                NaviList.Add(new DiskInfoPageListItem("[C4] 扇区物理位置重分配时间计数（与坏道相关）", Info.ReallocationEventData));
                NaviList.Add(new DiskInfoPageListItem("[C5] 有待处置扇区数（状态存疑 - 需保持关注）", Info.PendingSectorData));
                NaviList.Add(new DiskInfoPageListItem("[C6] 不可校正的扇区数", Info.UncorrectableSectorData));
                NaviList.Add(new DiskInfoPageListItem("[XX] NAND总计写入（GB）", Info.TotalNandWritesData));
                NaviList.Add(new DiskInfoPageListItem("[XX] 平均磨损计数", Info.WearLevelingCountData));
                NaviList.Add(new DiskInfoPageListItem("[XX] 剩余寿命", Info.RemainingLifeData));
                NaviList.Add(new DiskInfoPageListItem("[XX] 已擦除GiB（GB）", Info.GigabytesErasedData));
                NaviList.Add(new DiskInfoPageListItem("[XX] 主机总计读取（GB）", Info.TotalHostReadsData));
                NaviList.Add(new DiskInfoPageListItem("[XX] 主机总计写入（GB）", Info.TotalHostWritesData));
                NaviListView.SelectedIndex = 0;

                OnPropertyChanged("Info");
                OnPropertyChanged("NaviList");
                if (DetailFrame.Content is OverviewPage page && page != null)
                    page.RefreshData(Info);
                //Todo: GraphPage 的数据更新通知
            }
        }

        private void Page_Loaded(object sender, Microsoft.UI.Xaml.RoutedEventArgs e)
        {
            UIHelper.MainWindow.Backdrop.BackdropTypeChanged -= Backdrop_BackdropTypeChanged;
            UIHelper.MainWindow.Backdrop.BackdropTypeChanged += Backdrop_BackdropTypeChanged;
            UpdateBackdropIndex();
        }

        private void ListView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var item = (DiskInfoPageListItem)NaviListView.SelectedItem;
            if (item == null)
                return;
            if (item.Name == "概述")
                DetailFrame.Navigate(typeof(OverviewPage), ID);
            else
                DetailFrame.Navigate(typeof(GraphPage), item.Data);
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

        private void Page_Unloaded(object sender, Microsoft.UI.Xaml.RoutedEventArgs e) {
            UIHelper.MainWindow.Backdrop.BackdropTypeChanged -= Backdrop_BackdropTypeChanged;
        }
    }
}
