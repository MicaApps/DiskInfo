using DiskTools.Helpers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DiskTools.ViewModels
{
    public class DiskInfoViewModel : INotifyPropertyChanged
    {
        private DriveInfo _driveInfo;
        public DriveInfo DriveInfo
        {
            get => _driveInfo;
            set
            {
                if (_driveInfo != value)
                {
                    _driveInfo = value;
                    RaisePropertyChangedEvent();
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void RaisePropertyChangedEvent([System.Runtime.CompilerServices.CallerMemberName] string name = null)
        {
            if (name != null) { PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name)); }
        }

        public DiskInfoViewModel(string id)
        {
            DriveInfo drives = DriveInfo.GetDrives().FirstOrDefault((x) => x.Name == id);
        }
    }
}
