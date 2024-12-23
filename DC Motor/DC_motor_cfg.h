/************************************************************************************************************************
 * 	Module:DC motor
 * 	File Name:DC_motor_cfg.h
 *  Authors: Esraa Fawzy
 *           Dina Hamed
 *	Date: Jan 30, 2024
 *	*********************************************************************************************************************
 *	Description:
 *The `DC_motor_cfg.h` file contains configuration constants and macros specific to the DC motor module. It provides
 pre-build configurations for defining the GPIO port and pins used to control the DC motor.
 *
 *
 ***********************************************************************************************************************/

#ifndef INC_DC_MOTOR_CFG_H_
#define INC_DC_MOTOR_CFG_H_
/************************************************************************************************************************
 *                     				    VENDOR & SOFTWARE VERSION CONTROL
 ***********************************************************************************************************************/

#define DC_MOTOR_CFG_SW_MAJOR_VERSION           (1U)
#define DC_MOTOR_CFG_SW_MINOR_VERSION           (1U)
#define DC_MOTOR_CFG_SW_PATCH_VERSION           (0U)
/************************************************************************************************************************
 *                            			     PRE-BUILD CONFIGURATIONS
 ***********************************************************************************************************************/

typedef enum {
    DRAG_MOTOR = 0,
    STEERING_MOTOR = 1
} DCMotor_Type;

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin0;
    uint16_t pin1;
} DCMotor_Config;

#define DRAG_MOTOR_PORT GPIOA
#define DRAG_MOTOR_PIN0 GPIO_PIN_8
#define DRAG_MOTOR_PIN1 GPIO_PIN_9

#define STEERING_MOTOR_PORT GPIOB
#define STEERING_MOTOR_PIN0 GPIO_PIN_8
#define STEERING_MOTOR_PIN1 GPIO_PIN_9

static const DCMotor_Config motorConfigs[] = {
    [DRAG_MOTOR] = {DRAG_MOTOR_PORT, DRAG_MOTOR_PIN0, DRAG_MOTOR_PIN1},
    [STEERING_MOTOR] = {STEERING_MOTOR_PORT, STEERING_MOTOR_PIN0, STEERING_MOTOR_PIN1}
};

#endif /* INC_DC_MOTOR_CFG_H_ */
