using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DiskTools
{
    public class ViewModel
    {
        public ObservableCollection<Model> Collection { get; set; }
        public ViewModel()
        {
            Collection = new ObservableCollection<Model>();

            Collection.Add(new Model()
            {
                XValue = 1,
                YValue1 = 18,
                YValue2 = 28,
                YValue3 = 108,
                YValue4 = 128,
            });
            Collection.Add(new Model()
            {
                XValue = 2,
                YValue1 = 36,
                YValue2 = 46,
                YValue3 = 136,
                YValue4 = 146
            });
            Collection.Add(new Model()
            {
                XValue = 3,
                YValue1 = 24,
                YValue2 = 34,
                YValue3 = 124,
                YValue4 = 134
            });
            Collection.Add(new Model()
            {
                XValue = 4,
                YValue1 = 42,
                YValue2 = 52,
                YValue3 = 142,
                YValue4 = 152
            });
            Collection.Add(new Model()
            {
                XValue = 5,
                YValue1 = 30,
                YValue2 = 40,
                YValue3 = 130,
                YValue4 = 140
            });
        }
    }
}
