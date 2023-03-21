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
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskInfo.Controls
{
    public sealed partial class GaugeControl : UserControl, INotifyPropertyChanged
    {
        public GaugeControl()
        {
            this.InitializeComponent();
            this.DataContext = this;
        }

        private static DependencyProperty valueProperty = DependencyProperty.Register(
            "Value", typeof(object), typeof(GaugeControl), new PropertyMetadata(0.0) );

        public double Value
        {
            get => (double)GetValue(valueProperty);
            set
            {
                SetValue(valueProperty, value);
                if (value < 60)
                    MyBrushIndex = 0;
                else if (value > 90)
                    MyBrushIndex = 2;
                else
                    MyBrushIndex = 1;
                OnPropertyChanged();
                OnPropertyChanged("Desc");
            }
        }

        private int myBrushIndex;

        public int MyBrushIndex
        {
            get { return myBrushIndex; }
            set { myBrushIndex = value; OnPropertyChanged(); }
        }

        public string Desc
        {
            get {
                if (Value < 60)
                    return "报废";
                else if (Value > 90)
                    return "正常";
                else
                    return "良好";
            }
        }


        private void rangePointer_ValueChanged(object sender, ValueChangedEventArgs e)
        {
            if (e.Value < 16)
            {
                gradient1.Value = e.Value / 2;
                gradient2.Value = e.Value;
                return;
            }
            else
            {
                gradient1.Value = e.Value - 16;
                gradient2.Value = e.Value;
            }
        }

        #region INotifyPropertyChanged members

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChangedEventHandler handler = this.PropertyChanged;
            if (handler != null)
            {
                var e = new PropertyChangedEventArgs(propertyName);
                handler(this, e);
            }
        }

        #endregion
    }
}
