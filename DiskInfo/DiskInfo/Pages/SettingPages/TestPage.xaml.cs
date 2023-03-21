using DiskInfo.Helpers;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using System;
using System.ComponentModel;
using System.Globalization;
using Windows.Globalization;
using Windows.System;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskInfo.Pages.SettingPages
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class TestPage : Page, INotifyPropertyChanged
    {
        internal bool IsExtendsTitleBar
        {
            get => UIHelper.HasTitleBar ? UIHelper.MainWindow.ExtendsContentIntoTitleBar : WindowHelper.GetAppWindowForCurrentWindow().TitleBar.ExtendsContentIntoTitleBar;
            set
            {
                if (IsExtendsTitleBar != value)
                {
                    if (UIHelper.HasTitleBar)
                    {
                        UIHelper.MainWindow.ExtendsContentIntoTitleBar = value;
                    }
                    else
                    {
                        WindowHelper.GetAppWindowForCurrentWindow().TitleBar.ExtendsContentIntoTitleBar = value;
                    }
                    ThemeHelper.UpdateSystemCaptionButtonColors();
                }
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        private void RaisePropertyChangedEvent([System.Runtime.CompilerServices.CallerMemberName] string name = null)
        {
            if (name != null) { PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name)); }
        }

        public TestPage()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            switch ((sender as FrameworkElement).Tag as string)
            {
                case "Store":
                    _ = Launcher.LaunchUriAsync(new Uri("ms-windows-store://pdp/?ProductId=9P2JFQ43FPPG&mode=mini"));
                    break;
                case "OutPIP":
                    WindowHelper.GetAppWindowForCurrentWindow().SetPresenter(Microsoft.UI.Windowing.AppWindowPresenterKind.Default);
                    break;
                case "EnterPIP":
                    WindowHelper.GetAppWindowForCurrentWindow().SetPresenter(Microsoft.UI.Windowing.AppWindowPresenterKind.CompactOverlay);
                    break;
                default:
                    break;
            }
        }

        private void ComboBox_Loaded(object sender, RoutedEventArgs e)
        {
            ComboBox ComboBox = sender as ComboBox;
            switch (ComboBox.Tag as string)
            {
                case "Language":
                    string lang = SettingsHelper.Get<string>(SettingsHelper.CurrentLanguage);
                    lang = lang == LanguageHelper.AutoLanguageCode ? LanguageHelper.GetCurrentLanguage() : lang;
                    CultureInfo culture = new(lang);
                    ComboBox.SelectedItem = culture;
                    break;
            }
        }

        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox ComboBox = sender as ComboBox;
            switch (ComboBox.Tag as string)
            {
                case "Language":
                    CultureInfo culture = ComboBox.SelectedItem as CultureInfo;
                    if (culture.Name != LanguageHelper.GetCurrentLanguage())
                    {
                        ApplicationLanguages.PrimaryLanguageOverride = culture.Name;
                        SettingsHelper.Set(SettingsHelper.CurrentLanguage, culture.Name);
                    }
                    else
                    {
                        ApplicationLanguages.PrimaryLanguageOverride = string.Empty;
                        SettingsHelper.Set(SettingsHelper.CurrentLanguage, LanguageHelper.AutoLanguageCode);
                    }
                    break;
            }
        }
    }
}
