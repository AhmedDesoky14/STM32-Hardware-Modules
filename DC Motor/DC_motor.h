/************************************************************************************************************************
 * 	Module:DC motor
 * 	File Name:DC_motor.h
 *  Authors: Esraa Fawzy
 *           Dina Hamed
 *	Date: Jan 30, 2024
 *	*********************************************************************************************************************
 *	Description:
 *	The purpose of the DC_motor.h module is to make it easier to control a DC motor with the HAL of the STM32F1 microcontroller.
 *	 It has functions for starting the motor, directing it, and changing its speed.
 *	 In order to define the direction of motor rotationâ€”stop, clockwise,
 *	 and anticlockwiseâ€”the module creates an enumeration called DCMotor_direction.
 ***********************************************************************************************************************/
#ifndef INC_DC_MOTOR_H_
#define INC_DC_MOTOR_H_
/************************************************************************************************************************
 *                     							             INCLUDES
 ***********************************************************************************************************************/

#include "stm32f1xx_hal.h"
#include "DC_motor_cfg.h"
/************************************************************************************************************************
 *                     				          VENDOR & SOFTWARE VERSION CONTROL
 ***********************************************************************************************************************/

#define VENDOR_ID (2024U)
#define DC_MOTOR_SW_MAJOR_VERSION (1U)
#define DC_MOTOR_SW_MINOR_VERSION (1U)
#define DC_MOTOR_SW_PATCH_VERSION (0U)

#if ((DC_MOTOR_SW_MAJOR_VERSION != DC_MOTOR_CFG_SW_MAJOR_VERSION) \
  || (DC_MOTOR_SW_MINOR_VERSION != DC_MOTOR_CFG_SW_MINOR_VERSION) \
  || (DC_MOTOR_SW_PATCH_VERSION != DC_MOTOR_CFG_SW_PATCH_VERSION))
#error "Software version mismatch between DC Motor module and configuration"
#endif
/************************************************************************************************************************
 *                     						          MODULE DATA TYPES
 ***********************************************************************************************************************/
typedef enum {
  stop = 0,
  clockwise = 1,
  anti_clockwise = 2
} DCMotor_direction;

typedef struct {
  TIM_HandleTypeDef *htim;
  uint32_t channel;
  DCMotor_Type motorType;
} DCMotor_HandleTypeDef;
/************************************************************************************************************************
 *                     				             Functions Prototypes
 ***********************************************************************************************************************/
void DCMotor_init(DCMotor_HandleTypeDef *motor, TIM_HandleTypeDef *htim, uint32_t channel, DCMotor_Type motorType);
void DCMotor_setDirection(DCMotor_HandleTypeDef *motor, DCMotor_direction direction);
void DCMotor_setSpeed(DCMotor_HandleTypeDef *motor, uint8_t dutyCycle);

#endif /* INC_DC_MOTOR_H_ */
