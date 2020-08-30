# LibRobot
## 融合语音识别控制的全自动图书馆借还机器人
https://github.com/XiaYubin/LibRobot

本项目在互联网大潮流和机器人飞速发展的大环境背景下，打造一款智能化图书馆机器人系统。该系统结合嵌入式系统开发的相关知识，自主组建并安装机器人，同时还结合图像识别、语音识别等技术，最终完成全自动图书馆借还机器人的研究与设计，实现通过机器人自主进行书籍的取还及整理。该项目使用STM32F429单片机作为下位机主控，直接控制机器人硬件，上位机4核Raspberry Pi 3B+微型电脑系统，主要进行语音采集、自然语言处理、机器视觉等运算工作，并通过WiFi与图书馆服务器进行通讯。

## TODO:

- [ ] TODO：语音识别接口
- [ ] TODO：还书过程运动逻辑
- [x] TODO：明确上位机指令

## 流程图：

```flow
st1=>start: 开始
op1=>operation: 运动到还书架
op2=>operation: 拾取图书
op3=>operation: 扫描图书编码
op4=>operation: 查询图书位置
op5=>operation: 运动到书架前
op6=>operation: 夹具将书放入书架
op7=>operation: 逐个书架扫描图书
op8=>operation: 整理图书
cond1=>condition: 书架上有书?
cond2=>condition: 编号在前后之间?
end1=>end: End

st1->op1->cond1
cond1(yes)->op2->op3->op4->op5->cond2
cond2(yes)->op6(left)->op1
cond2(no)->op5
cond1(no)->op7(right)->op8(right)->op1
```

