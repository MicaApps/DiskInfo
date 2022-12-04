

using DiskTools.WinUI.Pages.Disk;
using DiskTools.WinUI.Pages.Home;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.UI.Xaml;
using System;

namespace DiskTools.WinUI
{

    public partial class App : Application
    {
        public IHost Host
        {
            get;
        }


        public App()
        {
            this.InitializeComponent();
            Host = Microsoft.Extensions.Hosting.Host.
                CreateDefaultBuilder().UseContentRoot(AppContext.BaseDirectory).
                ConfigureServices((content, services) =>
                {
                    services.AddSingleton<HomePage>();
                    services.AddSingleton<HomePageViewModel>();
                    services.AddTransient<DiskPage>();
                    services.AddTransient<DiskPageViewModel>();
                }).Build();
        }

        public static T GetService<T>()
            where T : class
        {
            if ((App.Current as App)!.Host.Services.GetService(typeof(T)) is not T service)
            {
                throw new ArgumentException($"服务配置出错，或不存在该类型");
            }
            return service;
        }

        protected override void OnLaunched(Microsoft.UI.Xaml.LaunchActivatedEventArgs args)
        {
            m_window = new MainWindow();
            m_window.Activate();
        }

        private Window m_window;
    }
}
