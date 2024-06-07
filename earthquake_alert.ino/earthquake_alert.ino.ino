#include <ESP8266WiFi.h> 
#include<FirebaseArduino.h>
//#include<ArduinoJson.h>
//#include <ESP8266HTTPClient.h>
#define FIREBASE_HOST "earthquakedata-89740-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH ""
#define ssid ""
#define pass ""
int bpin=D4;
int lpin=D2;
int vpin=D0;
String DB="update";
String id="id";
String mes="message";
String vib="vibration";
void setup() {
   WiFi.begin(ssid, pass);
  //Serial.end();
// Serial.begin(115200);
 
  while (WiFi.status() != WL_CONNECTED) {
   //Serial.println("not connected:");
    delay(500);
  }
  //Serial.println(" connected:");
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  // pinMode(bpin, OUTPUT);
 
  pinMode(lpin, OUTPUT);
   pinMode(vpin, INPUT);
   noTone(bpin);
 
}

int id_n=6;
void loop() {
 // digitalWrite(LED_BUILTIN, LOW );   
 // delay(1000);                       
 // digitalWrite(LED_BUILTIN,HIGH );    
  //delay(1000);    
  int v;
  Firebase.setFloat("number", 42.0);
  v=digitalRead(vpin);
  int m=pulseIn(vpin,HIGH);
  if(m>=2000)
  {
     String msg2="earthquake Alert";
 String addid=DB+"/"+id_n+"/"+id;
 String addm=DB+"/"+id_n+"/"+mes;
  String addvib=DB+"/"+id_n+"/"+vib;
 Firebase.setInt(addid,id_n);
 // if (Firebase.failed()) {
//      Serial.print("setting /number failed:");
//      Serial.println(Firebase.error());  
//      return;
 // }
 
 Firebase.setString(addm,msg2); 
  Firebase.setInt(addvib,m); 
    delay(500);
  digitalWrite(lpin, HIGH);
   tone(bpin, 650) ;
   delay (3000); 
   noTone(bpin) ;
   delay (1000); 
   delay(2000);// wait for 3 second
   noTone(bpin);
id_n++;
  }
  else 
  {
  
  digitalWrite(D2, LOW); 
  delay(1000);
  noTone(bpin) ;
  }
 
  
  // wait for a second
}
