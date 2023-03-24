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
            foreach(var info in Instance.Info)
            {
                if(info.TemperatureData.Count < 2)
                {
                    info.Update();
                    info.Update();
                }
            }
            return Instance;
        }
    }
}
