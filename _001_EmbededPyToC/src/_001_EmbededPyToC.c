/*
 ============================================================================
 Name        : _001_EmbededPyToC.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include </usr/include/python2.7/Python.h>

#define MAX_SIZE 8

int my_py(unsigned int input_len, char *input_str, unsigned int *output_len, char *output_str);

int main()
{
	//initialize the parameters
	char input_str[MAX_SIZE] = {'1', '0', '1', '1', '0', '1', '\0'};
	char output_str[MAX_SIZE];
	unsigned int output_len;
	int is_ok;

	printf("\n");
	printf("input string is %s, length is %lu\n\n", input_str, strlen(input_str));

	is_ok = my_py(strlen(input_str), input_str, &output_len, output_str);

	if (is_ok == 1)
	{
		printf("output string is %s, length is %lu\n", output_str, strlen(output_str));
	}

	return is_ok;
}

int my_py(unsigned int input_len, char *input_str, unsigned int *output_len, char *output_str)
{
	char *output_str_after_python;
	PyObject *pName, *pModule, *pDict, *pFunc;
	PyObject *pArgs, *pValue, *result;

	Py_Initialize();
	pName = PyString_FromString("my_python");
	/* Error checking of pName left out */

	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (pModule != NULL)
	{
		pFunc = PyObject_GetAttrString(pModule, "stringTrans");
		/* pFunc is a new reference */

		if (pFunc && PyCallable_Check(pFunc))
		{
			pValue = PyString_FromString(input_str);
			printf("Use python c api PyString_FromString transfer the c string to python object string, pValue is: \n");
			PyObject_Print(pValue, stdout, 0);
			printf("\n\n");

			pArgs = PyTuple_New(1);
			PyTuple_SetItem(pArgs, 0, pValue);

			result = PyObject_CallObject(pFunc, pArgs);
			printf("Use python c api PyObject_CallObject call python function, after python function the result is: \n");
			PyObject_Print(result, stdout, 0);
			printf("\n\n");
			Py_DECREF(pArgs);
			if (result != NULL)
			{
				output_str_after_python = PyString_AsString(result);
				printf("After python function, use python c api PyString_AsString transfer python string to c string, output_str_after_python is: \n%s", output_str_after_python);
				printf("\n\n");
				Py_DECREF(result);

				int output_str_after_python_len = strlen(output_str_after_python);
				int i;
				for(i = 0; i < output_str_after_python_len; i++){
					output_str[i] = output_str_after_python[i];
				}
				output_str[i] = '\0';
				*output_len = i;
			}
			else
			{
				Py_DECREF(pFunc);
				Py_DECREF(pModule);
				PyErr_Print();
				fprintf(stderr, "Call failed\n");
				return 0;
			}
		}
		else
		{
			if (PyErr_Occurred())
				PyErr_Print();
			fprintf(stderr, "Cannot find function");
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	else
	{
		PyErr_Print();
		fprintf(stderr, "Failed to load");
		return 0;
	}
	Py_Finalize();
	return 1;
}
