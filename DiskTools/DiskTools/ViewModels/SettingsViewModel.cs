using APKInstaller.Helpers;
using CommunityToolkit.WinUI;
using DiskTools.Helpers;
using DiskTools.Models;
using DiskTools.Pages.SettingPages;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.Windows.AppLifecycle;
using System;
using System.ComponentModel;
using System.Reflection;
using System.Threading.Tasks;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Resources;
using Windows.Storage;
using Windows.System.Threading;
using WinRT;

namespace DiskTools.ViewModels
{
    public class SettingsViewModel : INotifyPropertyChanged
    {
        private readonly SettingPage _page;
        private readonly ResourceLoader _loader = ResourceLoader.GetForViewIndependentUse("SettingPage");

        public static SettingsViewModel Caches;

        public static string WASVersion => Assembly.GetAssembly(typeof(ExtendedActivationKind)).GetName().Version.ToString(3);

        public static string SDKVersion => Assembly.GetAssembly(typeof(PackageSignatureKind)).GetName().Version.ToString();

        public static string WinRTVersion => Assembly.GetAssembly(typeof(TrustLevel)).GetName().Version.ToString(3);

        public DateTime UpdateDate
        {
            get => SettingsHelper.Get<DateTime>(SettingsHelper.UpdateDate);
            set
            {
                if (UpdateDate != value)
                {
                    SettingsHelper.Set(SettingsHelper.UpdateDate, value);
                    RaisePropertyChangedEvent();
                }
            }
        }

        public static int SelectedTheme
        {
            get => 2 - (int)ThemeHelper.RootTheme;
            set
            {
                if (SelectedTheme != value)
                {
                    ThemeHelper.RootTheme = (ElementTheme)(2 - value);
                }
            }
        }

        public static int UpdateInterval
        {
            get => SettingsHelper.Get<int>(SettingsHelper.UpdateInterval);
            set
            {
                //设置更新间隔
                TimeSpan[] intervals =
                {
                    TimeSpan.FromMinutes(1),
                    TimeSpan.FromMinutes(3),
                    TimeSpan.FromMinutes(10),
                    TimeSpan.FromMinutes(30),
                    TimeSpan.FromMinutes(60),
                    TimeSpan.FromMinutes(120),
                    TimeSpan.FromMinutes(180),
                    TimeSpan.FromMinutes(360),
                    TimeSpan.FromMinutes(720),
                    TimeSpan.FromMinutes(1440),
                };

                if (value < 0 || value > intervals.Length)
                    return;

                if(UpdateInterval != value) 
                {
                    SettingsHelper.Set(SettingsHelper.UpdateInterval, value);
                }


                ThreadPoolTimer.CreatePeriodicTimer(
                    (ThreadPoolTimer timer) =>
                    {
                        ViewModel.LibInstance.UpdateAll();
                    }, intervals[value]
                );
            }
        }

        public bool AutoRefresh
        {
            get => SettingsHelper.Get<bool>(SettingsHelper.AutoRefresh);
            set
            {
                if (AutoRefresh != value)
                {
                    SettingsHelper.Set(SettingsHelper.AutoRefresh, value);
                    RaisePropertyChangedEvent();
                }
            }
        }

        public static int SelectedBackdrop
        {
            get => (int)SettingsHelper.Get<BackdropType>(SettingsHelper.SelectedBackdrop);
            set
            {
                if (SelectedBackdrop != value)
                {
                    BackdropType type = (BackdropType)value;
                    SettingsHelper.Set(SettingsHelper.SelectedBackdrop, type);
                    UIHelper.MainWindow.Backdrop.SetBackdrop(type);
                }
            }
        }

        private bool _checkingUpdate;
        public bool CheckingUpdate
        {
            get => _checkingUpdate;
            set
            {
                if (_checkingUpdate != value)
                {
                    _checkingUpdate = value;
                    RaisePropertyChangedEvent();
                }
            }
        }

        private string _gotoUpdateTag;
        public string GotoUpdateTag
        {
            get => _gotoUpdateTag;
            set
            {
                if (_gotoUpdateTag != value)
                {
                    _gotoUpdateTag = value;
                    RaisePropertyChangedEvent();
                }
            }
        }

