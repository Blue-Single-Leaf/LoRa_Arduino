/*
  This example shows how to log data from analog sensor
  to MySQL server
  
  For device:
  * LG01
  
  modified 29 Dec 2016
  by  Dragino Technology Co., Limited <support@dragino.com>

  This sketch needs write a script in the openwrt side. for more detail, please refer: http://wiki.dragino.com/index.php?title=Save_Data_to_MySQL
*/
 
#include <Bridge.h>

//If you use Dragino IoT Mesh Firmware, uncomment below lines.
//For product: LG01. 
#define BAUDRATE 115200         //波特率

//If you use Dragino Yun Mesh Firmware , uncomment below lines. 
//#define BAUDRATE 250000 

 
//int sensor;
 int HEART_LED=A2;        //设置心形灯亮灭
void setup() {            //初始化
  int i;
  // Initialize the Bridge and the Console
  Bridge.begin(BAUDRATE);         
  Console.begin();
  for(i = 0;i < 5;i++)
  {
    digitalWrite(HEART_LED, HIGH);   // turn the HEART_LED on (HIGH is the voltage level)
                                     //心形灯置高
    delay(1000);              // wait for a second
    digitalWrite(HEART_LED, LOW);    // turn the HEART_LED off by making the voltage LOW
                                      //心形灯置低
    delay(1000); 
  }
  pinMode(HEART_LED, OUTPUT);
 
  while (!Console); // wait for Serial port to connect.
  Console.println("Start Sketch\n");
}
 
void loop () {        //循环部分
  // read the sensor
  // sensor = analogRead(0);
  send_data();        //调用下方的发送数据函数
  digitalWrite(HEART_LED, HIGH);   // turn the HEART_LED on (HIGH is the voltage level)
                                   //心形灯置高
  delay(1000);              // wait for a second
  digitalWrite(HEART_LED, LOW);    // turn the HEART_LED off by making the voltage LOW
                                    //心形灯置低
  delay(1000); 
  delay(6000);                    //延时六秒
 
}
 
// This function call the linkmysql.lua
void send_data() {            //这个函数是调用Process.h里面的对象Process，可以调用Linux命令行
  Process logdata;           //创建对象
  // date is a command line utility to get the date and the time
  // in different formats depending on the additional parameter
  logdata.begin("lua");
  logdata.addParameter("/root/linkmysql.lua");  //
  logdata.addParameter("77.3");  //
                                    //上面三条语句看看括号里面的，是不是和之前在linux命令行下敲的   lua linkmysql.lua 33.7   。
// logdata.addParameter(string(());
  logdata.run();  // run the command      //上面是语句，下面这个logdata.run()函数是执行上面的语句
 
  // read the output of the command
  while (logdata.available() > 0) {       //下面这部分就认为是等待上面的语句执行完吧，我也得去看看，多试试才知道。但这个得有的。
    char c = logdata.read();
  }
  Console.println("send data done.");
}
