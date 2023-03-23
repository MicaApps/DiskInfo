using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Data;
using System.Collections.Generic;
using WinRT;

namespace DiskInfo.Controls
{
    public sealed partial class GraphControl : UserControl
    {
        public GraphControl()
        {
            this.InitializeComponent();
        }

        private static DependencyProperty collectionProperty = DependencyProperty.Register(
            "Collection", typeof(object), typeof(GraphControl), new PropertyMetadata(null));

        public IList<DiskInfoLibWinRT.GraphDataPoint> Collection
        {
            get => GetValue(collectionProperty) as IList<DiskInfoLibWinRT.GraphDataPoint>;
            set
            {
                SetValue(collectionProperty, value);
                Line.ItemsSource = null;
                Area.ItemsSource = null;
                Line.ItemsSource = (this.Resources["UnixTimeStampToTimeDateConverter"] as IValueConverter).Convert(value, null, null, null);
                Area.ItemsSource = (this.Resources["UnixTimeStampToTimeDateConverter"] as IValueConverter).Convert(value, null, null, null);
            }
        }
    }
}
