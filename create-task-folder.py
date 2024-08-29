#!/usr/bin/env python3

"""
Made a script that will create a task folder for me for fun
Python is pretty cool
"""

import os
import re 

root_dir = './'
main_task_dir_name = 'task'
initial_task_dir_num = 0 

dir_name_regex = re.compile(f'^{main_task_dir_name}-\d+$')
task_dirs = [ dir for dir in os.listdir(root_dir) if dir_name_regex.match(dir) ]

def get_dir_ending_num(dir_name: str):
    return int(dir_name.split('-')[1])

def task_dir_compare(dir_name: str):
    dir_num = get_dir_ending_num(dir_name) 

    return dir_num 

task_dirs.sort(key = task_dir_compare)

# Debugging print below
# print(task_dirs)

new_dir_name = None 
if task_dirs:
    task_num = get_dir_ending_num(task_dirs[-1]) + 1
    new_dir_name = f'{main_task_dir_name}-{task_num}'
else:
    new_dir_name = f'{main_task_dir_name}-{initial_task_dir_num}'

os.makedirs(new_dir_name)
