using DiskInfo.Converters;
using DiskInfo.Services;
using DiskInfo.ViewModels;
using DiskInfoLibWinRT;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Navigation;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace DiskInfo.Pages
{
    public partial class OverviewPage : Page, INotifyPropertyChanged
    {
        public ViewModel ViewModel => ViewModel.Instance;
        public AtaSmartInfo Info { get; set; }
        public List<DiskBasicInfoListItem> List1 { get; set; }
        public List<DiskBasicInfoListItem> List2 { get; set; }
        public List<DiskSmartInfoListItem> List3 { get; set; }


        public static bool IsCelsius { get; set; } = true;

        private static IValueConverter ReadableBytesConverter = new ReadableBytesConverter();
        private static IValueConverter ReadableCountConverter = new ReadableCountConverter();
        private static IValueConverter ReadableRotationConverter = new ReadableRotationConverter();
        private static IValueConverter ReadableTimeConverter = new ReadableTimeConverter();
        public OverviewPage()
        {
            InitializeComponent();
            this.DataContext = this;
        }
        //Text="{x:Bind Info.TemperatureData, Con={StaticResource GetIListLastConverter}, ConverterParameter={Binding IsCelsius}}"
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            if (e.Parameter is int id)
            {
                RefreshData(DiskInfoService.Instance.Info[id]);
            }
        }

        private void RefreshButton_Click(object sender, Microsoft.UI.Xaml.RoutedEventArgs e)
        {
            DiskInfoService.Instance.UpdateAll();
        }

        private void SplitCopyContentButton_Click(SplitButton sender, SplitButtonClickEventArgs args)
        {
            DiskInfoService.Instance.SaveText("");
        }

        public void RefreshData(AtaSmartInfo info)
        {
            this.Info = info;
            List1 = new List<DiskBasicInfoListItem>();
            List2 = new List<DiskBasicInfoListItem>();
            List3 = new List<DiskSmartInfoListItem>();
            List1.Add(new DiskBasicInfoListItem("\xEEA1", "固件", Info.Firmware));
            List1.Add(new DiskBasicInfoListItem("\xEE6F", "序列号", Info.SerialNumber));
            List1.Add(new DiskBasicInfoListItem("\xF404", "接口", Info.Interface));
            List1.Add(new DiskBasicInfoListItem("\xE8CB", "传输模式", Info.CurrentTransferMode));
            List1.Add(new DiskBasicInfoListItem("\xEDA2", "驱动器号", Info.DriveMap));
            List1.Add(new DiskBasicInfoListItem("\xEEA1", "主机总计读取", ReadableBytesConverter.Convert(Info.HostReads, null, null, null).ToString()));
            List1.Add(new DiskBasicInfoListItem("\xE104", "主机总计写入", ReadableBytesConverter.Convert(Info.HostWrites, null, null, null).ToString()));
            List1.Add(new DiskBasicInfoListItem("\xE14A", "转速", ReadableRotationConverter.Convert(Info.Rotation, null, null, null).ToString()));
            List1.Add(new DiskBasicInfoListItem("\xE945", "通电次数", ReadableCountConverter.Convert(Info.PowerOnCount, null, null, null).ToString()));
            List1.Add(new DiskBasicInfoListItem("\xE121", "通电时间", ReadableTimeConverter.Convert(Info.PowerOnTime, null, null, null).ToString()));
            List1.Add(new DiskBasicInfoListItem("\xE74C", "支持的功能", Info.Features));
            List1.Add(new DiskBasicInfoListItem("\xEEA1", "标准", Info.Standard));

            foreach (SmartAttribute item in Info.Attributes)
                List3.Add(new DiskSmartInfoListItem(item.Id, item.Name, item.RawValue, item.Threshold));

            OnPropertyChanged("List1");
            OnPropertyChanged("List2");
            OnPropertyChanged("List3");
            OnPropertyChanged("Info");
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

        private void TextBlock_Tapped(object sender, Microsoft.UI.Xaml.Input.TappedRoutedEventArgs e)
        {
            IsCelsius = !IsCelsius;
            OnPropertyChanged("Info");
        }
    }
}
