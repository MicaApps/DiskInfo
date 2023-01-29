using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DiskTools.Converters
{
    class ReadableBytesConverter : Microsoft.UI.Xaml.Data.IValueConverter
    {
        const UInt64 ToKB = 1024;
        const UInt64 ToMB = 1024 * 1024;
        const UInt64 ToGB = 1024 * 1024 * 1024;
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            //var bytes = (UInt64)value;
            //var bytesDouble = (double)bytes;
            //var toKB = bytesDouble / ToKB;
            //var toMB = bytesDouble / ToMB;
            //var toGB = bytesDouble / ToGB;
            //if (toKB < 1.0)
            //    return $"{bytes} B";
            //else if (toMB < 1.0)
            //    return $"{toKB:f0} KB";
            //else if (toGB < 1.0)
            //    return $"{toMB:f0} MB";
            //else return $"{toGB:f0} GB";

            if ((int)value == -1)
                return "----";
            return $"{(int)value} GB";
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            throw new NotImplementedException();
        }
    }
}
