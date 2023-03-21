using Microsoft.UI.Xaml;
using Windows.UI;

namespace DiskInfo.Helpers.DynamicThemeResource
{
    public class ColorWrapper : DependencyObject
    {
        public Color Color
        {
            get { return (Color)GetValue(ColorProperty); }
            set { SetValue(ColorProperty, value); }
        }

        public static readonly DependencyProperty ColorProperty =
            DependencyProperty.Register("Color", typeof(Color), typeof(ColorWrapper), new PropertyMetadata(null));
    }
}
