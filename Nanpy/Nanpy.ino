#include "cfg_all.h"

// external libraries should be put inside #if ... #endif
//    internal headers not.


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
//
    REGISTER_CLASS_CONDITIONAL(MCP41xxxClass, USE_MCP41xxx);
    REGISTER_CLASS_CONDITIONAL(nanpy::EEPROMClass, USE_EEPROM);                     // 0.3 k
    REGISTER_CLASS_CONDITIONAL(nanpy::RAMClass, USE_RAM);                           // 
    REGISTER_CLASS_CONDITIONAL(LiquidCrystalClass, USE_LiquidCrystal);              //  2.3 k
    REGISTER_CLASS_CONDITIONAL(LiquidCrystalClass_I2C, USE_LiquidCrystal_I2C);
    REGISTER_CLASS_CONDITIONAL(OneWireClass, USE_OneWire);                          // 1.7 k
    REGISTER_CLASS_CONDITIONAL(DallasTemperatureClass, USE_DallasTemperature);      // 6.1 k
    REGISTER_CLASS_CONDITIONAL(StepperClass, USE_Stepper);                          // 0.8 k
    REGISTER_CLASS_CONDITIONAL(ServoClass, USE_Servo);                              // 2.5 k
    REGISTER_CLASS_CONDITIONAL(ToneClass, USE_Tone);                                // 2.2 k
    REGISTER_CLASS_CONDITIONAL(CapacitiveSensorClass, USE_CapacitiveSensor);        // 2.2 k
    REGISTER_CLASS_CONDITIONAL(DefineClass, USE_Define);                            // 0.6 k
    REGISTER_CLASS_CONDITIONAL(ArduinoCoreClass, USE_ArduinoCore);                  // 
    REGISTER_CLASS_CONDITIONAL(WatchdogClass, USE_Watchdog);                        // 0.2 k
    REGISTER_CLASS_CONDITIONAL(RegisterClass, USE_Register);                        // 1.5 k

    REGISTER_CLASS_CONDITIONAL(CounterClass, USE_Counter);                          // 
    REGISTER_CLASS_CONDITIONAL(InfoClass, USE_Info);                          // 
    REGISTER_CLASS_CONDITIONAL(DHTClass, USE_DHT);
    REGISTER_CLASS_CONDITIONAL(WireClass, USE_Wire);
    
    REGISTER_CLASS_CONDITIONAL(TLC5947Class, USE_TLC5947);

    REGISTER_CLASS_CONDITIONAL(nanpy::EspClass, USE_ESP);

    // GW Classes
    REGISTER_CLASS_CONDITIONAL(UltrasonicClass, USE_Ultrasonic);
    REGISTER_CLASS_CONDITIONAL(ColorSensorClass, USE_ColorSensor);
    
    ComChannel::connect();
}

void loop() {
    if(ComChannel::available()) {
        m = new MethodDescriptor();
        Register::elaborate(m);
    }
}
