using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using System.Collections.Generic;

namespace DiskTools.Controls
{
    public sealed partial class GraphPage : UserControl
    {
        public GraphPage()
        {
            this.InitializeComponent();
        }

        private static DependencyProperty collectionProperty = DependencyProperty.Register(
            "Collection", typeof(object), typeof(GraphPage), new PropertyMetadata(null));

        public class Test
        {
            public DateTime XValue { get; set; }
            public uint YValue { get; set; }
        }

        public IList<DiskInfoLibWinRT.GraphDataPoint> Collection
        {
            get => GetValue(collectionProperty) as IList<DiskInfoLibWinRT.GraphDataPoint>;
            set => SetValue(collectionProperty, value);
        }
    }
}
