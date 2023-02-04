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

        public IList<GraphDataTimePoint> Collection
        {
            get => GetValue(collectionProperty) as IList<GraphDataTimePoint>; 
            set => SetValue(collectionProperty, value);
        }
    }
}
