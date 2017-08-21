'''
Created on Aug 18, 2017

@author: xin
'''
#!/usr/bin/python2.7
# -*- coding: UTF-8 -*-

def stringTrans(input_str):
    output_str = ""

    for index in range(len(input_str)):
        if input_str[index] == '0':
            output_str += '1'
        elif input_str[index] == '1':
            output_str += '0'

    return output_str