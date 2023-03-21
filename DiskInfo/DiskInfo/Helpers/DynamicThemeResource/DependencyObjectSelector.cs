using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Markup;
using System;
using Windows.Foundation.Collections;

namespace DiskInfo.Helpers.DynamicThemeResource
{
    [ContentProperty(Name = nameof(References))]
    public class DependencyObjectSelector<T> : DependencyObject where T : DependencyObject
    {
        #region Constructors
        public DependencyObjectSelector()
        {
            References = new DependencyObjectCollection();
        }
        #endregion

        #region Properties
        public DependencyObjectCollection References
        {
            get { return (DependencyObjectCollection)GetValue(ReferencesProperty); }
            set { SetValue(ReferencesProperty, value); }
        }

        public Int32 SelectedIndex
        {
            get { return (Int32)GetValue(SelectedIndexProperty); }
            set { SetValue(SelectedIndexProperty, value); }
        }

        public T SelectedObject
        {
            get { return (T)GetValue(SelectedObjectProperty); }
            set { SetValue(SelectedObjectProperty, value); }
        }
        #endregion

        #region Event Handlers
        private void Evt_OnVectorChangedReferences(IObservableVector<DependencyObject> sender, IVectorChangedEventArgs args)
        {
            UpdateSelectedObject();
        }
        #endregion

        #region Private Implementation Methods
        private void UpdateSelectedObject()
        {
            if (
                References != null
                &&
                SelectedIndex >= 0
                &&
                SelectedIndex < References.Count
                &&
                References[SelectedIndex] is DependencyObjectReference<T>
                )
            {
                BindingOperations.SetBinding
                (
                    this,
                    SelectedObjectProperty,
                    new Binding
                    {
                        Source = References[SelectedIndex],
                        Path = new PropertyPath(nameof(DependencyObjectReference<T>.Value))
                    }
                );
            }
            else
            {
                ClearValue(SelectedObjectProperty);
            }
        }

        private void OnReferencesPropertyChanged(DependencyObjectCollection oldValue, DependencyObjectCollection newValue)
        {
            if (oldValue != null)
                oldValue.VectorChanged -= Evt_OnVectorChangedReferences;

            if (newValue != null)
                newValue.VectorChanged += Evt_OnVectorChangedReferences;
        }

        private static void ReferencesPropertyChanged(DependencyObject dobj, DependencyPropertyChangedEventArgs args)
        {
            DependencyObjectSelector<T> _this = (DependencyObjectSelector<T>)dobj;

            _this.OnReferencesPropertyChanged(args.OldValue as DependencyObjectCollection, args.NewValue as DependencyObjectCollection);
        }

        private static void SelectedIndexPropertyChanged(DependencyObject dobj, DependencyPropertyChangedEventArgs args)
        {
            DependencyObjectSelector<T> _this = (DependencyObjectSelector<T>)dobj;

            _this.UpdateSelectedObject();
        }
        #endregion

        #region Static Data
        public static readonly DependencyProperty ReferencesProperty =
            DependencyProperty.Register(nameof(References),
                                        typeof(DependencyObjectCollection),
                                        typeof(DependencyObjectSelector<T>),
                                        new PropertyMetadata(null, ReferencesPropertyChanged));

        public static readonly DependencyProperty SelectedIndexProperty =
            DependencyProperty.Register(nameof(SelectedIndex),
                                        typeof(Int32),
                                        typeof(DependencyObjectSelector<T>),
                                        new PropertyMetadata(-1, SelectedIndexPropertyChanged));

        public static readonly DependencyProperty SelectedObjectProperty =
            DependencyProperty.Register(nameof(SelectedObject),
                                        typeof(T),
                                        typeof(DependencyObjectSelector<T>),
                                        new PropertyMetadata(default(T)));
        #endregion
    }
}
