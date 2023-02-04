using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DiskTools.Converters
{
    class UnixTimeStampToTimeDateConverter : Microsoft.UI.Xaml.Data.IValueConverter
    {
        class DateTimeGraphPoint
        {
            public DateTime XValue { get; set; }
            public uint YValue { get; set; }

            public DateTimeGraphPoint(DiskInfoLibWinRT.GraphDataPoint p)
            {
                XValue = p.XValue.DateTime;
                YValue = p.YValue;
            }
        }
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return (value as IList<DiskInfoLibWinRT.GraphDataPoint>).Select(p => new DateTimeGraphPoint(p)).ToList();
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            throw new NotImplementedException();
        }
    }
}
