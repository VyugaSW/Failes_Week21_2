
#include <Windows.h>
#include <iostream>

using namespace std;
//Задание 1. Дан текстовый файл. Удалить из него последнюю строку. Результат записать в другой файл.
void Task1() {
    FILE* out;
    FILE* in;
    const char* pathOut = "C:\\Test\\test.txt";
    const char* pathIn = "C:\\Test\\test2.txt";
    char* tempStr = new char[125];
    int numbsStr = 0; //Счётчик
    //Считаем кол-во строк в исходном файле
    if (!fopen_s(&out, pathOut, "r")) {
        while (!feof(out)) {
            fgets(tempStr, 125, out);
            numbsStr++;
        }
        fclose(out);
    }

    if (!fopen_s(&out, pathOut, "r")) {
        if (!fopen_s(&in, pathIn, "w")) {
            int a = 0; //Временная пременная для подсчёта
            while (!feof(out) && a < numbsStr-1) { //Копируем определенное кол-во строк (до последней)
                tempStr = fgets(tempStr, 126, out);
                fputs(tempStr, in);
                a++;
            }
            fclose(in);
        }
        fclose(out);
        cout << "Successful copy without last line\n";
    }
    else
        cout << "WRONG! File wasn't opened!\n";
    delete[] tempStr;
}

//Задание 2. Дан текстовый файл. Найти длину самой
//длинной строки.
void Task2() {
    FILE* out;
    const char* path= "C:\\Test\\test.txt";
    int counter = 0; //Счётчик символов в одной строке
    int sizeNum = 0; //Счётчик строк
    char s = NULL; //Буфер для подсчёта

    //Считаем кол-во строк в файле
    if (!fopen_s(&out, path, "r")) {
        char* temp = new char[125]; //Временный буфер для подсчета строк
        while (!feof(out)) {
            fgets(temp, 126, out);
            sizeNum++;
        }
        delete[] temp;
        fclose(out);
    }

    int* arrLong = new int[sizeNum]; //Создания массива для структурирования количества символов построчно ( в каждой строке)
    if (!fopen_s(&out, path, "r")) {
        int a = 0; //Переменная для инициализации временной матрицы
        while (!feof(out)) {
            s = fgetc(out);
            if (s == '\n') {
                arrLong[a] = counter;
                counter = 0;
                a++;
            }
            counter++;
        }
        fclose(out);
    }

    int max;
    //Выявление длинейшего
    max = arrLong[0];
    for (int i = 0; i < sizeNum; i++) {
        if (max < arrLong[i])
            max = arrLong[i];
    }
    cout << "The longest string in file contains " << max << " symbols";
    delete[] arrLong;
}

//Задание 3. Дан текстовый файл. Посчитать сколько раз
//в нем встречается заданное пользователем слово.
void Task3() {
    FILE* out;
    const char* path = "C:\\Test\\test.txt";
    const char* userWord =  "you" ;
    char* tempStr = new char[125]; //Буфер
    char* tempStrSec = new char[125]; //Строка для обработки
    int counter = 0; //Счетчик
    if (!fopen_s(&out, path, "r")) {
        while (!feof(out)) {
            tempStrSec = fgets(tempStr, 126, out);
            while (tempStrSec = strstr(tempStrSec, userWord)) {
                tempStrSec = tempStrSec+1;
                counter++;
            }
        }
        fclose(out);
    }
    cout << "Times - " << counter << endl;
    delete[] tempStr;
    delete[] tempStrSec;
}

//Задание 4. Дан текстовый файл. Найти и заменить в нем
//заданное слово.Что искать и на что заменять определяется пользователем.

char* Task4_ReplacementWord(char* string, char* userChange, char* userSearch) {
    char* newString = new char[strlen(string) + strlen(userChange) + strlen(userSearch)]{ NULL };
    char* temp;
    temp = strstr(string, userSearch);
    strncpy_s(newString, strlen(string) + strlen(userChange) + strlen(userSearch), string, strlen(string) - strlen(temp));
    strcat_s(newString, strlen(string) + strlen(userChange) + strlen(userSearch), userChange);
    strcat_s(newString, strlen(string) + strlen(userChange) + strlen(userSearch), temp + strlen(userSearch));
    if (newString != NULL)
        return newString;
    else
        return 0;
}
void Task4() {
    FILE* out;
    const char* path = "C:\\Test\\test.txt";
    char* userSearch = new char[125]{ "you" };
    char* userChange = new char[125]{ "pirate" };
    char* tempStr = new char[125]; 
    char* newString = new char[125];
    if (!fopen_s(&out, path, "r+b")) {
        while (!feof(out)) {
            fgets(tempStr, 126, out);
            newString = Task4_ReplacementWord(tempStr, userChange, userSearch);
            if (newString)
                fputs(newString, out); // не могу записать в файл новую отрдактированную строку
            else                       // но по отладчику всё прекрасно, проверьте, коль не веруете 
                continue;
        }
        fclose(out);
    }
}
int main()
{
    //Task1();
    //Task2();
    //Task3();
    Task4();
}

