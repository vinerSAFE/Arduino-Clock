#include<Wire.h>
#define RTC 0x68

const int touchPin = 2,buzzerPin = 3,led = 8,led2 = 9;
const int a=4,b=5,c=6,d=7;
const int e=10,f=11,g=12,h=13;

int secend,mint,houer,counter,set,show_animation;

int mint_ring,houer_ring=-1;
bool isring;
void setup() {
  pinMode(touchPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);

  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(h, OUTPUT);

  Wire.begin();
  Serial.begin(9600);

  GPCT();
  // setTime(0,48,13,6,19,4,25);
  byte Secends,Minutes,Hour,Day,Date,Month,Year;
  readTime(&Secends,&Minutes,&Hour,&Day,&Date,&Month,&Year);
  secend =Secends;
  mint=Minutes;
  houer=Hour;
}
void GPCT(){
  //get pc time 
  const char* Time = __TIME__;
  if (sscanf(Time, "%d:%d:%d", &houer, &mint, &secend) != 3) return;
  const char* Date = __DATE__;
  const char* monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  char Month[12];
  int mon,Day,Year;
  if (sscanf(Date, "%s %d %d", Month, &Day, &Year) != 3) return;
  for (int i = 0; i < 12; i++) {
    if (strcmp(Month, monthName[i]) == 0) {
      mon=i+1;
      break;
    }
  }
  int k=mon,j=Year,y,Weekday;
  if (mon < 3) {
    k += 12;
    j--;
  }
  y = j / 100;
  j=j%100;
  Year=Year%100;
  Weekday = (((Day+(13*(k+1))/5+j+j/4+y/4+5*y)%7)+6)%7;
  
  //Set to RTC
  Wire.beginTransmission(RTC);
  Wire.write(0);
  Wire.write(dec2bcd((byte)secend));
  Wire.write(dec2bcd((byte)mint));
  Wire.write(dec2bcd((byte)houer));
  Wire.write(dec2bcd((byte)Weekday));
  Wire.write(dec2bcd((byte)Day));
  Wire.write(dec2bcd((byte)mon));
  Wire.write(dec2bcd((byte)Year));
  Wire.endTransmission();
}
//void setTime(byte Secends,byte Minutes,byte Hour,byte Day,byte Date,byte Month,byte Year){
//  Wire.beginTransmission(RTC);
//  Wire.write(0);
//  Wire.write(dec2bcd(Secends));
//  Wire.write(dec2bcd(Minutes));
//  Wire.write(dec2bcd(Hour));
//  Wire.write(dec2bcd(Day));
//  Wire.write(dec2bcd(Date));
//  Wire.write(dec2bcd(Month));
//  Wire.write(dec2bcd(Year));
//  Wire.endTransmission();
//}
//void monitor(){
//  byte Secends,Minutes,Hour,Day,Date,Month,Year;
//  readTime(&Secends,&Minutes,&Hour,&Day,&Date,&Month,&Year);
//  Serial.print(Hour);
//  Serial.print(":");
//  Serial.print(Minutes);
//  Serial.print(":");
//  Serial.print(Secends);
//  Serial.print("    ");
//  Serial.print(Day);
//  Serial.print("    ");
//  Serial.print(Year);
//  Serial.print("/");
//  Serial.print(Month);
//  Serial.print("/");
//  Serial.print(Date);
//  Serial.println();
//}
byte bcd2dec(byte var){
  return ((var/16*10)+(var%16));
}
byte dec2bcd(byte var){
  return ((var/10*16)+(var%10));
}
void readTime(byte *Secends,byte *Minutes,byte *Hour,byte *Day,byte *Date,byte *Month,byte *Year){
  Wire.beginTransmission(RTC);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(RTC,7);
  *Secends=bcd2dec(Wire.read() & 0x7F);
  *Minutes=bcd2dec(Wire.read());
  *Hour=bcd2dec(Wire.read()& 0x3F);
  *Day=bcd2dec(Wire.read());
  *Date=bcd2dec(Wire.read());
  *Month=bcd2dec(Wire.read());
  *Year=bcd2dec(Wire.read());
}
void show(int bb){
  int numbers[2]={(bb / 10) % 10,bb % 10};
  switch (numbers[1]) {
    case 0:
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(a, LOW);
        break;
    case 1:
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(a, HIGH);
        break;
    case 2:
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(a, LOW);
        break;
    case 3:
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(a, HIGH);
        break;
    case 4:
        digitalWrite(b, LOW);
        digitalWrite(c, HIGH);
        digitalWrite(d, LOW);
        digitalWrite(a, LOW);
        break;
    case 5:
        digitalWrite(b, LOW);
        digitalWrite(c, HIGH);
        digitalWrite(d, LOW);
        digitalWrite(a, HIGH);
        break;
    case 6:
        digitalWrite(b, LOW);
        digitalWrite(c, HIGH);
        digitalWrite(d, HIGH);
        digitalWrite(a, LOW);
        break;
    case 7:
        digitalWrite(b, LOW);
        digitalWrite(c, HIGH);
        digitalWrite(d, HIGH);
        digitalWrite(a, HIGH);
        break;
    case 8:
        digitalWrite(b, HIGH);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(a, LOW);
        break;
    case 9:
        digitalWrite(b, HIGH);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(a, HIGH);
        break;
    default:
        digitalWrite(b, LOW);
        digitalWrite(c, LOW);
        digitalWrite(d, LOW);
        digitalWrite(a, LOW);
        break;
  }
  switch (numbers[0]) {
    case 0:
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        digitalWrite(h, LOW);
        digitalWrite(e, LOW);
        break;
    case 1:
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        digitalWrite(h, LOW);
        digitalWrite(e, HIGH);
        break;
    case 2:
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        digitalWrite(h, HIGH);
        digitalWrite(e, LOW);
        break;
    case 3:
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        digitalWrite(h, HIGH);
        digitalWrite(e, HIGH);
        break;
    case 4:
        digitalWrite(f, LOW);
        digitalWrite(g, HIGH);
        digitalWrite(h, LOW);
        digitalWrite(e, LOW);
        break;
    case 5:
        digitalWrite(f, LOW);
        digitalWrite(g, HIGH);
        digitalWrite(h, LOW);
        digitalWrite(e, HIGH);
        break;
    case 6:
        digitalWrite(f, LOW);
        digitalWrite(g, HIGH);
        digitalWrite(h, HIGH);
        digitalWrite(e, LOW);
        break;
    case 7:
        digitalWrite(f, LOW);
        digitalWrite(g, HIGH);
        digitalWrite(h, HIGH);
        digitalWrite(e, HIGH);
        break;
    case 8:
        digitalWrite(f, HIGH);
        digitalWrite(g, LOW);
        digitalWrite(h, LOW);
        digitalWrite(e, LOW);
        break;
    case 9:
        digitalWrite(f, HIGH);
        digitalWrite(g, LOW);
        digitalWrite(h, LOW);
        digitalWrite(e, HIGH);
        break;
    default:
        digitalWrite(f, LOW);
        digitalWrite(g, LOW);
        digitalWrite(h, LOW);
        digitalWrite(e, LOW);
        break;
  }
}

