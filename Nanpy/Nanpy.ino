#include "cfg_all.h"


#if USE_EEPROM
#include <EEPROM.h>
#endif

#include "BaseClass.h"
#include "ArduinoClass.h"
#include "MethodDescriptor.h"
#include "ComChannel.h"
#include "EEPROMClass.h"
#include "RAMClass.h"

#include "DefineClass.h"
#include "ArduinoCoreClass.h"
#include "WatchdogClass.h"
#include "RegisterClass.h"
#include "CounterClass.h"
#include "InfoClass.h"
#include "WireClass.h"

#include "UltrasonicClass.h"

using namespace nanpy;

MethodDescriptor *m = NULL;

void setup() {
    disable_watchdog_at_startup();
    REGISTER_CLASS(ArduinoClass);                                                   // 0.8 k
    REGISTER_CLASS_CONDITIONAL(nanpy::EEPROMClass, USE_EEPROM);                     // 0.3 k
    REGISTER_CLASS_CONDITIONAL(nanpy::RAMClass, USE_RAM);                           // 
    REGISTER_CLASS_CONDITIONAL(DefineClass, USE_Define);                            // 0.6 k
    REGISTER_CLASS_CONDITIONAL(ArduinoCoreClass, USE_ArduinoCore);                  // 
    REGISTER_CLASS_CONDITIONAL(WatchdogClass, USE_Watchdog);                        // 0.2 k
    REGISTER_CLASS_CONDITIONAL(RegisterClass, USE_Register);                        // 1.5 k
    REGISTER_CLASS_CONDITIONAL(CounterClass, USE_Counter);                          // 
    REGISTER_CLASS_CONDITIONAL(InfoClass, USE_Info);                          // 
    REGISTER_CLASS_CONDITIONAL(DHTClass, USE_DHT);
    REGISTER_CLASS_CONDITIONAL(WireClass, USE_Wire);
    
    // GW Classes
    REGISTER_CLASS_CONDITIONAL(UltrasonicClass, USE_Ultrasonic);

    
    ComChannel::connect();
}

void loop() {
    if(ComChannel::available()) {
        m = new MethodDescriptor();
        Register::elaborate(m);
    }
}
