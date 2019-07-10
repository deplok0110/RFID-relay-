// https://www.instructables.com/id/MFRC522-RFID-Reader-Interfaced-With-NodeMCU/
// https://kelasrobot.com/cara-mudah-mengirim-pesan-dari-nodemcu-ke-telegram-telegrambot-part1/

#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define RELAY D8

#define SS_PIN D4
#define RST_PIN D3
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

char ssid[] = "DeepLock"; 
char password[] = "deeplock1130@";
#define BOTtoken "819820249:AAGEe_ZX9mrgKuhfuF7eYJjDm8mKq9e1fO0"
String chatid = "-252060284";
int switchState, jumlah= 0;
int relay_session=1;

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() 
{
  Serial.begin(115200);
  WifiStatus();

  bot.sendMessage(chatid, "Bot Terkoneksi");
  Serial.print("\n\nBOT Sudah Siap Di Gunakan .....");
  
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  pinMode(RELAY,OUTPUT);
  digitalWrite(RELAY,HIGH);
  
  Serial.println("Tempelkan RFID tag ...");
  Serial.println();

}

void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "89 7B 97 55") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    
    if(relay_session==1){
        digitalWrite(RELAY,LOW);
        Serial.println("Relay Menyala");
        bot.sendMessage(chatid, "RFID CADIPA TerAutentikasi  ..... Relay Menyala");
        relay_session=0; 
     }else{
        digitalWrite(RELAY,HIGH);
        Serial.println("Relay Mati");
        bot.sendMessage(chatid, "RFID CADIPA TerAutentikasi  ..... Relay Mati");
        relay_session=1;
     }
     
    
    Serial.println("Notif Sended To Telegram\n");
  }
 
 else   {
    Serial.println("Access denied");
    bot.sendMessage(chatid, "Access denied  " + content.substring(1));
    Serial.println("Notif Sended To Telegram\n");
  }
}

void WifiStatus() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
