/* 
 * File:   button.h
 * Author: malterieck, alex
 *
 * Created on June 11, 2023, 3:49 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#define BUTTON_PRESS (PINB & (1<<PINB1))
extern void initializeButton();


#endif	/* BUTTON_H */
