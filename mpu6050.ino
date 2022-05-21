#include <Wire.h>
#include <SoftwareSerial.h>
#define MPU6050_I2C_ADDRESS 0x68
#define MPU_6050_ACCEL_XOUT_H 0x3B
#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_GYRO_XOUT_H 0x43

float gyro_x_angle = 0, gyro_y_angle = 0, gyro_z_angle = 0, gyro_0_angle = 0;
float gyro_x_raw_angle = 0, gyro_y_raw_angle = 0, gyro_z_raw_angle = 0;
int dt = 50;
int gyro_x_offset = 0, gyro_y_offset = 0, gyro_z_offset = 0;
int gyro_result = 0;
byte buffer[14];

void setRegister(int address, byte reg, byte data)
{
 Wire.beginTransmission(address);
 Wire.write(reg);
 Wire.write(data);
 Wire.endTransmission();
 delay(5); 
 }
byte getRegisters(int address, byte reg, byte *buffer, byte length)
{
  byte count = 0;
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.beginTransmission(address);
  Wire.requestFrom(address, (int) length);

  while(Wire.available())
  {
    buffer[count]= Wire.read();
    count++;
   }
   Wire.endTransmission();
   return count;
 }
void calibrateGyro(){
  long tmp_offset = 0;
  long tmp_offset_y = 0;
  long tmp_offset_z = 0;
  for (int i = 0; i < 100; ++i){
    if (getRegisters(MPU6050_I2C_ADDRESS, MPU6050_GYRO_XOUT_H, buffer, 6) == 6)
    {
      tmp_offset += (int)word(buffer[0], buffer[1]);
      tmp_offset_y += (int)word(buffer[2], buffer[3]);
      tmp_offset_z += (int)word(buffer[4], buffer[5]);
    }    
    else
    --i;
    delay(50);
    }
    gyro_x_offset = tmp_offset / 100;
    gyro_y_offset = tmp_offset_y / 100;
    gyro_z_offset = tmp_offset_z / 100;
  }

 
void setup() {
  // put your setup code here, to run once:
Wire.begin();
Serial.begin(9600);
setRegister(MPU6050_I2C_ADDRESS, MPU6050_PWR_MGMT_1, 0);
delay(50);
calibrateGyro();
}

//byte buffer[14];

void loop() {
  // put your main code here, to run repeatedly:
//beginTransmission();
byte readed = getRegisters(MPU6050_I2C_ADDRESS, MPU_6050_ACCEL_XOUT_H, buffer, 14);


if(readed != 14)
Serial.println("ERROR");
/*else
{
  byte byte9 = buffer[8];
  byte byte10 = buffer[9];
  Serial.print(byte9);
  Serial.print("\t");
  Serial.println(byte10);
}*/
else
{
  int gyro_x = word(buffer[8], buffer[9]);
  int gyro_y = word(buffer[10], buffer[11]);
  int gyro_z = word(buffer[12], buffer[13]);

  //gyro_x = map(gyro_x, -32768, 32767, -250, +250);
  //gyro_y = map(gyro_y, -32768, 32767, -250, +250);
  //gyro_z = map(gyro_z, -32768, 32767, -250, +250);

  //int gyro_x_map_raw = map(gyro_x, -32768, 32767, -250, +250);
  int gyro_x_map = map(gyro_x - gyro_x_offset, -32768, 32767, -250, +250);
  //int gyro_y_map_raw = map(gyro_y, -32768, 32767, -250, +250);
  //int gyro_y_map = map(gyro_y - gyro_y_offset, -32768, 32767, -250, +250);
  //int gyro_z_map_raw = map(gyro_z, -32768, 32767, -250, +250);
  //int gyro_z_map = map(gyro_z - gyro_z_offset, -32768, 32767, -250, +250);


  //gyro_x_raw_angle += gyro_x_map_raw *dt / 1000.0;
  gyro_x_angle += gyro_x_map * dt /1000.0;
  if(gyro_x_angle <0.5 && gyro_x_angle > -0.5 ) gyro_result += 1;
  /*gyro_y_raw_angle += gyro_y_map_raw *dt / 1000.0;
  gyro_y_angle += gyro_y_map * dt /1000.0;
  gyro_z_raw_angle += gyro_z_map_raw *dt / 1000.0;
  gyro_z_angle += gyro_z_map * dt /1000.0;
  //gyro_x_angle += gyro_x * dt / 1000.0;
  //gyro_y_angle += gyro_y * dt / 1000.0;
  //gyro_z_angle += gyro_z * dt / 1000.0;
  
 Serial.print(gyro_x_raw_angle); Serial.print("\t");
 Serial.print(gyro_x_angle);Serial.print("\t");
 Serial.print(gyro_y_raw_angle); Serial.print("\t");
 Serial.print(gyro_y_angle);Serial.print("\t");
 Serial.print(gyro_z_raw_angle); Serial.print("\t");
 Serial.println(gyro_z_angle);*/
 Serial.print(gyro_0_angle); Serial.print("\t");
 Serial.print(gyro_result); Serial.print("\t");
 Serial.println(gyro_x_angle);
 
  //Serial.print(gyro_x_angle); Serial.print("\t");
  //Serial.print(gyro_y_angle); Serial.print("\t");
  //Serial.println(gyro_z_angle);
  //Serial.print(gyro_x); Serial.print("\t");
  //Serial.print(gyro_y); Serial.print("\t");
  //Serial.println(gyro_z);
}
//delay(20);
delay (dt);

//endTransmission();
}
