using Microsoft.UI.Composition.SystemBackdrops;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WinUIEx;

namespace DiskTools.WinUI.Windowing
{
    public partial class BaseWindow : WindowEx
    {
        public BaseWindow() {

            if (DesktopAcrylicController.IsSupported())
            {
                Backdrop = new AcrylicSystemBackdrop();
            }
        }
    }
}
