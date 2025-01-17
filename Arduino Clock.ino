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

  Serial.begin(9600);
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
  int dly =975;
  secend ++;
  show_animation ++;
  if(digitalRead(touchPin) == HIGH){
    if(isring){
      isring=false;
    }else{
      counter++;
    }
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
      counter=set=0;
    }else if(set==0&&counter==2){
      counter=0;
      set=2;
    }else if(set==2&&counter>0){
      houer=counter;
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
    digitalWrite(led2, HIGH);
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
