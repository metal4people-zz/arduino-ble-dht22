#include <SoftwareSerial.h>
#include <iterator>
#include <string>
#include <pnew.cpp>  // placement new implementation
#include <inttypes.h>
#include <dht.h>

SoftwareSerial BTSerial(10, 11); //RX|TX
dht DHT;
const int dhtPin = 2; //Data pin of DHT-22 to Arduino digital pin 2

std::string in_buffer;
std::string out_buffer;

void read_dht22_data(float & temperature, float & humidity)
{
    int chk = DHT.read22(dhtPin);
    temperature = DHT.temperature;
    humidity = DHT.humidity;
}

void setup(){
  Serial.begin(9600);
  BTSerial.begin(9600); // default baud rate
  while(!Serial); //if it is an Arduino Micro
}

void read_byte( Stream & stream )
{
   in_buffer.push_back(static_cast<char>(stream.read()));
   Serial.write(in_buffer[in_buffer.size()-1]);
}

void write_byte( Stream & stream)
{
  if( !out_buffer.empty() )
  {
    Serial.write(*out_buffer.begin());
    if( stream.write(*out_buffer.begin() ) != 0 )
    {
      out_buffer.erase( out_buffer.begin( ) );
    }
  }
}

void to_string(int a, std::string & out)
{
  char buffer[50];
  memset(buffer, 0, sizeof(buffer));
  sprintf(buffer, "%d", a);
  out = buffer;
}

void to_string(float a, std::string & out)
{
  char buffer[6];
  dtostrf(a, 5, 2, buffer);
  out = buffer;
}

void process_request()
{
  if(!in_buffer.empty() && *(in_buffer.end() - 1) == '&')
  {
    in_buffer.erase(in_buffer.size() - 1);
    if(in_buffer == "Hello")
    {
      out_buffer.append("Hello, ololo\n");
    }
    else
    {
      out_buffer.append("Unsupported request\n");
    }
    in_buffer.clear();
  }
}

void loop()
{
  if(BTSerial.available())
  {
    read_byte(BTSerial);
    process_request();
  }
  if(out_buffer.empty())
  {
    delay(2000);
    float temperature;
    float humidity;
    read_dht22_data(temperature, humidity);  
    std::string sTemperature;
    to_string(temperature, sTemperature);
    std::string sHumidity;
    to_string(humidity, sHumidity);
    out_buffer.append(sTemperature);
    out_buffer.append(";");
    out_buffer.append(sHumidity);
  }
  write_byte(BTSerial);
}

