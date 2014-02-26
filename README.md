Robot
=====

Simple robot using a Beagle Bone Black and Arduino Nano.

Configuração da Beaglebone Black
================

1. [Instalação do Ubuntu 13.10](http://elinux.org/BeagleBoardUbuntu)
2. [Instalação das bibliotecas para IO com python da Adafrut](http://learn.adafruit.com/setting-up-io-python-library-on-beaglebone-black/installation-on-ubuntu)
3. [Configuração da UART1](http://learn.adafruit.com/introduction-to-the-beaglebone-black-device-tree/exporting-and-unexporting-an-overlay) 
4. Workaround para a porta USB ser alimentada na inicialização (hot plug issue)


Montagem do robo
================

Ligação da porta serial e do adaptador Wifi

![](https://raw2.github.com/leoheck/robot/master/docs/Serial%20Connection.png)

Ligação do controlador dos motores e dos sensores

![](https://raw2.github.com/leoheck/robot/master/docs/Sensor%20Connection.png)



Diagrama de pinos das Placas
============================

Beaglebone Black
----------------

![](https://raw.github.com/leoheck/robot/master/docs/Diagrams/Beaglebone%20Black%20Pinout.png)

Arduino Nano
------------

![](https://raw2.github.com/leoheck/robot/master/docs/Diagrams/Arduino%20Nano%20Pinout.png)



