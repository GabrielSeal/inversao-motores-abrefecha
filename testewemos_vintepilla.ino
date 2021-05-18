#include <ESP8266WiFi.h>

const char* ssid = "Gseal2.4";
const char* password = "CP1143SM3BB";
int ledPin= D5;
WiFiServer server(80);



void setup() {
Serial.begin(9600);
delay(10);


pinMode(ledPin,OUTPUT);
digitalWrite(ledPin, LOW);
//conecta na rede e mostra na porta serial
Serial.println();
Serial.println();
Serial.println("Conectando a rede ");

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED)
{
  delay(500);
  Serial.print(".");
    
}

Serial.println("");
Serial.println("Wifi conectado");

// inicia o servidor
server.begin();
Serial.println("Servidor iniciado");

// retorna o valor do IP que estará nosso servidor na rede

Serial.println("USar essa URL: ");
Serial.println("HTTP://");
Serial.println(WiFi.localIP());
Serial.println("/");


}

void loop() {
  // Monitora se existe Cliente( alguém) usando o navegador. Pode ser acompanhado pela porta COM
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Servidor fica em estado de espera para alguém enviar o comando( Dados)
  Serial.println("Embarcado");
  while(!client.available()){
    delay(1);
  }
 // AQUI COMEÇA O CÓDIGO HTML junto com a chamada HTTP>>>>>>
  // Faz a leitura da chamada HTTP e mostra os valores baseado no programa acima no VOID SETUP. 
  // Lembrando que aqui não é o programa que subimos( void setup()) e sim, a parte HTML que será enviado para o servidor.
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Compara o pedido de Chamada HTTP e verifica se bate com o programa que fizemos.
 
  int value = LOW;
  if (request.indexOf("/RELE=LIGADO") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/RELE=DESLIGADO") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
  }

  //  Se o Servidor, conseguiu entender a chamada que fizemos acima, Retorna o Valor Lido e mostra no Navegador. 
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); // Deixei em branco para quem adivinhar o que faz aqui. Não afeta o código, mas gera algo interessante (:
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Status do Rele WEMOS: ");
 
  if(value == HIGH) {
    client.print("LIGADO");
  } else {
    client.print("DESLIGADO");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/RELE=LIGADO\">Aqui</a> Ativar Rele LIGADO<br>");
  client.println("Click <a href=\"/RELE=DESLIGADO\">Aqui</a> Desativar Rele DESLIGADO<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Embarcado saiu :");
  Serial.println("");
 
}



  
