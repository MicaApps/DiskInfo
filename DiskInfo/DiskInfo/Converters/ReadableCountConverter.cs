using System;
using Windows.ApplicationModel.Resources;

namespace DiskInfo.Converters
{
    class ReadableCountConverter : Microsoft.UI.Xaml.Data.IValueConverter
    {
        private static readonly ResourceLoader _loader = ResourceLoader.GetForViewIndependentUse("DiskInfoPage");
        
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return $"{(uint)value} {_loader.GetString("Unit_Times")}";
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            throw new NotImplementedException();
        }
    }
}
