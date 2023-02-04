using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq.Expressions;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;


namespace DiskInfoLibWinRT
{
    public class AtaSmartInfo
    {
        public AtaSmartInfo()
        {

        }

        public void Update()
        {

        }

        public System.Collections.Generic.IList<object> Attributes { get; set; }

        public string CurrentTransferMode { get; set; }

        public string DriveMap { get; set; }

        public string Features { get; set; }

        public string Firmware { get; set; }

        public int HostReads { get; set; }

        public int HostWrites { get; set; }

        public int Index { get; set; }

        public string Interface { get; set; }

        public string Model { get; set; }

        public uint PowerOnCount { get; set; }

        public uint PowerOnTime { get; set; }

        public int Rotation { get; set; }

        public string SerialNumber { get; set; }

        public string Standard { get; set; }

        public System.Collections.Generic.IList<GraphDataPoint> TemperatureData { get; set; }

    }


    public class Class
    {
        public Class()
        {

        }


        public void UpdateAll()
        {

        }

        public void SaveText(string fileName)
        {

        }

        public bool AsciiView { get; set; }
        public bool DumpIdentifyDevice { get; set; }
        public bool DumpSmartReadData { get; set; }
        public bool DumpSmartReadThreshold { get; set; }

        public System.Collections.Generic.IList<AtaSmartInfo> Info { get; set; }
    }


    public class GraphDataPoint
    {
        public GraphDataPoint(ulong xValue, uint yValue)
        {
            XValue = DateTimeOffset.FromUnixTimeSeconds((long)xValue);
            YValue = yValue;
        }


        public DateTimeOffset XValue { get; set; }
        public uint YValue { get; set; }
    }

    public interface IAtaSmartInfo
    {
        void Update();
        global::System.Collections.Generic.IList<object> Attributes { get; }
        string CurrentTransferMode { get; set; }
        string DriveMap { get; set; }
        string Features { get; set; }
        string Firmware { get; set; }
        int HostReads { get; set; }
        int HostWrites { get; set; }
        int Index { get; set; }
        string Interface { get; set; }
        string Model { get; set; }
        uint PowerOnCount { get; set; }
        uint PowerOnTime { get; set; }
        int Rotation { get; set; }
        string SerialNumber { get; set; }
        string Standard { get; set; }
        global::System.Collections.Generic.IList<GraphDataPoint> TemperatureData { get; }
    }

    public interface IClass
    {
        void UpdateAll();
        void SaveText(string fileName);
        bool AsciiView { get; set; }
        bool DumpIdentifyDevice { get; set; }
        bool DumpSmartReadData { get; set; }
        bool DumpSmartReadThreshold { get; set; }
        global::System.Collections.Generic.IList<AtaSmartInfo> Info { get; }
    }

    public interface IGraphDataPoint
    {
        ulong XValue { get; set; }
        uint YValue { get; set; }
    }

    public interface IGraphDataPointFactory
    {
        GraphDataPoint CreateInstance(ulong xValue, uint yValue);
    }


    public enum SizeUnit : int
    {
        Bytes = unchecked((int)0),
        KB = unchecked((int)0x1),
        MB = unchecked((int)0x2),
        GB = unchecked((int)0x3),
    }


    public struct SmartAttribute : IEquatable<SmartAttribute>
    {
        public string Id;
        public string Name;
        public string RawValue;
        public string Threshold;

        public SmartAttribute(string _Id, string _Name, string _RawValue, string _Threshold)
        {
            Id = _Id; Name = _Name; RawValue = _RawValue; Threshold = _Threshold;
        }

        public static bool operator ==(SmartAttribute x, SmartAttribute y) => x.Id == y.Id && x.Name == y.Name && x.RawValue == y.RawValue && x.Threshold == y.Threshold;
        public static bool operator !=(SmartAttribute x, SmartAttribute y) => !(x == y);
        public bool Equals(SmartAttribute other) => this == other;
        public override bool Equals(object obj) => obj is SmartAttribute that && this == that;
        public override int GetHashCode() => Id.GetHashCode() ^ Name.GetHashCode() ^ RawValue.GetHashCode() ^ Threshold.GetHashCode();
    }
}

//namespace ABI.DiskInfoLibWinRT
//{
//    public struct AtaSmartInfo
//    {

