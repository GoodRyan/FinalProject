/*
 * gps.h
 *
 *  Created on: May 4, 2014
 *      Author: C15Ryan.Good
 */

#ifndef GPS_H_
#define GPS_H_

#include <xuartlite_l.h>
#include <xparameters.h>

void delay(unsigned char ammount);

void receive_data(unsigned char count, int size, unsigned char *data[]);

void storage(int size, unsigned char *data[]);


#endif /* GPS_H_ */
