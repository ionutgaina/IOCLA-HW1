#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "structs.h"

#define MAX_str 256

char *read_word()
{
	char *word = malloc(MAX_str);
	if (word == NULL)
		exit(1);

	scanf("%s", word);

	char *new_word = realloc(word, strlen(word) + 1);
	if (new_word == NULL)
	{
		free(word);
		exit(1);
	}
	return new_word;
}

data_structure *create_data()
{
	data_structure *data = (data_structure *)malloc(sizeof(data_structure));
	if (data == NULL)
		return NULL;

	data->header = (head *)malloc(sizeof(head));
	if (data->header == NULL)
	{
		free(data);
		return NULL;
	}

	data->header->len = 0;
	scanf("%s", &(data)->header->type);

	int8_t banknote8;
	int16_t banknote16;
	int32_t banknote32;
	char *aux, *name;

	// first name
	name = read_word();
	data->header->len += strlen(name) + 1;

	aux = (char *)malloc(data->header->len);
	if (aux == NULL)
	{
		free(data->header);
		free(data);
		return NULL;
	}
	memcpy(aux, name, strlen(name) + 1);

	if (data->header->type == '1')
	{
		// first banknote
		scanf("%hhu", &banknote8);
		data->header->len += sizeof(banknote8);
		aux = (char *)realloc(aux, data->header->len);
		if (aux == NULL)
		{
			free(data->header);
			free(data);
			return NULL;
		}
		memcpy(aux + data->header->len - sizeof(banknote8), &banknote8, sizeof(banknote8));

		// second banknote
		scanf("%hhu", &banknote8);
		data->header->len += sizeof(banknote8);
		aux = (char *)realloc(aux, data->header->len);
		if (aux == NULL)
		{
			free(data->header);
			free(data);
			return NULL;
		}
		memcpy(aux + data->header->len - sizeof(banknote8), &banknote8, sizeof(banknote8));
	}

	if (data->header->type == '2')
	{
		// first banknote
		scanf("%hu", &banknote16);
		data->header->len += sizeof(banknote16);
		aux = (char *)realloc(aux, data->header->len);
		if (aux == NULL)
		{
			free(data->header);
			free(data);
			return NULL;
		}
		memcpy(aux + data->header->len - sizeof(banknote16), &banknote16, sizeof(banknote16));

		// second banknote
		scanf("%u", &banknote32);
		data->header->len += sizeof(banknote32);
		aux = (char *)realloc(aux, data->header->len);
		if (aux == NULL)
		{
			free(data->header);
			free(data);
			return NULL;
		}
		memcpy(aux + data->header->len - sizeof(banknote32), &banknote32, sizeof(banknote32));
	}

	if (data->header->type == '3')
	{
		// first banknote
		scanf("%u", &banknote32);
		data->header->len += sizeof(banknote32);
		aux = (char *)realloc(aux, data->header->len);
		if (aux == NULL)
		{
			free(data->header);
			free(data);
			return NULL;
		}
		memcpy(aux + data->header->len - sizeof(banknote32), &banknote32, sizeof(banknote32));

		// second banknote
		scanf("%u", &banknote32);
		data->header->len += sizeof(banknote32);
		aux = (char *)realloc(aux, data->header->len);
		if (aux == NULL)
		{
			free(data->header);
			free(data);
			return NULL;
		}
		memcpy(aux + data->header->len - sizeof(banknote32), &banknote32, sizeof(banknote32));
	}
	if (data->header->type != '1' && data->header->type != '2' && data->header->type != '3')
	{
		free(aux);
		free(data->header);
		free(data);
		return NULL;
	}

	// second name
	name = read_word();
	data->header->len += strlen(name) + 1;
	aux = (char *)realloc(aux, data->header->len);
	if (aux == NULL)
	{
		free(data->header);
		free(data);
		return NULL;
	}
	memcpy(aux + data->header->len - strlen(name) - 1, name, strlen(name) + 1);
	// for (int i = 0; i < data->header->len; i++)
	// 	printf("result = 0x%c\n", *(aux + i));
	// copy to data
	data->data = realloc(aux, data->header->len);
	if (data->data == NULL)
	{
		free(data->header);
		free(data);
		free(aux);
		return NULL;
	}

	return data;
}

