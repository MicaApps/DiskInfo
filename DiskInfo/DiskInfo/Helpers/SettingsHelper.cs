using CommunityToolkit.WinUI.Helpers;
using MetroLog;
using MetroLog.Targets;
using Microsoft.UI.Xaml;
using System;
using System.IO;
using System.Threading.Tasks;
using Windows.Storage;
using IObjectSerializer = CommunityToolkit.Common.Helpers.IObjectSerializer;
using JsonSerializer = System.Text.Json.JsonSerializer;

namespace DiskInfo.Helpers
{
    public static partial class SettingsHelper
    {
        public const string UpdateDate = "UpdateDate";
        public const string CurrentLanguage = "CurrentLanguage";
        public const string SelectedAppTheme = "SelectedAppTheme";
        public const string SelectedBackdrop = "SelectedBackdrop";
        public const string UpdateInterval = "UpdateInterval";
        public const string AutoRefresh = "AutoRefresh";
        public const string AsciiView = "AsciiView";
        public const string DumpSmartReadData = "DumpSmartReadData";
        public const string DumpSmartReadThreshold = "DumpSmartReadThreshold";
        public const string DumpIdentifyDevice = "DumpIdentifyDevice";

        public static Type Get<Type>(string key) => LocalObject.Read<Type>(key);
        public static void Set<Type>(string key, Type value) => LocalObject.Save(key, value);
        public static void SetFile<Type>(string key, Type value) => LocalObject.CreateFileAsync(key, value);
        public static async Task<Type> GetFile<Type>(string key) => await LocalObject.ReadFileAsync<Type>(key);

        public static void SetDefaultSettings()
        {
            if (!LocalObject.KeyExists(UpdateDate))
            {
                LocalObject.Save(UpdateDate, new DateTime());
            }
            if (!LocalObject.KeyExists(CurrentLanguage))
            {
                LocalObject.Save(CurrentLanguage, LanguageHelper.AutoLanguageCode);
            }
            if (!LocalObject.KeyExists(SelectedAppTheme))
            {
                LocalObject.Save(SelectedAppTheme, ElementTheme.Default);
            }
            if (!LocalObject.KeyExists(SelectedBackdrop))
            {
                LocalObject.Save(SelectedBackdrop, BackdropType.Mica);
            }
        }
    }

    public static partial class SettingsHelper
    {
        public static readonly ILogManager LogManager = LogManagerFactory.CreateLogManager(GetDefaultReleaseConfiguration());
        private static readonly ApplicationDataStorageHelper LocalObject = ApplicationDataStorageHelper.GetCurrent(new SystemTextJsonObjectSerializer());

        static SettingsHelper() => SetDefaultSettings();

        private static LoggingConfiguration GetDefaultReleaseConfiguration()
        {
            string path = Path.Combine(ApplicationData.Current.LocalFolder.Path, "MetroLogs");
            if (!Directory.Exists(path)) { Directory.CreateDirectory(path); }
            LoggingConfiguration loggingConfiguration = new();
            loggingConfiguration.AddTarget(LogLevel.Info, LogLevel.Fatal, new StreamingFileTarget(path, 7));
            return loggingConfiguration;
        }
    }

    public class SystemTextJsonObjectSerializer : IObjectSerializer
    {
        string IObjectSerializer.Serialize<T>(T value) => JsonSerializer.Serialize(value);

        public T Deserialize<T>(string value) => JsonSerializer.Deserialize<T>(value);
    }
}
