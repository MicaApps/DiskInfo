using CommunityToolkit.Mvvm.ComponentModel;
using DiskTools.WinUI.Navigation.Model;

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
