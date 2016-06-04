/*
*  RosSerial Control Mode  
*  This program shows how to control a blink
*  from an arduino using RosSerial
*/

#include <stdlib.h>
#include <ros.h>
#include <std_msgs/String.h>

char led_pin = 3;
int mode = 0;
int count = 0;
int led_state = LOW;

void mode_cb( const std_msgs::String& mode_cmd)
{

  if (!(strcmp(mode_cmd.data,"manual")))
  {
    mode = 0;
  }

  else if (!(strcmp(mode_cmd.data,"auto")))
  {
    mode = 1;
  }

  else if (!(strcmp(mode_cmd.data,"panic")))
  {
    mode = 2;
  }
}

ros::NodeHandle  nh;
ros::Subscriber<std_msgs::String> sub("igvc/mode" , mode_cb);

void setup()
{
  pinMode(led_pin, OUTPUT);    //set up the LED
  digitalWrite(13, LOW);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  if (mode==0)
  {
    digitalWrite(led_pin, HIGH);
  }
  else if (mode==1 && count++ >= 50)
  {
    count = 0;
    led_state = ~led_state;
    digitalWrite(led_pin, led_state);
  }  else if (mode==2 && count++ >= 10 )
  {
    count = 0;
    led_state = ~led_state;
    digitalWrite(led_pin, led_state);
  }
  delay(10);
}
