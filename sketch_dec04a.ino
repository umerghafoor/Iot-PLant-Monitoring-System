#include<WiFi.h>
#include<HTTPClient.h>

const int soilMoisturePin = 32; // Replace with the actual pin connected to the soil moisture sensor


String URL = "http://192.168.10.14/dht11_project/test_data.php"; // Replace with the actual URL of the server

const char* ssid = "Redmi 12C"; // Replace with the actual SSID
const char* password = "password"; // Replace with the actual password

int moisture = 0;


void setup() {
  Serial.begin(115200);
 
  connectWiFi();

}

void loop() {
  int soilMoistureValue = analogRead(soilMoisturePin);

  // Reverse the mapping if lower values mean wet and higher values mean dry
  int moisturePercentage = map(soilMoistureValue, 4095, 0, 0, 100);

  Serial.print("Soil Moisture Value: ");
  Serial.println(soilMoistureValue);

  Serial.print("Moisture Percentage: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  if(WiFi.status() != WL_CONNECTED){
    connectWiFi();
    }

 String postData = "Moisture=" + String(moisturePercentage);

  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
 
  int httpCode = http.POST(postData);
  String payload = http.getString();
 

  Serial.print("URL : "); Serial.println(URL); 
  Serial.print("Data: "); Serial.println(postData);
  Serial.print("httpCode: "); Serial.println(httpCode);
  Serial.print("payload : "); Serial.println(payload);
  Serial.println("--------------------------------------------------");
  delay(5000);
}

void connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  //This line hides the viewing of ESP as wifi hotspot
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    
  Serial.print("connected to : "); Serial.println(ssid);
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
}
