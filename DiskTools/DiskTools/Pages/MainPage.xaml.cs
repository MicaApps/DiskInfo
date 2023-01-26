
using CommunityToolkit.WinUI.UI;
using DiskTools.Controls;
using DiskTools.Helpers;
using DiskTools.Pages.SettingPages;
using Microsoft.UI.Windowing;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Automation;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Media.Animation;
using Microsoft.UI.Xaml.Navigation;
using System;
using System.IO;
using System.Linq;
using Windows.ApplicationModel.Resources;
using Windows.Foundation.Metadata;
using Windows.Graphics;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskTools.Pages
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private readonly AppWindow AppWindow = WindowHelper.GetAppWindowForCurrentWindow();

        public PageHeader PageHeader => NavigationView.FindDescendant<PageHeader>();

        public MainPage()
        {
            InitializeComponent();
            UIHelper.MainPage = this;
            NavigationView.PaneDisplayMode = NavigationViewPaneDisplayMode.Left;
            UIHelper.MainWindow.Backdrop.BackdropTypeChanged += OnBackdropTypeChanged;
            if (UIHelper.HasTitleBar)
            {
                UIHelper.MainWindow.ExtendsContentIntoTitleBar = true;
            }
            else
            {
                AppWindow.TitleBar.ExtendsContentIntoTitleBar = true;
                ActualThemeChanged += (sender, arg) => ThemeHelper.UpdateSystemCaptionButtonColors();
            }

            AddNavigationMenuItems();
        }

        private void AddNavigationMenuItems()
        {
            DriveInfo[] allDirves = DriveInfo.GetDrives();
            foreach (DriveInfo drive in allDirves)
            {
                NavigationViewItem itemGroup = new NavigationViewItem() { Content = drive.Name, Tag = drive.Name, DataContext = drive, Icon = new FontIcon() { Glyph = "\uEDA2" } };

                AutomationProperties.SetName(itemGroup, drive.Name);

                NavigationView.MenuItems.Add(itemGroup);
            }
        }

        private void OnBackdropTypeChanged(BackdropHelper sender, object args) => RootBackground.Opacity = (BackdropType)args == BackdropType.DefaultColor ? 1 : 0;

        private void NavigationView_Loaded(object sender, RoutedEventArgs e)
        {
            // Add handler for ContentFrame navigation.
            NavigationViewFrame.Navigated += On_Navigated;
            NavigationView.SelectedItem = NavigationView.MenuItems[0];
            NavigationView.PaneDisplayMode = NavigationViewPaneDisplayMode.Auto;
        }

        private void NavigationView_Navigate(string NavItemTag, NavigationTransitionInfo TransitionInfo)
        {
            Type _page = null;
            object parameter = null;
            if (NavItemTag == "settings")
            {
                _page = typeof(SettingPage);
            }
            else
            {
                _page = typeof(DiskInfoPage);
                parameter = NavItemTag;
            }
            // Get the page type before navigation so you can prevent duplicate
            // entries in the backstack.
            Type PreNavPageType = NavigationViewFrame.CurrentSourcePageType;

            // Only navigate if the selected page isn't currently loaded.
            if (!(_page is null) && !Equals(PreNavPageType, _page))
            {
                _ = NavigationViewFrame.Navigate(_page, parameter, TransitionInfo);
            }
        }

        private void NavigationView_BackRequested(NavigationView sender, NavigationViewBackRequestedEventArgs args) => _ = TryGoBack();

        private void NavigationView_SelectionChanged(NavigationView sender, NavigationViewSelectionChangedEventArgs args)
        {
            if (args.IsSettingsSelected)
            {
                _ = NavigationViewFrame.Navigate(typeof(SettingPage), null, args.RecommendedNavigationTransitionInfo);
            }
            else if (args.SelectedItemContainer != null)
            {
                string NavItemTag = args.SelectedItemContainer.Tag.ToString();
                NavigationView_Navigate(NavItemTag, args.RecommendedNavigationTransitionInfo);
            }
        }

        private bool TryGoBack()
        {
            if (!NavigationViewFrame.CanGoBack)
            { return false; }

            // Don't go back if the nav pane is overlayed.
            if (NavigationView.IsPaneOpen &&
                (NavigationView.DisplayMode == NavigationViewDisplayMode.Compact ||
                 NavigationView.DisplayMode == NavigationViewDisplayMode.Minimal))
            { return false; }

            NavigationViewFrame.GoBack();
            return true;
        }

        private void On_Navigated(object _, NavigationEventArgs e)
        {
            NavigationView.IsBackEnabled = NavigationViewFrame.CanGoBack;
            if (NavigationViewFrame.SourcePageType == typeof(SettingPage))
            {
                // SettingsItem is not part of NavView.MenuItems, and doesn't have a Tag.
                NavigationView.SelectedItem = (NavigationViewItem)NavigationView.SettingsItem;
                NavigationView.Header = "设置";
            }
            else if (NavigationViewFrame.SourcePageType == typeof(TestPage))
            {
                NavigationView.Header = "测试";
            }
            else
            {
                if (NavigationViewFrame.SourcePageType == typeof(DiskInfoPage))
                {
                    DiskInfoPage page = NavigationViewFrame.Content as DiskInfoPage;
                    NavigationViewItem item = NavigationView.MenuItems.OfType<NavigationViewItem>().FirstOrDefault((x) => x.Content.ToString() == page.ID);
                    if (item != null) { NavigationView.SelectedItem = item; }
                }
                NavigationView.Header = (((NavigationViewItem)NavigationView.SelectedItem)?.Content?.ToString());
            }
        }

        public string GetAppTitleFromSystem => ResourceLoader.GetForViewIndependentUse()?.GetString("AppName") ?? "Disk Tools";

        private void UpdateHeaderMargin(NavigationView sender)
        {
            if (PageHeader != null)
            {
                PageHeader.HeaderPadding = sender.DisplayMode == NavigationViewDisplayMode.Minimal
                    ? (Thickness)Application.Current.Resources["PageHeaderMinimalPadding"]
                    : (Thickness)Application.Current.Resources["PageHeaderDefaultPadding"];

                if (ApiInformation.IsPropertyPresent("Microsoft.UI.Xaml.UIElement", "TranslationTransition"))
                {
                    PageHeader.TranslationTransition = new Vector3Transition();

                    PageHeader.Translation = sender.DisplayMode == NavigationViewDisplayMode.Minimal &&
                             sender.IsBackButtonVisible != NavigationViewBackButtonVisible.Collapsed
                        ? new System.Numerics.Vector3(-(float)sender.CompactPaneLength + 8, 0, 0)
                        : new System.Numerics.Vector3(0, 0, 0);
                }
                else
                {
                    Thickness currMargin = PageHeader.Margin;

                    PageHeader.Margin = sender.DisplayMode == NavigationViewDisplayMode.Minimal &&
                             sender.IsBackButtonVisible != NavigationViewBackButtonVisible.Collapsed
                        ? new Thickness(-sender.CompactPaneLength + 8, currMargin.Top, currMargin.Right, currMargin.Bottom)
                        : new Thickness(0, currMargin.Top, currMargin.Right, currMargin.Bottom);
                }
            }
        }

        #region 状态栏

        public void ShowProgressBar()
        {
            ProgressBar.Visibility = Visibility.Visible;
            ProgressBar.IsIndeterminate = true;
            ProgressBar.ShowError = false;
            ProgressBar.ShowPaused = false;
        }

        public void PausedProgressBar()
        {
            ProgressBar.Visibility = Visibility.Visible;
            ProgressBar.IsIndeterminate = true;
            ProgressBar.ShowError = false;
            ProgressBar.ShowPaused = true;
        }

        public void ErrorProgressBar()
        {
            ProgressBar.Visibility = Visibility.Visible;
            ProgressBar.IsIndeterminate = true;
            ProgressBar.ShowPaused = false;
            ProgressBar.ShowError = true;
        }

        public void HideProgressBar()
        {
            ProgressBar.Visibility = Visibility.Collapsed;
            ProgressBar.IsIndeterminate = false;
            ProgressBar.ShowError = false;
            ProgressBar.ShowPaused = false;
        }

        #endregion
    }
}
