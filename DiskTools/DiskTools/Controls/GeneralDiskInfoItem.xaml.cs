// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskTools.Controls
{
    public sealed partial class GeneralDiskInfoItem : UserControl
    {
        public GeneralDiskInfoItem()
        {
            this.InitializeComponent();
        }

        private static DependencyProperty glyphProperty = DependencyProperty.Register(
            "Glyph", typeof(object), typeof(GeneralDiskInfoItem), new PropertyMetadata(null));
        private static DependencyProperty nameProperty = DependencyProperty.Register(
            "ValueName", typeof(object), typeof(GeneralDiskInfoItem), new PropertyMetadata(null));
        private static DependencyProperty valueProperty = DependencyProperty.Register(
            "Value", typeof(object), typeof(GeneralDiskInfoItem), new PropertyMetadata(null));

        public string Glyph
        {
            get => GetValue(glyphProperty) as string;
            set => SetValue(glyphProperty, value);
        }

        public string ValueName
        {
            get=>GetValue(nameProperty) as string;
            set => SetValue(nameProperty, value);
        }

        public string Value
        {
            get => GetValue(valueProperty) as string; 
            set => SetValue(valueProperty, value);
        }
    }
}
