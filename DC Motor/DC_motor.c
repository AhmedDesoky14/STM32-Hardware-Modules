/************************************************************************************************************************
 * 	Module:DC motor
 * 	File Name:DC_motor.c
 *  Authors: Esraa Fawzy
 *           Dina Hamed
 *	Date: Jan 30, 2024
 *	*********************************************************************************************************************
 *	Description:
 *	This file implements the HAL and STM32F1 microcontroller capabilities for operating a DC motor.
 *	It has methods to configure the motor's orientation,initialize it,and use PWM to regulate its speed.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 *                     							      INCLUDES
 ***********************************************************************************************************************/
#include "DC_motor.h"
/***********************************************************************************************************************
 *                     					           GLOBAL VARIABLES
 ***********************************************************************************************************************/
///* Drag motor global variables (htim & channel)*/
//TIM_HandleTypeDef *g_htim_drag;
//uint32_t g_channel_drag;
//
///* Steering motor global variables (htim & channel)*/
//TIM_HandleTypeDef *g_htim_steering;
//uint32_t g_channel_steering;
/***********************************************************************************************************************
 *                     					        FUNCTIONS DEFINTITIONS
 ***********************************************************************************************************************/
/************************************************************************************************************************
 * Function Name:DCMotor_init
 * Function ID[hex]: 0x00
 * Sync/Async:Synchronous
 * Reentrancy:Non-Reentrant
 * Parameters (in):htim (pointer to TIM_HandleTypeDef struct), channel (uint32_t)
 * Parameters (inout):None
 * Parameters (out):None
 * Return value:void
 * Description:Initializes a DC motor connected to a specific timer channel.
 ************************************************************************************************************************/
void DCMotor_init(DCMotor_HandleTypeDef *motor, TIM_HandleTypeDef *htim, uint32_t channel, DCMotor_Type motorType) {
    motor->htim = htim;
    motor->channel = channel;
    motor->motorType = motorType;

    const DCMotor_Config* config = &motorConfigs[motorType];
    HAL_GPIO_WritePin(config->port, config->pin0, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(config->port, config->pin1, GPIO_PIN_RESET);
}


/************************************************************************************************************************
 * Function Name: DCMotor_setDirection
 * Function ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Non-Reentrant
 * Parameters (in): direction (DCMotor_direction)
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: void
 * Description: Sets the direction of a DC motor based on the provided direction.
 *              The function configures GPIO pins and starts PWM if needed to control motor direction and speed.
 *              The desired direction of the DC motor (stop, clockwise, anti-clockwise).

 ************************************************************************************************************************/

void DCMotor_setDirection(DCMotor_HandleTypeDef *motor, DCMotor_direction direction) {
    const DCMotor_Config* config = &motorConfigs[motor->motorType];

    switch (direction) {
        case stop:
            HAL_GPIO_WritePin(config->port, config->pin0, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(config->port, config->pin1, GPIO_PIN_RESET);
            break;
        case clockwise:
            HAL_GPIO_WritePin(config->port, config->pin0, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(config->port, config->pin1, GPIO_PIN_SET);
            HAL_TIM_PWM_Start(motor->htim, motor->channel);
            break;
        case anti_clockwise:
            HAL_GPIO_WritePin(config->port, config->pin0, GPIO_PIN_SET);
            HAL_GPIO_WritePin(config->port, config->pin1, GPIO_PIN_RESET);
            HAL_TIM_PWM_Start(motor->htim, motor->channel);
            break;
        default:
            HAL_GPIO_WritePin(config->port, config->pin0, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(config->port, config->pin1, GPIO_PIN_RESET);
            break;
    }
}


/************************************************************************************************************************

 * Function Name: DCMotor_setSpeed
 * Function ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Non-Reentrant
 * Parameters (in): dutyCycle (uint8_t)
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: void
 * Description: Sets the speed of a DC motor by adjusting the PWM duty cycle.
 *               The function calculates the compare value based on the duty cycle percentage
 *               and updates the corresponding timer channel's capture/compare register (CCR).
 *               dutyCycle: The duty cycle percentage (0-100) to set the motor speed.

 ************************************************************************************************************************/

void DCMotor_setSpeed(DCMotor_HandleTypeDef *motor, uint8_t dutyCycle) {
    uint16_t CompareValue = (uint16_t)(((float)dutyCycle / 100) * (float)(motor->htim->Init.Period));

    switch (motor->channel) {
        case TIM_CHANNEL_1:
            motor->htim->Instance->CCR1 = CompareValue;
            break;
        case TIM_CHANNEL_2:
            motor->htim->Instance->CCR2 = CompareValue;
            break;
        case TIM_CHANNEL_3:
            motor->htim->Instance->CCR3 = CompareValue;
            break;
        case TIM_CHANNEL_4:
            motor->htim->Instance->CCR4 = CompareValue;
            break;
        default:
            // Invalid channel
            break;
    }
}
