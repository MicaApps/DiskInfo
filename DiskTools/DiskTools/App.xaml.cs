using DiskTools.Helpers;
using Microsoft.UI.Xaml;
using System;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskTools
{
    /// <summary>
    /// Provides application-specific behavior to supplement the default Application class.
    /// </summary>
    public partial class App : Application
    {
        /// <summary>
        /// Initializes the singleton application object.  This is the first line of authored code
        /// executed, and as such is the logical equivalent of main() or WinMain().
        /// </summary>
        public App()
        {
            InitializeComponent();
            UnhandledException += Application_UnhandledException;
            AppDomain.CurrentDomain.UnhandledException += CurrentDomain_UnhandledException;

            //注册 Syncfusion 许可证
            Syncfusion.Licensing.SyncfusionLicenseProvider.RegisterLicense("Mgo+DSMBaFt/QHRqVVhjVFpFdEBBXHxAd1p/VWJYdVt5flBPcDwsT3RfQF5jSHxSdkVgUH5ZcnBcRw==;Mgo+DSMBPh8sVXJ0S0J+XE9HflRDX3xKf0x/TGpQb19xflBPallYVBYiSV9jS31Td0diWX9deXVSRGZYUA==;ORg4AjUWIQA/Gnt2VVhkQlFadVdJXGFWfVJpTGpQdk5xdV9DaVZUTWY/P1ZhSXxQdkRhWH9ec31UQWJbVkI=;OTc5NzUwQDMyMzAyZTM0MmUzME5wYW9IQUtKWEg0T1JOTWVrd2tkV2YvcG84WTJpcFhtdFIvelBBT0JhZmc9;OTc5NzUxQDMyMzAyZTM0MmUzMGFhNEpxMW5uTE5xMmFUcGxXUXVjY0MrSHBUKzMrYTVORjBvTzdsZnB0Kzg9;NRAiBiAaIQQuGjN/V0Z+WE9EaFxKVmJLYVB3WmpQdldgdVRMZVVbQX9PIiBoS35RdUViW35ecHdcR2dfVUFx;OTc5NzUzQDMyMzAyZTM0MmUzME1NbkZoN3oraHdRYzFuUzB5eFdiWlhBTUZvL0VjYkFWc0QrQTNZMTl3S289;OTc5NzU0QDMyMzAyZTM0MmUzME1yVUpHY2JKSFJic0QrKzEwVFpsZzNDYkUvNS94d2pXTjBMTE5wSW13a0U9;Mgo+DSMBMAY9C3t2VVhkQlFadVdJXGFWfVJpTGpQdk5xdV9DaVZUTWY/P1ZhSXxQdkRhWH9ec31UQWRdWUY=;OTc5NzU2QDMyMzAyZTM0MmUzMGdqeUxUS2JYcnI3TFZKZjBIWFo5STNRVkhrT1V1Y3JhK2h5VUs5bitIMmc9;OTc5NzU3QDMyMzAyZTM0MmUzMFovclRCMEhRbWRyR2FLbnhnQW0wbGxLNE9MQUhWQzN6RjdnU2hFcVNGd2s9;OTc5NzU4QDMyMzAyZTM0MmUzME1NbkZoN3oraHdRYzFuUzB5eFdiWlhBTUZvL0VjYkFWc0QrQTNZMTl3S289");

        }

        /// <summary>
        /// Invoked when the application is launched normally by the end user.  Other entry points
        /// will be used such as when the application is launched to open a specific file.
        /// </summary>
        /// <param name="args">Details about the launch request and process.</param>
        private MainWindow m_window;

        protected override void OnLaunched(LaunchActivatedEventArgs args)
        {
            RegisterExceptionHandlingSynchronizationContext();
            m_window = new();
            m_window.TrackWindow();
            ThemeHelper.Initialize();
            m_window.Title = "Disk Tools";
            m_window.Activate();
        }

        private void Application_UnhandledException(object sender, Microsoft.UI.Xaml.UnhandledExceptionEventArgs e)
        {
            SettingsHelper.LogManager.GetLogger("Unhandled Exception - Application").Error(e.Exception.ExceptionToMessage(), e.Exception);
            e.Handled = true;
        }

        private void CurrentDomain_UnhandledException(object sender, System.UnhandledExceptionEventArgs e)
        {
            if (e.ExceptionObject is Exception Exception)
            {
                SettingsHelper.LogManager.GetLogger("Unhandled Exception - CurrentDomain").Error(Exception.ExceptionToMessage(), Exception);
            }
        }

        /// <summary>
        /// Should be called from OnActivated and OnLaunched
        /// </summary>
        private void RegisterExceptionHandlingSynchronizationContext()
        {
            ExceptionHandlingSynchronizationContext
                .Register()
                .UnhandledException += SynchronizationContext_UnhandledException;
        }

        private void SynchronizationContext_UnhandledException(object sender, Helpers.UnhandledExceptionEventArgs e)
        {
            SettingsHelper.LogManager.GetLogger("Unhandled Exception - SynchronizationContext").Error(e.Exception.ExceptionToMessage(), e.Exception);
            e.Handled = true;
        }
    }
}
