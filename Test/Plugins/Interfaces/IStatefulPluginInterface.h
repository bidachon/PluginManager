#ifndef ISTATEFULPLUGININTERFACE_H_697F0162_2C99_46A9_9AEA_D86724F726EF
#define ISTATEFULPLUGININTERFACE_H_697F0162_2C99_46A9_9AEA_D86724F726EF

#include "IPluginInterface.h"

namespace plugin::interfaces {

    class IStatefulPluginInterface : public IPluginInterface
    {
    public:
        static constexpr auto DEFAULT_VALUE = -12345;

        virtual void SetNumber(int value) = 0;
        virtual int  GetNumber() const = 0;

        InterfaceId GetId() const override
        {
            return GetInterfaceId();
        }

        static InterfaceId GetInterfaceId()
        {
            return InterfaceId("IStatefulPluginInterface");
        }
    };
}

#endif // ISTATEFULPLUGININTERFACE_H_697F0162_2C99_46A9_9AEA_D86724F726EF