//        public static IObjectReference CreateMarshaler(global::DiskInfoLibWinRT.AtaSmartInfo obj) => obj is null ? null : MarshalInspectable<global::DiskInfoLibWinRT.AtaSmartInfo>.CreateMarshaler<IUnknownVftbl>(obj, GuidGenerator.GetIID(typeof(global::DiskInfoLibWinRT.IAtaSmartInfo).GetHelperType()));
//        public static ObjectReferenceValue CreateMarshaler2(global::DiskInfoLibWinRT.AtaSmartInfo obj) => MarshalInspectable<object>.CreateMarshaler2(obj, GuidGenerator.GetIID(typeof(global::DiskInfoLibWinRT.IAtaSmartInfo).GetHelperType()));
//        public static IntPtr GetAbi(IObjectReference value) => value is null ? IntPtr.Zero : MarshalInterfaceHelper<object>.GetAbi(value);
//        public static global::DiskInfoLibWinRT.AtaSmartInfo FromAbi(IntPtr thisPtr) => global::DiskInfoLibWinRT.AtaSmartInfo.FromAbi(thisPtr);
//        public static IntPtr FromManaged(global::DiskInfoLibWinRT.AtaSmartInfo obj) => obj is null ? IntPtr.Zero : CreateMarshaler2(obj).Detach();
//        public static MarshalInterfaceHelper<global::DiskInfoLibWinRT.AtaSmartInfo>.MarshalerArray CreateMarshalerArray(global::DiskInfoLibWinRT.AtaSmartInfo[] array) => MarshalInterfaceHelper<global::DiskInfoLibWinRT.AtaSmartInfo>.CreateMarshalerArray2(array, (o) => CreateMarshaler2(o));
//        public static (int length, IntPtr data) GetAbiArray(object box) => MarshalInterfaceHelper<global::DiskInfoLibWinRT.AtaSmartInfo>.GetAbiArray(box);
//        public static global::DiskInfoLibWinRT.AtaSmartInfo[] FromAbiArray(object box) => MarshalInterfaceHelper<global::DiskInfoLibWinRT.AtaSmartInfo>.FromAbiArray(box, FromAbi);
//        public static (int length, IntPtr data) FromManagedArray(global::DiskInfoLibWinRT.AtaSmartInfo[] array) => MarshalInterfaceHelper<global::DiskInfoLibWinRT.AtaSmartInfo>.FromManagedArray(array, (o) => FromManaged(o));
//        public static void DisposeMarshaler(IObjectReference value) => MarshalInspectable<object>.DisposeMarshaler(value);
//        public static void DisposeMarshalerArray(MarshalInterfaceHelper<global::DiskInfoLibWinRT.AtaSmartInfo>.MarshalerArray array) => MarshalInterfaceHelper<global::DiskInfoLibWinRT.AtaSmartInfo>.DisposeMarshalerArray(array);
//        public static void DisposeAbi(IntPtr abi) => MarshalInspectable<object>.DisposeAbi(abi);
//        public static void DisposeAbiArray(object box) => MarshalInspectable<object>.DisposeAbiArray(box);
//    }

//    public struct Class
//    {

//        public static IObjectReference CreateMarshaler(global::DiskInfoLibWinRT.Class obj) => obj is null ? null : MarshalInspectable<global::DiskInfoLibWinRT.Class>.CreateMarshaler<IUnknownVftbl>(obj, GuidGenerator.GetIID(typeof(global::DiskInfoLibWinRT.IClass).GetHelperType()));
//        public static ObjectReferenceValue CreateMarshaler2(global::DiskInfoLibWinRT.Class obj) => MarshalInspectable<object>.CreateMarshaler2(obj, GuidGenerator.GetIID(typeof(global::DiskInfoLibWinRT.IClass).GetHelperType()));
//        public static IntPtr GetAbi(IObjectReference value) => value is null ? IntPtr.Zero : MarshalInterfaceHelper<object>.GetAbi(value);
//        public static global::DiskInfoLibWinRT.Class FromAbi(IntPtr thisPtr) => global::DiskInfoLibWinRT.Class.FromAbi(thisPtr);
//        public static IntPtr FromManaged(global::DiskInfoLibWinRT.Class obj) => obj is null ? IntPtr.Zero : CreateMarshaler2(obj).Detach();
//        public static MarshalInterfaceHelper<global::DiskInfoLibWinRT.Class>.MarshalerArray CreateMarshalerArray(global::DiskInfoLibWinRT.Class[] array) => MarshalInterfaceHelper<global::DiskInfoLibWinRT.Class>.CreateMarshalerArray2(array, (o) => CreateMarshaler2(o));
//        public static (int length, IntPtr data) GetAbiArray(object box) => MarshalInterfaceHelper<global::DiskInfoLibWinRT.Class>.GetAbiArray(box);
//        public static global::DiskInfoLibWinRT.Class[] FromAbiArray(object box) => MarshalInterfaceHelper<global::DiskInfoLibWinRT.Class>.FromAbiArray(box, FromAbi);
//        public static (int length, IntPtr data) FromManagedArray(global::DiskInfoLibWinRT.Class[] array) => MarshalInterfaceHelper<global::DiskInfoLibWinRT.Class>.FromManagedArray(array, (o) => FromManaged(o));
//        public static void DisposeMarshaler(IObjectReference value) => MarshalInspectable<object>.DisposeMarshaler(value);
//        public static void DisposeMarshalerArray(MarshalInterfaceHelper<global::DiskInfoLibWinRT.Class>.MarshalerArray array) => MarshalInterfaceHelper<global::DiskInfoLibWinRT.Class>.DisposeMarshalerArray(array);
//        public static void DisposeAbi(IntPtr abi) => MarshalInspectable<object>.DisposeAbi(abi);
//        public static void DisposeAbiArray(object box) => MarshalInspectable<object>.DisposeAbiArray(box);
//    }

