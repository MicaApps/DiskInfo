using DiskInfoLibWinRT;
using DiskTools.Helpers;
using Microsoft.UI.Xaml.Media.Animation;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DiskTools.Services
{
    public class DiskInfoService
    {
        public static DiskInfoLibWinRT.Class Instance { get; set; }


        public static DiskInfoLibWinRT.Class GetInfo()
        {
            //return Mock();
            Instance = new Class();
            return Instance;
        }

        //private static Class Mock()
        //{
        //    var vm = new DiskInfoLibWinRT.Class();

        //    var info1 = new DiskInfoLibWinRT.AtaSmartInfo();
        //    info1.Firmware = "2BQEXM7";
        //    info1.SerialNumber = "S4EVNF0N402289K";
        //    info1.Interface = "NVM Express";
        //    info1.CurrentTransferMode = "PCIe 3.0 x4 | PCIe 3.0 x4";
        //    info1.DriveMap = "C:";
        //    info1.Features = "S.M.A.R.T";
        //    info1.Model = "Samsung SSD 860 EVO 250GB";
        //    info1.HostReads = 1234;
        //    info1.HostWrites = 5678;
        //    info1.Rotation = 0;
        //    info1.PowerOnCount = 1170;
        //    info1.PowerOnTime = 10886;
        //    info1.Standard = "NVM Express 1.3";

        //    info1.Attributes = new List<object>();
        //    //填充假attribute
        //    for (int i = 0; i < 15; ++i)
        //    {
        //        info1.Attributes.Add(
        //            new SmartAttribute()
        //            {
        //                Id = "01",
        //                Name = "Some attribute",
        //                RawValue = "000000000050",
        //                Threshold = "50"
        //            });
        //    }
        //    info1.Index = 0;

        //    //填充假temperature
        //    Random rd = new Random();
        //    info1.TemperatureData = new List<GraphDataPoint>();
        //    info1.PowerOnHoursData = new List<GraphDataPoint>();
        //    info1.GigabytesErasedData = new List<GraphDataPoint>();
        //    info1.PendingSectorData = new List<GraphDataPoint>();
        //    info1.PowerOnHoursData = new List<GraphDataPoint>();
        //    info1.PowerCycleData = new List<GraphDataPoint>();
        //    info1.ReallocatedSectorsData = new List<GraphDataPoint>();
        //    info1.TotalHostReadsData = new List<GraphDataPoint>();
        //    info1.TotalNandWritesData = new List<GraphDataPoint>();
        //    info1.UncorrectableSectorData = new List<GraphDataPoint>();
        //    info1.WearLevelingCountData = new List<GraphDataPoint>();
        //    for (int i = 0; i < 10; i++)
        //    {
        //        info1.TemperatureData.Add(new GraphDataPoint((ulong)(1674738232 + i * 4), (uint)rd.Next(40, 50)));
        //        info1.PowerOnHoursData.Add(new GraphDataPoint((ulong)(1674738232 + i * 4), (uint)rd.Next(40, 50)));
        //        info1.GigabytesErasedData.Add(new GraphDataPoint((ulong)(1674738232 + i * 4), (uint)rd.Next(40, 50)));
        //        info1.PendingSectorData.Add(new GraphDataPoint((ulong)(1674738232 + i * 4), (uint)rd.Next(40, 50)));
        //        info1.PowerOnHoursData.Add(new GraphDataPoint((ulong)(1674738232 + i * 4), (uint)rd.Next(40, 50)));
        //        info1.PowerCycleData.Add(new GraphDataPoint((ulong)(1674738232 + i * 4), (uint)rd.Next(40, 50)));
        //        info1.ReallocatedSectorsData.Add(new GraphDataPoint((ulong)(1674738232 + i * 4), (uint)rd.Next(40, 50)));
        //        info1.TotalHostReadsData.Add(new GraphDataPoint((ulong)(1674738232 + i * 4), (uint)rd.Next(40, 50)));
        //        info1.TotalNandWritesData.Add(new GraphDataPoint((ulong)(1674738232 + i * 4), (uint)rd.Next(40, 50)));
        //        info1.UncorrectableSectorData.Add(new GraphDataPoint((ulong)(1674738232 + i * 4), (uint)rd.Next(40, 50)));
        //        info1.WearLevelingCountData.Add(new GraphDataPoint((ulong)(1674738232 + i * 4), (uint)rd.Next(40, 50)));
        //    }


        //    var info2 = new DiskInfoLibWinRT.AtaSmartInfo();
        //    info2.Firmware = "ENKJHUV";
        //    info2.SerialNumber = "WIO@^HJEEEE";
        //    info2.Interface = "NVME;STAT";
        //    info2.CurrentTransferMode = "PCIe 4.0";
        //    info2.DriveMap = "D:";
        //    info2.Features = "S.M.A.R.T, TRIM";
        //    info2.Model = "ST4000VX005-2LY104 4000.7 GB";
        //    info2.HostReads = 44;
        //    info2.HostWrites = 55;
        //    info2.Rotation = 0;
        //    info2.PowerOnCount = 3435;
        //    info2.PowerOnTime = 12567;
        //    info2.Standard = "NVM Express 1.4";

        //    info2.Attributes = new List<object>();
        //    //填充假attribute
        //    for (int i = 0; i < 15; ++i)
        //    {
        //        info2.Attributes.Add(
        //            new SmartAttribute()
        //            {
        //                Id = "FF",
        //                Name = "Some attribute",
        //                RawValue = "f0000e040050",
        //                Threshold = "99"
        //            });
        //    }
        //    info2.Index = 0;

        //    //填充假temperature
        //    info2.TemperatureData = new List<GraphDataPoint>();
        //    info2.TemperatureData.Add(new GraphDataPoint(1674738230, 21));
        //    info2.TemperatureData.Add(new GraphDataPoint(1674738230, 21));


        //    vm.Info = new List<AtaSmartInfo>() { info1, info2 };
        //    vm.AsciiView = SettingsHelper.Get<bool>(SettingsHelper.AsciiView);
        //    vm.DumpSmartReadThreshold = SettingsHelper.Get<bool>(SettingsHelper.DumpSmartReadThreshold);
        //    vm.DumpSmartReadData = SettingsHelper.Get<bool>(SettingsHelper.DumpSmartReadData);
        //    vm.DumpIdentifyDevice = SettingsHelper.Get<bool>(SettingsHelper.DumpIdentifyDevice);

        //    return Instance = vm;
        //}
    }
}
