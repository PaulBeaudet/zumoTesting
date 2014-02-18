#include <Wire.h>// I2C library comes with IDE
//#include <LSM303.h>// https://github.com/pololu/lsm303-arduino
//honesly pololu's library is a bit difficult to follow...?
//Some examples extend objects in the library, kinda confusing for beginer and hobbyist
#include <Adafruit_LSM303.h> //Adafruit's library for the same chip
//https://github.com/adafruit/Adafruit_LSM303
Adafruit_LSM303 lsm303;

/*
LSM303 compass;
#define CALIBRATION_SAMPLES 70  // Number of compass readings to take when calibrating
#define CRB_REG_M_2_5GAUSS 0x60 // CRB_REG_M value for magnetometer +/-2.5 gauss full scale
#define CRA_REG_M_220HZ    0x1C // CRA_REG_M value for magnetometer 220 Hz update rate
LSM303::vector<int16_t> running_min = {
  32767, 32767, 32767}
, running_max = {
  -32767, -32767, -32767};
//set up object variables running min/max as ints //creats 6 assosiated variables
//lowest/highest -2047/2047
*/


byte checkForPickup()
{//detects if the zumo has been picked up
  lsm303.read(); //read the z axis of the accelerometer
  if ( lsm303.accelData.z > 1500)
  { // detect if its enought acceloration for a pick-up event
    return 1 ;//return event number if picked up 0 if not
  }
  return 0;
}

void lsm303Up()
{
  Wire.begin();
  if (!lsm303.begin())
  {
    bugLight();//flash the LED if the chip Fails to load
  }
}



/*

void compassAccelUp()
{// intiates the compass and the accelerometer... hopefully...
  Wire.begin(); //open I2C bus as the master to communicate with compass/accel
  compass.init();// Initiate LSM303
  compass.enableDefault();// Enables accelerometer and magnetometer
  compass.writeReg(LSM303::CRB_REG_M, CRB_REG_M_2_5GAUSS); // +/- 2.5 gauss sensitivity to hopefully avoid overflow problems
  compass.writeReg(LSM303::CRA_REG_M, CRA_REG_M_220HZ);    // 220 Hz compass update rate
}

void calibrateCompass()
{
  for(unsigned char index = 0; index < CALIBRATION_SAMPLES; index ++)
  {// Take a reading of the magnetic vector and store it in compass.m
    goFor(9001, -150, 150);// turn sowly for over 9000ms
    compass.read();
    running_min.x = min(running_min.x, compass.m.x);//thanks for sharing what these methods do...
    running_min.y = min(running_min.y, compass.m.y);// I'll just guess
    running_max.x = max(running_max.x, compass.m.x);// my guess is decr/increments the max/min
    running_max.y = max(running_max.y, compass.m.y);// based on the reading
    delay(200);//delay inorder to be sure reading increments as robot spins 
  }
  goFor(900,0,0);//stop the motors!! 

  // write calibration information to EEPROM

  promIntWrite(running_max.x, 0);//write intergers
  promIntWrite(running_max.y, 2);//to even places in EEPROM
  promIntWrite(running_min.x, 4);// this alows the arduino to remember
  promIntWrite(running_min.y, 6);// the calibration 

  // Set calibrated values to compass.m_max and compass.m_min
  compass.m_max.x = running_max.x;
  compass.m_max.y = running_max.y;
  compass.m_min.x = running_min.x;
  compass.m_min.y = running_min.y;

}

void rememberCalibration() // remembers calibration from last session
{
  compass.m_max.x = promRead(0);// read calibration value
  compass.m_max.y = promRead(2);// into compass.m variables
  compass.m_min.x = promRead(4);
  compass.m_min.y = promRead(6);
}


#define BUFFER 0 // change heading sensitivity in degree increments
// what you need in differance before a new reading is recorded

void headingRecord()// reports the heading to the serial monitor
{
  static byte lastHeading;

  float more;
  float orLess;


  compass.read();
  float heading = averageHeading();//read the average heading 
  //as opposed to the library heading method
  //################################################testing
  if (lastHeading + BUFFER > 360)
  {
    more = lastHeading - BUFFER; // more will just be a larger number
  }
  else
  {
    more = lastHeading + BUFFER;
  };
  if (lastHeading - BUFFER < 0)
  {
    orLess = lastHeading + BUFFER; // orless will just be a smaller number
  }
  else
  {
    orLess = lastHeading - BUFFER;
  };
  if (heading < more || heading > orLess)//!! potential overflow!!!
    //#@N#########################################testing
  {
    lastHeading= (byte) heading;//cast the heading as a byte for recorded degrees all
    promWrite(lastHeading);
  }

}

template <typename T> float heading(LSM303::vector<T> v)//?? needed for average heading function!
{
  float x_scaled =  2.0*(float)(v.x - compass.m_min.x) / ( compass.m_max.x - compass.m_min.x) - 1.0;
  float y_scaled =  2.0*(float)(v.y - compass.m_min.y) / (compass.m_max.y - compass.m_min.y) - 1.0;

  float angle = atan2(y_scaled, x_scaled)*180 / M_PI;
  if (angle < 0)
    angle += 360;
  return angle;
}

// Average 10 vectors to get a better measurement and help smooth out
// the motors' magnetic interference.
float averageHeading()
{
  LSM303::vector<int32_t> avg = {
    0, 0, 0        };

  for(int i = 0; i < 10; i ++)
  {
    compass.read();
    avg.x += compass.m.x;
    avg.y += compass.m.y;
  }
  avg.x /= 10.0;
  avg.y /= 10.0;

  // avg is the average measure of the magnetic vector.
  return heading(avg);
}
*/