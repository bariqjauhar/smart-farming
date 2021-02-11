// kelompok D4 proyek penyiraman otomatis berbasis IOT
#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).LJbQLPE-YuPB3RAL-1o8v341R-y7RfNF
char auth[] = "jtiPbKBcVigAr6UHwtJbptPf8jRuzYdT";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "mmmm";
char pass[] = "gajahterbang";

// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial1

    const int pinDigital = A0; //inisialisasi pin sensor
    const int relay = 12;       //inisialisasi pin relay 


// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX 

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);
WidgetLCD lcd(V1); //lcd android


void setup()
{
  // Debug console
  Serial.begin(9600);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

//  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 8080); //khusus indihomo
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);


      pinMode(pinDigital, INPUT);   //menetapkan pin A0 sebagai input
      pinMode(relay, OUTPUT);       //menetapkan pin 6 sebagai output
}



void loop()
{
  Blynk.run();
 
int dataAnalog = analogRead (pinDigital);  //membaca nilai dari pin sensor
//print hasil ke serial monitor
Blynk.virtualWrite (V3, dataAnalog);// data ke Blynk
Serial.print ("A0 : ");
Serial.print (dataAnalog);

//jika nilai A0 kurang dari 500, print kata serta nyalakan led hijau dan matikan led kuning, merah dan juga relay
if (dataAnalog < 500) { 
  Serial.println(". Media Masih Basah"); 

  digitalWrite (relay, HIGH);
//      BLYNK_READ(V1)
//        {
          Blynk.virtualWrite(V1,"Media Masih");
          Blynk.virtualWrite(V2,"Basah");
//        }
  }

 //tetapi, jika nilai A0 kurang dari 900, print kata serta nyalakan led kuning dan relay kemudian matikan led hijau dan juga merah
 else if (dataAnalog > 501 && dataAnalog < 800) {
  Serial.println(". Kelembaban Tanah Masih Cukup"); 

  digitalWrite (relay, HIGH);
          Blynk.virtualWrite(V1,"Kelembaban Tanah");
          Blynk.virtualWrite(V2,"Masih Cukup");
  }

 //selain dari itu, hanya nyalakan led merah dan juga relay
 else if ( dataAnalog > 800){ 
  Serial.println (". Media Kering Perlu Tambahan Air"); 

  digitalWrite (relay, LOW);

          Blynk.virtualWrite(V1,"Media Kering");
          Blynk.virtualWrite(V2,"Perlu Tambahan Air");
  }

 delay (500);
  
}
