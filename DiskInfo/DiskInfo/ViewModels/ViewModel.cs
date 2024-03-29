using DiskInfo.Helpers;
using DiskInfo.Services;
using System;

namespace DiskInfo
{
    public class ViewModel
    {
        public bool AsciiView
        {
            get => ViewModel.LibInstance.AsciiView;
            set
            {
                SettingsHelper.Set(SettingsHelper.AsciiView, value);
                ViewModel.LibInstance.AsciiView = value;
            }
        }
        public bool DumpSmartReadData
        {
            get => ViewModel.LibInstance.DumpSmartReadData;
            set
            {
                SettingsHelper.Set(SettingsHelper.DumpSmartReadData, value);
                ViewModel.LibInstance.DumpSmartReadData = value;
            }
        }

        public bool DumpSmartReadThreshold
        {
            get => ViewModel.LibInstance.DumpSmartReadThreshold;
            set
            {
                SettingsHelper.Set(SettingsHelper.DumpSmartReadThreshold, value);
                ViewModel.LibInstance.DumpSmartReadThreshold = value;
            }
        }

        public bool DumpIdentifyDevice
        {
            get => ViewModel.LibInstance.DumpIdentifyDevice;
            set
            {
                SettingsHelper.Set(SettingsHelper.DumpIdentifyDevice, value);
                ViewModel.LibInstance.DumpIdentifyDevice = value;
            }
        }

        static ViewModel()
        {
            ViewModel.LibInstance.AsciiView = SettingsHelper.Get<bool>(SettingsHelper.AsciiView);
            ViewModel.LibInstance.DumpSmartReadThreshold = SettingsHelper.Get<bool>(SettingsHelper.DumpSmartReadThreshold);
            ViewModel.LibInstance.DumpSmartReadData = SettingsHelper.Get<bool>(SettingsHelper.DumpSmartReadData);
            ViewModel.LibInstance.DumpIdentifyDevice = SettingsHelper.Get<bool>(SettingsHelper.DumpIdentifyDevice);
        }

        public static DiskInfoLibWinRT.Class LibInstance => DiskInfoService.Instance;

        private static readonly Lazy<ViewModel> lazy =
           new Lazy<ViewModel>(() => new ViewModel());

        public static ViewModel Instance { get { return lazy.Value; } }
    }
}