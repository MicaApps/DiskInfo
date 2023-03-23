using DiskInfoLibWinRT;

namespace DiskInfo.Services
{
    public class DiskInfoService
    {
        public static DiskInfoLibWinRT.Class Instance { get; set; }


        public static DiskInfoLibWinRT.Class GetInfo()
        {
            //return Mock();
            Instance = new Class();
            return Instance;
        }
    }
}
