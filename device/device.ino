#include <ESP8266WiFi.h>

// WiFi parameters
const char* ssid = "ds";
const char* password = "";
//IPAddress myServer(192,168,122,1);
char myServer[] = "smvdsb.000webhostapp.com";
// Create an instance of the server
WiFiServer server(80);
//wifi client
WiFiClient client;
int timeout = 100000;
String user_name = "durgeshsatyam2@gmail.com";
String _id = "1";
int distortionValue;
int DustbinFullShow;





//for pins for output sensors
const int pin1 = 16;//D0
const int pin2 = 5;//D1
const int pin3 = 4;//D2
const int pin4 = 0;//D3




void connect_server()
{
  
  Serial.println("connecting...");
  

  // if you get a connection, report back via serial:
  if (client.connect(myServer, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    String website_passcode="qwerty";
    String website_username="durgeshsatyam2@gmail.com";
    //String variable= "value";

    String query = "?username="+website_username+"&passcode="+website_passcode+"&user_name="+user_name;
    client.println("GET /feedBack/check.php"+query+" HTTP/1.1");
    client.println("Host: smvdsb.000webhostapp.com");
    client.println("Connection: close");
    client.println();
    Serial.println(query);
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }


  
}



void setup() {
  pinMode(pin1, OUTPUT); 
  pinMode(pin2, OUTPUT); 
  pinMode(pin3, OUTPUT); 
  pinMode(pin4, OUTPUT); 
  
  Serial.begin(115200); // Starts the serial communication
  


  //connectting to the available wifi
  // Print the IP address
  Serial.println(WiFi.localIP());
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".C");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

  connect_server();
}
void loop() {
  
  // getting the response from the server if there is any connections
  String response = "";
  while (client.available()) {
    char c = client.read();
    response+=c;
    //Serial.print(c);
    //Serial.print("heyaa");
  }
  Serial.print(response);

  const char * recieved = response.c_str();
  //checking whether the Value is present or not
  if(strstr(recieved, "SWITCH1:ON") != NULL) {
    Serial.println("SWITCH1:ON");
    digitalWrite(pin1,HIGH);
  }
  else
  {
    digitalWrite(pin1,LOW);
  }

  // pin 2
  if(strstr(recieved, "SWITCH2:ON") != NULL) {
    Serial.println("SWITCH2:ON");
    digitalWrite(pin2,HIGH);
  }
  else
  {
    digitalWrite(pin2,LOW);
  }

//  // pin 2
//  if(strstr(recieved, "SWITCH3:ON") != NULL) {
//    Serial.println("SWITCH3:ON");
//    digitalWrite(pin3,HIGH);
//  }
//  else
//  {
//    digitalWrite(pin3,LOW);
//  }
//
//  // pin 2
//  if(strstr(recieved, "SWITCH4:ON") != NULL) {
//    Serial.println("SWITCH4:ON");
//    digitalWrite(pin4,HIGH);
//  }
//  else
//  {
//    digitalWrite(pin4,LOW);
//  }
  
  

  //connecting to the server
  if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting.");
    client.stop();
    Serial.println("Connecting to the server again.");
    connect_server();

    // do nothing forevermore:
    //while (true);
  }

  
}
