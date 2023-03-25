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
        public List<DiskSmartInfoListItem> ListSMARTInfoDisplay { get; set; }


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

        private int m_id = 0;
        //Text="{x:Bind Info.TemperatureData, Con={StaticResource GetIListLastConverter}, ConverterParameter={Binding IsCelsius}}"
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            if (e.Parameter is int id)
            {
                RefreshData(DiskInfoService.Instance.Info[id]);
                m_id = id;
            }
        }

        private void RefreshButton_Click(object sender, Microsoft.UI.Xaml.RoutedEventArgs e)
        {
            DiskInfoService.Instance.Info[m_id].Update();
            RefreshData(DiskInfoService.Instance.Info[m_id]);
            TemperatureGraph.Collection = Info.TemperatureData;
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

            ListSMARTInfoDisplay = new List<DiskSmartInfoListItem>();
            ListSMARTInfoDisplay.Add(new DiskSmartInfoListItem("ID", "属性名称", "原始值", "临界值", "当前值", "最差值"));
            foreach (SmartAttribute item in Info.Attributes)
                ListSMARTInfoDisplay.Add(new DiskSmartInfoListItem(item.Id, item.Name, item.RawValue, item.Threshold, item.Current, item.Worst));

            OnPropertyChanged("List1");
            OnPropertyChanged("List2");
            OnPropertyChanged("ListSMARTInfoDisplay");
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
