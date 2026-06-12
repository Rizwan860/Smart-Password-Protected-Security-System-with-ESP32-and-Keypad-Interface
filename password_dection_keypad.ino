#include <Keypad.h>
#include <string.h>

// ---------------- LED PINS ----------------
#define GREEN_LED 21
#define RED_LED   19
#define BLUE_LED  18
#define WHITE_LED 5

// ---------------- KEYPAD ----------------
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {13, 12, 14, 27};
byte colPins[COLS] = {26, 25, 33, 32};

Keypad keypad = Keypad(makeKeymap(keys),
                       rowPins,
                       colPins,
                       ROWS,
                       COLS);

// ---------------- PASSWORDS ----------------
char currentPassword[5] = "1234";

char passwordHistory[5][5] =
{
  "1111",
  "2222",
  "3333",
  "4444",
  "1234"
};

char enteredPassword[5];
byte indexPos = 0;

// ---------------- STATES ----------------
enum State
{
  NORMAL_MODE,
  VERIFY_OLD_PASSWORD,
  ENTER_NEW_PASSWORD,
  CONFIRM_NEW_PASSWORD
};

State systemState = NORMAL_MODE;

char newPassword[5];

// ------------------------------------------------

void blinkLED(int pin, int times)
{
  for(int i=0;i<times;i++)
  {
    digitalWrite(pin,HIGH);
    delay(250);

    digitalWrite(pin,LOW);
    delay(250);
  }
}

// ------------------------------------------------

bool passwordExists(char *pass)
{
  for(int i=0;i<5;i++)
  {
    if(strcmp(pass,passwordHistory[i]) == 0)
    {
      return true;
    }
  }
  return false;
}

// ------------------------------------------------

void addToHistory(char *pass)
{
  for(int i=0;i<4;i++)
  {
    strcpy(passwordHistory[i], passwordHistory[i+1]);
  }

  strcpy(passwordHistory[4], pass);
}

// ------------------------------------------------

void clearInput()
{
  memset(enteredPassword,0,sizeof(enteredPassword));
  indexPos = 0;
}

// ------------------------------------------------

void setup()
{
  Serial.begin(115200);

  pinMode(GREEN_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  pinMode(BLUE_LED,OUTPUT);
  pinMode(WHITE_LED,OUTPUT);

  Serial.println("System Ready");
  Serial.println("Enter Password and press #");
  Serial.println("Press * to change password");
}

// ------------------------------------------------

void loop()
{
  char key = keypad.getKey();

  if(!key) return;

  Serial.print("Key: ");
  Serial.println(key);

  // -------- CHANGE PASSWORD MODE --------
  if(key == '*' && systemState == NORMAL_MODE)
  {
    clearInput();

    systemState = VERIFY_OLD_PASSWORD;

    Serial.println("Enter OLD password then press #");
    return;
  }

  // -------- PASSWORD ENTRY --------
  if(key >= '0' && key <= '9')
  {
    if(indexPos < 4)
    {
      enteredPassword[indexPos++] = key;
    }

    return;
  }

  // -------- CONFIRM --------
  if(key == '#')
  {
    enteredPassword[indexPos] = '\0';

    switch(systemState)
    {

      // ================= NORMAL LOGIN =================
      case NORMAL_MODE:

        if(strcmp(enteredPassword,currentPassword)==0)
        {
          Serial.println("ACCESS GRANTED");

          digitalWrite(GREEN_LED,HIGH);
          delay(2000);
          digitalWrite(GREEN_LED,LOW);
        }
        else
        {
          Serial.println("ACCESS DENIED");

          digitalWrite(RED_LED,HIGH);
          delay(2000);
          digitalWrite(RED_LED,LOW);
        }

        clearInput();
      break;

      // ================= VERIFY OLD PASSWORD =================
      case VERIFY_OLD_PASSWORD:

        if(strcmp(enteredPassword,currentPassword)==0)
        {
          Serial.println("Old Password Correct");

          systemState = ENTER_NEW_PASSWORD;

          Serial.println("Enter NEW password then press #");
        }
        else
        {
          Serial.println("Wrong Old Password");

          blinkLED(RED_LED,3);

          systemState = NORMAL_MODE;
        }

        clearInput();
      break;

      // ================= NEW PASSWORD =================
      case ENTER_NEW_PASSWORD:

        strcpy(newPassword,enteredPassword);

        systemState = CONFIRM_NEW_PASSWORD;

        Serial.println("Confirm NEW password then press #");

        clearInput();
      break;

      // ================= CONFIRM PASSWORD =================
      case CONFIRM_NEW_PASSWORD:

        if(strcmp(newPassword,enteredPassword)!=0)
        {
          Serial.println("Password Mismatch");

          blinkLED(RED_LED,3);
        }
        else if(passwordExists(newPassword))
        {
          Serial.println("Password Already Used");

          blinkLED(WHITE_LED,5);
        }
        else
        {
          strcpy(currentPassword,newPassword);

          addToHistory(newPassword);

          Serial.println("Password Updated Successfully");

          digitalWrite(BLUE_LED,HIGH);
          delay(2000);
          digitalWrite(BLUE_LED,LOW);
        }

        systemState = NORMAL_MODE;

        clearInput();
      break;
    }
  }
}