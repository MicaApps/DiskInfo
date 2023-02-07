// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using Syncfusion.UI.Xaml.Gauges;
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
    public sealed partial class GaugeControl : UserControl
    {
        public GaugeControl()
        {
            this.InitializeComponent();
        }

        private static DependencyProperty valueProperty = DependencyProperty.Register(
            "Value", typeof(object), typeof(GaugeControl), new PropertyMetadata(0.0) );

        public double Value
        {
            get => (double)GetValue(valueProperty);
            set => SetValue(valueProperty, value);
        }

        private void rangePointer_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            if (e.Value > 10)
            {
                lastgradient.Value = e.Value - 10;
            }
        }
    }
}