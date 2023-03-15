using DiskInfoLibWinRT;
using DiskTools.Pages;
using Microsoft.UI.Xaml.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DiskTools.Converters
{
    public class GetIListLastConverter : IValueConverter {
        public object Convert(object value, Type targetType, object parameter, string language) {
            IList<GraphDataPoint> data = value as IList<GraphDataPoint>;
            bool isCelsius = OverviewPage.IsCelsius;
            if (data is null)
                return "";
            if (data.Count > 0) {
                var temp = data[data.Count - 1];
                if (isCelsius)
                    return $"{temp.YValue}℃";
                else
                    return $"{Math.Round(32 + temp.YValue * 1.8f)}℉";
            }
            return "";
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language) {
            throw new NotImplementedException();
        }
    }
}
