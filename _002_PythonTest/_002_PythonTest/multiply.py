'''
Created on Aug 18, 2017

@author: xin
'''
def multiply(a, b):
    print "Will compute", a, "times", b
    c = 0
    for i in range(0, a):
        c = c + b
    return c

#!/usr/bin/python3
# -*- coding: UTF-8 -*-
def stringTrans(input_array, output_array):
    for index in range(len(input_array)):
        if input_array[index] == '0':
            output_array.append('1')
        elif input_array[index] == '1':
            output_array.append('0')

    output_array.append('/0')
    return output_array


input_array = ['1', '0', '0', '1', '0', '1', '\0']
output_array = []
output_array = stringTrans(input_array, output_array)
print output_array