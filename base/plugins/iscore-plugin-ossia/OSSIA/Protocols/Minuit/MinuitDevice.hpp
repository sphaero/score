#pragma once
#include <OSSIA/Protocols/OSSIADevice.hpp>

namespace Engine
{
namespace Network
{
class MinuitDevice final : public OwningOSSIADevice
{
    public:
        MinuitDevice(const Device::DeviceSettings& settings);

        bool reconnect() override;
};
}
}
