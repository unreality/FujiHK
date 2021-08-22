#include <NeoPixelBus.h>

////////////////////////////////
//         NeoBlinker         //
////////////////////////////////

class NeoBlinker {
  
  TaskHandle_t neoTask;
  int pin;

  bool ledOn = false;
  bool taskActive = false;

  int nBlinks;
  int onTime;
  int offTime;
  int delayTime;
  int count;

  uint8_t fadeDirection = -1;
  uint8_t brightness = 255;
  bool pulseMode = false;

  NeoPixelBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod> *pixels;
  RgbColor c;

  static void taskLoop(void *pvParameters); 

  public:

  NeoBlinker();
  NeoBlinker(int pin, int timerNum=0);

  void init(int pin, int timerNum=0);
  void start(int period, float dutyCycle=0.5);
  void start(int period, float dutyCycle, int nBlinks, int delayTime);
  void startPulse(int delayTime);
  void stop();
  void on();
  void off();
  void setColor(byte r, byte g, byte b);
  void setBrightness(byte b);
};
