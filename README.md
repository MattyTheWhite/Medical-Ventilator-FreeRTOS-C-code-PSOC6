# Medical-Ventilator-FreeRTOS-C-code-PSOC6
Provide Real- Time task Scheduling to the VUB Medical Ventilator using FreeRTOS adapted with C code, transmit through BLE the values from the sensors by using a PSOC6
  PROVIDE A REAL-TIME SCHEDULING FOR THE VUB MEDICAL VENTILATOR
SOFTWARE AND ENGINEERING FOR EMBEDDED SYSTEMS
Mahtab Hosseinalizadehshalmani Sincy Raj
1

Table of Contents
1 Project presentation
2 Engineering process
3 Hardware description
4 Project in PSoC Creator
4.1 Schematic specification in TopDesign
4.1.1 Timer
4.1.2 Port0_Interrupt
4.1.3 UART
4.1.4 ADC
4.1.5 Analog/digital pins
4.1.6 Analog/digital pins
Error! Bookmark not defined. Error! Bookmark not defined. Error! Bookmark not defined.
Error! Bookmark not defined.
Error! Bookmark not defined. Error! Bookmark not defined. Error! Bookmark not defined. Error! Bookmark not defined. Error! Bookmark not defined. Error! Bookmark not defined. Error! Bookmark not defined.
4.2 Additional modification prior to application generationError! Bookmark not defined.
4.3 Modification of generated code & Application CodeError! Bookmark not defined.
4.3.1 Application code in main_cm4.cError! Bookmark not defined.
4.3.2 Application Code in main_cm0p.cError! Bookmark not defined.
8 Conclusion & Discussion
Error! Bookmark not defined.
2

1 Project presentation
Introduction to the Ventilator Functionality
A ventilator is a machine that provides mechanical ventilation by moving breathable air into and out of the lungs, to deliver breaths to a patient who is physically unable to breathe or breathing insufficiently. Ventilators are computerized microprocessor-controlled machines.
This Particular Ventilator consists of a microcontroller for controlling the bellows and processing the outputs of all sensors. This microcontroller is coupled with a PC, running a GUI, to control all settings and visualize the measured data.
 1- Controller embedded Device, an Atmega-based Controller (Controller Device):
 This controller will implement the closed loop control of the machine. • Reads out the sensors of the machine
• Compute target values for the system
• Steers the currents of the electrical motor
• Communicates the data back to PC
 2- Sensors/actuators
 This controller will implement the closed loop control of the machine. • Pressure sensor 1
• Pressure sensor 2
• Flow sensor
• End Switch
• Motor Driver
  Overview of control loop – runs every 10ms (Task one)
1) Readout sensors:
– Pressure to patient – Airflow
– End switches
2) Compute new values:
– Volume of oxygen to patient
3) Send values to PC
4) Compute new motor speed, based on pressure 5) Actuate motor
  3

The ventilator needs a RTOS scheduler which fits with the function of it. Real-time Operating System or (RTOS) is basically talking about and Operating System which is designed for Real- Time tasks. These real time tasks are the ones which need to be responded from the system immediately or base on a specific deadline defined by them. So, the operating system has a time limitation and not having time forever! The job of task scheduling refers to identifying
 the order in which tasks should execute in a The mentioned 4 tasks are as listed below:
• Task1: Control loop which contains several functions • Task2: Getting new data from PC
• Task3: Getting ambient Pressure
• Task4: Checking the Fan still works
system.
Task1 has been considered in the ventilator requirements as a PERIODIC task with 10ms periodicity.
I have considered the new three tasks as first Periodic and then Aperiodic or Sporadic ones which may occur with no alarms.
The goal of the project is to Provide real-time task scheduling to the VUB Medical Ventilator. For doing so we need to Understand the existing code and the real-time needs, explore existing solutions using FreeRTOS, Adapt the code for FreeRTOS. The main language which is used in this project is C Language.
The main Idea of the project is to create processes which generate the proper interruptions respecting the description of the VUB Ventilator. This interruption will act like sensors in case of which the sensors are getting input from the around environment. To implement this idea on the ventilator, we decided to try different scheduling strategies on it. For example, Task 1 (Control Loop should happen every 10ms) and Task2,3,4 are here to be executed. To do so we should wake up our processor in defined time tables and make it sleep accordingly. So here comes the topic of scheduling the related above tasks. The job of task scheduling refers to identifying the order in which tasks should execute in a system. To schedule tasks, we need to have periodic ones or consider them as periodic!! Because it would be much easier to deal with periodic rather than aperiodic tasks! To schedule task, we need to specify the priority among them and classify them with their priority! The priority of them can be either their periodicity or their deadline!
4

2 Engineering Process
How to schedule Tasks (1 to 4)
Classification types of task are as follows: Periodic and Apriodic(Sporadic). We consider Clock driven scheduling for periodic tasks and Event driven scheduling for aperiodic and periodic tasks.
In this project we are examining the Clock Driven Scheduling. Clock Driven Scheduling
As the name suggests, a clock driven scheduler works in synchronism with a clock/timer signal. The timer periodically generates interrupts. On receiving an interrupt, the scheduler is activated which then takes a decision about the process to be scheduled next. we start with the Cyclic scheduling and apply on our ventilator. In cyclic scheduling, the major cycle (equal to the LCM of periodicity of tasks) is divided into a number of equal sized minor cycles or frames (F). The scheduler gets up at individual frame boundaries via interrupts from a periodic timer and performs the switching of tasks that may be necessary between successive frames.
  Figure 1
 The tasks with the most optimize frame size1 are scheduled theoretically as the above figure shows. To implement such this scheduling on our PSOC6 for the ventilator case we need to apply several components form the catalogue in the IDE and then start to modify the programming part.
