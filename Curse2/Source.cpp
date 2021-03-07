#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
//#include <unistd.h>
//#include <dirent.h>
#include <errno.h>
#include <assert.h>
#include <stdbool.h>

#define BUF_SIZE 128

/*
 * Функция обрабатывает специальные последовательности "\n" (переход на новую
 * строку) и "\b" (удаление предшествующего символа) в строке @echo_data и
 * записывает результат в файл @file_name. Обработка @echo_data может
 * производиться с помощью strchr() и memmove(), запись в файл - с помощью
 * fopen() и fwrite().
 */
static int run_echo(const char* file_name, const char* echo_data)
{

    file_name = strtok(echo_data, "\n");
    printf("%s", file_name);

	return 0;
}





int main(int argc, char* argv[])
{
    char* name;
    char* data = "Goooooooooooooooovno\n123123";

    name = "Govno";
    run_echo(name, data);
}
