#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tarefa
{
  char nome[100];
  char data[100];
  char prazo[100];
  struct tarefa *proximo;
  struct tarefa *anterior;
} TAREFA;

typedef struct registro
{
  char nome[100];
  char departamento[100];
  char cargo[100];
  TAREFA *tarefa;
  struct registro *proximo;
  struct registro *anterior;
} REGISTRO;

REGISTRO *inserirRegistroInicio(REGISTRO *inicio, REGISTRO *novo)
{
	if(inicio != NULL)
	{
		novo->proximo = inicio;
		novo->anterior = NULL;
		inicio->anterior = novo;
	}
	else
	{
		novo->proximo = NULL;
		novo->anterior = NULL;
	}
	return novo;
}

REGISTRO *inserirRegistroFinal(REGISTRO *inicio, REGISTRO *novo)
{
	REGISTRO *temp;
	if(inicio != NULL)
	{
		temp = inicio;
		while(temp->proximo !=NULL)
		{
			temp = temp->proximo;
		}
		temp->proximo = novo;
		novo->anterior = temp;
		novo->proximo = NULL;
		return inicio;
	}
	else
	{
		novo->proximo = NULL;
		novo->anterior = NULL;
		return novo;
	}
}

REGISTRO *inserirRegistro(REGISTRO *inicio, REGISTRO *novo, int posicao)
{
	int i=1;
	REGISTRO *temp;

	if(posicao==0 || inicio == NULL)
	{
		return inserirRegistroInicio(inicio, novo);
	}

	if(posicao<0)
	{
		return inicio;
	}

	temp = inicio->proximo;
	while(i!=posicao && temp!=NULL)
	{
		temp = temp->proximo;
		i++;
	}

	//adicionar no final da lista
	if(temp == NULL)
	{
		inserirRegistroFinal(inicio, novo);
		return inicio;
	}

	novo->proximo = temp;
	novo->anterior = temp->anterior;
	temp->anterior->proximo = novo;
	temp->anterior = novo;

	return inicio;
}

REGISTRO *removerInicioLista(REGISTRO *inicio)
{
	if(inicio != NULL && inicio->proximo != NULL)
	{
		inicio->proximo->anterior = NULL;
		return inicio->proximo;
	}
	if(inicio == NULL)
	{
		return inicio;
	}
	else
	{
		return NULL;
	}
}

REGISTRO *removerFinalLista(REGISTRO *inicio)
{
	REGISTRO *temp;
	temp = inicio;

	if(inicio == NULL)
	{
		return inicio;
	}

	while(temp->proximo !=NULL)
	{
		temp = temp->proximo;
	}

	if(temp->anterior == NULL)
	{
		return NULL;
	}
	else
	{
		temp->anterior->proximo = NULL;
		return inicio;
	}
}

REGISTRO *removerRegistro(REGISTRO *inicio, int posicao)
{
	int i=1;
	REGISTRO *temp;

	if(posicao==0)
	{
		return removerInicioLista(inicio);
	}

	if(posicao<0 || inicio == NULL)
	{
		return inicio;
	}

	temp = inicio->proximo;
	while(i!=posicao && temp!=NULL)
	{
		temp = temp->proximo;
		i++;
	}

	if(temp==NULL)
	{
		printf("nao ha registro nessa posicao\n\n");
		return inicio;
	}

	temp->anterior->proximo = temp->proximo;
	if(temp->proximo != NULL)
	{
		temp->proximo->anterior = temp->anterior;
	}

	return inicio;
}

REGISTRO *buscarRegistro(REGISTRO *inicio, char *nome)
{
	REGISTRO *temp;

	temp = inicio;
	while(temp!=NULL)
	{
		if(strcmp(nome, temp->nome)==0)
		{
			return temp;
		}
		temp = temp->proximo;
	}
	printf("nao ha registro com esse nome");
	return temp;
}

void exibirRegistro(REGISTRO registro)
{
	printf("\nNome         : %s\n", registro.nome);
	printf("Departamento : %s\n", registro.departamento);
	printf("Cargo        : %s\n\n", registro.cargo);
}

void exibirTodosRegistros(REGISTRO *inicio)
{
	REGISTRO *temp;

	if(inicio==NULL)
	{
		puts("\nlista de registros vazios\n");
	}
	else
	{
		temp = inicio;
		puts("\nInformacoes de todos os registros:");
		while(temp != NULL)
		{
			exibirRegistro(*temp);
			temp = temp->proximo;
		}
	}
}

void buscarTarefa(REGISTRO *inicio, char *nome)
{
	REGISTRO *temp;
	TAREFA *temp2;
	short int encontrou = 0;
	temp = inicio;
	while(temp != NULL)
	{
		temp2 = temp->tarefa;
		while(temp2 != NULL)
		{
			if(strcmp(nome, temp2->nome) == 0)
			{
				encontrou++;
				printf("\nNome: %s\n", temp2->nome);
				printf("Data: %s\n", temp2->data);
				printf("Prazo: %s\n\n", temp2->prazo);
				temp2 = NULL;
			}
			else
			{
				temp2 = temp2->proximo;
			}
		}
		temp = temp->proximo;
	}
	if(!encontrou)
	{
		printf("Tarefa inexistente \n\n");
	}
}

void exibirTodasTarefas(REGISTRO *inicio)
{
	REGISTRO *temp;
	TAREFA *temp2;
	temp = inicio;
	while(temp != NULL)
	{
		printf("Tarefas do registro de %s\n\n", temp->nome);
		temp2 = temp->tarefa;
		while(temp2 != NULL)
		{
			buscarTarefa(inicio, temp2->nome);
			temp2 = temp2->proximo;
		}
		temp = temp->proximo;
	}
}

