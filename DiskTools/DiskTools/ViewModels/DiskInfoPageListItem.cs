using DiskInfoLibWinRT;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DiskTools.ViewModels
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
