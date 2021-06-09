/*!
 * MindPlus
 * mpython
 *
 */
#include <MPython.h>
#include <DFRobot_Iot.h>

// 动态变量
volatile float mind_n_control;
// 函数声明
void obloqMqttEventT0(String& message);
void obloqMqttEventT1(String& message);
void onButtonAPressed();
void obloqMqttEventT2(String& message);
void obloqMqttEventT3(String& message);
void obloqMqttEventT4(String& message);
// 静态常量
const String topics[5] = {"mNpb6JCGg","0jNUHm3Mg","USbIdiqMg","hzXhdi3MR","Ikq1dm3Gg"};
const MsgHandleCb msgHandles[5] = {obloqMqttEventT0,obloqMqttEventT1,obloqMqttEventT2,obloqMqttEventT3,obloqMqttEventT4};
// 创建对象
DFRobot_Iot myIot;


// 主程序开始
void setup() {
	mPython.begin();
	myIot.setMqttCallback(msgHandles);
	buttonA.setPressedCallback(onButtonAPressed);
	myIot.wifiConnect("DAV", "20150224");
	while (!myIot.wifiStatus()) {yield();}
	display.setCursorLine(1);
	display.printLine("WiFi连接成功");
	myIot.init("iot.dfrobot.com.cn","yl4KXylMg","","slVFus_GRz",topics,1883);
	myIot.connect();
	while (!myIot.connected()) {yield();}
	display.setCursorLine(2);
	display.printLine("MQTT连接成功");
	display.setCursorLine(3);
	display.printLine("欢迎使用抢答器");
	display.setCursorLine(4);
	display.printLine("按下A键开始抢答");
}
void loop() {

}

// 事件回调函数
void obloqMqttEventT0(String& message) {
	display.fillScreen(0);
	if ((message==String("start1"))) {
		display.setCursorLine(1);
		display.printLine("开始抢答！");
		rgb.write(-1, 0xFF0000);
		mind_n_control = 0;
	}
	if ((message==String("start"))) {
		display.setCursorLine(1);
		display.printLine("开始出题！");
		rgb.write(-1, 0x0000FF);
	}
}
void obloqMqttEventT1(String& message) {
	display.setCursorLine(2);
	display.printLine(message);
}
void onButtonAPressed() {
	display.fillScreen(0);
	if ((mind_n_control==0)) {
		myIot.publish(topic_2, "1号");
	}
	rgb.write(-1, 0x00FFFF);
}
void obloqMqttEventT2(String& message) {
	display.setCursorLine(1);
	display.printLine((String(message) + String("选手答题！")));
	mind_n_control = 1;
}
void obloqMqttEventT3(String& message) {
	display.setCursorLine(2);
	display.printLine(message);
}
void obloqMqttEventT4(String& message) {
	display.setCursorLine(3);
	display.printLine(message);
	rgb.write(-1, 0x000000);
}
