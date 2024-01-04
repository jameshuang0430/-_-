//pin position declaration:
const int confirmPin = 2;
const int sw1Pin = 11;
const int clearPin = 12;
const int signals = A0;
const int unlockPin = A1;
const int oK = 13;
//global variables declaration:
int counter = 0;
int k=0;
int wrongCounter = 0;
int password=0;
int UserInput=0;
int userInput=0;
int p0=0, p1=0, p2=0, p3=0, p4=0, p5=0, p6=0, p7=0;
int sw1State =0;
//features:
bool confirm();
void waiting();
void blink();
void setPassword();
int getUserInput();
bool isIdentical(int enteredPassword);
void unlock();
void ok();
void clear();

void setup() {
  pinMode(sw1Pin,INPUT);
  pinMode(confirmPin,INPUT);
  for(int i=3;i<=10;i++)
  {
    pinMode(i,INPUT);
  }
  pinMode(clearPin,OUTPUT);
  pinMode(unlockPin,OUTPUT);
  pinMode(signals,OUTPUT);
  pinMode(oK,OUTPUT);
  Serial.begin(9600);
  digitalWrite(clearPin,HIGH);
}

void loop() {
  Serial.println("Do you want to alter the password? ");
  Serial.println("If yes,please keep pressing the setting botton.");
  Serial.println("Or just enter the password to unlock");
  while(!confirm())
  {
    sw1State = digitalRead(sw1Pin);
    if (sw1State == HIGH)
    {
      counter++;
      Serial.println("Current counter: " + String(counter));
    }
    if (counter == 100) 
    {
      Serial.println("SETTING MODE");
      Serial.println("Please enter the old password!");
      //check if user know the old password.
      while(1)
      {      
        waiting();
        if(confirm())
        {
          if (isIdentical(getUserInput()))
          {
            //ok();
            clear();
            break;
          }
          else
          {
            Serial.println("Old password wrong.");
            clear();
            blink();
          }
        }
      }
      blink(); 
      blink();     
      Serial.println("Please setting password and press confirm bottom!");
      while(!confirm())
      {
        waiting();//wating for user enter the password
      }
      setPassword();
      blink();
      counter = 0;
    }
  } 
    userInput = getUserInput();
    //Serial.println("Press comfirm botton to continue.");
    //check password
  if (isIdentical(userInput)) {
    Serial.println("PASSWORD CORRECT!!");
    wrongCounter = 0;
    Serial.println("Wrong times: " + String(wrongCounter));
    //ok();
    unlock();
  } else {
    Serial.println("WRONG!! PLEASE TRY AGAIN.");
    wrongCounter++;
    blink();
    Serial.println("Wrong times: " + String(wrongCounter));
    if(wrongCounter == 3)
    {
      Serial.println("You are entering the wrong password for 3 times in a row. Please waiting 15 second and try again.");
      digitalWrite(clearPin,LOW);
      //waiting for 15s.
      while(k<=15)
      {
        Serial.print(k);
        blink();
        k++;
      }
      analogWrite(signals,0);
      k=0;
      wrongCounter = 0;
    }
    //blinkFor10s();
    clear();
  }
  delay(500);
}

void setPassword() 
{
  password = getUserInput();
  Serial.println("Current Password: " + String(password));
  clear();
  Serial.println("New password set successfully.");
}

int getUserInput()
{
  p0 = digitalRead(3);
  p1 = digitalRead(4);
  p2 = digitalRead(5);
  p3 = digitalRead(6);
  p4 = digitalRead(7);
  p5 = digitalRead(8);
  p6 = digitalRead(9);
  p7 = digitalRead(10);
  int n1 = (p3 << 3) | (p2 << 2) | (p1 << 1) | p0;
  int n2 = p4 + 2*p5 + 4*p6 + 8*p7;
  UserInput =  n2*10 + n1;
  Serial.println("Current input: " + String(UserInput));
  return UserInput;
}
bool isIdentical(int enterPassword) {
  return (password == enterPassword);
}
void unlock(){
  analogWrite(unlockPin, 255);
  delay(3000);
  analogWrite(unlockPin, 0);
  clear();  
}
void clear()
{
  digitalWrite(clearPin, LOW);
  delay(500);
  digitalWrite(clearPin, HIGH);
  delay(500);
}
void blink()
{
  analogWrite(signals,255);
  delay(500);
  analogWrite(signals,0);
  delay(500);
}
//keep the light on.
void waiting()
{
  analogWrite(signals,255);
  delay(250);
  if(confirm() == HIGH){
    analogWrite(signals,0);
  }
}
bool confirm()
{
  return (digitalRead(confirmPin) == HIGH);
}
void ok()
{
  digitalWrite(oK,HIGH);
  delay(2000);
  digitalWrite(oK,LOW);
}