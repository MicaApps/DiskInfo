using DiskInfo.Helpers;
using DiskInfo.Services;
using DiskInfo.ViewModels;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Windows.ApplicationModel.Resources;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskInfo.Pages
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class DiskInfoPage : Page, INotifyPropertyChanged, ITimerUpdatable
    {
        public int ID;
        public DiskInfoLibWinRT.AtaSmartInfo Info { get; set; }
        public List<DiskInfoPageListItem> NaviList { get; set; }
        private int backdropIndex;
        private readonly ResourceLoader _loader = ResourceLoader.GetForViewIndependentUse("DiskInfoPage");

        public int BackdropIndex
        {
            get { return backdropIndex; }
            set
            {
                backdropIndex = value;
                OnPropertyChanged();
            }
        }

        public DiskInfoPage()
        {
            InitializeComponent();
            this.DataContext = this;

        }

        private void Backdrop_BackdropTypeChanged(BackdropHelper sender, object args)
        {
            UpdateBackdropIndex();
        }

        private void UpdateBackdropIndex()
        {
            switch (UIHelper.MainWindow.Backdrop.Backdrop)
            {
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
                AutoUpdater.Instance.CurrentPage = this;
                ((ITimerUpdatable)this).update();
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
            if (item.Name == _loader.GetString("Disk_Overview/Content"))
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

        private void Page_Unloaded(object sender, Microsoft.UI.Xaml.RoutedEventArgs e)
        {
            UIHelper.MainWindow.Backdrop.BackdropTypeChanged -= Backdrop_BackdropTypeChanged;
        }

        void ITimerUpdatable.update()
        {
            NaviList = new List<DiskInfoPageListItem>();
            NaviList.Add(new DiskInfoPageListItem(_loader.GetString("Disk_Overview/Content"), null));
            NaviList.Add(new DiskInfoPageListItem(_loader.GetString("Disk_Reallocated_Sectors_Count/Content"), Info.ReallocatedSectorsData));
            NaviList.Add(new DiskInfoPageListItem(_loader.GetString("Disk_Power_On_Hours/Content"), Info.PowerOnHoursData));
            NaviList.Add(new DiskInfoPageListItem(_loader.GetString("Disk_Power_Cycle_Count/Content"), Info.PowerCycleData));
            NaviList.Add(new DiskInfoPageListItem(_loader.GetString("Disk_Temperature/Content"), Info.TemperatureData));
            NaviList.Add(new DiskInfoPageListItem(_loader.GetString("Disk_Reallocation_Event_Count/Content"), Info.ReallocationEventData));
            NaviList.Add(new DiskInfoPageListItem(_loader.GetString("Disk_Current_Pending_Sector_Count/Content"), Info.PendingSectorData));
            NaviList.Add(new DiskInfoPageListItem(_loader.GetString("Disk_Uncorrectable_Sector_Count/Content"), Info.UncorrectableSectorData));
            NaviList.Add(new DiskInfoPageListItem(_loader.GetString("Disk_Total_NAND_Writes/Content"), Info.TotalNandWritesData));
            NaviList.Add(new DiskInfoPageListItem(_loader.GetString("Disk_Wear_Leveling_Count/Content"), Info.WearLevelingCountData));
            NaviList.Add(new DiskInfoPageListItem(_loader.GetString("Disk_Remaining_Life/Content"), Info.RemainingLifeData));
            NaviList.Add(new DiskInfoPageListItem(_loader.GetString("Disk_Gigabytes_Erased/Content"), Info.GigabytesErasedData));
            NaviList.Add(new DiskInfoPageListItem(_loader.GetString("Disk_Total_Host_Reads/Content"), Info.TotalHostReadsData));
            NaviList.Add(new DiskInfoPageListItem(_loader.GetString("Disk_Total_Host_Writes/Content"), Info.TotalHostWritesData));
            NaviListView.SelectedIndex = 0;

            OnPropertyChanged("NaviList");
            if (DetailFrame.Content is OverviewPage page && page != null)
                page.RefreshData(Info);
        }
    }
}
