using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace DiskTools
{
    /// <summary>
    /// 封装对dll的引用
    /// </summary>
    internal static partial class Interop
    {
        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetFirmware();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetDriveNum();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern void AtaSmartInit(int useWmi, int advancedDiskSearch, ref int flagChangeDisk, int workaroundHD204UI, int workaroundAdataSsd, int flagHideNoSmartDisk);

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern double GetDiskStatus();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern double GetCapacity();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetAtaAtapi();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetBufferSize();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetFeature();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetFirmwareRev();

        [DllImport("DiskInfo.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetDriveMap();
    }
}