//    public struct GraphDataPoint
//    {

//        public static IObjectReference CreateMarshaler(global::DiskInfoLibWinRT.GraphDataPoint obj) => obj is null ? null : MarshalInspectable<global::DiskInfoLibWinRT.GraphDataPoint>.CreateMarshaler<IUnknownVftbl>(obj, GuidGenerator.GetIID(typeof(global::DiskInfoLibWinRT.IGraphDataPoint).GetHelperType()));
//        public static ObjectReferenceValue CreateMarshaler2(global::DiskInfoLibWinRT.GraphDataPoint obj) => MarshalInspectable<object>.CreateMarshaler2(obj, GuidGenerator.GetIID(typeof(global::DiskInfoLibWinRT.IGraphDataPoint).GetHelperType()));
//        public static IntPtr GetAbi(IObjectReference value) => value is null ? IntPtr.Zero : MarshalInterfaceHelper<object>.GetAbi(value);
//        public static global::DiskInfoLibWinRT.GraphDataPoint FromAbi(IntPtr thisPtr) => global::DiskInfoLibWinRT.GraphDataPoint.FromAbi(thisPtr);
//        public static IntPtr FromManaged(global::DiskInfoLibWinRT.GraphDataPoint obj) => obj is null ? IntPtr.Zero : CreateMarshaler2(obj).Detach();
//        public static MarshalInterfaceHelper<global::DiskInfoLibWinRT.GraphDataPoint>.MarshalerArray CreateMarshalerArray(global::DiskInfoLibWinRT.GraphDataPoint[] array) => MarshalInterfaceHelper<global::DiskInfoLibWinRT.GraphDataPoint>.CreateMarshalerArray2(array, (o) => CreateMarshaler2(o));
//        public static (int length, IntPtr data) GetAbiArray(object box) => MarshalInterfaceHelper<global::DiskInfoLibWinRT.GraphDataPoint>.GetAbiArray(box);
//        public static global::DiskInfoLibWinRT.GraphDataPoint[] FromAbiArray(object box) => MarshalInterfaceHelper<global::DiskInfoLibWinRT.GraphDataPoint>.FromAbiArray(box, FromAbi);
//        public static (int length, IntPtr data) FromManagedArray(global::DiskInfoLibWinRT.GraphDataPoint[] array) => MarshalInterfaceHelper<global::DiskInfoLibWinRT.GraphDataPoint>.FromManagedArray(array, (o) => FromManaged(o));
//        public static void DisposeMarshaler(IObjectReference value) => MarshalInspectable<object>.DisposeMarshaler(value);
//        public static void DisposeMarshalerArray(MarshalInterfaceHelper<global::DiskInfoLibWinRT.GraphDataPoint>.MarshalerArray array) => MarshalInterfaceHelper<global::DiskInfoLibWinRT.GraphDataPoint>.DisposeMarshalerArray(array);
//        public static void DisposeAbi(IntPtr abi) => MarshalInspectable<object>.DisposeAbi(abi);
//        public static void DisposeAbiArray(object box) => MarshalInspectable<object>.DisposeAbiArray(box);
//    }

//    public static class IAtaSmartInfoMethods
//    {

//        public static void Update(IObjectReference _obj)
//        {

//        }
//        public static global::System.Collections.Generic.IList<object> get_Attributes(IObjectReference _obj)
//        {

//        }

//        public static string get_CurrentTransferMode(IObjectReference _obj)
//        {

//        }
//        public static void set_CurrentTransferMode(IObjectReference _obj, string value)
//        {

//        }

//        public static string get_DriveMap(IObjectReference _obj)
//        {

//        }
//        public static void set_DriveMap(IObjectReference _obj, string value)
//        { 

//        }

