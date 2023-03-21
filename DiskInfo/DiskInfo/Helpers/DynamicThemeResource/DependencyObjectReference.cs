using Microsoft.UI.Xaml;

namespace DiskInfo.Helpers.DynamicThemeResource
{
    public class DependencyObjectReference<T> : DependencyObject where T : DependencyObject
    {
        #region Properties
        public T Value
        {
            get { return (T)GetValue(ValueProperty); }
            set { SetValue(ValueProperty, value); }
        }
        #endregion

        #region Static Data
        public static readonly DependencyProperty ValueProperty =
            DependencyProperty.Register(nameof(Value),
                                        typeof(T),
                                        typeof(DependencyObjectReference<T>),
                                        new PropertyMetadata(default(T)));
        #endregion
    }
}
