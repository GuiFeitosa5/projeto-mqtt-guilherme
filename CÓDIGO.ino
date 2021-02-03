#include <PubSubClient.h>

#include <UIPEthernet.h>
#include <utility/logging.h>

#include <SPI.h>

//Variável utilizada para enviar as mensagens utilizando o cliente MQTT
bool mensagem; 

//Define o endereço MAC que será utilizado
byte mac[] = { 0x00, 0xE0, 0x4C, 0x3E, 0x07, 0x95 };

//Inicia o cliente Ethernet
EthernetClient client;

//Inicia o client MQTT
PubSubClient mqttClient(client);

int pino2 = 2 ; // Cria uma variável para o Pino 2
bool estado_sensor; // Cria uma variável para armazenar o estado do sensor

void setup() {
    //Inicia o controlador Ethernet e solicita um IP para o servidor de DHCP
    Ethernet.begin(mac);

    //Inicia o monitor Serial
    Serial.begin(9600);

    //Define o IP e Porta TCP do Broker MQTT que vamos utilizar
    mqttClient.setServer("54.144.190.205",1883);

    //Exibe no Monitor Serial as informações sobre o IP do Arduino
    Serial.print("O IP do Arduino e: ");
    Serial.println(Ethernet.localIP());

    //Exibe no Monitor Serial as informações sobre a Máscara de Rede do Arduino
    Serial.print("A Mascara de Rede do Arduino e: ");
    Serial.println(Ethernet.subnetMask());

    //Exibe no Monitor Serial as informações sobre o Gateway do Arduino
    Serial.print("O Gateway do Arduino e: ");
    Serial.println(Ethernet.gatewayIP());

    //Exibe uma linha em branco 
    Serial.println("");

     pinMode(pino2,INPUT_PULLUP); //Coloca o Pino 2 como Entrada
    
    //Aguarda 10 segundos
}

void loop() {

    //Define o nome do cliente MQTT e efetua a conexão com o servidor.
   //Serial.println(mensagem);
   mqttClient.connect("guifeitosa");

    /*
      Variável que envia a mensagem e armazena o valor de '1' caso 
      a mensagem seja enviada com sucesso e '0' caso o envio falhe
    */

  estado_sensor = digitalRead(pino2); //Efetua a leitura do Pino 2 e armazena o valor obtido na variável

  Serial.println(estado_sensor); //Exibe no Monitor Serial o Estado do Sensor

  if (estado_sensor == 0) {


   Serial.println("o pino2 está fechado"); //Exibe no Monitor Serial 0
     mensagem = mqttClient.publish("guifeitosa-t","FECHADO");
    
    }else{
      
      

    Serial.println("o pino2 está aberto"); //Exibe no Monitor Serial o Estado do
      mensagem = mqttClient.publish("guifeitosa-t","ABERTO");

    }
      
   
  Serial.println(mensagem);

    //Função que verifica a conexão entre o Cliente e o Broker e evita a queda de conexão entre eles.
    mqttClient.loop();
}

    