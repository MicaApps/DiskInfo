using Microsoft.UI.Xaml;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
