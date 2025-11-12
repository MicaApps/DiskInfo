using System;
using Windows.ApplicationModel.Resources;

namespace DiskInfo.Converters
{
    class ReadableTimeConverter : Microsoft.UI.Xaml.Data.IValueConverter
    {
        private static readonly ResourceLoader _loader = ResourceLoader.GetForViewIndependentUse("DiskInfoPage");
        
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return $"{(uint)value} {_loader.GetString("Unit_Hours")}";
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            throw new NotImplementedException();
        }
    }
}
