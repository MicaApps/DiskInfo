namespace DiskInfo.ViewModels
{

    public class DiskBasicInfoListItem
    {
        public DiskBasicInfoListItem(string icon, string name, string value)
        {
            Icon = icon;
            Name = name;
            Value = value;
        }

        public string Icon { get; set; }
        public string Name { get; set; }
        public string Value { get; set; }
    }
}
