using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace DiskTools
{
    /// <summary>
    /// 封装对dll的引用
    /// </summary>
    internal static partial class Interop
    {
        [LibraryImport("DiskInfo.dll", StringMarshalling = StringMarshalling.Utf16)]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial IntPtr GetFirmware();

        [LibraryImport("DiskInfo.dll", StringMarshalling = StringMarshalling.Utf16)]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial int GetDriveNum();

        [LibraryImport("DiskInfo.dll", StringMarshalling = StringMarshalling.Utf16)]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial void AtaSmartInit(int useWmi, int advancedDiskSearch, ref int flagChangeDisk, int workaroundHD204UI, int workaroundAdataSsd, int flagHideNoSmartDisk);

        [LibraryImport("DiskInfo.dll", StringMarshalling = StringMarshalling.Utf16)]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial double GetDiskStatus();

        [LibraryImport("DiskInfo.dll", StringMarshalling = StringMarshalling.Utf16)]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial double GetCapacity();

        [LibraryImport("DiskInfo.dll", StringMarshalling = StringMarshalling.Utf16)]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial IntPtr GetAtaAtapi();

        [LibraryImport("DiskInfo.dll", StringMarshalling = StringMarshalling.Utf16)]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial IntPtr GetBufferSize();

        [LibraryImport("DiskInfo.dll", StringMarshalling = StringMarshalling.Utf16)]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial IntPtr GetFeature();

        [LibraryImport("DiskInfo.dll", StringMarshalling = StringMarshalling.Utf16)]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial IntPtr GetFirmwareRev();

        [LibraryImport("DiskInfo.dll", StringMarshalling = StringMarshalling.Utf16)]
        [UnmanagedCallConv(CallConvs = new[] { typeof(CallConvCdecl) })]
        public static partial IntPtr GetDriveMap();
    }
}
