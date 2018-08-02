// Gianlouie Molinary gi713278

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fibonacci.h"

int power(int a, unsigned int b)
{
	int i, k = 1;
	
	for(i = 0; i < b; i++)
		k *= a;
	
	return k;
}

HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{
	HugeInteger *r = malloc(sizeof(HugeInteger));
	int i, k, len;
	
	if(p == NULL || q == NULL || r == NULL) // check for NULL pointers
		return NULL;
	

	if(p->length >= q->length) // sets sum length to larger struct
	{
		r->length = p->length + 1;
		i = 1;
	}
		
	if (q->length > p->length) // ditto
	{
		r->length = q->length + 1;
		i = 0;
	}
		
	len = r->length;
	
	r->digits = calloc(len, sizeof(int)); 
	
	if(i == 1) // if first sruct array is larger or equal, these execute
	{
		for(k = 0; k < q->length; k++)
		{
			if(p->digits[k] + q->digits[k] + r->digits[k] <= 9) // checks for carry over
			{
				r->digits[k] += p->digits[k] + q->digits[k];
			}
			else
			{
				r->digits[k] += (p->digits[k] + q->digits[k]) % 10;
				r->digits[k+1] += 1;
			}
			
			if(r->digits[k] % 10 == 0) // fixed something weird where one of the elements
				r->digits[k] = r->digits[k] % 10; // was more than one digit
		}
	
		for(k = q->length; k < p->length; k++) // drops down rest of digits
		{
			r->digits[k] += p->digits[k];
		}
		
		if(r->digits[len-1] == 0) // gets rid of padded zero 
		{
			r->length -= 1;
		}
			
	}
	
	if (i == 0) // if second struct array is larger, these execute
	{
		for(k = 0; k < p->length; k++)
		{
			if(q->digits[k] + p->digits[k] + r->digits[k] <= 9)  // checks for carry over
				r->digits[k] += q->digits[k] + p->digits[k];
			else
			{
				r->digits[k] += (q->digits[k] + p->digits[k]) % 10;
				r->digits[k+1] += 1;
			}
			
			if(r->digits[k] % 10 == 0) // fixed something weird where one of the elements 
				r->digits[k] = r->digits[k] % 10; // was more than one digit
		}
	
		for(k = p->length; k < q->length; k++) // drops down rest of digits
		{
			r->digits[k] += q->digits[k];
		}
		
		if(len > 2 && r->digits[len-1] == 0) // gets rid of padded zero
		{
			r->length -= 1;
		}
	}
	
	return r;
}

HugeInteger *hugeDestroyer(HugeInteger *p)
{
	if(p != NULL && p->digits == NULL) 
		free(p);
	else if(p == NULL)
		return NULL;	
	else
	{
		free(p->digits);
		free(p);
	}

	return NULL;
}

HugeInteger *parseInt(unsigned int n)
{
	HugeInteger *t = malloc(sizeof(HugeInteger));
	int i, digs = 0;
	unsigned int temp = n;
	
	if(t == NULL)
		return NULL;
	
	while(temp != 0) // determines number of digits
	{
		temp /= 10;
		++digs;
	}
	
	if(n == 0) // the case that zero is passed 
		digs = 1;
	
	t->length = digs;
	t->digits = malloc(sizeof(int) * digs);
	
	for(i = 0; i < digs; i++) // each digits place is put in to its own element
	{
		t->digits[i] = n % 10;
		n /= 10;
	}
	
	return t;
}

HugeInteger *parseString(char *str) // idk man
{
	HugeInteger *s = malloc(sizeof(HugeInteger));
	int i, len;
	
	if(str == NULL || s == NULL) // returns NULL if passed string is NULL
		return NULL;
		
	if(strcmp(str, "") == 0)
	{
		s->length = 1;
		s->digits = malloc(sizeof(int));
		s->digits[0] = 0;
		return s;
	}
		
	len = strlen(str);
		
	s->digits = malloc(sizeof(int) * len);
	s->length = len;
	len--;
	
	for(i = 0; i < s->length; i++)
	{
		s->digits[i] = str[len] - '0';
		len--;
	}
	
	return s;
	
}

unsigned int *toUnsignedInt(HugeInteger *p)
{
	unsigned int *thing = malloc(sizeof(unsigned int));
	int i;
	
	if(thing == NULL)
		return NULL;
	
	*thing = 0;
	
	if(p == NULL)
		return NULL;
	
	else if(p->length > 10)
		return NULL;
	
	else if(p->digits[p->length - 1] < 0)
		return NULL;
	
	else if(p->digits[0] == 0 && p->length == 1)
		return thing;
			
	
	for(i = 0; i < p->length; i++)
	{
		*thing += (p->digits[i] * power(10, i));
	}
	
	return thing;
}

HugeInteger *fib(int n)
{
	HugeInteger *y = NULL, *x = NULL, *z = NULL;
	int i;
	unsigned int n1 = 0, n2 = 1;
	
	if(n == 0)
		return z = parseInt(n1);
	if(n == 1)
		return z = parseInt(n2);
	
	y = parseInt(n1);
	x = parseInt(n2);
	
	for(i = 2; i <= n; i++) // magic happens
	{
		z = hugeAdd(y,x);
		y = x;
		x = z;
	}
	
	return z;
}

double difficultyRating(void)
{
	return 5.0;
}

double hoursSpent(void)
{
	return 40;
}

