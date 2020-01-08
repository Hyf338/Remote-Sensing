# softwara

## 遥控器
【进行模式选择和切换】

- [X]传统推杆模式下，对采集到推杆的值进行ADC模数转化,采用均值滤波算法进行数据处理；

- [X]体感控制模式下，对MPU6050陀螺仪采集的数据进行姿态融合和解算，以输出对应角度。

### 程序设计思路
>在整体软件中，遥控器部分，首先通过遥控器进行**模式选择**，进入不同的模式，从而执行不同的**数据采集和处理**
- 推杆遥感模式下对采集到推杆的值进行ADC模数转化,采用均值滤波算法进行数据处理；
- 遥感模式下对MPU6050陀螺仪采集的数据进行姿态解算以输出对应角度
根据模式选择不同的发送数据；

### 程序流程图
![遥控器流程图]("..\Docs\Flow_chart\遥控器流程图.jpg")


## 被控小车

- [X]分解接收到的数据，判断遥控器所处的模式，调用不同的数据处理算法和运动控制算法。

- [X]断连和避障模式下进行停车处理

### 程序设计思路

- 遥感的小车部分，根据接收到的不同数据和模式，调用不同的控制函数与数据处理算法，再调用不同的数据处理和运动控制算法。
- 利用超声波测距模块，进行避障处理
- 断连模式下，小车进行停车处理

### 程序流程图
![遥控器流程图]("..\Docs\Flow_chart\遥控车流程图.jpg")



## 通讯协议

| 包头1 | 包头2 | 模式位 | buffer[4] | buffer[5] | buffer[6] | buffer[7] | buffer[8] | buffer[9] | buffer[10] | buffer[11] | buffer[12] | buffer[13] | buffer[14] | buffer[15] | buffer[16] | buffer[17] | buffer[18] | buffer[19] |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0xaa | 0x55 | sens_mode-->1 | pitch第一字节/低 | pitch第二字节 | pitch第三字节 | pitch第四字节 | roll第一字节/低 | roll第二字节 | roll第三字节 | roll第四字节 | yaw第一字节/低 | yaw第二字节 | yaw第三字节 | yaw第四字节 |  |  |  |  |
| 0xaa | 0x55 | remote_mode--2 |adc_left_UD第一字节/低 | adc_left_UD第二字节 | adc_left_UD第三字节 | adc_left_UD第四字节 | adc_left_LR第一字节/低 | adc_left_LR第二字节 | adc_left_LR第三字节 | adc_left_LR第四字节 | adc_right_UD第一字节/低 | adc_right_UD第二字节 | adc_right_UD第三字节 | adc_right_UD第四字节 | adc_right_LR第一字节/低 | adc_right_LR第二字节 | adc_right_LR第三字节 | adc_right_LR第四字节 | 