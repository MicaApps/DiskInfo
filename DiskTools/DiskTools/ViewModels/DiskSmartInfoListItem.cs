using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DiskTools.ViewModels
{
    public class DiskSmartInfoListItem
    {
        public DiskSmartInfoListItem(string id, string name, string rawValue, string threshold)
        {
            Id = id;
            Name = name;
            RawValue = rawValue;
            Threshold = threshold;
        }

        public string Id { get; set; }
        public string Name { get; set; }
        public string RawValue { get; set; }
        public string Threshold { get; set; }
    }
}
