using DiskInfoLibWinRT;
using System.Collections.Generic;

namespace DiskInfo.ViewModels
{
    public class DiskInfoPageListItem
    {
        public DiskInfoPageListItem(string name, IList<GraphDataPoint> data)
        {
            Name = name;
            Data = data;
        }

        public string Name { get; set; }
        public IList<GraphDataPoint> Data { get; set; }
    }
}
