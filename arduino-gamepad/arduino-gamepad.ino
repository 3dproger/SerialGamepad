#define BUTTONS_COUNT 4
const int buttonsPins[BUTTONS_COUNT] = { 16, 5, 4, 14 }; // ESP2866
int timer = 0;

bool buttonsStates[BUTTONS_COUNT];

void printStates()
{
  for (int i = 0; i < BUTTONS_COUNT; ++i)
  {
    Serial.print(String() + buttonsStates[i]);
  }

  Serial.println("");
}

void setup()
{
  Serial.begin(9600);
  
  for (int i = 0; i < BUTTONS_COUNT; ++i)
  {
    pinMode(buttonsPins[i], INPUT);
  }
}

void loop()
{
  bool needSend = false;
  
  for (int i = 0; i < BUTTONS_COUNT; ++i)
  {
    const bool down = digitalRead(buttonsPins[i]);
    if (buttonsStates[i] != down)
    {
      buttonsStates[i] = down;
      needSend = true;
    }
  }

  if (needSend)
  {
    printStates();
    delay(10);
    timer = 0;
  }

  if (timer > 500)
  {
    printStates();
    timer = 0;
  }
  
  timer++;
  delay(1);
}
