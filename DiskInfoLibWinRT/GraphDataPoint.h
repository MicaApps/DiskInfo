#pragma once

#include "GraphDataPoint.g.h"

namespace winrt::DiskInfoLibWinRT::implementation
{
    struct GraphDataPoint : GraphDataPointT<GraphDataPoint>
    {
        GraphDataPoint(uint64_t xValue, uint32_t yValue) : m_xValue{ xValue }, m_yValue{ yValue } {}
        
        uint64_t XValue() { return m_xValue; }
        void XValue(uint64_t xValue) { m_xValue= xValue; }

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
