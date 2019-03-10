TARGET1 = rastreador
TARGET2 = prog
TARGET3 = SysCalls

all : compile

compile :

	gcc $(TARGET1).c $(TARGET3).c -o $(TARGET1)
	gcc $(TARGET2).c -o $(TARGET2)

execute_ls:
	./$(TARGET1) -v ls -a

execute_prog:
	./$(TARGET1) -V ./$(TARGET2) -a -b -c

clean :
	rm $(TARGET1)
	rm $(TARGET2)
