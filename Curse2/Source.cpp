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
 * ������� ������������ ����������� ������������������ "\n" (������� �� �����
 * ������) � "\b" (�������� ��������������� �������) � ������ @echo_data �
 * ���������� ��������� � ���� @file_name. ��������� @echo_data �����
 * ������������� � ������� strchr() � memmove(), ������ � ���� - � �������
 * fopen() � fwrite().
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
