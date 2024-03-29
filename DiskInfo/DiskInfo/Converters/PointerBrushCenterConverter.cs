using Microsoft.UI.Xaml.Data;
using System;
using Windows.Foundation;

namespace DiskInfo.Converters
{
    /// <summary>
    /// 数学相关的代码，勿动！！！
    /// </summary>
    public class PointerBrushCenterConverter : IValueConverter
    {
        const double R = 86d * 220 / 300;
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            double v = (double)value;
            if (v > 50)
                return new Point(R, R);
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
