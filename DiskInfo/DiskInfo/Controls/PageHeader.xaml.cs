using Microsoft.UI.Composition;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Hosting;
using System;
using Windows.UI;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace DiskInfo.Controls
{
    public sealed partial class PageHeader : UserControl
    {
        public Action CopyLinkAction { get; set; }
        public Action ToggleThemeAction { get; set; }

        public object Title
        {
            get => GetValue(TitleProperty);
            set => SetValue(TitleProperty, value);
        }

        public static readonly DependencyProperty TitleProperty =
            DependencyProperty.Register("Title", typeof(object), typeof(PageHeader), new PropertyMetadata(null));


        public object Subtitle
        {
            get => GetValue(SubtitleProperty);
            set => SetValue(SubtitleProperty, value);
        }

        public static readonly DependencyProperty SubtitleProperty =
            DependencyProperty.Register("Subtitle", typeof(object), typeof(PageHeader), new PropertyMetadata(null));



        public Thickness HeaderPadding
        {
            get => (Thickness)GetValue(HeaderPaddingProperty);
            set => SetValue(HeaderPaddingProperty, value);
        }

        // Using a DependencyProperty as the backing store for BackgroundColorOpacity.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty HeaderPaddingProperty =
            DependencyProperty.Register("HeaderPadding", typeof(Thickness), typeof(PageHeader), new PropertyMetadata((Thickness)App.Current.Resources["PageHeaderDefaultPadding"]));


        public double BackgroundColorOpacity
        {
            get => (double)GetValue(BackgroundColorOpacityProperty);
            set => SetValue(BackgroundColorOpacityProperty, value);
        }

        // Using a DependencyProperty as the backing store for BackgroundColorOpacity.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty BackgroundColorOpacityProperty =
            DependencyProperty.Register("BackgroundColorOpacity", typeof(double), typeof(PageHeader), new PropertyMetadata(0.0));


        public double AcrylicOpacity
        {
            get => (double)GetValue(AcrylicOpacityProperty);
            set => SetValue(AcrylicOpacityProperty, value);
        }

        // Using a DependencyProperty as the backing store for BackgroundColorOpacity.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty AcrylicOpacityProperty =
            DependencyProperty.Register("AcrylicOpacity", typeof(double), typeof(PageHeader), new PropertyMetadata(0.3));

        public double ShadowOpacity
        {
            get => (double)GetValue(ShadowOpacityProperty);
            set => SetValue(ShadowOpacityProperty, value);
        }

        // Using a DependencyProperty as the backing store for BackgroundColorOpacity.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty ShadowOpacityProperty =
            DependencyProperty.Register("ShadowOpacity", typeof(double), typeof(PageHeader), new PropertyMetadata(0.0));

        public UIElement TitlePanel => PageTitle;

        public PageHeader()
        {
            InitializeComponent();
            InitializeDropShadow(ShadowHost, TitleTextBlock.GetAlphaMask());
        }

        /// <summary>
        /// This method will be called when a <see cref="ItemPage"/> gets unloaded. 
        /// Put any code in here that should be done when a <see cref="ItemPage"/> gets unloaded.
        /// </summary>
        /// <param name="sender">The sender (the ItemPage)</param>
        /// <param name="e">The <see cref="RoutedEventArgs"/> of the ItemPage that was unloaded.</param>
        public void Event_ItemPage_Unloaded(object sender, RoutedEventArgs e)
        {

        }

        private void InitializeDropShadow(UIElement shadowHost, CompositionBrush shadowTargetBrush)
        {
            Visual hostVisual = ElementCompositionPreview.GetElementVisual(shadowHost);
            Compositor compositor = hostVisual.Compositor;

            // Create a drop shadow
            DropShadow dropShadow = compositor.CreateDropShadow();
            dropShadow.Color = Color.FromArgb(102, 0, 0, 0);
            dropShadow.BlurRadius = 4.0f;
            // Associate the shape of the shadow with the shape of the target element
            dropShadow.Mask = shadowTargetBrush;

            // Create a Visual to hold the shadow
            SpriteVisual shadowVisual = compositor.CreateSpriteVisual();
            shadowVisual.Shadow = dropShadow;

            // Add the shadow as a child of the host in the visual tree
            ElementCompositionPreview.SetElementChildVisual(shadowHost, shadowVisual);

            // Make sure size of shadow host and shadow visual always stay in sync
            ExpressionAnimation bindSizeAnimation = compositor.CreateExpressionAnimation("hostVisual.Size");
            bindSizeAnimation.SetReferenceParameter("hostVisual", hostVisual);

            shadowVisual.StartAnimation("Size", bindSizeAnimation);
        }
    }
}
