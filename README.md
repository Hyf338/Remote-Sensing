# Remote-Sensing
基于MPU6050+stm32f103，设计一集遥感和推杆两种控制模式一体的小车。Base on mpu6050，designed a car with remote sense.

<p align="center">
  <a href="https://img.shields.io/badge/language-C-brigreen.svg?style=flat-square"><img src="https://img.shields.io/badge/language-C-brigreen.svg?style=flat-square" alt="C"></a>
  <a href="https://img.shields.io/endpoint?label=remoted&logo=mpu6050"><img src="https://img.shields.io/endpoint?label=remoted&logo=mpu6050" alt="C"></a>
</p>

****
[软件说明](https://github.com/Hyf338/Remote-Sensing/tree/master/hardware)


## Title
2019集大电协 基于MPU6050的体感遥控车

## Background
在玩具制造业中，遥控手柄控制的玩具车占有很大比重。但是**传统的按键手柄控制方式已经很难吸引大众的眼球**。故本项目研究基于陀螺仪的手势遥感车，**它能够完整地监测游戏者手的位移和旋转**，利用玩家的手势姿态来替代繁琐的按键操作，从而实现各种游戏的操作效果。系统的目的是，利用陀螺仪进行角度检测，改善繁琐的按键控制方式，改变传统遥控方式。

## Introduction

## 系统功能框图
![遥控器流程图]("\Docs\Flow_chart\遥感车系统功能框图.jpg")
## 工具介绍

工具     | 描述
-------- | -----
**Altium Design**|PCB设计
**Keil**|软件编程
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


## Hardware
- 主控与外设描述

硬件     | 描述
-------- | -----
芯片型号  |STM32F103
UART  | ZIGBEE
UART  | HC-05
IIC   | MPU6050
SPI  | oled

- [x]  车载主控板

![主控板](/Docs/Pictures/STM32-controller.png "主控板")

- [x] 手持遥控器

![手持遥控器](/Docs/Pictures/Remoted-Broad.png "手持遥控器")

- [x] 手持遥控器3D

![手持遥控器](/Docs/Pictures/Remoted-3D.png "手持遥控器")

- [x] 手持遥控器实物
![遥控器](/Docs/Pictures/Remote.jpg "遥控器")




