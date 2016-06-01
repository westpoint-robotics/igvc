/*
*  RosSerial Control Mode  
*  This program shows how to control a blink
*  from an arduino using RosSerial
*/

#include <stdlib.h>
#include <ros.h>
#include <std_msgs/String.h>

void mode_cb( const std_msgs::String& mode_cmd)
{

  if (!(strcmp(mode_cmd.data,"manual")))
  {
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  }

  else if (!(strcmp(mode_cmd.data,"autonomous")))
  {
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);              // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);              // wait for a second
  }

  else if (!(strcmp(mode_cmd.data,"panic")))
  {
    digitalWrite(13, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(200);           
    digitalWrite(13, LOW);   // turn the LED off by making the voltage LOW
    delay(200);           
  }
}

ros::NodeHandle  nh;
ros::Subscriber<std_msgs::String> sub("igvc/mode" , mode_cb);

void setup()
{
  pinMode(13, OUTPUT);    //set up the LED
  digitalWrite(13, LOW);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}
