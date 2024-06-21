#include <Wire.h>                   // Biblioteca para comunicação I2C
#include <Adafruit_MPU6050.h>       // Biblioteca da Adafruit para o sensor MPU6050
#include <Adafruit_Sensor.h>        // Biblioteca da Adafruit para suporte a sensores

Adafruit_MPU6050 mpu;               // Cria um objeto para o MPU6050

void setup() {
  Serial.begin(115200);             // Inicializa a comunicação serial a 115200 bps
  
  while (!Serial) {
    delay(10);                      // Aguarda a inicialização da porta serial
  }
  
  // Inicializa a comunicação I2C com pinos definidos para o ESP32
  Wire.begin(19, 22);               // Configura o pino GPIO 19 como SDA e GPIO 22 como SCL

  if (!mpu.begin()) {               // Inicializa o sensor MPU6050
    while (1) {
      delay(10);                    // Entra em loop infinito caso o sensor não seja detectado
    }
  }
  
  // Configura o MPU6050
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);   // Define o alcance do acelerômetro para ±8G
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);        // Define o alcance do giroscópio para ±500 graus por segundo
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);     // Define a largura de banda do filtro para 21 Hz
}

void loop() {
  sensors_event_t a, g, temp;        // Declara estruturas para armazenar dados do acelerômetro, giroscópio e temperatura
  
  mpu.getEvent(&a, &g, &temp);       // Captura os dados do sensor

  // Imprime os valores de aceleração em cada eixo (X, Y, Z) na porta serial
  Serial.print(a.acceleration.x); Serial.print(" ");
  Serial.print(a.acceleration.y); Serial.print(" ");
  Serial.println(a.acceleration.z);
  
  delay(100);                        // Aguarda 100 ms antes de capturar os próximos dados
}
