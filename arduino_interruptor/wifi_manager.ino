
void setup_wifiManager() {
  Serial.println("Passei aqui 1");
  //declaração do objeto wifiManager
  WiFiManager wifiManager;

  
  //utilizando esse comando, as configurações são apagadas da memória
  //caso tiver salvo alguma rede para conectar automaticamente, ela é apagada.
  //  wifiManager.resetSettings();

  //callback para quando entra em modo de configuração AP
  wifiManager.setAPCallback(configModeCallback); 

  //callback para quando se conecta em uma rede, ou seja, quando passa a trabalhar em modo estação
  wifiManager.setSaveConfigCallback(saveConfigCallback); 

  //cria uma rede de nome ESP_AP com senha 12345678
  //wifiManager.autoConnect("EspTeste", "12345678"); 

  Serial.println("Passei aqui");
  if(!wifiManager.autoConnect("EspTeste", "12345678") )
  {
    Serial.println("Falha ao conectar");
    delay(2000);
    ESP.restart();
  }else{
    Serial.println("WiFi Manager");
    setup_wifi();
  }
  
}

//callback que indica que o ESP entrou no modo AP
void configModeCallback (WiFiManager *myWiFiManager) {  
  //  Serial.println("Entered config mode");
  Serial.println("Entrou no modo de configuração");
  Serial.println(WiFi.softAPIP()); //imprime o IP do AP
  Serial.println(myWiFiManager->getConfigPortalSSID()); //imprime o SSID criado da rede

}

//callback que indica que salvamos uma nova rede para se conectar (modo estação)
void saveConfigCallback () {
  Serial.println("Configuração salva");
  setup_wifi();
}
