using Microsoft.UI.Xaml.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Foundation;

namespace DiskTools.Converters
{
    /// <summary>
    /// 数学相关的代码，勿动！！！
    /// </summary>
    public class PointerBrushCenterConverter : IValueConverter
    {
        const double R = 86;
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            double v = (double)value;
            if (v > 50)
                return new Point(86, 86);
            if (v <= 5d / 28d * 100d)
            {
                var theta = v / 100d * 14d / 9d * Math.PI;
                var alpha = Math.PI / 2d - 40d / 180d * Math.PI - theta;
                return new Point(R * Math.Cos(alpha), 0);
            }

            var theta1 = v / 100d * 14d / 9d * Math.PI;
            var alpha1 = Math.PI - 40d / 180d * Math.PI - theta1;
            return new Point(R, R * Math.Cos(alpha1));
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            throw new NotImplementedException();
        }
    }
}
