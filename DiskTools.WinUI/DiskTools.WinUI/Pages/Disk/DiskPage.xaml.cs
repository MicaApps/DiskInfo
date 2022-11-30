// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using DiskTools.WinUI.Navigation.Model;
using DiskTools.WinUI.Pages.Disk.Detail;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Navigation;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskTools.WinUI.Pages.Disk
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class DiskPage : Page
    {
        private DiskPageViewModel viewModel = new();
        public DiskPage()
        {
            this.InitializeComponent();
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            if (e.Parameter is DiskModel diskModel)
            {
                viewModel.DiskModel= diskModel;
            }
        }

        private void ListView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (ItemList.SelectedItem is ListViewItem item && item.Content is string content && viewModel.DiskModel != null)
            {
                switch(content)
                {
                    case "Overview":
                        DiskInfoContent.Navigate(typeof(OverviewPage), viewModel.DiskModel);
                        break;

                }
            }
        }
    }
}
