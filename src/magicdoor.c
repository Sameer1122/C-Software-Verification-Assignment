/*
 ============================================================================
 Name        : magicdoor.c
 Author      : Sharwan
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

pthread_t thread_id;
pthread_mutex_t O1;
int  magicCode= 0;
int doorNumber;
void lock() {
	pthread_mutex_lock(&O1);
}

void unlock() {
	pthread_mutex_unlock(&O1);
}

void* verifyMagicCode() {
	lock();
	/*=========================================*/
	//input sanitization --> if inputs are negative make it positive
	//compute square of magicCode
	magicCode *= magicCode;
	//compute square root of magicCode
	magicCode = sqrt(magicCode);

	/*=========================================*/
	switch (magicCode) {
	case 12234:
		doorNumber = 1;
		unlock();
		break;
	case 12335:
		doorNumber = 2;
		unlock();
		break;
	case 11232:
		doorNumber = 3;
		unlock();
		break;
	case 14235:
		doorNumber = 4;
		unlock();
		break;
	case 19231:
		doorNumber = 5;
		unlock();
		break;
	case 18236:
		doorNumber = 6;
		unlock();
		break;
	case 19930:
		doorNumber = 7;
		unlock();
		break;
	case 17833:
		doorNumber = 8;
		unlock();
		break;
	case 13444:
		doorNumber = 9;
		// unlock() is missing here  That is why this magic door is not working
		break;
	case 22234:  /* This is called the buffer overflow the value of this case is higher than the
	 int value which cause buffer overflow that is why this case is not working */
		doorNumber = 10;
		unlock();
		break;
	default:
		if (magicCode) {
			printf("Wrong Magic Code\n");
			exit(0);
		}

	}
	if (!magicCode) {
		unlock();
	}
	return NULL;
}

int main(void) {
	int error;
	printf("Enter Magic code: ");
	scanf("%d", &magicCode);
	if (magicCode == 0) {
		printf("please enter a non-zero integer number as a magic code\n");
		return -1;
	}
	printf("\n");
	if (pthread_mutex_init(&O1, NULL) != 0) {
		printf("\n mutex init has failed\n");
		return 1;
	}
	error = pthread_create(&thread_id, NULL, &verifyMagicCode, NULL);
	if (error != 0)
		printf("\nThread can't be created :[%s]", strerror(error));
	pthread_join(thread_id, NULL);
	lock();
	if(doorNumber){
		printf("Magic door %d opened successfully\n",doorNumber);
	} else{
		printf("All magic doors are opened successfully\n");
	}
	unlock();
	pthread_mutex_destroy(&O1);
	return 0;
}

