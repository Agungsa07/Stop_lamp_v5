#define RUN_DEMO 0
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "font.h"
#include "web.h"
#include "animasi.h"
#include <ArduinoJson.h>
#include <FS.h>
// Turn on debug statements to the serial output
// Specific SPI hardware interface
//MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, SPI1, CS_PIN, MAX_DEVICES);
// Arbitrary pins5
//MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// We always wait a bit between updates of the display

void saveToJson(int intValue1, int intValue2, String text1,String text2,String text3, String a2,
                String a3, String a4, String a5, String a6, String a7, String a8, String a9, String a10, String a11,
                String a12, String a13, String a14, String a15, String a16, String a17, String a18, String a19,
                String a20, String a21, String a22, String a23, String a24, String a25, String a26, String a27, String a28,
                String a29, String a30, int font, int durasi, int bright) {
  DynamicJsonDocument doc(1024);  // Ukuran buffer JSON
  doc["font"] = font;
  doc["durasi"] = durasi;
  doc["bright"] = bright;
  doc["mode"] = intValue1;
  doc["rem"] = intValue2;
  doc["text1"] = text1;
  doc["text2"] = text2;
  doc["text3"] = text3;
  doc["anim1"] = a2;
  doc["anim2"] = a3;
  doc["anim3"] = a4;
  doc["anim4"] = a5;
  doc["anim5"] = a6;
  doc["anim6"] = a7;
  doc["anim7"] = a8;
  doc["anim8"] = a9;
  doc["anim9"] = a10;
  doc["anim10"] = a11;
  doc["anim11"] = a12;
  doc["anim12"] = a13;
  doc["anim13"] = a14;
  doc["anim14"] = a15;
  doc["anim15"] = a16;
  doc["anim16"] = a17;
  doc["anim17"] = a18;
  doc["anim18"] = a19;
  doc["anim19"] = a20;
  doc["anim20"] = a21;
  doc["anim21"] = a22;
  doc["anim22"] = a23;
  doc["anim23"] = a24;
  doc["anim24"] = a25;
  doc["anim25"] = a26;
  doc["anim26"] = a27;
  doc["anim27"] = a28;
  doc["anim28"] = a29;
  doc["anim29"] = a30;


  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    return;  // Jika gagal membuka file, keluar dari fungsi
  }
  serializeJson(doc, configFile);  // Serialisasi objek JSON ke file
  configFile.close();              // Menutup file setelah penulisan
}
const char *msgTab[4];
String stbang="STOPLAMP  CONTROL WITH WEB  IP: 192.168.4.1  OR APK";
int zmode;
int zxrem;
int zfont;
int zdurasi;
int zbright;
String textrem; 

const char *anim[32];


