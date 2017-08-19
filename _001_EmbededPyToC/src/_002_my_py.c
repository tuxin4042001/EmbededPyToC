#include <stdio.h>
#include <string.h>

#define MAX_SIZE 8

int my_py(unsigned int input_len, char *input_str,
		  unsigned int *output_len, char *output_str);

int main(void)
{
	char input_str[MAX_SIZE] = {'1', '0', '1', '1', '0', '1', '\0'};
	
	char output_str[MAX_SIZE];
	unsigned int output_len;
	
	
	int is_ok;

	printf("input string is %s, length is %lu\n", input_str, strlen(input_str));
	is_ok = my_py(strlen(input_str), input_str,
				  &output_len, output_str);

	if(is_ok == 1)
	{
		printf("output string is %s, length is %lu\n", output_str, strlen(output_str));
	}
	
	return is_ok;
}


// this is c implementation of my_py, you need to implement this in python
int my_py(unsigned int input_len, char *input_str,
		  unsigned int *output_len, char *output_str)
{
	int i;

	for(i = 0; i< input_len-1; i++)
	{
		if(input_str[i] == '1')
		{
			output_str[i] = '0';
		}
		else if(input_str[i] == '0')
		{
			output_str[i] = '1';
		}
	}

	output_str[i] = '\0';
	*output_len = i;
	
	return 1;
}