By considering the above conditions for the ventilator we start to test the hardware connections of PSOC6 and then we start planning the software development which was a major part of the project. To do so we needed to create interrupts which would virtually call the sensors to get input from the environment or go through the control loop. It depends on what time scheduling the interruption is generated (created). By the way, when all the tasks are in the base statement we push the button to create an interrupt or initialize the procedure. Looks like in this case by pushing the button on the board(PSOC6) the first
5

interrupt is the start of ventilator motor. So till here we need a Port0_Interrupt component, a Timer and of course a UART.
We go through detail of the component and the cause they are being used soon. But to get more familiar with the project procedures let’s look at the bellow figure which shows the step by step processes of our project:
   PRESS THE BUTTON ON PSOC6
  WAIT FOR THE TIMER TO RICH THE SCHEDULED TIME FOR TASK 1
FIRST INTERRUPT HAPPENS
      WAIT FOR THE TIMER TO RICH THE SCHEDULED TIME FOR TASK 3
SECOND INTERRUPT HAPPENS
WAIT FOR THE TIMER TO RICH THE SCHEDULED TIME FOR TASK 2
    THIRD INTERRUPT HAPPENS
WAIT FOR THE TIMER TO RICH THE SCHEDULED TIME FOR TASK 4
 LAST INTERRUPT HAPPENS
  Figure 2
  6

3 Hardware Description
For this project we used the recommended PSoC 6 prototyping microcontrollers from Cypress. This MCU is very versatile in IoT applications and covers all of the needs of the project, including the BLE functionality. PSoC 6 was programmed in an interactive IDE, called PSoC Creator, that helped us generate and build the code with all the necessities and program the device. Regarding the code to be on the PSOC6, the idea is that we port the relevant code from the Ventilator to the PSOC and you generate fake functions interruption like the real Ventilator. The basic hardware overview and its connection through a breadboard alongside with some more electronics (described in section 3) are depicted in Figure 1 .
Figure 3 PSOC6
Cypress website describes it as “a low-cost hardware platform that enables design and debug of PSoC 6 MCUs. This kit is designed with a snap-away form-factor, allowing users to separate the KitProg (onboard programmer and debugger) from the target board and use independently”. The board includes the following features:
• Two LEDs to provide feedback
• A push button to provide a simple user input • 1.8V to 3.3V operation
• Bluetooth Low Energy (BLE) Connectivity
• I/O headers including 34 GPIOs
• Several analog and digital blocks (ADC, timer...) • On-board programming with the KitProg
    7

4.Project in PSoC Creator
4.1 Schematic specification in TopDesign
 Figure 4 .Components of the PSoC Creator used in project development
 8

 4.1.1 Timer
The timer block is used as an interrupt generator. Its period is defined in the code and is different depending whether the device is in normal mode or in debug mode. When the timer expires an interrupt is generated that activates the task schedule and timer is reset.
 Figure 5
 9

 4.1.2 Port0_Interrupt
This global interrupt component generates an interrupt on port 0 when the user button is pressed.
 Figure 6
 10

 4.1.3 UART
The UART component handles the UART communication between the PSoC and the PC through USB. None of the parameters of the UART block were changed.
 Figure 7
 11

 4.1.4. Analog/digital pins
The button is an input pin while the LED pins are output pins.
 Figure 8
 12

 4.1.4. Buid-Settings
Before we can process with the IDE and auto-generate the code some of the build settings needed to be changed according to this project.
 Figure 9
13

 4.1.4. Interrupts
 Figure 10-Interrupts setting of the project
 4.1.5. Pins
All the components with I/Os and analog/digital pins were assigned in the Pins sections of the Design Wide Resources of the project as demonstrated in Figure 11, with corresponding Port and Pin numbers
 Figure 11
 After specifying and modifying all the above build settings, the application was generated, and we then continued with its further modification and construction of the application code in our main c files.
14

 4.2 Modification of generated code & Application Code
The first of the header files that needed to be changed after the application generation was FreeRTOSConfig.h. A code snippet of the file’s macros, shown in Figure 12, was changed on line 71 to allow macros.
.
 Figure 12-FreeRTOS
4.2.1 Application code in main_cm4.c The final code that we put together in the main_cm4.c consists of modified parts of different examples explained in the report, while a large part of the code consists of the added custom functions that cover the functionality of the ventilator scheduler.
15

Function buttonInterruptHandler,Is the function handles the timer interrupt. It clears the interrupt on the timer.
Figure 13 main.c
 16

4.2.2 Application code in main_cm4.c ,Below is the Timer interrupt Handler function .
 Figure 14
4.2.3 There are 4 task() functions in this main.c file. Each task function is to perform different tasks like below. But since we are mimicking the VUB ventilator tasks, we don’t implement the exact task here but we have implemented the code for calling interrupters and setting appropriate delays for each tasks. After each delay we are toggling the LED.
 Figure 15
17

 Figure 16
  Figure 18
Figure 17
18

8. Conclusion & Discussion
When we started off the project, the scope of the project was bigger which includes hardware like temperature sensor and pressure sensors to mimic the ventilator functionalities but with the time constraint as well as limited knowledge of the electronics and C programming language, we narrowed down the scope of the project and we were able to schedule 4 ventilator tasks using appropriate interrupts and timers.
9. References
1. Experimenting With Peripherals and the Clicker 2 for PSoC 6 (rs-online.com)
2. CY8CPROTO-063-BLE PSoC® 6 BLE Prototyping Board Guide (mouser.de)
3. PSoC 6 Peripheral Driver Library: SysInt (System Interrupt) (infineon.github.io)
   19