void inserirTarefa(REGISTRO *inicio, TAREFA *tarefa, REGISTRO *r1)
{
	REGISTRO *temp;

	temp = inicio;
	while(temp != NULL)
	{
		if(temp == r1)
		{
			if(temp->tarefa == NULL)
			{
				temp->tarefa = tarefa;
				temp->tarefa->anterior = NULL;
				temp->tarefa->proximo = NULL;
			}
			else
			{
				tarefa->anterior = NULL;
				tarefa-> proximo = temp->tarefa;
				temp->tarefa->anterior = tarefa;
				temp->tarefa = tarefa;
			}
		}
		temp = temp->proximo;
	}
}

void removerTarefa(REGISTRO *inicio, char *nome)
{
	REGISTRO *temp;
	TAREFA *temp2;

	temp = inicio;
	while(temp != NULL)
	{
		temp2 = temp->tarefa;
		while(temp2 != NULL)
		{
			if(strcmp(temp2->nome,nome)==0)
			{
				if(temp2->proximo == NULL && temp2->anterior==NULL)
				{
					temp->tarefa = NULL;
				}
				else if(temp2->anterior == NULL)
				{
					temp2->proximo->anterior = NULL;
					temp->tarefa = temp2->proximo;
				}
				else if(temp2->proximo == NULL)
				{
					temp2->anterior->proximo = NULL;
					temp2->anterior = NULL;
				}
				else
				{
					temp2->anterior->proximo = temp2->proximo;
					temp2->proximo->anterior = temp2->anterior;
					temp2->anterior = NULL;
					temp2->anterior = NULL;
				}
//				temp = NULL;
				temp2 = NULL;
			}
			else
			{
				temp2=temp2->proximo;
			}
		}
		temp = temp->proximo;
	}
}

REGISTRO *criarRegistro(void)
{
	REGISTRO *temp;

	temp = (REGISTRO*)calloc(1,sizeof(REGISTRO));
	puts("Nome do colaborador:");
	scanf("%[^\n]",temp->nome);
	getchar();
	puts("Nome do departamento do colaborador:");
	scanf("%[^\n]",temp->departamento);
	getchar();	
	puts("Nome cargo do colaborador:");
	scanf("%[^\n]",temp->cargo);
	getchar();
	temp->tarefa = NULL;
	return temp;
}

TAREFA *criarTarefa(void)
{
	TAREFA *temp;

	temp = (TAREFA*)calloc(1,sizeof(TAREFA));
	puts("Nome da tarefa:");
	scanf("%[^\n]",temp->nome);
	getchar();	
	puts("Data da tarefa:");
	scanf("%[^\n]",temp->data);
	getchar();	
	puts("Prazo para a conclusao da tarefa:");
	scanf("%[^\n]",temp->prazo);
	getchar();
//	temp->proximo = NULL;
//	temp->anterior = NULL;
	return temp;
}

int main()
{
	// lista inicial

    REGISTRO r1, r2, r3, r4, *temp, r5;
    REGISTRO *inicio = NULL, *registro;
    TAREFA *tarefa;
    TAREFA t1,t2,t3,t4,t5;
    int opcao=-1;
    char nome[100];

	while(1)
	{
		puts("Digite um numero indicando a opcao desejada:");
		puts("Opcao 0: sair do programa");
		puts("Opcao 1: inserir registro no inicio");
		puts("Opcao 2: inserir registro no final");
		puts("Opcao 3: inserir registro em uma posicao especifica");
		puts("Opcao 4: remover registro no inicio");
		puts("Opcao 5: remover registro no final");
		puts("Opcao 6: remover registro em uma posicao especifica");
		puts("Opcao 7: buscar registro");
		puts("Opcao 8: exibir todos os registros");
		puts("Opcao 9: inserir tarefa");
		puts("Opcao 10: remover tarefa");
		puts("Opcao 11: buscar tarefa");
		puts("Opcao 12: buscar todas as tarefas");
		scanf("%d", &opcao);
		getchar();

		if(opcao==0)
		{
			break;
		}
		switch(opcao)
		{
			case 1:
				inicio = inserirRegistroInicio(inicio, criarRegistro());
				break;
			case 2:
				inicio = inserirRegistroFinal(inicio, criarRegistro());
				break;
			case 3:
				puts("Inserir em qual posicao?");
				scanf("%d",&opcao);
				getchar();
				inicio = inserirRegistro(inicio, criarRegistro(),opcao);
				break;
			case 4:
				inicio = removerInicioLista(inicio);
				break;
			case 5:
				inicio = removerFinalLista(inicio);
				break;
			case 6:
				puts("Remover qual posicao?");
				scanf("%d",&opcao);
				getchar();
				inicio = removerRegistro(inicio,opcao);
				break;
			case 7:
				puts("Qual nome?");
				scanf("%[^\n]", nome);
				getchar();
				exibirRegistro(*buscarRegistro(inicio, nome));
				break;
			case 8:
				exibirTodosRegistros(inicio);
				break;
			case 9:
				puts("Digite o nome do funcionario que devera realizar a tarefa");
				scanf("%[^\n]", nome);
				getchar();
				tarefa = criarTarefa();
				registro = buscarRegistro(inicio, nome);
				inserirTarefa(inicio, tarefa , registro);
				break;
			case 10:
				puts("Digite o nome da tarefa a ser removida");
				scanf("%[^\n]", nome);
				getchar();
				removerTarefa(inicio, nome);
				break;
			case 11:
				puts("Digite o nome da tarefa");
				scanf("%[^\n]", nome);
				getchar();
				buscarTarefa(inicio, nome);
				break;
			case 12:
				exibirTodasTarefas(inicio);
				break;
		}
	}

    return 0;
}