void readAndProcessJson() {
  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
    return;  // Jika gagal membuka file, keluar dari fungsi
  }

  size_t size = configFile.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);

  DynamicJsonDocument doc(1024);  // Ukuran buffer JSON
  deserializeJson(doc, buf.get());


    
  zmode = doc["mode"].as<int>();
  zxrem = doc["rem"].as<int>();
  zfont = doc["font"].as<int>();
  zdurasi = doc["durasi"].as<int>();
  zbright = doc["bright"].as<int>();
  String textz1 = doc["text1"].as<String>();
  String textz2 = doc["text2"].as<String>();
  String textz3 = doc["text3"].as<String>();
  String anim1 = doc["anim1"].as<String>();
  String anim2 = doc["anim2"].as<String>();
  String anim3 = doc["anim3"].as<String>();
  String anim4 = doc["anim4"].as<String>();
  String anim5 = doc["anim5"].as<String>();
  String anim6 = doc["anim6"].as<String>();
  String anim7 = doc["anim7"].as<String>();
  String anim8 = doc["anim8"].as<String>();
  String anim9 = doc["anim9"].as<String>();
  String anim10 = doc["anim10"].as<String>();
  String anim11 = doc["anim11"].as<String>();
  String anim12 = doc["anim12"].as<String>();
  String anim13 = doc["anim13"].as<String>();
  String anim14 = doc["anim14"].as<String>();
  String anim15 = doc["anim15"].as<String>();
  String anim16 = doc["anim16"].as<String>();
  String anim17 = doc["anim17"].as<String>();
  String anim18 = doc["anim18"].as<String>();
  String anim19 = doc["anim19"].as<String>();
  String anim20 = doc["anim20"].as<String>();
  String anim21 = doc["anim21"].as<String>();
  String anim22 = doc["anim22"].as<String>();
  String anim23 = doc["anim23"].as<String>();
  String anim24 = doc["anim24"].as<String>();
  String anim25 = doc["anim25"].as<String>();
  String anim26 = doc["anim26"].as<String>();
  String anim27 = doc["anim27"].as<String>();
  String anim28 = doc["anim28"].as<String>();
  String anim29 = doc["anim29"].as<String>();
  msgTab[0] = strdup(textz1.c_str());
  msgTab[1] = strdup(textz2.c_str());
  msgTab[2] = strdup(textz3.c_str());
  anim[0] = strdup(textz1.c_str());
  anim[1] = strdup(textz2.c_str());
  anim[2] = strdup(textz3.c_str());
  anim[3] = strdup(anim1.c_str());
  anim[4] = strdup(anim2.c_str());
  anim[5] = strdup(anim3.c_str());
  anim[6] = strdup(anim4.c_str());
  anim[7] = strdup(anim5.c_str());
  anim[8] = strdup(anim6.c_str());
  anim[9] = strdup(anim7.c_str());
  anim[10] = strdup(anim8.c_str());
  anim[11] = strdup(anim9.c_str());
  anim[12] = strdup(anim10.c_str());
  anim[13] = strdup(anim11.c_str());
  anim[14] = strdup(anim12.c_str());
  anim[15] = strdup(anim13.c_str());
  anim[16] = strdup(anim14.c_str());
  anim[17] = strdup(anim15.c_str());
  anim[18] = strdup(anim16.c_str());
  anim[19] = strdup(anim17.c_str());
  anim[20] = strdup(anim18.c_str());
  anim[21] = strdup(anim19.c_str());
  anim[22] = strdup(anim20.c_str());
  anim[23] = strdup(anim21.c_str());
  anim[24] = strdup(anim22.c_str());
  anim[25] = strdup(anim23.c_str());
  anim[26] = strdup(anim24.c_str());
  anim[27] = strdup(anim25.c_str());
  anim[28] = strdup(anim26.c_str());
  anim[29] = strdup(anim27.c_str());
  anim[30] = strdup(anim28.c_str());
  anim[31] = strdup(anim29.c_str());


  // Gunakan intValue1, intValue2, dan stringValue sesuai kebutuhan Anda
}
// ========== General Variables ===========
const char *ssid = "ASA_StopLamp";
const char *password = "Kontol123";
ESP8266WebServer server(80);


