
@ECHO OFF

FOR /f %%i IN ('dir /b *.proto') DO ( 
    IF EXIST %%i (
        ECHO %%i 
rem		ECHO %%~ni
		protoc_meng --cpp_out=./pb_src %%i
    )
)

start python gen_proto_cmd_win.py

PAUSE