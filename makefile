TARGET1 = rastreador
TARGET2 = prog

all : compile

compile :

	gcc $(TARGET1).c -o $(TARGET1)
	gcc $(TARGET2).c -o $(TARGET2)

execute_ls:
	./$(TARGET1) ls -ll

execute_prog:
	./$(TARGET1) ./$(TARGET2) -a -b -c

clean :
	rm $(TARGET1)
	rm $(TARGET2)
