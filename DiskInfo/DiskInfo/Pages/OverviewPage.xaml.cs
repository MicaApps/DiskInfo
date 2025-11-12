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
using Windows.ApplicationModel.Resources;

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
        private readonly ResourceLoader _loader = ResourceLoader.GetForViewIndependentUse("DiskInfoPage");
        
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
            
            List1.Add(new DiskBasicInfoListItem("\xEEA1", _loader.GetString("Overview_Firmware"), Info.Firmware));
            List1.Add(new DiskBasicInfoListItem("\xEE6F", _loader.GetString("Overview_SerialNumber"), Info.SerialNumber));
            List1.Add(new DiskBasicInfoListItem("\xF404", _loader.GetString("Overview_Interface"), Info.Interface));
            List1.Add(new DiskBasicInfoListItem("\xE8CB", _loader.GetString("Overview_TransferMode"), Info.CurrentTransferMode));
            List1.Add(new DiskBasicInfoListItem("\xEDA2", _loader.GetString("Overview_DriveMap"), Info.DriveMap));
            List1.Add(new DiskBasicInfoListItem("\xEEA1", _loader.GetString("Overview_HostReads"), ReadableBytesConverter.Convert(Info.HostReads, null, null, null).ToString()));
            List1.Add(new DiskBasicInfoListItem("\xE104", _loader.GetString("Overview_HostWrites"), ReadableBytesConverter.Convert(Info.HostWrites, null, null, null).ToString()));
            List1.Add(new DiskBasicInfoListItem("\xE14A", _loader.GetString("Overview_Rotation"), ReadableRotationConverter.Convert(Info.Rotation, null, null, null).ToString()));
            List1.Add(new DiskBasicInfoListItem("\xE945", _loader.GetString("Overview_PowerOnCount"), ReadableCountConverter.Convert(Info.PowerOnCount, null, null, null).ToString()));
            List1.Add(new DiskBasicInfoListItem("\xE121", _loader.GetString("Overview_PowerOnTime"), ReadableTimeConverter.Convert(Info.PowerOnTime, null, null, null).ToString()));
            List1.Add(new DiskBasicInfoListItem("\xE74C", _loader.GetString("Overview_Features"), Info.Features));
            List1.Add(new DiskBasicInfoListItem("\xEEA1", _loader.GetString("Overview_Standard"), Info.Standard));

            ListSMARTInfoDisplay = new List<DiskSmartInfoListItem>();
            ListSMARTInfoDisplay.Add(new DiskSmartInfoListItem(_loader.GetString("SMART_ID"), _loader.GetString("SMART_AttributeName"), _loader.GetString("SMART_RawValue"), _loader.GetString("SMART_Threshold"), _loader.GetString("SMART_CurrentValue"), _loader.GetString("SMART_WorstValue")));
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
