/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include <math.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <limits.h>

#define TIMER_PERIOD_MSEC           2000U   // 1 hour timer period in milliseconds
int16_t COUNT_TIMER = 0;

#define MY_TCPWM_CNT_NUM   (0UL)
void task1();
void task2();
void task3();
void task4();



/*****************************************************************************\
 * Function:    timerInterruptHandler(void)
 * Input:       void (it is called inside of the ISR)
 * Returns:     void
 * Description: 
 *   This function handles the timer interrupt. It clears the interrupt on the
 *   timer
\*****************************************************************************/
void timerInterruptHandler(void)
{
    Cy_TCPWM_ClearInterrupt(Timer_HW, Timer_CNT_NUM, CY_TCPWM_INT_ON_TC); // Clear the Timer terminal count interrupt
    COUNT_TIMER += 1; 
    
    if(COUNT_TIMER == 1)
       task1();
    if(COUNT_TIMER == 2)
       task2();
    if(COUNT_TIMER == 3)
       task3();
    if(COUNT_TIMER == 4)
       task4();
       COUNT_TIMER = 0;
  
}



/*****************************************************************************\
 * Function:    task1()
 * Input:       void (it is called inside of the ISR)
 * Returns:     void
 * Description: 
 *   This function is called when a timer expires, when a button is pressed . It toggles the red LED on for
 *   3 seconds.
\*****************************************************************************/
void task1()
{
    /* Toggle the LED  */
    //printf("Inside Task 1");
    //printf("Control loop which contains several functions");
     
    //Cy_GPIO_Clr(LED_GREEN_PORT, LED_GREEN_NUM);
    Cy_GPIO_Write(LED_GREEN_PORT, LED_GREEN_NUM, 0);
    Cy_SysLib_Delay(1000); // Duration LED are on
      /* Toggle the LED  */
    Cy_GPIO_Write(LED_GREEN_PORT, LED_GREEN_NUM, 1);
    //Cy_GPIO_Set(LED_GREEN_PORT, LED_GREEN_NUM);
    
}


/*****************************************************************************\
 * Function:    task2()
 * Input:       void (it is called inside of the ISR)
 * Returns:     void
 * Description: 
 *   This function is called when a timer expires, when a button is pressed . It toggles the red LED on for
 *   3 seconds.
\*****************************************************************************/
void task2()
{
    /* Toggle the LED  */
   
   printf("Inside Task 2");
   printf("Getting new data from PCs");
    //Cy_GPIO_Clr(LED_RED_PORT, LED_RED_NUM);
   Cy_GPIO_Write(LED_RED_PORT, LED_RED_NUM, 0);
   Cy_SysLib_Delay(1000); // Duration LED are on
      /* Toggle the LED  */
    //Cy_GPIO_Set(LED_RED_PORT, LED_RED_NUM);
   Cy_GPIO_Write(LED_RED_PORT, LED_RED_NUM, 1);
 
}

/*****************************************************************************\
 * Function:    task3()
 * Input:       void (it is called inside of the ISR)
 * Returns:     void
 * Description: 
 *   This function is called when a timer expires, when a button is pressed . It toggles the red LED on for
 *   3 seconds.
\*****************************************************************************/
void task3()
{
    /* Toggle the LED  */
    printf("Task 3");
    printf("Getting ambient Pressure");
    Cy_GPIO_Write(LED_GREEN_PORT, LED_GREEN_NUM, 0);
    Cy_SysLib_Delay(1000); // Duration LED are on
      /* Toggle the LED  */
    Cy_GPIO_Write(LED_GREEN_PORT, LED_GREEN_NUM, 1);
 
}

    

/*****************************************************************************\
 * Function:    task4()
 * Input:       void (it is called inside of the ISR)
 * Returns:     void
 * Description: 
 *   This function is called when a timer expires, when a button is pressed . It toggles the red LED on for
 *   3 seconds.
\*****************************************************************************/
void task4()
{
   
    printf("Task 4");
    printf(" Checking the Fan still works");
   
    Cy_GPIO_Write(LED_RED_PORT, LED_RED_NUM, 0);
    Cy_SysLib_Delay(1000); // Duration LED are on
      /* Toggle the LED  */
    Cy_GPIO_Write(LED_RED_PORT, LED_RED_NUM, 1);
   
}
    
  
 /*****************************************************************************\
 * Function:    buttonInterruptHandler(void)
 * Input:       void (it is called inside of the ISR)
 * Returns:     void
 * Description: 
 *   This function handles the button interrupt. It clears the interrupt on the
 *   button pin 
\*****************************************************************************/
void buttonInterruptHandler(void)
{
    NVIC_ClearPendingIRQ(SysInt_Port0_cfg.intrSrc);
    Cy_SysInt_Init(&SysInt_Port0_cfg, timerInterruptHandler);
    NVIC_ClearPendingIRQ(SysInt_Port0_cfg.intrSrc); // Clears the interrupt
    NVIC_EnableIRQ(SysInt_Port0_cfg.intrSrc); // Enable the core interrupt
    Cy_TCPWM_Counter_SetPeriod(Timer_HW, Timer_CNT_NUM, TIMER_PERIOD_MSEC - 1);
    Cy_TCPWM_TriggerReloadOrIndex(Timer_HW, Timer_CNT_MASK);
   
}       
   

int main(void)
{    
    COUNT_TIMER = 0;
    
   

    /* Initialize the interrupt vector table with the timer interrupt handler
     * address and assign priority. */
  //  Cy_SysInt_Init(&isrTimer_cfg, timerInterruptHandler);
  
    __enable_irq(); // Enable global interrupts
    
    /* Start the TCPWM component in timer/counter mode. The return value of the
     * function indicates whether the arguments are valid or not. It is not used
     * here for simplicity. */
    (void)Cy_TCPWM_Counter_Init(Timer_HW, Timer_CNT_NUM, &Timer_config);
      
    /* Set the timer period in milliseconds. To count N cycles, period should be
     * set to N-1. */
    Cy_TCPWM_Counter_SetPeriod(Timer_HW, Timer_CNT_NUM, TIMER_PERIOD_MSEC - 1);
    
  
     
    UART_1_Start(); // Start the UART communication
 
    Cy_SCB_UART_PutString(UART_1_HW,"\033[2J\033[H");
    Cy_SCB_UART_PutString(UART_1_HW,"Terminal Output Running...\r\n");
    
    Cy_GPIO_SetInterruptEdge(BUTTON_1_PORT, BUTTON_1_NUM, CY_GPIO_INTR_RISING);
    Cy_GPIO_SetInterruptMask(BUTTON_1_PORT, BUTTON_1_NUM, CY_GPIO_INTR_EN_MASK);
/* Configure CM4+ CPU GPIO interrupt vector for Port 0 */
    Cy_SysInt_Init(&SysInt_Press_cfg, buttonInterruptHandler);
    NVIC_ClearPendingIRQ(SysInt_Press_cfg.intrSrc);
    NVIC_EnableIRQ((IRQn_Type)SysInt_Press_cfg.intrSrc);

    /* Configure CM4+ CPU GPIO interrupt vector for Port 0 */
    //Cy_SysInt_Init(&SysInt_Press_cfg, buttonInterruptHandler);  
    //NVIC_EnableIRQ(SysInt_Press_cfg.intrSrc);
 
    
    /* The PSOC is in sleep mode and waits for an interrupt */
    for(;;)
    {
        Cy_SysPm_Sleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
}

    
     


/* [] END OF FILE */
