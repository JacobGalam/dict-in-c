#include <string.h>
#include <stdio.h>

#include "array.h"
#include "dict.h"

#define NUM_ARGC 2
#define NO_ENOUGH_NUM_ARGC 1
#define CANT_READ_DICT 1

#define LINE_BUFFER 256
#define WORD_BUFFER 256

Dict* read_dict(char* path);
void reaplce_words(Dict* dict, char* path);

int not_main(int argc, char* argv[])
{
	int have_src_dest = argc < NUM_ARGC;
	if (0 == have_src_dest)
	{
		printf("Please enter source and destination file paths");
		return NO_ENOUGH_NUM_ARGC;
	}

	char* dest_path = argv[1];
	char* dict_path = argv[2];

	Dict* dict = read_dict(dict_path);

	if (NULL == dict)
	{
		printf("Can't read the dict file");
		return CANT_READ_DICT;
	}

	reaplce_words(dict, dest_path);
	// loop over all the words in the dest file

	// set all the words

	dict_free(dict);

	return 0;
}

int reaplce_words(Dict* dict, char* path)
{
	FILE* fp;
	if (NULL != fopen_s(&fp, path, "r"))
	{
		return NULL;
	}

	fseek(fp, 0, SEEK_END); // seek to end of file
	unsigned long long size = ftell(fp); // get current file pointer
	fseek(fp, 0, SEEK_SET); // seek back to beginning of file
	// proceed with allocating memory and reading the file

	char* word_buff = malloc(sizeof(char) * size);
	if (NULL == word_buff)
	{
		return -1;
	}

	fread(word_buff, sizeof(char), size, fp);

	fclose(fp);

	// get word - 2
	// check if have - 1
	// random get it from the list - 3
	//
	// change the word and add padding/remove padding
	// if have too much -
	// if have too little -

	if (NULL != fopen_s(&fp, path, "w"))
	{
		free(word_buff);
		return NULL;
	}

	unsigned long long space_index = 0;
	char word_buffer[WORD_BUFFER] = { 0 };
	while (space_index < size)
	{
		if (word_buff[space_index] != ' ')
		{
		}
		else
		{
			// search if word in the dict
			// wire the word
		}
		space_index++;
	}

	for (unsigned long long i = 0; i < size; ++i) {
		//Some calculations to fill a[]
		fwrite(word_buff, sizeof(char), size * sizeof(char), fp);
	}

	fclose(fp);

	free(word_buff);

	return 0;
}

// mine
//int hash_str(char* str, int size)
//{
//	int result = 0;
//	for (int size_of_key_word = 0; size_of_key_word < size; size_of_key_word++)
//	{
//		result += str[size_of_key_word] + str[size_of_key_word] * size_of_key_word;
//	}
//	return result;
//}

inline unsigned long hash_str(unsigned char* str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return hash;
}

unsigned long hash_str_void(void* str)
{
	return hash_str((unsigned char*)str);
}

int strcmp_void(void* str1, void* str2)
{
	return strcmp((char*)str1, (char*)str2);
}

void str_destory_void(void* str)
{
	free((char*)str);
}

void list_destroy_void(void* array)
{
	return list_destroy((List*)array, str_destory_void);
}

List* read_values(char* buffer, int start_index)
{
	List* list = list_init();
	if (NULL == list)
	{
		return NULL;
	}

	int line_index = 0;
	int word_index = 0;
	while (1)
	{
		char c = buffer[line_index + start_index];
		if (0 == c || '\n' == c)
		{
			return list;
		}
		else if (',' == c)
		{
			char* value = (char*)malloc(sizeof(char) * word_index + 1);
			if (NULL == value)
			{
				free(list);
				return NULL;
			}
			memcpy(value, &buffer[line_index], word_index);
			value[word_index] = 0;

			list_add(list, value);
			word_index = 0;
		}
		else
		{
			word_index++;
		}
		line_index++;
	}
}

int size_of_key(char* buffer)
{
	int buffer_index = -1;
	while (1)
	{
		buffer_index++;
		if (buffer[buffer_index] == ':')
		{
			return buffer_index;
		}
	}
}

// return key, value
DictPair* read_line(FILE* file)
{
	char line[LINE_BUFFER] = { 0 };

	if (fgets(line, sizeof(line), file))
	{
		int buffer_index = size_of_key(line);

		if (0 == buffer_index)
		{
			return NULL;
		}

		char key_value[256];

		char* key = (char*)malloc(sizeof(char) * buffer_index + 1); // 1 for null
		if (NULL == key)
		{
			return NULL;
		}

		memcpy(key, line, buffer_index);
		key[buffer_index] = 0;

		List* values = read_values(line, buffer_index);
		if (NULL == values)
		{
			free(key);
			return NULL;
		}

		return _init_pair(key, values);
	}
	else
	{
		return NULL;
	}
}

Dict* read_dict(char* path)
{
	DictFunctions dictFunc;
	dictFunc.hash_func = hash_str_void;
	dictFunc.comp_func = strcmp_void;
	dictFunc.destory_value = list_destroy_void;
	dictFunc.destory_key = str_destory_void;
	Dict* dict = init_dict(dictFunc);

	if (NULL == dict)
	{
		return NULL;
	}

	FILE* fp;
	if (NULL != fopen_s(&fp, path, "r"))
	{
		return NULL;
	}

	DictPair* new_pair;
	while (new_pair = read_line(fp))
	{
		dict_insert_pair(dict, new_pair);
	}

	fclose(fp);

	return dict;
}