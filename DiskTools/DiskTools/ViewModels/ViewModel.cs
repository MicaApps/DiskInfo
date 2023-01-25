using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DiskInfoLibWinRT;

namespace DiskTools
{
    public class ViewModel
    {
        public IList<DiskInfoLibWinRT.GraphDataPoint> Collection
        {
            get => collection;
        }
        private IList<DiskInfoLibWinRT.GraphDataPoint> collection = new ObservableCollection<DiskInfoLibWinRT.GraphDataPoint>();

        public ViewModel()
        {
            for(int i = 0; i < 10; ++i)
            {
                var p = new GraphDataPoint((ulong)i, (uint)((ulong)i * (ulong)i));
                collection.Add(p);
            }
        }

        public static DiskInfoLibWinRT.Class LibInstance = new Class();
    }
}