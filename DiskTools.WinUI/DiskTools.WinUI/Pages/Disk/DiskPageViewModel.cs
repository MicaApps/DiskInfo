using CommunityToolkit.Mvvm.ComponentModel;
using DiskTools.WinUI.Navigation.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DiskTools.WinUI.Pages.Disk
{
    [INotifyPropertyChanged]
    internal partial class DiskPageViewModel
    {

        [ObservableProperty]
        private DiskModel diskModel;

        partial void OnDiskModelChanged(DiskModel value)
        {
            // TODO Get Disk info
        }
    }
}
