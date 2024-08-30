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
inner_task_dir_main_file_name = 'main.cpp'
inner_task_dir_main_file_name_content = """#include<iostream>

int main() {

    return 0;
}
"""


dir_name_regex = re.compile(f'^{main_task_dir_name}-\d+$')

def get_dir_ending_num(dir_name: str):
    return int(dir_name.split('-')[1])

def task_dir_compare(dir_name: str):
    dir_num = get_dir_ending_num(dir_name) 

    return dir_num 

def get_task_dirs():
    task_dirs = [ dir for dir in os.listdir(root_dir) if dir_name_regex.match(dir) ]
    task_dirs.sort(key = task_dir_compare)
    return task_dirs

def get_new_dir_name():
    task_dirs = get_task_dirs()

    # Debugging print below
    # print(task_dirs)

    if task_dirs:
        task_num = get_dir_ending_num(task_dirs[-1]) + 1
        return f'{main_task_dir_name}-{task_num}'
    
    return f'{main_task_dir_name}-{initial_task_dir_num}'

def main():
    new_dir_name = get_new_dir_name() 

    os.makedirs(new_dir_name)
    
    with open(f'./{new_dir_name}/{inner_task_dir_main_file_name}', 'w') as file:
        file.write(inner_task_dir_main_file_name_content)

if __name__ == '__main__':
    main()
