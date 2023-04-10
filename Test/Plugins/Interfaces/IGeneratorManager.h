#ifndef GENERATORMANAGER
#define GENERATORMANAGER

#include "IPluginInterface.h"

namespace plugin {
    namespace interfaces {


        class IGeneratorManager : public IPluginInterface
        {
        public:
            InterfaceId GetId() const override
            {
                return GetInterfaceId();
            }

            static InterfaceId GetInterfaceId()
            {
                return InterfaceId("IGeneratorManager");
            }
        };
    }
}


#endif // GENERATORMANAGER
