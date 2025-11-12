#ifndef __MOTOR_H__
#define __MOTOR_H__
#include <LPC21xx.h>

#define MOTOR_PIN  (1<<7)
#define LIGHT_PIN  (1<<8)

static inline void motor_init(void) 
{ IODIR0 |= MOTOR_PIN | LIGHT_PIN; }
static inline void motor_on(void)  { IO0SET = MOTOR_PIN; }
static inline void motor_off(void) { IO0CLR = MOTOR_PIN; }
static inline void light_on(void)  { IO0SET = LIGHT_PIN; }
static inline void light_off(void) { IO0CLR = LIGHT_PIN; }


