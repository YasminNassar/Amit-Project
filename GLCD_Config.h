/*
 * GLCD_Config.h
 *
 *  Created on: Nov 23, 2023
 *      Author: Yasmin
 */

#ifndef GLCD_CONFIG_H_
#define GLCD_CONFIG_H_

/*Control Port Options:
 * 1- DIO_PORTA
 * 2- DIO_PORTB
 * 3- DIO_PORTC
 * 4- DIO_PORTD
 */
#define GLCD_CONTROL_PORT   DIO_PORTC

/*RW, RS, E Pin Options:
 * PIN1:PIN7
 */
#define GLCD_RS_PIN   PIN0
#define GLCD_RW_PIN   PIN1
#define GLCD_E_PIN    PIN2

/*Data Port Options:
 * 1- DIO_PORTA
 * 2- DIO_PORTB
 * 3- DIO_PORTC
 * 4- DIO_PORTD
 */
#define GLCD_DATA_PORT   DIO_PORTB

/*Page Options:
 * 0:7
 */

/*Column Options:
 * 0:127
 */

#endif /* GLCD_CONFIG_H_ */
