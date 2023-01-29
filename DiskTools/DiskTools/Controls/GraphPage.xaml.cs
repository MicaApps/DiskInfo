// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using ABI.DiskInfoLibWinRT;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

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
