/*
 * gps.c
 *
 *  Created on: May 4, 2014
 *      Author: C15Ryan.Good
 */
#include "gps.h"

void delay(int ammount){
	int timer = 0;
	while (timer < ammount){
	timer++;
	}
}

unsigned char rotate_right(unsigned char x, int n) {
    unsigned char temp = x << (8 - n);
    x = x >> n;
    return (x | temp);
}
