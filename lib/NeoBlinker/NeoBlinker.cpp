#include "NeoBlinker.h"

////////////////////////////////
//         Blinker            //
////////////////////////////////

NeoBlinker::NeoBlinker(){
}

//////////////////////////////////////

NeoBlinker::NeoBlinker(int pin, int timerNum){
  init(pin, timerNum);
}

//////////////////////////////////////

void NeoBlinker::init(int pin, int timerNum){
  this->pin=pin;
  this->c = RgbColor(0, 0, 255);

  this->pixels = new NeoPixelBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod>(1, pin);
  this->pixels->Begin();

  xTaskCreatePinnedToCore(
                    NeoBlinker::taskLoop,   /* Task function. */
                    "neoTask",              /* name of task. */
                    1000,                   /* Stack size of task */
                    this,                   /* parameter of the task */
                    1,                      /* priority of the task */
                    &this->neoTask,         /* Task handle to keep track of created task */
                    xPortGetCoreID());      /* pin task to core 0 */    

  Serial.print("NeoTask begin on core ");
  Serial.println(xPortGetCoreID());
}

//////////////////////////////////////

void NeoBlinker::taskLoop(void *pvParameters){
  NeoBlinker *b = (NeoBlinker *)pvParameters;

  RgbColor newC;
  int delayTime = 0;

  while(true) {
    if(!b->taskActive) {
      delay(1);
      continue;
    }

    if(b->pulseMode) {
      float progress = float(b->brightness)/255;

      newC = RgbColor(b->c.R + ((0 - b->c.R) * progress),
                      b->c.G + ((0 - b->c.G) * progress),
                      b->c.B + ((0 - b->c.B) * progress));

      b->pixels->SetPixelColor(0, newC);

      b->brightness += b->fadeDirection;

      if(b->brightness <= 1) {
          b->fadeDirection = 1;
      } else if (b->brightness >= 255) {
          b->fadeDirection = -1;
      }

      delayTime = b->delayTime;

    } else {
      if(!b->ledOn){
          b->pixels->SetPixelColor(0, b->c);
          
          delayTime = b->onTime;
          b->count--;
          b->ledOn = true;
      } else {
          b->pixels->ClearTo(0);
          b->ledOn = false;

          if(b->count){
            delayTime = b->offTime;
          } else {
            delayTime = b->delayTime;
            b->count=b->nBlinks;
          }
      }
    }

    b->pixels->Show();
    
    delay(delayTime);
  }
}

//////////////////////////////////////

void NeoBlinker::start(int period, float dutyCycle){

  start(period, dutyCycle, 1, 0);
}

//////////////////////////////////////

void NeoBlinker::start(int period, float dutyCycle, int nBlinks, int delayTime){
  onTime=dutyCycle*period;
  offTime=period-onTime;
  this->delayTime=delayTime+offTime;
  this->nBlinks=nBlinks;
  count=nBlinks;
  this->pulseMode = false;
  this->taskActive = true;
}

void NeoBlinker::startPulse(int delayTime){
  this->delayTime = delayTime;
  this->pulseMode = true;
  this->taskActive = true;
}

//////////////////////////////////////

void NeoBlinker::stop(){
  this->taskActive = false;
}

//////////////////////////////////////

void NeoBlinker::on(){
  stop();
  this->pixels->SetPixelColor(0, this->c);
  this->pixels->Show();
  this->ledOn = true;
}

//////////////////////////////////////

void NeoBlinker::off(){
  stop();
  this->pixels->ClearTo(0);
  this->pixels->Show();
  this->ledOn = false;
}

void NeoBlinker::setColor(byte r, byte g, byte b) {
    this->c = RgbColor(r, g, b);
}

void NeoBlinker::setBrightness(byte b) {
  float progress = float(b)/255;

  this->c = RgbColor(this->c.R * progress,
                     this->c.G * progress,
                     this->c.B * progress);
}