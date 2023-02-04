#pragma once

#include "GraphDataPoint.g.h"

namespace winrt::DiskInfoLibWinRT::implementation
{
    struct GraphDataPoint : GraphDataPointT<GraphDataPoint>
    {
        GraphDataPoint(uint64_t xValue, uint32_t yValue) : m_xValue{ xValue }, m_yValue{ yValue } {}
        
        auto XValue() 
        { 
            return winrt::clock::from_time_t(static_cast<time_t>(m_xValue)); 
        }
        void XValue(winrt::Windows::Foundation::DateTime xValue) 
        { 
            m_xValue = winrt::clock::to_time_t(xValue); 
        }

        uint64_t YValue() { return m_yValue; }
        void YValue(uint64_t yValue) { m_yValue = yValue; }
    private:
        uint64_t m_xValue{};
        uint32_t m_yValue{};
    };
}

namespace winrt::DiskInfoLibWinRT::factory_implementation
{
    struct GraphDataPoint : GraphDataPointT<GraphDataPoint, implementation::GraphDataPoint>
    {
    };
}
