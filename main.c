#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "structs.h"

#define MAX_str 256

void print(void *arr, int len);
int add_last(void **arr, int *len, data_structure *data);
int delete_at(void **arr, int *len, int index);
int add_at(void **arr, int *len, data_structure *data, int index);

int length_arr(void *arr, int len)
{
	int bytes = 0;
	data_structure *data ;
	for ( int i = 0 ; i < len ; i++)
	{
		data = (data_structure *)malloc(sizeof(data_structure));

		data->header = (head *)malloc(sizeof(head));

		data->data = (void *)malloc(sizeof(void));
		memcpy(data->header, arr + bytes, sizeof(head));
		bytes += sizeof(head);

		data->data = realloc(data->data, data->header->len);

		memcpy(data->data, arr + bytes, data->header->len);
		bytes += data->header->len;
		free(data->header);
		free(data->data);
		free(data);
	}
	return bytes;
}

char *read_word()
{
	char *word = malloc(MAX_str);

	scanf("%s", word);

	char *new_word = NULL;
	new_word = realloc(word, MAX_str);

	return new_word;
}

data_structure *create_data()
{
	data_structure *data = (data_structure *)malloc(sizeof(data_structure));

	data->header = (head *)malloc(sizeof(head));
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

	memcpy(aux, name, strlen(name) + 1);

	if (data->header->type == '1')
	{
		// first banknote
		scanf("%hhu", &banknote8);
		data->header->len += sizeof(banknote8);
		aux = (char *)realloc(aux, data->header->len);

		memcpy(aux + data->header->len - sizeof(banknote8), &banknote8, sizeof(banknote8));

		// second banknote
		scanf("%hhu", &banknote8);
		data->header->len += sizeof(banknote8);
		aux = (char *)realloc(aux, data->header->len);

		memcpy(aux + data->header->len - sizeof(banknote8), &banknote8, sizeof(banknote8));
	}

	if (data->header->type == '2')
	{
		// first banknote
		scanf("%hu", &banknote16);
		data->header->len += sizeof(banknote16);
		aux = (char *)realloc(aux, data->header->len);
		memcpy(aux + data->header->len - sizeof(banknote16), &banknote16, sizeof(banknote16));

		// second banknote
		scanf("%u", &banknote32);
		data->header->len += sizeof(banknote32);
		aux = (char *)realloc(aux, data->header->len);

		memcpy(aux + data->header->len - sizeof(banknote32), &banknote32, sizeof(banknote32));
	}

	if (data->header->type == '3')
	{
		// first banknote
		scanf("%u", &banknote32);
		data->header->len += sizeof(banknote32);
		aux = (char *)realloc(aux, data->header->len);

		memcpy(aux + data->header->len - sizeof(banknote32), &banknote32, sizeof(banknote32));

		// second banknote
		scanf("%u", &banknote32);
		data->header->len += sizeof(banknote32);
		aux = (char *)realloc(aux, data->header->len);

		memcpy(aux + data->header->len - sizeof(banknote32), &banknote32, sizeof(banknote32));
	}
	free(name);
	// second name
	name = read_word();
	data->header->len += strlen(name) + 1;
	aux = (char *)realloc(aux, data->header->len);

	memcpy(aux + data->header->len - strlen(name) - 1, name, strlen(name) + 1);

	// copy to data
	data->data = realloc(aux, data->header->len);

	free(name);
	return data;
}

