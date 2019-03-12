TARGET1 = rastreador
TARGET2 = SysCalls

all : compile

compile :

	gcc $(TARGET1).c $(TARGET2).c -o $(TARGET1)

execute_ls:
	./$(TARGET1) -v ls -a

clean :
	rm $(TARGET1)
