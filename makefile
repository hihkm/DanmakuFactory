
TempPath := temp

DanmakuFactory: $(TempPath)/main.o $(TempPath)/string.o $(TempPath)/list.o $(TempPath)/config.o $(TempPath)/ass.o $(TempPath)/json.o $(TempPath)/xml.o
	gcc $(TempPath)/main.o $(TempPath)/string.o $(TempPath)/list.o $(TempPath)/config.o $(TempPath)/ass.o $(TempPath)/json.o $(TempPath)/xml.o -o DanmakuFactory

$(TempPath)/string.o: String/DanmakuFactoryString.c
	gcc -c String/DanmakuFactoryString.c -o $(TempPath)/string.o

$(TempPath)/list.o: List/DanmakuFactoryList.c
	gcc -c List/DanmakuFactoryList.c -o $(TempPath)/list.o

$(TempPath)/config.o: Config/Config.c
	gcc -c Config/Config.c -o $(TempPath)/config.o

$(TempPath)/ass.o: AssFile.c
	gcc -c AssFile.c -o $(TempPath)/ass.o

$(TempPath)/xml.o: XmlFile.c
	gcc -c XmlFile.c -o $(TempPath)/xml.o

$(TempPath)/json.o: JsonFile.c
	gcc -c JsonFile.c -o $(TempPath)/json.o

$(TempPath)/main.o: main.c
	gcc -c main.c -o $(TempPath)/main.o