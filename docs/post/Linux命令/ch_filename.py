# coding=utf-8
'''
批量修改文件名
'''

import os

dir = "/root/na/庆余年" 

for file in os.listdir(dir):
#	print(file)
	str = file.find("E")
	if str == -1:
		continue;
	new_name = dir + "/" + file[str+1:str+3] + ".mp4"
    old_name = dir + "/" + file
#	print(new_name)
#   print(old_name)

    os.rename(old_name, new_name)

