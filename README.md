# Remote-Sensing
Base on mpu6050，designed a car with remote sense.


基于MPU6050，制作手势遥感遥控车。
两种遥控模式：
- 推杆摇杆
- 基于MPU6050的俯仰角和偏航角进行遥控。

<p align="center">
  <a href="https://img.shields.io/badge/language-C-brigreen.svg?style=flat-square"><img src="https://img.shields.io/badge/language-C-brigreen.svg?style=flat-square" alt="C"></a>
</p>



## 简介
2019集大电协 手势遥感遥控车

工具     | 描述
-------- | -----
Altium Design|PCB设计
Keil|软件编程
123D Design|3D软件


- 3轴姿态方向说明

![3轴姿态方向说明](/Docs/Pictures/MPU6050.png "3轴姿态方向说明")

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

- [x] 自动追踪模式
- [x] 遥控模式
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