void loop() {
  //monitor();
  int dly =975;
  secend ++;
  show_animation ++;
  if(digitalRead(touchPin) == HIGH){
    if(isring){
      isring=false;
    }else{
      counter++;
    }
    digitalWrite(led2, LOW);
    analogWrite(buzzerPin, 50);
    delay(50);
    dly-=50;
    digitalWrite(buzzerPin, LOW);
  }else{
    if(set==0&&counter==1){
      counter=0;
      set=1;
    }else if(set==1&&counter>0){
      mint=counter;
      Wire.beginTransmission(RTC);
      Wire.write(0);
      Wire.write(dec2bcd(secend));
      Wire.write(dec2bcd(mint));
      Wire.write(dec2bcd(houer));
      Wire.endTransmission();
      counter=set=0;
    }else if(set==0&&counter==2){
      counter=0;
      set=2;
    }else if(set==2&&counter>0){
      houer=counter;
      Wire.beginTransmission(RTC);
      Wire.write(0);
      Wire.write(dec2bcd(secend));
      Wire.write(dec2bcd(mint));
      Wire.write(dec2bcd(houer));
      Wire.endTransmission();
      counter=set=0;
    }else if(set==0&&counter==3){
      counter=0;
      set=3;
    }else if(set==3&&counter>0){
      mint_ring=counter;
      counter=set=0;
    }else if(set==0&&counter==4){
      counter=0;
      set=4;
    }else if(set==4&&counter>0){
      houer_ring=counter;
      counter=set=0;
    }else{
      counter=set=0;
    }
  }
  
  if(secend>=60){
    mint ++;
    secend =0;
  }
  
  if(mint >=60){
    houer ++;
    mint =0;
  }
  if(houer >24){
    houer =1;
  }

  if(counter>0){
    show(counter);
  }else if(show_animation==1){
    show(houer);
    //digitalWrite(led2, HIGH);
    analogWrite(led2, 80);
  }else if(show_animation==5){
    show(mint);
    digitalWrite(led2, LOW);
  }else if(show_animation>15){
    show_animation=0;
  }

  if(houer==houer_ring&&mint==mint_ring&&secend<2){
    isring=true;
  }else if(isring){
    dly-=200;
    digitalWrite(buzzerPin, HIGH);
    delay(200);
    digitalWrite(buzzerPin, LOW);
  }
  
  digitalWrite(led, HIGH);
  delay(25);
  digitalWrite(led, LOW);
  delay(dly);
}
