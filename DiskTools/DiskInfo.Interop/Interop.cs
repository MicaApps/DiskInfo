using System.Runtime.InteropServices;

namespace DiskTools
{
    /// <summary>
    /// 封装对dll的引用
    /// </summary>
    internal static class Interop
    {

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public extern static IntPtr GetFirmware();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public extern static int GetDriveNum();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public extern static void AtaSmartInit(int useWmi, int advancedDiskSearch, ref int flagChangeDisk, int workaroundHD204UI, int workaroundAdataSsd, int flagHideNoSmartDisk);

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public extern static double GetDiskStatus();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public extern static double GetCapacity();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public extern static IntPtr GetAtaAtapi();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public extern static IntPtr GetBufferSize();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public extern static IntPtr GetFeature();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public extern static IntPtr GetFirmwareRev();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public extern static IntPtr GetDriveMap();
    }
}
