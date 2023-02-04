using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DiskInfoLibWinRT;
using DiskTools.Helpers;

namespace DiskTools
{
    public class GraphDataTimePoint
    {
        public DateTime XValue { get; set; }
        public UInt32 YValue { get; set; }
        public GraphDataTimePoint(DiskInfoLibWinRT.GraphDataPoint graphDataPoint)
        {
            XValue = DateTimeOffset.FromUnixTimeSeconds((long)graphDataPoint.XValue).LocalDateTime;
            YValue = graphDataPoint.YValue;
        }
    }
    //public class ViewModel
    //{
    //    public IList<GraphDataTimePoint> Collection
    //    {
    //        get
    //        {
    //            var list = new List<GraphDataTimePoint>();
    //                list.Add(new GraphDataTimePoint(new GraphDataPoint(1674738230, 21)));
    //                list.Add(new GraphDataTimePoint(new GraphDataPoint(1674746492, 22)));
    //                return list;
    //        }
    //    }

    //    public bool AsciiView
    //    {
    //        get => ViewModel.LibInstance.AsciiView;
    //        set
    //        {
    //            SettingsHelper.Set(SettingsHelper.AsciiView, value);
    //            ViewModel.LibInstance.AsciiView = value;
    //        }
    //    }
    //    public bool DumpSmartReadData
    //    {
    //        get => ViewModel.LibInstance.DumpSmartReadData;
    //        set
    //        {
    //            SettingsHelper.Set(SettingsHelper.DumpSmartReadData, value);
    //            ViewModel.LibInstance.DumpSmartReadData = value;
    //        }
    //    }

    //    public bool DumpSmartReadThreshold
    //    {
    //        get => ViewModel.LibInstance.DumpSmartReadThreshold;
    //        set
    //        {
    //            SettingsHelper.Set(SettingsHelper.DumpSmartReadThreshold, value);
    //            ViewModel.LibInstance.DumpSmartReadThreshold = value;
    //        }
    //    }

    //    public bool DumpIdentifyDevice
    //    {
    //        get => ViewModel.LibInstance.DumpIdentifyDevice;
    //        set
    //        {
    //            SettingsHelper.Set(SettingsHelper.DumpIdentifyDevice, value);
    //            ViewModel.LibInstance.DumpIdentifyDevice = value;
    //        }
    //    }

    //    public ViewModel()
    //    {
    //        if (ViewModel.LibInstance.Info.Count == 0)
    //        {
    //            //无管理员权限时的示例数据
    //            var info = new DiskInfoLibWinRT.AtaSmartInfo();
    //            info.Firmware = "2BQEXM7";
    //            info.SerialNumber = "S4EVNF0N402289K";
    //            info.Interface = "NVM Express";
    //            info.CurrentTransferMode = "PCIe 3.0 x4 | PCIe 3.0 x4";
    //            info.DriveMap = "C:";
    //            info.Features = "S.M.A.R.T";
    //            info.HostReads = 1234;
    //            info.HostWrites = 5678;
    //            info.Rotation = 0;
    //            info.PowerOnCount = 1170;
    //            info.PowerOnTime = 10886;
    //            info.Standard = "NVM Express 1.3";

    //            //填充假attribute
    //            for (int i = 0; i < 15; ++i)
    //            {
    //                info.Attributes.Add(
    //                    new SmartAttribute()
    //                    {
    //                        Id = "01",
    //                        Name = "Some attribute",
    //                        RawValue = "000000000050",
    //                        Threshold = "50"
    //                    });
    //            }
    //            info.Index = 0;

    //            //填充假temperature
    //            info.TemperatureData.Add(new GraphDataPoint(1674738230, 21));
    //            info.TemperatureData.Add(new GraphDataPoint(1674738230, 21));
    //            LibInstance.Info.Add(info);
    //        }
    //        ViewModel.LibInstance.AsciiView = SettingsHelper.Get<bool>(SettingsHelper.AsciiView);
    //        ViewModel.LibInstance.DumpSmartReadThreshold = SettingsHelper.Get<bool>(SettingsHelper.DumpSmartReadThreshold);
    //        ViewModel.LibInstance.DumpSmartReadData = SettingsHelper.Get<bool>(SettingsHelper.DumpSmartReadData);
    //        ViewModel.LibInstance.DumpIdentifyDevice = SettingsHelper.Get<bool>(SettingsHelper.DumpIdentifyDevice);
    //    }

    //    public static DiskInfoLibWinRT.Class LibInstance = new Class();
    //}
}