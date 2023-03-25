#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>



#define PIN_A 2
#define PIN_B 3
#define PIN_S 4




#define IR_DEBOUNCE_TIME 60

bool left_turn = false;
bool right_turn = false;
bool button = false;
int curr_num = 0;

uint32_t last_interrupt_time_RE = 0;
uint32_t last_interrupt_time_S = 0;

uint32_t A_timestamp = 0;
uint32_t B_timestamp = 0;

// left is A
// right is B

void isrLeft()
{
  uint32_t interrupt_time = millis();
  if (interrupt_time - last_interrupt_time_RE > IR_DEBOUNCE_TIME)
  {
    A_timestamp = millis();
  }
  last_interrupt_time_RE = interrupt_time;
}

void isrRight()
{
  uint32_t interrupt_time = millis();
  if (interrupt_time - last_interrupt_time_RE > IR_DEBOUNCE_TIME)
  {
    B_timestamp = millis();
  }
  last_interrupt_time_RE = interrupt_time;
}

void isrButton()
{
  uint32_t interrupt_time = millis();
  if (interrupt_time - last_interrupt_time_S > IR_DEBOUNCE_TIME)
  {
  }
  last_interrupt_time_S = interrupt_time;
}

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_A, INPUT);
  pinMode(PIN_B, INPUT);
  pinMode(PIN_S, INPUT_PULLUP);
  attachInterrupt(PIN_A, isrLeft, FALLING);
  attachInterrupt(PIN_B, isrRight, FALLING);
}

void loop()
{
  int32_t time_delta = (int32_t)(A_timestamp - B_timestamp);

  if (time_delta < 0)
  {
    
    A_timestamp = 0;
    B_timestamp = 0;
    if(curr_num < 9){
      curr_num += 1;
      Serial.println("\b");
      Serial.println(curr_num);
    }
  }
  if (time_delta > 0)
  {
    A_timestamp = 0;
    B_timestamp = 0;
    if(curr_num > 0){
      curr_num -= 1;
      Serial.println("\r");
      Serial.println(curr_num);

    }
  }
  int pin_S_state = digitalRead(PIN_S);
  if (pin_S_state == LOW)
  {
    Serial.println(" ");
    delay(500);
  }
  
  
}