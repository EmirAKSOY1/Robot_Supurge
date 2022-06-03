 #define echoPin 12 //Ultrasonik sensörün echo pini Arduino'nun 12.pinine
#define trigPin 13 //Ultrasonik sensörün trig pini Arduino'nun 13.pinine tanımlandı.
#define MotorR1 9
#define MotorR2 10
#define MotorRE 11  // Motor pinlerini tanımlıyoruz.
#define MotorL1 4
#define MotorL2 5
#define MotorLE 3

long sure, uzaklik; //süre ve uzaklık diye iki değişken tanımlıyoruz.
int islem;
char Incoming_value = 0;
#include <Servo.h>
Servo servo;                
void setup() 
{
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorLE, OUTPUT); //Motorlarımızı çıkış olarak tanımlıyoruz.
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorRE, OUTPUT);
  Serial.begin(9600);         
        
  servo.attach(8);
}

void loop()
{
  Serial.println("Loop a Girdim");
  if(Serial.available() > 0)  
  {
    
    Incoming_value = Serial.read();      
    Serial.println(Incoming_value);        
         
    if(Incoming_value == '1'){
      
        

      islem=1;
      }
    else if(Incoming_value == '0')       
    {
      islem=0;
       
     }
  
  }///

  if(islem==1)
  {
    digitalWrite(trigPin, LOW); //sensör pasif hale getirildi
        delayMicroseconds(5);
        digitalWrite(trigPin, HIGH); //Sensore ses dalgasının üretmesi için emir verildi
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW); //Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi

        sure = pulseIn(echoPin, HIGH); //ses dalgasının geri dönmesi için geçen sure ölçülüyor
        uzaklik = sure / 29.1 / 2; //ölçülen süre uzaklığa çevriliyor

        Serial.println(uzaklik);

        if (uzaklik < 20) // Uzaklık 15'den küçük ise,
        {
          geri();  // 150 ms geri git
          
          delay(200);
          sag();  // 250 ms sağa dön
          delay(250);
        }
        else {  // değil ise,
            
          Serial.println("İleri");
          ileri(); // ileri git
        }             
      
      servo.write(0);//Sonsuz Döner 
  }

  if(islem==0){
    dur();
      servo.write(90);//Dönen Servoyu Durdurur.
  }
                       
} 
void ileri(){  // Robotun ileri yönde hareketi için fonksiyon tanımlıyoruz.

  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi pasif
  analogWrite(MotorRE, 150); // Sağ motorun hızı 150

  digitalWrite(MotorL1, HIGH); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi pasif
  analogWrite(MotorLE, 150); // Sol motorun hızı 150
  
  
}


void sag(){ // Robotun sağa dönme hareketi için fonksiyon tanımlıyoruz.

  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi pasif
  analogWrite(MotorRE, 0); // Sağ motorun hızı 0 (Motor duruyor)

  digitalWrite(MotorL1, HIGH); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi pasif
  analogWrite(MotorLE, 150); // Sol motorun hızı 150
  
  
}


void geri(){ // Robotun geri yönde hareketi için fonksiyon tanımlıyoruz.

  digitalWrite(MotorR1, LOW); // Sağ motorun ileri hareketi pasif
  digitalWrite(MotorR2, HIGH); // Sağ motorun geri hareketi aktif
  analogWrite(MotorRE, 150); // Sağ motorun hızı 150

  digitalWrite(MotorL1, LOW); // Sol motorun ileri hareketi pasif
  digitalWrite(MotorL2, HIGH); // Sol motorun geri hareketi aktif
  analogWrite(MotorLE, 150); // Sol motorun hızı 150
  
}
void dur(){
    digitalWrite(MotorR1, LOW); // Sağ motorun ileri hareketi pasif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi aktif
  analogWrite(MotorRE, 0); // Sağ motorun hızı 150

  digitalWrite(MotorL1, LOW); // Sol motorun ileri hareketi pasif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi aktif
  analogWrite(MotorLE, 0); // Sol motorun hızı 150
}
