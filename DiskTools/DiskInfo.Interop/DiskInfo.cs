using DiskTools;
using System.Runtime.InteropServices;

namespace DiskInfo
{
    public class DiskInfo
    {
        public event Action<bool> Initialized;

        public DiskInfo()
        {
            int flag = 0;
            Interop.AtaSmartInit(1, 0, ref flag, 0, 1, 0);
            Initialized?.Invoke(flag == 1);
        }

        public int GetDriveNum() => Interop.GetDriveNum();

        public string GetFirmware()
        {
            IntPtr outPtr = Interop.GetFirmware();
            return Marshal.PtrToStringUni(outPtr);
        }

        public string Firmware
        {
            get=>GetFirmware();
        }

        public double GetDiskStatus() => Interop.GetDiskStatus();

        public double GetCapacity() => Interop.GetCapacity();

        public string GetAtaAtapi()
        {
            IntPtr ptr = Interop.GetAtaAtapi();
            return Marshal.PtrToStringUni(ptr);
        }

        public string GetBufferSize()
        {
            IntPtr intptr = Interop.GetBufferSize();
            return Marshal.PtrToStringUni(intptr);

        }

        public string GetFeature()
        {
            IntPtr intptr = Interop.GetFeature();
            return Marshal.PtrToStringUni(intptr);
        }

        public string GetFirmwareRev()
        {
            IntPtr intptr = Interop.GetFirmwareRev();
            return Marshal.PtrToStringUni(intptr);
        }

        public string GetDriveMap()
        {
            IntPtr intptr = Interop.GetDriveMap();
            return Marshal.PtrToStringUni(intptr);
        }
    }
}
