//#include <stdio.h>
//#include <stdlib.h> // For exit()
//#include <string.h>
//
//#define BUFF_SIZE 1024
//#define NAME_TYPE_SIZE 10
//#define VALUE_SIZE 20
//
//#define NOT_ENOUGH_MEMORY 1
//#define CANT_OPEN_FILE 2
//#define FILE_ENDED 3
//#define TOO_BIG_STR 4
//#define CANT_FORMAT_VALUE 5
//#define NOT_FOUND_LINE 6
//
//#define SEARCH_NAME "A"
//
//#pragma warning(disable : 4996) // for vs
//
//struct variable {
//	char type[NAME_TYPE_SIZE];
//	char name[NAME_TYPE_SIZE];
//	int value;
//};
//
//int find_var_in_file(char* file_path, char* find_name, struct variable* dest);
//
//int main()
//{
//	struct variable* object2 = malloc(sizeof(struct variable));
//
//	if (NULL == object2)
//	{
//		printf("not enough memory");
//		return NOT_ENOUGH_MEMORY;
//	}
//
//	int error = find_var_in_file("input.txt", SEARCH_NAME, object2);
//
//	if (CANT_OPEN_FILE == error)
//	{
//		return printf("can't open file");
//	}
//
//	if (error == 0)
//	{
//		// Printing data to check validity
//		printf("read: type: %s name: %s value: %d", object2->type, object2->name, object2->value);
//		int a = object2->value;
//		// do stuff with a
//	}
//	else
//	{
//		if (error == NOT_FOUND_LINE)
//		{
//			printf("not find the var \"" SEARCH_NAME "\" in the file");
//		}
//		else
//		{
//			printf("error reading the file. error code: %d", error);
//		}
//	}
//
//	free(object2);
//
//	return 0;
//}
//
//int read_line(char* buffer, int buffer_size, char* dest, int dest_size, FILE* stream)
//{
//	if (!fgets(buffer, buffer_size, stream))
//	{
//		return NOT_FOUND_LINE;
//	}
//
//	int read_len = strlen(buffer);
//
//	if ('\n' == buffer[read_len - 1])
//	{
//		if (read_len == 1)
//		{
//			return NOT_FOUND_LINE;
//		}
//		buffer[read_len - 1] = '\0'; // remove "\n" in the end
//	}
//
//	if (dest_size <= strlen(buffer)) // last chat is null
//	{
//		return TOO_BIG_STR;
//	}
//
//	strcpy(dest, buffer);
//
//	// clear the read
//	memset(buffer, '\0', read_len);
//
//	return 0;
//}
//
//int find_var_in_file(char* file_path, char* find_name, struct variable* dest)
//{
//	char file_buffer[BUFF_SIZE] = { 0 }; // Buffer to store data
//	FILE* stream = fopen(file_path, "r");
//	if (NULL == stream)
//	{
//		return CANT_OPEN_FILE;
//	}
//
//	int error = 0;
//	while (1)
//	{
//		// read type
//		int read_type_result = read_line(file_buffer, BUFF_SIZE, dest->type, NAME_TYPE_SIZE, stream);
//		if (read_type_result != 0)
//		{
//			error = read_type_result;
//			break;
//		}
//
//		int read_name_result = read_line(file_buffer, BUFF_SIZE, dest->name, NAME_TYPE_SIZE, stream);
//
//		if (read_name_result != 0)
//		{
//			error = read_name_result;
//			break;
//		}
//
//		char value_buffer[VALUE_SIZE] = { 0 };
//		int read_value_result = read_line(file_buffer, BUFF_SIZE, value_buffer, VALUE_SIZE, stream);
//		if (read_value_result != 0)
//		{
//			error = read_value_result;
//			break;
//		}
//
//		if (0 == strcmp(find_name, dest->name))
//		{
//			if (1 != sscanf(value_buffer, "%d", &dest->value))
//			{
//				error = CANT_FORMAT_VALUE;
//			}
//			break;
//		}
//	}
//
//	fclose(stream);
//
//	return error;
//}