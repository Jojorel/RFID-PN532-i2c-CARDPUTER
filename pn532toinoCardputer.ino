#include M5CoreS3.h
#include Wire.h
#include PN532.h
#include NfcAdapter.h
#include PN532_I2C.h
#include M5Cardputer.h


PN532_I2C pn532(Wire);   Create PN532 instance.  创建PN532实例
PN532 nfc(pn532);

void setup() {
    M5.begin();              Init M5Stack.  初始化M5Stack
    M5.Power.begin();        Init power  初始化电源模块
    M5.Lcd.setTextSize(1);   Set the text size to 2.  设置文字大小为2
    Wire.begin();   Wire init, adding the I2C bus.  Wire初始化, 加入i2c总线
    pn532.begin();
    pn532.wakeup();   Init PN532.  初始化 PN532
    Serial.begin(115200);
    nfc.begin();
  Verifica a conexao do modulo PN532
    uint32_t versiondata = nfc.getFirmwareVersion();

  if (! versiondata)
  {
    M5.Lcd.setRotation(1);
    M5.Lcd.setTextColor(RED);
    M5.Lcd.println(Not Found Pn532Card...);
    while (1);  halt
  } 


    M5.Lcd.setRotation(1);
  Conexao ok, mostra informacoes do firmware
    M5.Lcd.print(Found chip PN5); M5.Lcd.println((versiondata  24) & 0xFF, HEX);
    M5.Lcd.print(Firmware verion ); M5.Lcd.print((versiondata  16) & 0xFF, DEC);
    M5.Lcd.print('.'); M5.Lcd.println((versiondata  8) & 0xFF, DEC);
   Set the max number of retry attempts to read from a card
   This prevents us from waiting forever for a card, which is
   the default behaviour of the PN532.
    nfc.setPassiveActivationRetries(0xFF);
   configure board to read RFID tags
    nfc.SAMConfig();
    M5.Lcd.println(Waiting Card...);
    M5.Lcd.println();
    }

void loop() {
  M5.Lcd.setRotation(1);
  boolean success;
  Buffer para armazenar a UID lida
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  Tamanho da UID (4 ou 7 bytes dependendo do tipo do cartao)
  uint8_t uidLength;
  Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  'uid' will be populated with the UID, and uidLength will indicate
  if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
    M5.Lcd.setTextWrap(true,false);
    M5.Lcd.setCursor(0, 47);
    if (success)
    M5.Lcd.println(Detected Card!);
    M5.Lcd.print(Size UID ); M5.Lcd.print(uidLength, DEC); M5.Lcd.println( bytes);
    M5.Lcd.println(UID );
    for (uint8_t i = 0; i  uidLength; i++)
    {
      M5Cardputer.Speaker.tone(8000, 20);
      M5.Lcd.print( 0x); M5.Lcd.print(uid[i], HEX);
    }
    M5.Lcd.println();
    Aguarda 1 segundo para continuar
    delay(1000);
  


        return;
}