void handleRoot() {
  server.send(200, "text/html", htmlContent);
}
void setupWiFi() {
  WiFi.softAP(ssid, password);

  IPAddress apIP(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(apIP, apIP, subnet);
  server.handleClient();

  server.on("/", HTTP_GET, handleRoot);

  server.on("/message", HTTP_POST, []() {
    if (server.hasArg("radio")) {
      String f;
      String Rem;
      String radio;
      String text1;
      String text2;
      String text3;
      String d;
      String bright;
      String a2;
      String a3;
      String a4;
      String a5;
      String a6;
      String a7;
      String a8;
      String a9;
      String a10;
      String a11;
      String a12;
      String a13;
      String a14;
      String a15;
      String a16;
      String a17;
      String a18;
      String a19;
      String a20;
      String a21;
      String a22;
      String a23;
      String a24;
      String a25;
      String a26;
      String a27;
      String a28;
      String a29;
      String a30;
      if (server.arg("radio") == "5") {
        radio = String(zmode);
        f = server.arg("font");
        d = server.arg("durasi");
        bright = server.arg("bright");
        Rem = server.arg("rem");
        text1 = String(msgTab[0]);
        text2 = String(msgTab[1]);
        text3 = String(msgTab[2]);
        a2 = String(anim[1]);
        a3 = String(anim[2]);
        a4 = String(anim[3]);
        a5 = String(anim[4]);
        a6 = String(anim[5]);
        a7 = String(anim[6]);
        a8 = String(anim[7]);
        a9 = String(anim[8]);
        a10 = String(anim[9]);
        a11 = String(anim[10]);
        a12 = String(anim[11]);
        a13 = String(anim[12]);
        a14 = String(anim[13]);
        a15 = String(anim[14]);
        a16 = String(anim[15]);
        a17 = String(anim[16]);
        a18 = String(anim[17]);
        a19 = String(anim[18]);
        a20 = String(anim[19]);
        a21 = String(anim[20]);
        a22 = String(anim[21]);
        a23 = String(anim[22]);
        a24 = String(anim[23]);
        a25 = String(anim[24]);
        a26 = String(anim[25]);
        a27 = String(anim[26]);
        a28 = String(anim[27]);
        a29 = String(anim[28]);
        a30 = String(anim[29]);
      } else {
        if (server.arg("text1")==""){text1 = "";}else{
        text1 = server.arg("text1") + "      ";
        }
        if (server.arg("text2")==""){text2 = "";}else{
        text2 = server.arg("text2") + "      ";
        }
        if (server.arg("text3")==""){text3 = "";}else{
        text3 = server.arg("text3") + "      ";
        }
        
        radio = server.arg("radio");
        f = String(zfont);
        d = String(zdurasi);
        bright = String(zbright);
        Rem = String(zxrem);
        a2 = server.arg("animation1");
        a3 = server.arg("animation2");
        a4 = server.arg("animation3");
        a5 = server.arg("animation4");
        a6 = server.arg("animation5");
        a7 = server.arg("animation6");
        a8 = server.arg("animation7");
        a9 = server.arg("animation8");
        a10 = server.arg("animation9");
        a11 = server.arg("animation10");
        a12 = server.arg("animation11");
        a13 = server.arg("animation12");
        a14 = server.arg("animation13");
        a15 = server.arg("animation14");
        a16 = server.arg("animation15");
        a17 = server.arg("animation16");
        a18 = server.arg("animation17");
        a19 = server.arg("animation18");
        a20 = server.arg("animation19");
        a21 = server.arg("animation20");
        a22 = server.arg("animation21");
        a23 = server.arg("animation22");
        a24 = server.arg("animation23");
        a25 = server.arg("animation24");
        a26 = server.arg("animation25");
        a27 = server.arg("animation26");
        a28 = server.arg("animation27");
        a29 = server.arg("animation28");
        a30 = server.arg("animation29");
      }
      saveToJson(radio.toInt(), Rem.toInt(), text1, text2, text3, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, f.toInt(), d.toInt(), bright.toInt());
      readAndProcessJson();
      //server.send(200, "text/html", htmlContent);
       server.send(200, "text/html", "<div class=\"content-200\"><center><h1>Animasi Berhasil disimpan</h1><br><a style=\" background:#111111;color: #ffffff;text-decoration:none;display: inline-block;border:0px;padding: 10px 30px;text-align:center;border-radius:10px;\" href=\"/\">Return to Home Page</a></center></div>");

    } else {
      //server.send(400, "text/plain", "Bad Request");
       server.send(400, "text/html", "</h3>Animasi Gagal disimpan<br><a href=\"/\">Return to Home Page</a></h3>");

    }
  });
  server.begin();
}
void cleanup() {
  free((void *)msgTab[0]);
}

void setup() {
    msgTab[4] = strdup(stbang.c_str());
  if(MAX_DEVICES==4){
textrem = "$STOP$";
}
else{
textrem = "!STOP!";
}
  pinMode(rem, INPUT_PULLUP);
  pinMode(kanan, INPUT_PULLUP);
  pinMode(kiri, INPUT_PULLUP);

  Serial.begin(9600);
  SPIFFS.begin();
  setupWiFi();
  readAndProcessJson();
  mx.begin();
}
// Memastikan pilihan pengguna dalam batas yang benar
struct FontInfo {
  const uint8_t *fontData;
};
FontInfo availableFonts[] = {
  { f1 },
  { f2 },
  { f3 },
  { f4 },
  { f5 },
  { f6 },
  { f7 },
  { f8 },
  { f9 },
  { f10 },
  { f11 }
};


int j = 0;
int k = 0;


void loop() {
  mx.control(MD_MAX72XX::INTENSITY, zbright);
  server.handleClient();  // Ganti dengan pilihan yang sesuai

  if (zfont >= 0 && zfont < sizeof(availableFonts) / sizeof(availableFonts[0])) {

    mx.setFont(availableFonts[zfont].fontData);
  } else {
    Serial.println("Pilihan font tidak valid");
  }
  int tombolrem = digitalRead(rem);
  int tombolkanan = digitalRead(kanan);
  int tombolkiri = digitalRead(kiri);
  if (tombolrem == HIGH) {
    j++;
    if (j == 1) {
      mx.clear();
    }
    if (zxrem == 1) {
      rem1();
    } else if (zxrem == 2) {
      rem2();
    } else if (zxrem == 3) {
      mx.setFont(availableFonts[3].fontData);
      char textArray[textrem.length() + 1];
      textrem.toCharArray(textArray, sizeof(textArray));
      for (int i = 0; i < 5; i++) {
        rem3(0, MAX_DEVICES - 1, textArray);
        delay(100);  // Tampilkan teks selama 500 ms (setengah detik)
        mx.clear();  // Hapus tampilan teks
        delay(100);  // Tunggu selama 500 ms sebelum mengulang
      }
    } else if (zxrem == 4) {
      rem4();
    }
    k = 0;
  }  else {
    j = 0;
    k++;
    if (k == 1) {
      mx.clear();
    }
    run();
  }
}

void run() {
  static unsigned long startTime = 0;
  int xdurasi;
  if(String(zdurasi)==""){
  xdurasi = 10 * 1000;  // Durasi animasi (15 detik)
  }
  else{
   xdurasi = zdurasi * 1000;  // Durasi animasi (15 detik)
  }
  const unsigned long animationDuration=xdurasi;
  static uint8_t state = 0;
  static uint8_t mesg = 0;
  static boolean bRestart = true;
  static boolean bInMessages = false;
  boolean changeState = false;
  int previousMode = zmode;
  bool textFinished = false;
  if (zmode != previousMode) {
    mx.clear();
    state = 0;
    bRestart = true;  // Reset state ke nilai awal jika mode berubah
  }

  if (zmode == 4) {
    Serial.println(state);
    if (state != 0 || state != 1 ||state != 2 ) {
      if (millis() - startTime >= animationDuration) {
        mx.clear();
        state = state + 1;     // Beralih ke case berikutnya setelah durasi tertentu
        startTime = millis();  // Reset waktu mulai
      }
    }
    if(anim[0]!=""){
    anim[0] = "true";
    }
    if(anim[1]!=""){
    anim[1] = "true";
    }
    if(anim[2]!=""){
    anim[2] ="true";
    }
    if (String(anim[state]) == "true") {
      switch (state) {
        case 0:
          if (String(msgTab[0])==""/* condition */)
          {
            state++;
            /* code */
          }
          
          else{bInMessages = true;
          bRestart = scrollTextnormal(bRestart, msgTab[0], textFinished);
          if (textFinished) {
            state++;
            startTime = millis();  // Tambahkan logika sesuai dengan kebutuhan program Anda
          }}
          break;
        case 1:
          if (String(msgTab[1])==""/* condition */)
          {
            state++;
            /* code */
          }
          
          else{bInMessages = true;
          bRestart = scrollTextnormal(bRestart, msgTab[1], textFinished);
          if (textFinished) {
            state++;
            startTime = millis();  // Tambahkan logika sesuai dengan kebutuhan program Anda
          }}
          break;
        case 2:
          if (String(msgTab[2])==""/* condition */)
          {
            state++;
            /* code */
          }
          
          else{bInMessages = true;
          bRestart = scrollTextnormal(bRestart, msgTab[2], textFinished);
          if (textFinished) {
            state++;
            startTime = millis();  // Tambahkan logika sesuai dengan kebutuhan program Anda
          }}
          break;
        case 3: bRestart = graphicMidline2(bRestart); break;
        case 4: bRestart = graphicScanner(bRestart); break;
        case 5: bRestart = graphicRandom(bRestart); break;
        case 6: bRestart = graphicSpectrum1(bRestart); break;
        case 7: bRestart = graphicHeartbeat(bRestart); break;
        case 8: bRestart = graphicHearts(bRestart); break;
        case 9: bRestart = graphicEyes(bRestart); break;
        case 10: bRestart = graphicBounceBall(bRestart); break;
        case 11: bRestart = graphicScroller(bRestart); break;
        case 12: bRestart = graphicWiper(bRestart); break;
        case 13: bRestart = graphicInvader(bRestart); break;
        case 14: bRestart = graphicPacman(bRestart); break;
        case 15: bRestart = graphicSpectrum2(bRestart); break;
        case 16: bRestart = graphicSinewave(bRestart); break;
        case 17: animasi7(); break;
        case 18: animasi14(); break;
        case 19: animasi15(); break;
        case 20: animasi16(); break;
        case 21: animasi17(); break;
        case 22: animasi18(); break;
        case 23: animasi19(); break;
        case 24: animasi20(); break;
        case 25: bullseye(); break;
        case 26: customWaveAnimation(); break;
        case 27: alternateWaveAnimation(); break;
        case 28: alternateWaveAnimation2(); break;
        case 29: oppositeWaveAnimation(); break;
        case 30: waveAnimation(); break;
        case 31: circleWaveAnimation(); break;
        default: state = 0;
      }
    } else {
      if (state > 31) {
        state = 0;
      } else {
        mx.clear();
        state = state + 1;
      }
    }

    // now do whatever we do in the current state
  } else if (zmode == 3) {
    if (state != 0 ||state != 1 ||state != 2) {
      if (millis() - startTime >= animationDuration) {
        mx.clear();
        state = state + 1;     // Beralih ke case berikutnya setelah durasi tertentu
        startTime = millis();  // Reset waktu mulai
      }
    }

    switch (state) {
     case 0:
          if (String(msgTab[0])==""/* condition */)
          {
            state++;
            /* code */
          }
          
          else{bInMessages = true;
          bRestart = scrollTextnormal(bRestart, msgTab[0], textFinished);
          if (textFinished) {
            state++;
            startTime = millis();  // Tambahkan logika sesuai dengan kebutuhan program Anda
          }}
          break;
        case 1:
          if (String(msgTab[1])==""/* condition */)
          {
            state++;
            /* code */
          }
          
          else{bInMessages = true;
          bRestart = scrollTextnormal(bRestart, msgTab[1], textFinished);
          if (textFinished) {
            state++;
            startTime = millis();  // Tambahkan logika sesuai dengan kebutuhan program Anda
          }}
          break;
        case 2:
          if (String(msgTab[2])==""/* condition */)
          {
            state++;
            /* code */
          }
          
          else{bInMessages = true;
          bRestart = scrollTextnormal(bRestart, msgTab[2], textFinished);
          if (textFinished) {
            state++;
            startTime = millis();  // Tambahkan logika sesuai dengan kebutuhan program Anda
          }}
          break;
        case 3: bRestart = graphicMidline2(bRestart); break;
        case 4: bRestart = graphicScanner(bRestart); break;
        case 5: bRestart = graphicRandom(bRestart); break;
        case 6: bRestart = graphicSpectrum1(bRestart); break;
        case 7: bRestart = graphicHeartbeat(bRestart); break;
        case 8: bRestart = graphicHearts(bRestart); break;
        case 9: bRestart = graphicEyes(bRestart); break;
        case 10: bRestart = graphicBounceBall(bRestart); break;
        case 11: bRestart = graphicScroller(bRestart); break;
        case 12: bRestart = graphicWiper(bRestart); break;
        case 13: bRestart = graphicInvader(bRestart); break;
        case 14: bRestart = graphicPacman(bRestart); break;
        case 15: bRestart = graphicSpectrum2(bRestart); break;
        case 16: bRestart = graphicSinewave(bRestart); break;
        case 17: animasi7(); break;
        case 18: animasi14(); break;
        case 19: animasi15(); break;
        case 20: animasi16(); break;
        case 21: animasi17(); break;
        case 22: animasi18(); break;
        case 23: animasi19(); break;
        case 24: animasi20(); break;
        case 25: bullseye(); break;
        case 26: customWaveAnimation(); break;
        case 27: alternateWaveAnimation(); break;
        case 28: alternateWaveAnimation2(); break;
        case 29: oppositeWaveAnimation(); break;
        case 30: waveAnimation(); break;
        case 31: circleWaveAnimation(); break;
        default: state = 0; 
    }

  } else if (zmode == 2) {
    switch (state) {
      case 0:
          if (String(msgTab[0])!=""/* condition */)
          {
          bInMessages = true;
          bRestart = scrollTextnormal(bRestart, msgTab[0], textFinished);
          if (textFinished) {
            state++;
  // Tambahkan logika sesuai dengan kebutuhan program Anda
          }
          }
          
          else{
            state++;
          }
          break;
        case 1:
          if (String(msgTab[1])!=""/* condition */)
          {bInMessages = true;
          bRestart = scrollTextnormal(bRestart, msgTab[1], textFinished);
          if (textFinished) {
            state++;
     // Tambahkan logika sesuai dengan kebutuhan program Anda
          }
            /* code */
          }
          
          else{

            state++;
          }
          break;
        case 2:
          if (String(msgTab[2])!=""/* condition */)
          {
            bInMessages = true;
          bRestart = scrollTextnormal(bRestart, msgTab[2], textFinished);
          if (textFinished) {
            state++;
            startTime = millis();  // Tambahkan logika sesuai dengan kebutuhan program Anda
          }
            /* code */
          }
          
          else{
            state++;

          }
          break;
      default: state = 0 ;textFinished=false;
    }
  } else if (zmode == 1) {
    if (millis() - startTime >= animationDuration) {
      mx.clear();
      state = (state + 1);   // Beralih ke case berikutnya setelah durasi tertentu
      startTime = millis();  // Reset waktu mulai
    }
    switch (state) {
      case 0: bRestart = graphicMidline2(bRestart); break;
      case 1: bRestart = graphicScanner(bRestart); break;
      case 2: bRestart = graphicRandom(bRestart); break;
      case 3: bRestart = graphicSpectrum1(bRestart); break;
      case 4: bRestart = graphicHeartbeat(bRestart); break;
      case 5: bRestart = graphicHearts(bRestart); break;
      case 6: bRestart = graphicEyes(bRestart); break;
      case 7: bRestart = graphicBounceBall(bRestart); break;
      case 8: bRestart = graphicScroller(bRestart); break;
      case 9: bRestart = graphicWiper(bRestart); break;
      case 10: bRestart = graphicInvader(bRestart); break;
      case 11: bRestart = graphicPacman(bRestart); break;
      case 12: bRestart = graphicSpectrum2(bRestart); break;
      case 13: bRestart = graphicSinewave(bRestart); break;
      case 14: animasi7(); break;
      case 15: animasi14(); break;
      case 16: animasi15(); break;
      case 17: animasi16(); break;
      case 18: animasi17(); break;
      case 19: animasi18(); break;
      case 20: animasi19(); break;
      case 21: animasi20(); break;
      case 22: bullseye(); break;
      case 23: customWaveAnimation(); break;
      case 24: alternateWaveAnimation(); break;
      case 25: alternateWaveAnimation2(); break;
      case 26: oppositeWaveAnimation(); break;
      case 27: waveAnimation(); break;
      case 28: circleWaveAnimation(); break;
      default: state = 0; startTime = millis();textFinished=false;
    }
  }
  else{
    mx.setFont(availableFonts[3].fontData); 
  switch (state) {
      case 0:   
          bInMessages = true;
          bRestart = scrollTextnormal(bRestart, msgTab[4], textFinished);
          if (textFinished) {
            state++;
          }
          break;
      default: state = 0 ;textFinished=false;
    }   
  }
}
