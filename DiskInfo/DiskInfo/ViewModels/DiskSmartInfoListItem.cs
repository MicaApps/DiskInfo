namespace DiskInfo.ViewModels
{
    public class DiskSmartInfoListItem
    {
        public DiskSmartInfoListItem(string id, string name, string rawValue, string threshold, string current, string worst)
        {
            Id = id;
            Name = name;
            RawValue = rawValue;
            Threshold = threshold;
            Current = current;
            Worst = worst;
        }

        public string Id { get; set; }
        public string Name { get; set; }
        public string RawValue { get; set; }
        public string Threshold { get; set; }
        public string Current { get; set; }
        public string Worst { get; set; }
    }
}
