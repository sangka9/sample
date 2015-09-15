#include"problem51.h"
#include<iostream>
	
int Problem::checkSum()
{
	num1 = num>>24;
	num2 = num<<8;
	num2 = num2>>24;
	num3 = num<<16;
	num3 = num3>>24;
	num4 = num<<24;
	num4 = num4>>24;

	sum=num1+num2+num3;

	while(1){
		if(sum>256)
			sum-=256;
		else
			break;
	}
		
	sum = 255-sum;

	if(sum==num4)
		return 1;
	else
		return 0;
}