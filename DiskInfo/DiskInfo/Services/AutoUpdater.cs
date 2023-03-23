using DiskInfo.Helpers;
using DiskInfo.Pages;
using DiskInfo.ViewModels;
using Microsoft.UI.Dispatching;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.System.Threading;

namespace DiskInfo.Services
{
    class AutoUpdater
    {
        public ITimerUpdatable CurrentPage
        {
            get => m_currentPage; 
            set
            {
                m_currentPage = value;
                if(m_timer == null)
                {
                    if (SettingsHelper.Get<bool>(SettingsHelper.AutoRefresh))
                    {
                        SetInterval(SettingsViewModel.intervals[SettingsViewModel.UpdateInterval]);
                    }
                }
            }
        }

        public void SetInterval(TimeSpan interval)
        {
            if(m_timer != null)
            {
                m_timer.Cancel();
            }
            m_timer = ThreadPoolTimer.CreatePeriodicTimer(
                (ThreadPoolTimer timer) => timerProc(), interval);
        }

        public static AutoUpdater Instance = new();

        private ThreadPoolTimer m_timer;

        private AutoUpdater() { }

        private void timerProc()
        {
            UIHelper.UIDispatcherQueue.TryEnqueue(() => { CurrentPage?.update(); });
        }
        private ITimerUpdatable m_currentPage;
    }
}
