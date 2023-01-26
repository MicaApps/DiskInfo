
using CommunityToolkit.WinUI.UI;
using DiskTools.Controls;
using DiskTools.Helpers;
using DiskTools.Pages.SettingPages;
using DiskTools.Services;
using Microsoft.UI.Windowing;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Automation;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Media.Animation;
using Microsoft.UI.Xaml.Navigation;
using System;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using Windows.ApplicationModel.Resources;
using Windows.Graphics;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskTools.Pages
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page, INotifyPropertyChanged
    {
        #region Properties
        private readonly AppWindow AppWindow = WindowHelper.GetAppWindowForCurrentWindow();

        public PageHeader PageHeader => NavigationView.FindDescendant<PageHeader>();

        public string GetAppTitleFromSystem => ResourceLoader.GetForViewIndependentUse()?.GetString("AppName") ?? "Disk Tools";

        private bool isShowHeader = false;

        public bool IsShowHeader
        {
            get { return isShowHeader; }
            set { isShowHeader = value; OnPropertyChanged(); OnPropertyChanged("FrameMargin"); }
        }

        public Thickness FrameMargin
        {
            get { return IsShowHeader ? new Thickness(0) : new Thickness(0); }// new Thickness(-46, 0, -32, -36); }
        }

        #endregion

        #region Constructors
        public MainPage()
        {
            InitializeComponent();
            UIHelper.MainPage = this;
            UIHelper.MainWindow.Backdrop.BackdropTypeChanged += OnBackdropTypeChanged;
            DiskInfoService.GetInfo();
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
        #endregion

        #region Initialize
        private void AddNavigationMenuItems()
        {
            int i = 0;
            foreach (var drive in DiskInfoService.Instance.Info)
            {
                NavigationViewItem itemGroup = new NavigationViewItem() { Content = drive.Model, Tag = i, DataContext = drive, Icon = new FontIcon() { Glyph = "\uEDA2" } };

                AutomationProperties.SetName(itemGroup, drive.Model);

                NavigationView.MenuItems.Add(itemGroup);
                ++i;
            }
        }

        private void OnBackdropTypeChanged(BackdropHelper sender, object args) => RootBackground.Opacity = (BackdropType)args == BackdropType.DefaultColor ? 1 : 0;

        private void NavigationView_Loaded(object sender, RoutedEventArgs e)
        {
            // Add handler for ContentFrame navigation.
            NavigationViewFrame.Navigated += On_Navigated;
            NavigationView.SelectedItem = NavigationView.MenuItems.FirstOrDefault();
            NavigationView.PaneDisplayMode = NavigationViewPaneDisplayMode.Auto;
        }
        #endregion

        #region 导航
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

            if (!(_page is null))
            {
                _ = NavigationViewFrame.Navigate(_page, parameter, TransitionInfo);
            }
        }

        private void On_Navigated(object sender, NavigationEventArgs e)
        {
            NavigationView.IsBackEnabled = NavigationViewFrame.CanGoBack;
            if (NavigationViewFrame.SourcePageType == typeof(SettingPage))
            {
                // SettingsItem is not part of NavView.MenuItems, and doesn't have a Tag.
                IsShowHeader = true;
                NavigationView.SelectedItem = (NavigationViewItem)NavigationView.SettingsItem;
                NavigationView.Header = "设置";
            }
            else if (NavigationViewFrame.SourcePageType == typeof(TestPage))
            {
                IsShowHeader = true;
                NavigationView.Header = "测试";
            }
            else
            {
                IsShowHeader = false;
                if (NavigationViewFrame.SourcePageType == typeof(DiskInfoPage))
                {
                    //DiskInfoPage page = NavigationViewFrame.Content as DiskInfoPage;
                    //NavigationViewItem item = (NavigationViewItem)NavigationView.MenuItems[page.ID];
                    //if (item != null) { NavigationView.SelectedItem = item; }
                }
                //NavigationView.Header = (((NavigationViewItem)NavigationView.SelectedItem)?.Content?.ToString());
            }
        }
        #endregion

        #region 任务进度条

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

        #region 标题栏

        private void AppTitleBar_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            if (!UIHelper.HasTitleBar)
            {
                RectInt32 Rect = new((ActualWidth - AppTitleBar.ActualWidth + 48).GetActualPixel(), 0, AppTitleBar.ActualWidth.GetActualPixel(), 32);
                AppWindow.TitleBar.SetDragRectangles(new RectInt32[] { Rect });
            }
        }
        #endregion

        #region Unused : 返回按钮
        //private void NavigationView_BackRequested(NavigationView sender, NavigationViewBackRequestedEventArgs args) => _ = TryGoBack();
        //private bool TryGoBack()
        //{
        //    if (!NavigationViewFrame.CanGoBack)
        //    { return false; }

        //    // Don't go back if the nav pane is overlayed.
        //    if (NavigationView.IsPaneOpen &&
        //        (NavigationView.DisplayMode == NavigationViewDisplayMode.Compact ||
        //         NavigationView.DisplayMode == NavigationViewDisplayMode.Minimal))
        //    { return false; }

        //    NavigationViewFrame.GoBack();
        //    return true;
        //}
        #endregion

        #region Unused : UpdateHeaderMargin
        //private void UpdateHeaderMargin(NavigationView sender)
        //{
        //    if (PageHeader != null)
        //    {
        //        PageHeader.HeaderPadding = sender.DisplayMode == NavigationViewDisplayMode.Minimal
        //            ? (Thickness)Application.Current.Resources["PageHeaderMinimalPadding"]
        //            : (Thickness)Application.Current.Resources["PageHeaderDefaultPadding"];

        //        if (ApiInformation.IsPropertyPresent("Microsoft.UI.Xaml.UIElement", "TranslationTransition"))
        //        {
        //            PageHeader.TranslationTransition = new Vector3Transition();

        //            PageHeader.Translation = sender.DisplayMode == NavigationViewDisplayMode.Minimal &&
        //                     sender.IsBackButtonVisible != NavigationViewBackButtonVisible.Collapsed
        //                ? new System.Numerics.Vector3(-(float)sender.CompactPaneLength + 8, 0, 0)
        //                : new System.Numerics.Vector3(0, 0, 0);
        //        }
        //        else
        //        {
        //            Thickness currMargin = PageHeader.Margin;

        //            PageHeader.Margin = sender.DisplayMode == NavigationViewDisplayMode.Minimal &&
        //                     sender.IsBackButtonVisible != NavigationViewBackButtonVisible.Collapsed
        //                ? new Thickness(-sender.CompactPaneLength + 8, currMargin.Top, currMargin.Right, currMargin.Bottom)
        //                : new Thickness(0, currMargin.Top, currMargin.Right, currMargin.Bottom);
        //        }
        //    }
        //}
        #endregion

        #region INotifyPropertyChanged members

        public event PropertyChangedEventHandler PropertyChanged;

        protected void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChangedEventHandler handler = this.PropertyChanged;
            if (handler != null)
            {
                var e = new PropertyChangedEventArgs(propertyName);
                handler(this, e);
            }
        }

        #endregion
    }
}