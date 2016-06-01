# igvc
Repo for the West Point Intelligent Ground Vehicle Competition Team

## Safety LED for Control Modes

From the IGVC Rules --" Safety Light: The vehicle must have an easily viewed solid indicator light which is turned on whenever the vehicle power is turned on. The light must go from solid to flashing whenever the vehicle is in autonomous mode. As soon as the vehicle comes out of autonomous mode the light must go back to solid."

The IGVC LED has three modes: manual, autonomous, and panic.  Manual mode is solid, autonomous mode blinks at 1 Hz, panic mode blinks at 5 Hz.

### Configuration

1. Connect the LED to Digital Pin 13 (the same pin as the on-board LED).
2. Clone the igvc ros package into your catkin workspace src folder.
 - `cd ~/catkin_ws/src`
 - `git clone https://github.com/westpoint-robotics/igvc.git igvc`
4. Open the sketch from the /sketches/control_mode folder and program your Arduino.
 - Ensure the correct board and COM port is selected (in Linux, it is typically ttyACM0).

### Testing

1. Start up the roscore in a new terminal.
 - `roscore`
2. Launch the rosserial_python serial_node. Make sure to choose the right serial port.
 - `rosrun rosserial_python serial_node.py /dev/ttyACM0`
3. Publish to the mode topic with a string.
 - `rostopic pub igvc/mode std_msgs/String "manual" -r 10`
 - `rostopic pub igvc/mode std_msgs/String "autonomous" -r 10`
 - `rostopic pub igvc/mode std_msgs/String "panic" -r 10`
