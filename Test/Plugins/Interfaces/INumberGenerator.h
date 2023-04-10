#ifndef INUMBERGENERATOR
#define INUMBERGENERATOR

#include "IPluginInterface.h"

namespace plugin {
    namespace interfaces {

        class INumberGenerator : public IPluginInterface
        {
        public:
            virtual int GetNumber() = 0;

            InterfaceId GetId() const override
            {
                return GetInterfaceId();
            }

            static InterfaceId GetInterfaceId()
            {
                return InterfaceId("INumberGenerator");
            }
        };
    }
}


#endif // INUMBERGENERATOR
