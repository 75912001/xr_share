#!/usr/bin/python
# -*- coding:utf-8 -*-

import sys
reload(sys)
sys.setdefaultencoding('utf-8')



#import os
#proto_src = os.environ.get('SERVER_PROTO')

#生成cpp文件的路径
gen_cpp_path=r"./pb_src/";


def parse_line(cmd_file, fun_name, type):
	cmd_file.write(r"BIND_PROTO_CMD(" + type + r",on_" + fun_name + r"," + fun_name + ");");
	cmd_file.write("\n");
	
def parse_line_no_call_back(cmd_file, fun_name, type):
	cmd_file.write(r"BIND_PROTO_CMD_NO_CB(" + type + r",on_" + fun_name + r"," + fun_name + ");");
	cmd_file.write("\n");




def gen_proto(src_file, gen_file):
	file = open(src_file);
	cmd_file = open(gen_file, "w");
	while 1:
		line = file.readline();
		if not line:
			break
		else:
			#查找字符串message
			str_message = "message";
			message_pos = line.find(str_message);
			if 0 != message_pos:
				continue;
			else:
				str_annotation = "//1,";
				annotation_pos = line.find(str_annotation);
				if -1 == annotation_pos:
					str_annotation = "//0,";
					annotation_pos = line.find(str_annotation);
					if -1 == annotation_pos:
						continue;
					else:
						rm = "\r\n\t ";
						fun_name = line[len(str_message)+1:annotation_pos];
						fun_name.strip(rm);
						cmd_str = line[annotation_pos+len(str_annotation):];
						cmd_str.strip(rm);
						sharp_pos = cmd_str.find("#");
						#cmd_type = cmd_str[:-1];
						cmd_type = cmd_str[:sharp_pos];
						cmd_type.strip(rm);
						parse_line_no_call_back(cmd_file, fun_name, cmd_type);
					continue;
				else:
					rm = "\r\n\t ";
					fun_name = line[len(str_message)+1:annotation_pos];
					fun_name.strip(rm);
					cmd_str = line[annotation_pos+len(str_annotation):];
					cmd_str.strip(rm);
					sharp_pos = cmd_str.find("#");
					#cmd_type = cmd_str[:-1];
					cmd_type = cmd_str[:sharp_pos];
					cmd_type.strip(rm);
					parse_line(cmd_file, fun_name, cmd_type);

#################################################################
def main():
	#生成代码的XML文件名
	gen_proto(r"./common_msg.proto", gen_cpp_path+r"common_cmd.h");
	gen_proto(r"./share_msg.proto", gen_cpp_path+r"share_cmd.h");
#	gen_proto(r"./gateway_msg.proto", gen_cpp_path+r"gateway_cmd.h");
#	gen_proto(r"./lobby_gateway.proto", gen_cpp_path+r"lobby_gateway_cmd.h");
	gen_proto(r"./db.proto", gen_cpp_path+r"db_cmd.h");
#	gen_proto(r"./statisitcs.proto", gen_cpp_path+r"statisitcs_cmd.h");
#	gen_proto(r"./loginserv.proto", gen_cpp_path+r"loginserv_cmd.h");
if __name__ == "__main__":
	main();