int add_last(void **arr, int *len, data_structure *data)
{
	if (data == NULL)
		return 1;

	char *aux = (char *)malloc(sizeof(data->header) + data->header->len);
	if (aux == NULL)
		return 1;

	int aux_len = 0;
	// add header (type & len)
	memcpy(aux, data->header, sizeof(*data->header));
	aux_len += sizeof(data->header);

	// add data
	memcpy(aux + aux_len, data->data, data->header->len);
	aux_len += data->header->len;

	// for (int i = 0; i < aux_len; i++)
	// printf("result1 = 0x%hx\n", *(aux + i));

	// alloc the big array
	if (*(arr) != NULL)
	{
		*(arr) = (void *)realloc(&(*arr), aux_len + *(len));
		if (*arr == NULL)
			return 1;
	}

	if (*(arr) == NULL)
	{
		*(arr) = (void *)malloc(aux_len);
		if (*(arr) == NULL)
			return 1;
	}

	// add to the big array
	memcpy(*(arr) + *(len), aux, aux_len);
	*(len) += aux_len;

	// printf("add last\n");
	// for (int i = 0; i < *(len); i++)
	// 	printf("result2 = 0x%hx\n", *((char *)*(arr) + i));

	return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{
	printf("add_at");
	return 0;
}

void find(void *data_block, int len, int index)
{
	printf("find");
	return;
}

int delete_at(void **arr, int *len, int index)
{
	printf("delete");
	return 0;
}

void print(void *arr, int len)
{
	data_structure *data = (data_structure *)malloc(sizeof(data_structure));
	if (data == NULL)
		return;

	data->header = (head *)malloc(sizeof(head));
	if (data->header == NULL)
	{
		free(data);
		return;
	}
	data->data = (void *)malloc(sizeof(void));
	int len_aux = 0;

	// while (len_aux != len)
	// {
	memcpy(data->header, arr + len_aux, sizeof(*data->header));
	len_aux += sizeof(data->header);

	data->data = realloc(data->data, data->header->len);
	if (data->data == NULL)
	{
		free(data->header);
		free(data);
		return;
	}
	memcpy(data->data, arr + len_aux, data->header->len);
	len_aux += data->header->len;
	// }

	for (int i = 0; i < data->header->len; i++)
		printf("result = 0x%d\n", *((char *)data->data + i));

	printf("Tipul %c\n", data->header->type);

	char *p = (char *)arr + sizeof(data->header);

	while (*p != '\0')
	{
		printf("%c", *p);
		p++;
	}

	void *first_banknote, *second_banknote;
	if (data->header->type == '1')
	{

		// printf("%"PRId8"\n", val);   //unde val este un int8_t
		// printf("%"PRId8"\n", val);   //unde val este un int8_t
	}

	if (data->header->type == '2')
	{
		// printf("%"PRId16"\n", val);  //unde val este un int16_t
		// printf("%"PRId32"\n", val); //unde val este un int32_t
	}

	if (data->header->type == '3')
	{
		// printf("%"PRId32"\n", val); //unde val este un int32_t
		// printf("%"PRId32"\n", val); //unde val este un int32_t
	}

	return;
}

int main()
{
	// the vector of bytes u have to work with
	// good luck :)
	void *arr = NULL;
	int len = 0;

	data_structure *data;

	char *cmd = read_word();
	int index;

	while (strcmp(cmd, "exit"))
	{
		if (strcmp(cmd, "insert") == 0)
		{
			data = create_data();
			add_last(&arr, &len, data);
		}

		if (strcmp(cmd, "insert_at") == 0)
		{
			scanf("%d", &index);
			add_at(&arr, &len, data, index);
		}

		if (strcmp(cmd, "find") == 0)
		{
			scanf("%d", &index);
			find(data, len, index);
		}

		if (strcmp(cmd, "delete_at") == 0)
		{
			scanf("%d", &index);
			delete_at(&arr, &len, index);
		}

		if (strcmp(cmd, "print") == 0)
		{
			// TO DO lenght
			print(arr, len);
		}
		cmd = read_word();
	}

	if (arr != NULL)
		free(arr);

	if (cmd != NULL)
		free(cmd);

	if (data != NULL)
	{
		if (data->header != NULL)
			free(data->header);

		if (data->data != NULL)
			free(data->data);

		free(data);
	}

	return 0;
}
