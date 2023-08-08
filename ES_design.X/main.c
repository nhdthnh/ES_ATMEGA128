/*
 * File:   main.c
 * Author: thanh
 *
 * Created on August 3, 2023, 9:10 AM
 */


#include <xc.h>
#include "user_define.h"
#define F_CPU 10000000
#include <util/delay.h>
unsigned long led = 0x55555555;
unsigned char segcode[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};

void led_display(unsigned long led) {
    LED0 = led & 0x000000ff;
    LED1 = (led >> 8) & 0x000000ff;
    LED2 = (led >> 16) & 0x000000ff;
    LED3 = (led >> 24) & 0x000000ff;
}
int i;

SevenDisplay(unsigned int value) {
    LED70 = segcode[value % 10];
    LED71 = segcode[(value / 10) % 10];
    LED72 = segcode[(value / 100) % 10 % 10];
    LED73 = segcode[(value / 1000) % 10 % 10];
}

SevenDisplayScan(unsigned int value) {
    LED7IDATA = segcode[value % 10];
    LED7IDTR = 0b11111110;
    //    _delay_ms(500);
    //    LED7IDTR = 0xff;

    LED7IDATA = segcode[value / 10 % 10];
    LED7IDTR = 0b11111101;
    //    _delay_ms(500);
    //    LED7IDTR = 0xff;

    LED7IDATA = segcode[(value / 100) % 10 % 10];
    LED7IDTR = 0b11111011;
    //    _delay_ms(500);
    //    LED7IDTR = 0xff;

    LED7IDATA = segcode[(value / 1000) % 10 % 10];
    LED7IDTR = 0b11110111;
    //    _delay_ms(500);
    //    LED7IDTR = 0xff;
}

void LcdInit() {
    LCD_INS = 0x38;
    LCDE_H;
    _delay_us(1);
    LCDE_L;
    _delay_us(1);
    _delay_us(200);
    LCD_INS = 0x0C;
    LCDE_H;
    _delay_us(1);
    LCDE_L;
    _delay_us(1);
    _delay_us(200);
    LCD_INS = 0x06;
    LCDE_H;
    _delay_us(1);
    LCDE_L;
    _delay_us(1);
    _delay_us(200);
    LCD_INS = 0x01;
    LCDE_H;
    _delay_us(1);
    LCDE_L;
    _delay_us(1);
    _delay_ms(20);
}

void Print(const char *str, unsigned line, unsigned col) {
    unsigned char add;
    switch (line) {
        case 0: add = 0x80;
            break;
        case 1: add = 0xC0;
            break;
        case 2: add = 0x94;
            break;
        case 3: add = 0xD4;
            break;
    }
    LCD_INS = add + col;
    LCDE_H;
    _delay_us(1);
    LCDE_L;
    _delay_us(50);
    while (*(str) != '\0') {
        LCD_DATA = *str++;
        LCDE_H;
        _delay_us(1);
        LCDE_L;
        _delay_us(10);
    }
}

MenuDisplay(Menu *menu, unsigned char select) {
    Print(menu ->Title, 0, 0);
    Print(menu ->List1, 1, 0);
    Print(menu ->List2, 2, 0);
    Print(menu ->List3, 3, 0);

    Print(">", select, 0);
}

void main(void) {
    unsigned char select = 1;
    unsigned char *p;
    MCUCR |= 0x80;
    DDRG = 0x0f;
    //    relays.relayall = 0x55;
    //    //    relays.relay.RL2=0;
    //    SevenDisplay(1234);
    //    SevenDisplayScan(4321);
    //    RELAY_ACTIVATION;
    //    LcdInit();
    //    //    LCD_DATA = 'abc';
    //    Print("Hello", 0, 0);
    //    Print("XIN CHAO", 3, 0);
    //    for (i = 0; i < 32; i++) {
    //        led = (unsigned long) 1 << i;
    //        led_display(led);
    //        _delay_ms(200);
    //    }
    //    MOTORS.DC1 = STOP;
    //    MOTORS.DC2 = STOP;
    //    MOTOR_ACTIVATION;
    //    while (1) {
    //        READKEY;
    //        if (!BUTTONS.LEFT) {
    //            while (!BUTTONS.LEFT)READKEY;
    //            MOTORS.DC1 = FORWARD;
    //        }
    //        if (!BUTTONS.RIGHT)
    //            MOTORS.DC1 = STOP;
    //        MOTOR_ACTIVATION;
    //    }

    Menu *menu;
    menu = &MainMenu;
    LcdInit();
    MenuDisplay(menu, select);
    while (1) {
        READKEY;
        if (!BUTTONS.DOWN) {
            while (!BUTTONS.DOWN) READKEY;
            select = (select == 3) ? 1 : select + 1;
            MenuDisplay(menu, select);
        }
        if (!BUTTONS.UP) {
            while (!BUTTONS.UP) READKEY;
            select = (select == 1) ? 3 : select - 1;
            MenuDisplay(menu, select);
        }

        if (!BUTTONS.RIGHT) {
            while (!BUTTONS.RIGHT) READKEY;
            switch (select) {
                case 1: menu = (menu -> MenuList1 == NULL) ? menu: menu->MenuList1;
                    break;
                case 2: menu = (menu -> MenuList2 == NULL) ? menu: menu->MenuList2;
                    break;
                case 3: menu = (menu -> MenuList3 == NULL) ? menu: menu->MenuList3;
                    break;
            }
            MenuDisplay(menu, select);
        }

        if (!BUTTONS.LEFT) {
            while (!BUTTONS.LEFT) READKEY;
            menu = (menu -> pre == NULL) ? menu : menu->pre;
            MenuDisplay(menu, select);
        }

        if (!BUTTONS.GO) {
            while (!BUTTONS.GO) READKEY;
            switch (select) {
                case 1: 
                    if(menu -> ActivationON != NULL) menu-> ActivationON(menu->MenuID, ON);
                    break;
                case 2:
                    if(menu -> ActivationOFF != NULL) menu-> ActivationOFF(menu->MenuID, OFF);
                    break;
            }
            MenuDisplay(menu, select);
        }

    }
    while (1);
    return;
}
