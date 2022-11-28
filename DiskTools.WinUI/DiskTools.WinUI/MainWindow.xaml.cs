// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using DiskTools.WinUI.Windowing;
using Microsoft.UI;
using Microsoft.UI.Windowing;
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskTools.WinUI
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainWindow : BaseWindow
    {

        public MainWindow()
        {
            this.InitializeComponent();

            //Setup title bar
            var titleBar = AppWindow.TitleBar;
            titleBar.ExtendsContentIntoTitleBar = true;
            titleBar.BackgroundColor = Colors.Transparent;
            titleBar.ButtonBackgroundColor = Colors.Transparent;
            titleBar.ButtonInactiveBackgroundColor = Colors.Transparent;
            Title = Windows.ApplicationModel.Package.Current.DisplayName;
        }

        
    }
}
