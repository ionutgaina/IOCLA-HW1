#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "structs.h"

#define MAX_str 256

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
	// for (int i = 0; i < data->header->len; i++)
	// 	printf("result = 0x%c\n", *(aux + i));
	// copy to data
	data->data = realloc(aux, data->header->len);

	free(name);
	return data;
}

int add_last(void **arr, int *len, data_structure *data)
{
	if (data == NULL)
		return 1;

	char *aux = (char *)malloc(sizeof(head) + data->header->len);


	int aux_len = 0;
	// add header (type & len)
	memcpy(aux, data->header, sizeof(head));
	aux_len += sizeof(head);

	// add data
	memcpy(aux + aux_len, data->data, data->header->len);
	aux_len += data->header->len;

	// for (int i = 0; i < aux_len; i++)
	// printf("result1 = 0x%hx\n", *(aux + i));

	// alloc the big array
	if (*(arr) != NULL)
	{
		*(arr) = (void *)realloc(*(arr), aux_len + *(len));
	}

	if (*(arr) == NULL)
	{
		*(arr) = (void *)malloc(aux_len);
	}

	// add to the big array
	memcpy(*(arr) + *(len), aux, aux_len);
	// printf("p= %p\n", *(arr) + *(len));
	*(len) += aux_len;

	// printf("add last\n");
	// for (int i = 0; i < *(len); i++)
	// 	printf("result2 = 0x%hx\n", *((char *)*(arr) + i));
	free(aux);
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
	data_structure *data = NULL;
	int len_aux = 0;

	while (len_aux < len)
	{
		data = (data_structure *)malloc(sizeof(data_structure));


		data->header = (head *)malloc(sizeof(head));

		data->data = (void *)malloc(sizeof(void));
		memcpy(data->header, arr + len_aux, sizeof(head));
		len_aux += sizeof(head);

		data->data = realloc(data->data, data->header->len);

		memcpy(data->data, arr + len_aux, data->header->len);
		len_aux += data->header->len;

		// for (int i = 0; i < len; i++)
		// 	printf("result = 0x%d p=%p\n", *((char *)arr + i), arr + i);

		printf("Tipul %c\n", data->header->type); 

		char *p = (char *)arr + len_aux - data->header->len ;

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
			p +=2;

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
		// printf("p2= %p \n", arr + len_aux);
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
			free(data->header);
			free(data->data);
			free(data);
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