int add_last(void **arr, int *len, data_structure *data)
{
	if (data == NULL)
		return 1;

	//calculate lenght of array in bytes
	int arr_bytes = length_arr(*arr, *len);

	char *aux = (char *)malloc(sizeof(head) + data->header->len);

	int aux_len = 0;
	// add header (type & len)
	memcpy(aux, data->header, sizeof(head));
	aux_len += sizeof(head);

	// add data
	memcpy(aux + aux_len, data->data, data->header->len);
	aux_len += data->header->len;
	
	// alloc the big array
	if (*(arr) != NULL)
	{
		*(arr) = (void *)realloc(*(arr), aux_len + arr_bytes);
	}

	if (*(arr) == NULL)
	{
		*(arr) = (void *)malloc(aux_len);
	}

	// add to the big array
	memcpy(*(arr) + arr_bytes, aux, aux_len);

	free(aux);
	return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{
	if (index < 0)
		return 1;

	if (*(arr) == NULL)
	{
		if (index == 0)
		{
			add_last(&(*arr), &(*len), data);
			return 0;
		}
		if (index != 0)
			return 1;
	}

	data_structure *data_aux = NULL;
	int i, len_aux = 0;

	// find_index
	for (i = 0; i <= index && len_aux < *(len); i++)
	{
		data_aux = (data_structure *)malloc(sizeof(data_structure));

		data_aux->header = (head *)malloc(sizeof(head));

		data_aux->data = (void *)malloc(sizeof(void));
		memcpy(data_aux->header, *(arr) + len_aux, sizeof(head));

		len_aux += sizeof(head);

		data_aux->data = realloc(data_aux->data, data_aux->header->len);

		memcpy(data_aux->data, *(arr) + len_aux, data_aux->header->len);
		len_aux += data_aux->header->len;
		if (i < index && len_aux != *(len))
		{
			free(data_aux->data);
			free(data_aux->header);
			free(data_aux);
		}
	}

	if (i - 1 != index)
	{
		free(data_aux->data);
		free(data_aux->header);
		free(data_aux);
		add_last(&(*arr), &(*len), data);
		return 0;
	}

	// go to first byte for add arr
	int len_initial = len_aux - data_aux->header->len - sizeof(head);

	void *arr_new = NULL;
	int len_new = 0;

	// creating a new array for my new data

	add_last(&arr_new, &len_new, data);

	// allocating memory for my array
	*(arr) = (void *)realloc(*(arr), *(len) + len_new);

	memmove(*(arr) + len_initial + len_new, *(arr) + len_initial, *(len)-len_initial);
	*(len) += len_new;

	memcpy(*(arr) + len_initial, arr_new, len_new);

	free(data_aux->data);
	free(data_aux->header);
	free(data_aux);

	free(arr_new);
	return 0;
}

void find(void *data_block, int len, int index)
{
	if (index < 0 || data_block == NULL)
		return;
	data_structure *data = NULL;
	int i, len_aux = 0;

	// find_index
	for (i = 0; i <= index && len_aux < len; i++)
	{
		data = (data_structure *)malloc(sizeof(data_structure));

		data->header = (head *)malloc(sizeof(head));

		data->data = (void *)malloc(sizeof(void));
		memcpy(data->header, data_block + len_aux, sizeof(head));

		len_aux += sizeof(head);

		data->data = realloc(data->data, data->header->len);

		memcpy(data->data, data_block + len_aux, data->header->len);
		len_aux += data->header->len;
		if (i < index && len_aux != len)
		{
			free(data->data);
			free(data->header);
			free(data);
		}
	}
	if (i - 1 != index)
	{
		free(data->data);
		free(data->header);
		free(data);
		return;
	}

	void *arr = NULL;
	len_aux = 0;
	add_last(&arr, &len_aux, data);
	print(arr, len_aux);

	free(data->header);
	free(data->data);
	free(data);
	free(arr);
}

int delete_at(void **arr, int *len, int index)
{
	if (index < 0 || *(arr) == NULL || *(len) < index)
		return 1;
	data_structure *data = NULL;
	int i, len_aux = 0;

	int arr_bytes = length_arr(*arr, *len);
	
	// find_index
	for (i = 0; i <= index; i++)
	{
		data = (data_structure *)malloc(sizeof(data_structure));

		data->header = (head *)malloc(sizeof(head));

		data->data = (void *)malloc(sizeof(void));
		memcpy(data->header, *(arr) + len_aux, sizeof(head));

		len_aux += sizeof(head);

		data->data = realloc(data->data, data->header->len);

		memcpy(data->data, *(arr) + len_aux, data->header->len);
		len_aux += data->header->len;
		if (i < index )
		{
			free(data->data);
			free(data->header);
			free(data);
		}
	}


	// go to first byte from deleted arr
	int len_initial = len_aux - data->header->len - sizeof(head);

	memcpy(*(arr) + len_initial, *(arr) + len_aux, arr_bytes-len_aux);

	*(arr) = (void *)realloc(*(arr), arr_bytes - (len_aux - len_initial));

	free(data->data);
	free(data->header);
	free(data);
	return 0;
}

void print(void *arr, int len)
{
	data_structure *data = NULL;
	int len_aux = 0;
	int arr_bytes = length_arr(arr, len);

	for ( int i = 0 ; i < len ; i++)
		{
		data = (data_structure *)malloc(sizeof(data_structure));

		data->header = (head *)malloc(sizeof(head));

		data->data = (void *)malloc(sizeof(void));
		memcpy(data->header, arr + len_aux, sizeof(head));
		len_aux += sizeof(head);

		data->data = realloc(data->data, data->header->len);

		memcpy(data->data, arr + len_aux, data->header->len);
		len_aux += data->header->len;

		printf("Tipul %c\n", data->header->type);

		char *p = (char *)arr + len_aux - data->header->len;

		while (*p != '\0')
		{
			printf("%c", *p);
			p++;
		}
		printf(" pentru ");

		void *first_banknote, *second_banknote;
		if (data->header->type == '1')
		{
			first_banknote = (int8_t *)++p;
			second_banknote = (int8_t *)++p;

			p++;
			while (*p != '\0')
			{
				printf("%c", *p);
				p++;
			}
			printf("\n");
			printf("%" PRId8 "\n", *(int8_t *)first_banknote);
			printf("%" PRId8 "\n", *(int8_t *)second_banknote);
		}

		if (data->header->type == '2')
		{
			first_banknote = (int16_t *)++p;
			p += 2;

			second_banknote = (int32_t *)p;
			p += 4;

			while (*p != '\0')
			{
				printf("%c", *p);
				p++;
			}
			printf("\n");
			printf("%" PRId16 "\n", *(int16_t *)first_banknote);
			printf("%" PRId32 "\n", *(int32_t *)second_banknote);
		}

		if (data->header->type == '3')
		{
			first_banknote = (int32_t *)++p;
			p += 4;

			second_banknote = (int32_t *)p;
			p += 4;

			while (*p != '\0')
			{
				printf("%c", *p);
				p++;
			}
			printf("\n");
			printf("%" PRId32 "\n", *(int32_t *)first_banknote);
			printf("%" PRId32 "\n", *(int32_t *)second_banknote);
		}
		printf("\n");
		free(data->data);
		free(data->header);
		free(data);
	}
}

int main()
{
	// the vector of bytes u have to work with
	// good luck :)
	void *arr = NULL;
	int len = 0;

	data_structure *data = NULL;

	char *cmd = read_word();
	int index;

	while (strcmp(cmd, "exit"))
	{
		if (strcmp(cmd, "insert") == 0)
		{
			data = create_data();
			add_last(&arr, &len, data);
			len++;
			free(data->header);
			free(data->data);
			free(data);
		}

		if (strcmp(cmd, "insert_at") == 0)
		{
			scanf("%d", &index);
			data = create_data();
			add_at(&arr, &len, data, index);
			free(data->header);
			free(data->data);
			free(data);
		}

		if (strcmp(cmd, "find") == 0)
		{
			scanf("%d", &index);
			find(arr, len, index);
		}

		if (strcmp(cmd, "delete_at") == 0)
		{
			scanf("%d", &index);
			if ( !delete_at(&arr, &len, index) )
				len --;
		}

		if (strcmp(cmd, "print") == 0)
		{
			print(arr, len);
		}
		free(cmd);
		cmd = read_word();
	}

	if (arr != NULL)
		free(arr);

	free(cmd);

	return 0;
}
