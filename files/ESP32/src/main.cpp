#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>
#include "html_content.h"  // Ahora busca en /include automáticamente

// Configuración EEPROM
#define EEPROM_SIZE 512
#define SSID_ADDR 0
#define PASS_ADDR 32

// Variables globales
WebServer server(80);
bool wifiConnected = false;
String currentSSID = "";
String currentPassword = "";

// Declaraciones adelantadas
void startAPMode();
bool connectToWiFi(String ssid, String password);
void handleRoot();
void handleScan();
void handleConnect();
void handleStatus();
String readEEPROM(int startAddr);
void writeEEPROM(int startAddr, String data);

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  
  // Cargar credenciales
  currentSSID = readEEPROM(SSID_ADDR);
  currentPassword = readEEPROM(PASS_ADDR);
  
  // Intentar conexión automática
  if (currentSSID.length() > 0) {
    if (!connectToWiFi(currentSSID, currentPassword)) {
      startAPMode();
    }
  } else {
    startAPMode();
  }

  // Configurar endpoints
  server.on("/", HTTP_GET, handleRoot);
  server.on("/scan", HTTP_GET, handleScan);
  server.on("/connect", HTTP_POST, handleConnect);
  server.on("/status", HTTP_GET, handleStatus);
  
  server.begin();
}

void loop() {
  server.handleClient();
  
  // Verificar conexión periódicamente
  if (wifiConnected && WiFi.status() != WL_CONNECTED) {
    wifiConnected = false;
    Serial.println("Conexión WiFi perdida");
    startAPMode();
  }
}

// Implementación de funciones
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleScan() {
  int n = WiFi.scanNetworks();
  String json = "[";
  for (int i = 0; i < n; i++) {
    if (i) json += ",";
    json += String() + "{\"ssid\":\"" + WiFi.SSID(i) + 
            "\",\"rssi\":" + WiFi.RSSI(i) + 
            ",\"enc\":" + WiFi.encryptionType(i) + "}";
  }
  json += "]";
  server.send(200, "application/json", json);
  WiFi.scanDelete();
}

void handleConnect() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");
  
  if (ssid.isEmpty()) {
    server.send(400, "text/plain", "SSID requerido");
    return;
  }

  if (connectToWiFi(ssid, password)) {
    String ip = WiFi.localIP().toString();
    server.send(200, "text/plain", "success|" + ip);
  } else {
    server.send(500, "text/plain", "Error de conexión");
  }
}

void handleStatus() {
  if (wifiConnected) {
    server.send(200, "application/json", 
      String() + "{\"connected\":true,\"ssid\":\"" + currentSSID + 
      "\",\"ip\":\"" + WiFi.localIP().toString() + "\"}");
  } else {
    server.send(200, "application/json", "{\"connected\":false}");
  }
}

bool connectToWiFi(String ssid, String password) {
  WiFi.disconnect();
  delay(100);
  WiFi.begin(ssid.c_str(), password.c_str());
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts++ < 20) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    writeEEPROM(SSID_ADDR, ssid);
    writeEEPROM(PASS_ADDR, password);
    EEPROM.commit();
    wifiConnected = true;
    return true;
  }
  return false;
}

void startAPMode() {
  WiFi.softAP("ESP32-WiFi-Adapter", "", 1, 0, 1);
  IPAddress apIP(192, 168, 4, 1);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  wifiConnected = false;
}

String readEEPROM(int startAddr) {
  String value;
  for (int i = startAddr; i < startAddr + 32; ++i) {
    char c = EEPROM.read(i);
    if (c == 0) break;
    value += c;
  }
  return value;
}

void writeEEPROM(int startAddr, String data) {
  for (int i = 0; i < data.length() && i < 32; ++i) {
    EEPROM.write(startAddr + i, data[i]);
  }
  EEPROM.write(startAddr + data.length(), 0);
}