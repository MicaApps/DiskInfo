using CommunityToolkit.Mvvm.ComponentModel;
using DiskTools.WinUI.Navigation.Model;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DiskTools.WinUI.Pages.Home
{
    [INotifyPropertyChanged]
    internal sealed partial class HomePageViewModel
    {

        [ObservableProperty]
        private object selectedItem;

        [ObservableProperty]
        private DiskModel[] diskList =
            {
            new DiskModel
            {
                DiskName = "ST2000DM008-2FR1 SCSI Disk",
                DiskId = ""
            }

            };

        public HomePageViewModel()
        {
            SelectedItem = diskList[0];
        }
        
    }

    class DiskNameConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            if (value is DiskModel diskModel)
            {
                return diskModel.DiskName;
            }
            else if (value is NavigationViewItem item && item.Content is string title)
            {
                return title;
            }
            else
            {
                return string.Empty;
            }
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            throw new NotImplementedException();
        }

    }
}
