#include "WinRTLibUtils.h"

CString GetFeatures(CAtaSmart::ATA_SMART_INFO const& info)
{
	CString feature;
	if (info.IsSmartSupported)
	{
		feature += _T("S.M.A.R.T., ");
	}
	if (info.IsApmSupported)
	{
		feature += _T("APM, ");
	}
	if (info.IsAamSupported)
	{
		feature += _T("AAM, ");
	}
	if (info.IsNcqSupported)
	{
		feature += _T("NCQ, ");
	}
	if (info.IsTrimSupported)
	{
		feature += _T("TRIM, ");
	}
	if (info.IsDeviceSleepSupported)
	{
		feature += _T("DevSleep, ");
	}
	if (info.IsStreamingSupported)
	{
		feature += _T("Streaming, ");
	}
	if (info.IsGplSupported)
	{
		feature += _T("GPL, ");
	}
	if (info.IsVolatileWriteCachePresent)
	{
		feature += _T("VolatileWriteCache, ");
	}

	if (!feature.IsEmpty())
	{
		feature.Delete(feature.GetLength() - 2, 2);
	}
	return feature;
}