        private Visibility _gotoUpdateVisibility;
        public Visibility GotoUpdateVisibility
        {
            get => _gotoUpdateVisibility;
            set
            {
                if (_gotoUpdateVisibility != value)
                {
                    _gotoUpdateVisibility = value;
                    RaisePropertyChangedEvent();
                }
            }
        }

        private bool _updateStateIsOpen;
        public bool UpdateStateIsOpen
        {
            get => _updateStateIsOpen;
            set
            {
                if (_updateStateIsOpen != value)
                {
                    _updateStateIsOpen = value;
                    RaisePropertyChangedEvent();
                }
            }
        }

        private string _updateStateMessage;
        public string UpdateStateMessage
        {
            get => _updateStateMessage;
            set
            {
                if (_updateStateMessage != value)
                {
                    _updateStateMessage = value;
                    RaisePropertyChangedEvent();
                }
            }
        }

        private InfoBarSeverity _updateStateSeverity;
        public InfoBarSeverity UpdateStateSeverity
        {
            get => _updateStateSeverity;
            set
            {
                if (_updateStateSeverity != value)
                {
                    _updateStateSeverity = value;
                    RaisePropertyChangedEvent();
                }
            }
        }

        private string _updateStateTitle;
        public string UpdateStateTitle
        {
            get => _updateStateTitle;
            set
            {
                if (_updateStateTitle != value)
                {
                    _updateStateTitle = value;
                    RaisePropertyChangedEvent();
                }
            }
        }

        private string _aboutTextBlockText;
        public string AboutTextBlockText
        {
            get => _aboutTextBlockText;
            set
            {
                if (_aboutTextBlockText != value)
                {
                    _aboutTextBlockText = value;
                    RaisePropertyChangedEvent();
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void RaisePropertyChangedEvent([System.Runtime.CompilerServices.CallerMemberName] string name = null)
        {
            if (name != null) { PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name)); }
        }

        public string VersionTextBlockText
        {
            get
            {
                string ver = $"{Package.Current.Id.Version.Major}.{Package.Current.Id.Version.Minor}.{Package.Current.Id.Version.Build}";
                string name = Package.Current.DisplayName;
                GetAboutTextBlockText();
                return $"{name} v{ver}";
            }
        }

        private async void GetAboutTextBlockText()
        {
            await Task.Run(async () =>
            {
                string langcode = LanguageHelper.GetPrimaryLanguage();
                Uri dataUri = new($"ms-appx:///Assets/About/About.{langcode}.md");
                StorageFile file = await StorageFile.GetFileFromApplicationUriAsync(dataUri);
                if (file != null)
                {
                    string markdown = await FileIO.ReadTextAsync(file);
                    _ = _page?.DispatcherQueue.EnqueueAsync(() => AboutTextBlockText = markdown);
                }
            });
        }



        public SettingsViewModel(SettingPage Page)
        {
            _page = Page;
            Caches = this;
        }

        public async void CheckUpdate()
        {
            CheckingUpdate = true;
            UpdateInfo info = null;
            try
            {
                info = await UpdateHelper.CheckUpdateAsync("DiskTools", "DiskInfo");
            }
            catch (Exception ex)
            {
                UpdateStateIsOpen = true;
                UpdateStateMessage = ex.Message;
                UpdateStateSeverity = InfoBarSeverity.Error;
                GotoUpdateVisibility = Visibility.Collapsed;
                UpdateStateTitle = _loader.GetString("CheckFailed");
                SettingsHelper.LogManager.GetLogger(nameof(SettingsViewModel)).Error(ex.ExceptionToMessage(), ex);
            }
            if (info != null)
            {
                if (info.IsExistNewVersion)
                {
                    UpdateStateIsOpen = true;
                    GotoUpdateTag = info.ReleaseUrl;
                    GotoUpdateVisibility = Visibility.Visible;
                    UpdateStateSeverity = InfoBarSeverity.Warning;
                    UpdateStateTitle = _loader.GetString("FindUpdate");
                    UpdateStateMessage = $"{VersionTextBlockText} -> {info.TagName}";
                }
                else
                {
                    UpdateStateIsOpen = true;
                    GotoUpdateVisibility = Visibility.Collapsed;
                    UpdateStateSeverity = InfoBarSeverity.Success;
                    UpdateStateTitle = _loader.GetString("UpToDate");
                }
            }
            UpdateDate = DateTime.Now;
            CheckingUpdate = false;
        }
    }
}
