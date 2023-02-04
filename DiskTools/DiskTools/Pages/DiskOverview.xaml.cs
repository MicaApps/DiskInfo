// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

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
using WinRT;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskTools.Pages
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class DiskOverview : Page
    {
        public DiskOverview()
        {
            this.InitializeComponent();
        }
        public DiskInfoLibWinRT.AtaSmartInfo Info;
        public ViewModel ViewModel = ViewModel.Instance;
        public int Id
        {
            set
            {
                Info = ViewModel.LibInstance.Info[value];
            }
        }

        private void AppBarButton_Click(object sender, Microsoft.UI.Xaml.RoutedEventArgs e)
        {
            ViewModel.LibInstance.UpdateAll();
        }

        private void SplitButton_Click(SplitButton sender, SplitButtonClickEventArgs args)
        {
            ViewModel.LibInstance.SaveText("");
        }
    }
}
