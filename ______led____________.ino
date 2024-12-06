
#include <ESP8266WiFi.h>
 
const char* ssid = "Galaxy A12BC19";
const char* password = "09184897247";
 
int LED = 16;                 // led connected to D0
WiFiServer server(80);
 
void setup() 
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);  // intial LED =0
 
  Serial.print("Connecting to Internet ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) //waiting wifi connected
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
 
 /*-------- server started---------*/ 
  server.begin();
  Serial.println("Server started");
 
  /*------printing ip address--------*/
  Serial.print("IP Address of network: ");
  Serial.println(WiFi.localIP());
  Serial.print("Copy and paste the following URL: https://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
 
void loop() 
  {
    WiFiClient client = server.available();    
    if (!client) 
    {
      return;
    }
  Serial.println("Waiting for new client");   
  while(!client.available())  //waiting for request from client or Wait until the client sends some data
  {
    delay(1);
  }
 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();  //empty of client
 
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  
  {
    digitalWrite(LED, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  
  {
    digitalWrite(LED, LOW);
    value = LOW;
  }
 
/*------------------Creating html page---------------------*/

  
  client.println("HTTP/1.1 200 OK");// HTTP headers always start with a response code 
    client.println("Content-Type: text/html");//a content-type so the client knows what's coming, then a blank line:
  client.println(""); 
  client.println("<!DOCTYPE HTML>");// we are sending html formated
   client.println("<h1>ESP8266 Web Server</h1>");
   client.print("<h1>LED is:    </h1>");
 
  if(value == HIGH) 
  {
    client.print("ON");
  } 
  else 
  {
    client.print("OFF");
  }
  client.println("<br><br>");
    client.println("<a href=\"/LED=ON\"\"><button><h1>ON<h1></button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button><h1>OFF<h1></button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
