# Remote-Sensing
基于MPU6050+stm32f103，设计一集遥感和推杆两种控制模式一体的小车。Base on mpu6050，designed a car with remote sense.

<p align="center">
  <a href="https://img.shields.io/badge/language-C-brigreen.svg?style=flat-square"><img src="https://img.shields.io/badge/language-C-brigreen.svg?style=flat-square" alt="C"></a>

  <a href="https://img.shields.io/endpoint?label=remoted&logo=mpu6050"><img src="https://img.shields.io/endpoint?label=remoted&logo=mpu6050" alt="C"></a>
</p>

****
<p align="center">
  <a href="./software/README.md">软件说明|</a>
  <a href="./hardware/README.md">硬件说明|</a>
  <a href="./Docs/姿态相关参考文档/姿态解算说明（Mini AHRS）.pdf">姿态解算|</a>
</p>

## 简介
2019集大电协 手势遥感遥控车

## 背景
在玩具制造业中，遥控手柄控制的玩具车占有很大比重。但是传统的按键手柄控制方式已经很难吸引大众的眼球。故本项目研究基于陀螺仪的手势遥感车，它能够完整地监测游戏者手的位移和旋转，利用玩家的手势姿态来替代繁琐的按键操作，从而实现各种游戏的操作效果。系统的目的是，利用陀螺仪进行角度检测，改善繁琐的按键控制方式，改变传统遥控方式。

## 工具介绍

工具     | 描述
-------- | -----
Altium Design|PCB设计
Keil|软件编程
123D Design|3D软件

## 目录说明
````
+——Marine craft
|---- 3D model: 【设计文档】
|----+ hardware:【电路设计】  
|       ├──STM32_Controller 【车载主控板】
|       ├──Remote control 【遥控器】
|---+ software:【软件设计】
|       ├──Remote vehicle【遥感车程序】
|       ├──Remote control【遥控器程序】
````


- 3轴姿态方向说明

![3轴姿态方向说明](/Docs/Pictures/MPU6050.png "3轴姿态方向说明")



## Hardware
- 主控与外设描述

硬件     | 描述
-------- | -----
芯片型号  |STM32F103
串口  | ZIGBEE
蓝牙  | HC-05
陀螺仪  | MPU6050
显示|oled

- [x]  车载主控板

![主控板](/Docs/Pictures/STM32-controller.png "主控板")


- [x] 手持遥控器

![手持遥控器](/Docs/Pictures/Remoted-Broad.png "手持遥控器")

- [x] 手持遥控器3D
![手持遥控器](/Docs/Pictures/Remoted-3D.png "手持遥控器")

- [x] 手持遥控器实物
![遥控器](/Docs/Pictures/Remote.jpg "遥控器")

## Software

### 两种模式

- [x] 摇杆遥控模式
- [x] 推杆遥控模式
- 数据包通信协议

| 编号 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 
| --- | --- | --- | --- | --- | --- | --- | --- |
| 数据所代表的含义 | 模式位 | 包头 | 包头 | 数据长度位 | X轴角度 | Y轴角度 | 校验 | 
| 说明 | 1-遥控、0-追踪 | AA | 55 | 2 | X_angle | Y_angle | 累加 |
| 数组编号 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |

### 核心PID算法

PID算法的详解已上传至CSDN。

【PID算法详解】：https://blog.csdn.net/weixin_42881419/article/details/86551249

【欢迎关注个人主页】：https://me.csdn.net/weixin_42881419

````
float PID_Cal(float Speed)
{
	pid.SetSpeed = Speed;
	pid.Err = pid.SetSpeed - pid.ActualSpeed;//误差的计算，即比例控制
	pid.Integral += pid.Err;//误差相加，即积分控制
	pid.Voltage = pid.Kp * pid.Err + pid.Ki * pid.Integral + pid.Kd *
		(pid.Err - pid.Err_last);//根据位置型PID控制的公式
	pid.Err_last = pid.Err;
	pid.ActualSpeed = pid.Voltage * 1.0; //转换
	return pid.ActualSpeed;//PID控制后的实际输出值
}

````