//        public static string get_Features(IObjectReference _obj)
//        {

//        }
//        public static void set_Features(IObjectReference _obj, string value)
//        {

//        }

//        public static string get_Firmware(IObjectReference _obj)
//        {

//        }
//        public static void set_Firmware(IObjectReference _obj, string value)
//        {

//        }

//        public static int get_HostReads(IObjectReference _obj)
//        {

//        }
//        public static void set_HostReads(IObjectReference _obj, int value)
//        {

//        }

//        public static int get_HostWrites(IObjectReference _obj)
//        {

//        }
//        public static void set_HostWrites(IObjectReference _obj, int value)
//        {

//        }

//        public static int get_Index(IObjectReference _obj)
//        {

//        }
//        public static void set_Index(IObjectReference _obj, int value)
//        {

//        }

//        public static string get_Interface(IObjectReference _obj)
//        {

//        }
//        public static void set_Interface(IObjectReference _obj, string value)
//        {

//        }

//        public static string get_Model(IObjectReference _obj)
//        {

//        }
//        public static void set_Model(IObjectReference _obj, string value)
//        {

//        }

//        public static uint get_PowerOnCount(IObjectReference _obj)
//        {

//        }
//        public static void set_PowerOnCount(IObjectReference _obj, uint value)
//        {
   
//        }

//        public static uint get_PowerOnTime(IObjectReference _obj)
//        {

//        }
//        public static void set_PowerOnTime(IObjectReference _obj, uint value)
//        {

//        }

//        public static int get_Rotation(IObjectReference _obj)
//        {

//        }
//        public static void set_Rotation(IObjectReference _obj, int value)
//        {

//        }

//        public static string get_SerialNumber(IObjectReference _obj)
//        {

//        }
//        public static void set_SerialNumber(IObjectReference _obj, string value)
//        {

//        }

//        public static string get_Standard(IObjectReference _obj)
//        {

//        }
//        public static void set_Standard(IObjectReference _obj, string value)
//        {

//        }

//        public static global::System.Collections.Generic.IList<global::DiskInfoLibWinRT.GraphDataPoint> get_TemperatureData(IObjectReference _obj)
//        {

//        }


//    }

//    public interface IAtaSmartInfo : global::DiskInfoLibWinRT.IAtaSmartInfo
//    {
//    }
//    public static class IClassMethods
//    {

//        public static void UpdateAll(IObjectReference _obj)
//        {

//        }

//        public static void SaveText(IObjectReference _obj, string fileName)
//        {

//        }
//        public static bool get_AsciiView(IObjectReference _obj)
//        {

//        }
//        public static void set_AsciiView(IObjectReference _obj, bool value)
//        {

//        }

//        public static bool get_DumpIdentifyDevice(IObjectReference _obj)
//        {

//        }
//        public static void set_DumpIdentifyDevice(IObjectReference _obj, bool value)
//        {

//        }

//        public static bool get_DumpSmartReadData(IObjectReference _obj)
//        {

//        }
//        public static void set_DumpSmartReadData(IObjectReference _obj, bool value)
//        {

//        }

//        public static bool get_DumpSmartReadThreshold(IObjectReference _obj)
//        {

//        }
//        public static void set_DumpSmartReadThreshold(IObjectReference _obj, bool value)
//        {

//        }

//        public static global::System.Collections.Generic.IList<global::DiskInfoLibWinRT.AtaSmartInfo> get_Info(IObjectReference _obj)
//        {

//        }


//    }
//    public interface IClass : global::DiskInfoLibWinRT.IClass
//    {
//    }
//    public static class IGraphDataPointMethods
//    {
//        public static ulong get_XValue(IObjectReference _obj)
//        {

//        }
//        public static void set_XValue(IObjectReference _obj, ulong value)
//        {

//        }

//        public static uint get_YValue(IObjectReference _obj)
//        {

//        }
//        public static void set_YValue(IObjectReference _obj, uint value)
//        {

//        }


//    }
//    public interface IGraphDataPoint : global::DiskInfoLibWinRT.IGraphDataPoint
//    {
//    }
//    public static class IGraphDataPointFactoryMethods
//    {

//        public static global::DiskInfoLibWinRT.GraphDataPoint CreateInstance(IObjectReference _obj, ulong xValue, uint yValue)
//        {

//        }

//    }
//    public interface IGraphDataPointFactory : global::DiskInfoLibWinRT.IGraphDataPointFactory
//    {
//    }

//    public struct SmartAttribute
//    {
//        public IntPtr Id;
//        public IntPtr Name;
//        public IntPtr RawValue;
//        public IntPtr Threshold;
//    }
//}
