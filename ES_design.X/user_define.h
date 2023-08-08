/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stddef.h>
// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

#define exmem_add 0x1100

//cs offset
#define	cs0	0
#define	cs1	1
#define	cs2	2
#define	cs3	3
#define	cs4	4
#define	cs5	5
#define	cs6	6
#define	cs7	7
#define	cs8	8
#define	cs9	9
#define	cs10	10
#define	cs11	11
#define	cs12	12
#define	cs13	13
#define	cs14	14
#define	cs15	15
#define	cs16	16
#define	cs17	17
#define	cs18	18

#define LCDE_H (PORTG |= (1<<3));
#define LCDE_L (PORTG &= ~(1<<3));

#define LED0 *(unsigned char*) (exmem_add+cs0)
#define LED1 *(unsigned char*) (exmem_add+cs1)
#define LED2 *(unsigned char*) (exmem_add+cs2)
#define LED3 *(unsigned char*) (exmem_add+cs3)

#define LED70 *(unsigned char*) (exmem_add+cs4)
#define LED71 *(unsigned char*) (exmem_add+cs5)
#define LED72 *(unsigned char*) (exmem_add+cs6)
#define LED73 *(unsigned char*) (exmem_add+cs7)

#define LED7IDTR *(unsigned char*) (exmem_add+cs8)
#define LED7IDATA *(unsigned char*) (exmem_add+cs9)

#define LCD_DATA *(unsigned char*) (exmem_add+cs11)
#define LCD_INS *(unsigned char*) (exmem_add+cs12)

#define RELAYMAP *(unsigned char*) (exmem_add+cs10)
#define RELAY_ACTIVATION (*(volatile unsigned char*) (exmem_add+cs10) = *(unsigned char*) (&relays))
#define MOTOR_ACTIVATION (*(volatile unsigned char*) (exmem_add+cs13) = *(unsigned char*) (&MOTORS))
#define READKEY (*(unsigned char*)(&BUTTONS) = *(volatile unsigned char*) (exmem_add+cs14))

#define STOP 0
#define FORWARD 1
#define REWARD 2

#define ON 1
#define OFF 0

#define Device_Relay 0
#define Device_Motor1 1
#define Device_Motor2 2
#define Device_LED 3



struct bits {
    unsigned char RL0 : 1;
    unsigned char RL1 : 1;
    unsigned char RL2 : 1;
    unsigned char RL3 : 1;
    unsigned char RL4 : 1;
    unsigned char RL5 : 1;
    unsigned char RL6 : 1;
    unsigned char RL7 : 1;
};

union RL {
    unsigned char relayall;
    struct bits relay;
};

union RL relays;

struct motor {
    unsigned char DC1 : 2;
    unsigned char DC2 : 2;
    unsigned char DC_FREE : 4;
};

struct motor MOTORS;

struct button {
    unsigned char LEFT : 1;
    unsigned char RIGHT : 1;
    unsigned char UP : 1;
    unsigned char DOWN : 1;
    unsigned char GO : 1;
    unsigned char BTN1 : 1;
    unsigned char BTN2 : 1;
    unsigned char BTN3 : 1;
};
struct button BUTTONS;


void ActuatorActivation(char Devices, char status) {
    switch (Devices) {
        case Device_Relay: if (status)relays.relayall = 0xff;
        else relays.relayall = 0x00;
        RELAY_ACTIVATION;
            break;
        case Device_Motor1: MOTORS.DC1 = status; MOTOR_ACTIVATION;
            break;
        case Device_Motor2: MOTORS.DC2 = status; MOTOR_ACTIVATION;
            break;
        case Device_LED: if (status) LED0 = 0xff;
        else LED0 = 0x00;
            break;
    }
}
//menu---------------------

typedef struct Linker {
    char MenuID;
    struct Linker *pre;
    char Title[20];
    char List1[20];
    struct Linker *MenuList1; void (*ActivationON)(char, char);
    char List2[20];
    struct Linker *MenuList2; void (*ActivationOFF)(char, char);
    char List3[20];
    struct Linker *MenuList3;
} Menu;
Menu MainMenu, SensorMenu, ActuatorMenu, SettingMenu, TempMenu, HumidMenu, DateTimeMenu, RelayMenu, MotorMenu, LedMenu, Motor1Menu, Motor2Menu;

Menu MainMenu = {
    NULL,
    NULL,
    "      Main menu    ",
    "  Sensors          ", &SensorMenu, NULL,
    "  Actuator         ", &ActuatorMenu, NULL,
    "  Setting          ", &SettingMenu, NULL,
};
//----------------------------------
Menu SensorMenu = {
    NULL,
    &MainMenu,
    "      Sensor       ",
    "  Temperatures     ", NULL, NULL,
    "  Humidity         ", NULL, NULL,
    "  Date & Time      ", NULL,
};
Menu TempMenu = {
    NULL,
    &SensorMenu,
    "      Temperature  ",
    "  ON               ", NULL, NULL,
    "  OFF              ", NULL, NULL,
    "  NONE             ", NULL,
};

Menu HumidMenu = {
    NULL,
    &SensorMenu,
    "      Humidity     ",
    "  ON               ", NULL, NULL,
    "  OFF              ", NULL, NULL,
    "  NONE             ", NULL,
};

Menu DateTimeMenu = {
    NULL,
    &SensorMenu,
    "      Date & Time  ",
    "  ON               ", NULL, NULL,
    "  OFF              ", NULL, NULL,
    "  NONE             ", NULL,
};

//----------------------------------

Menu ActuatorMenu = {
    NULL,
    &MainMenu,
    "      Actuator     ",
    "  Motor            ", &MotorMenu, NULL,
    "  Relay            ", &RelayMenu, NULL,
    "  LEDS             ", &LedMenu, NULL,
};

Menu MotorMenu = {
    NULL,
    &ActuatorMenu,
    "      Motor        ",
    "  Motor1           ", &Motor1Menu, NULL,
    "  Motor2           ", &Motor2Menu, NULL,
    "  NONE             ", NULL,
};

Menu RelayMenu = {
    Device_Relay,
    &ActuatorMenu,
    "      Relay        ",
    "  ON           ", NULL, *ActuatorActivation,
    "  OFF           ", NULL, *ActuatorActivation,
    "  NONE             ", NULL,
};

Menu LedMenu = {
    Device_LED,
    &ActuatorMenu,
    "      LED          ",
    "  LED1             ", NULL, *ActuatorActivation,
    "  LED2             ", NULL, *ActuatorActivation,
    "  NONE             ", NULL,
};
Menu Motor1Menu = {
    Device_Motor1,
    &MotorMenu,
    "      Motor 1      ",
    "  ON               ", NULL, *ActuatorActivation,
    "  OFF              ", NULL, *ActuatorActivation,
    "  NONE             ", NULL,
};

Menu Motor2Menu = {
    Device_Motor2,
    &MotorMenu,
    "      Motor 1      ",
    "  ON               ", NULL, *ActuatorActivation,
    "  OFF              ", NULL, *ActuatorActivation,
    "  NONE             ", NULL,
};


//----------------------------------
Menu SettingMenu = {
    NULL,
    &MainMenu,
    "      Setting menu ",
    "  Time             ", NULL, NULL,
    "  Speeds           ", NULL, NULL,
    "  Channel          ", NULL,
};
//----------------------------------

