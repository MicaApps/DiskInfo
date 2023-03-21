using DiskInfo.Helpers;
using Microsoft.UI.Xaml;
using System;
using System.IO;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskInfo {
    /// <summary>
    /// Provides application-specific behavior to supplement the default Application class.
    /// </summary>
    public partial class App : Application {
        /// <summary>
        /// Initializes the singleton application object.  This is the first line of authored code
        /// executed, and as such is the logical equivalent of main() or WinMain().
        /// </summary>
        public App() {
            InitializeComponent();
            UnhandledException += Application_UnhandledException;
            AppDomain.CurrentDomain.UnhandledException += CurrentDomain_UnhandledException;

            //注册 Syncfusion 许可证
            var personalFolder = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
            var keyPath = System.IO.Path.Combine(personalFolder, "syncfusionKey.txt");
            var key = File.ReadAllText(keyPath);
            if (key == "")
                throw new Exception("Key file not found in C:\\Users\\<Your Account>\\Documents\\syncfusionKey.txt");
            Syncfusion.Licensing.SyncfusionLicenseProvider.RegisterLicense(key);
        }

        /// <summary>
        /// Invoked when the application is launched normally by the end user.  Other entry points
        /// will be used such as when the application is launched to open a specific file.
        /// </summary>
        /// <param name="args">Details about the launch request and process.</param>
        private MainWindow m_window;

        protected override void OnLaunched(LaunchActivatedEventArgs args) {
            RegisterExceptionHandlingSynchronizationContext();
            m_window = new();
            m_window.TrackWindow();
            ThemeHelper.Initialize();
            m_window.Title = "Disk Tools";
            m_window.Activate();
        }

        private void Application_UnhandledException(object sender, Microsoft.UI.Xaml.UnhandledExceptionEventArgs e) {
            SettingsHelper.LogManager.GetLogger("Unhandled Exception - Application").Error(e.Exception.ExceptionToMessage(), e.Exception);
            e.Handled = true;
        }

        private void CurrentDomain_UnhandledException(object sender, System.UnhandledExceptionEventArgs e) {
            if (e.ExceptionObject is Exception Exception) {
                SettingsHelper.LogManager.GetLogger("Unhandled Exception - CurrentDomain").Error(Exception.ExceptionToMessage(), Exception);
            }
        }

        /// <summary>
        /// Should be called from OnActivated and OnLaunched
        /// </summary>
        private void RegisterExceptionHandlingSynchronizationContext() {
            ExceptionHandlingSynchronizationContext
                .Register()
                .UnhandledException += SynchronizationContext_UnhandledException;
        }

        private void SynchronizationContext_UnhandledException(object sender, Helpers.UnhandledExceptionEventArgs e) {
            SettingsHelper.LogManager.GetLogger("Unhandled Exception - SynchronizationContext").Error(e.Exception.ExceptionToMessage(), e.Exception);
            e.Handled = true;
        }
    }
}
