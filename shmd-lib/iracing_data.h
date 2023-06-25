#pragma once

#include <memory>
#include <string>
#include <vector>

#include "irsdk/irsdk_defines.h"

namespace iRacing {
struct Data {
    irsdk_header header;
    irsdk_varHeader headerEntry;
    std::string sessionInfo;
    size_t rawDataLength{};
    std::unique_ptr<char[]> rawData;
};

std::vector<char> serializeData(const Data& data);
Data deserializeData(const std::vector<char>& bytes);
}
