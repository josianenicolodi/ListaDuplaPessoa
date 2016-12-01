#include <stdio.h>  	
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include<stdbool.h>
//Número de registros aleatórios para gerar
#define TAMANHOINICIAL 50

//tamanho da matriz de randomização NÃO ALTERAR!!!!!!
#define MAX 122

//estruturas
typedef struct Pessoa {
	char   nome[100];
	char   cpf[12];
	float  altura;
	float  peso;
	Pessoa *proximo;
	Pessoa *anterior;
}Pessoa;

typedef struct Indice {
	Pessoa *registro;
	Indice *proximo;
	Indice *anterior;
}Indice;


Indice* InicializaIndiceVazio();
Indice* InicializaIndice(Pessoa *registro);
void ImprimePessoa(Pessoa *p) {
	printf(".......................................................................\n");
	printf("Nome: %s - CPF: %s \n", p->nome, p->cpf);
	printf("Altura: %f - Peso: %f \n", p->altura, p->peso);
	printf(".......................................................................\n");
}

Pessoa* GetPrimeiro(Pessoa* fila) {

	Pessoa* pessoaAtual = NULL;
	Pessoa* retorno = NULL;

	for (pessoaAtual = fila; pessoaAtual != NULL; pessoaAtual = pessoaAtual->anterior)
	{
		retorno = pessoaAtual;
	}
	return retorno;
}

void ImprimeCrescente(Pessoa * fila) {

	Pessoa* atual = NULL;
	printf("Lista de Pessoas: \n");

	if (fila != NULL) {
		for (atual = GetPrimeiro(fila); atual != NULL; atual = atual->proximo) {
			ImprimePessoa(atual);
		}
	}
	else {
		printf("Opss, parece que a lista esta vazia....\n");
	}

	system("pause");
}


//funções
Pessoa* buscaPorCPF(Pessoa* atual, char* cpf)
{
	if (atual == NULL) {
		return NULL;
	}

	int compa = strcmp(atual->cpf, cpf);

	if (compa == 0) {
		return atual;
	}
	else {
		return buscaPorCPF(atual->proximo, cpf);
	}
}

Pessoa* BuscaPorNome(Pessoa* atual, char* nome) {
	if (atual == NULL) {
		return NULL;
	}

	int compa = strcmp(atual->nome, nome);

	if (compa == 0) {
		return atual;
	}
	else {
		return buscaPorCPF(atual->proximo, nome);
	}
}


char inserir(Pessoa **pLista, Pessoa *registro)
{

	if (*pLista != NULL) {
		Pessoa* atual = *pLista;

		int compa = strcmp(atual->nome, registro->nome);

		if (compa == 0) {
			printf("Ja existe este nome cadastrado");
			return '0';
		}
		else if (compa < 0) {
			if (atual->proximo == NULL) {
				atual->proximo = registro;
				registro->anterior = atual;
				return '1';
			}
			else
			{
				compa = strcmp(atual->proximo->nome, registro->nome);
				if (compa > 0) {
					registro->proximo = atual->proximo;
					registro->anterior = atual;
					atual->proximo->anterior = registro;
					atual->proximo = registro;
					return '1';
				}
				else {
					return inserir(&atual->proximo, registro);
				}
			}
		}
		else if (compa > 0) {

			if (atual->anterior == NULL) {
				atual->anterior = registro;
				registro->proximo = atual;
				return '1';
			}
			else
			{
				compa = strcmp(atual->anterior->nome, registro->nome);
				if (compa > 0) {
					registro->proximo = atual;
					registro->anterior = atual->anterior;
					atual->anterior->proximo = registro;
					atual->anterior = registro;
					return '1';
				}
				else {
					return inserir(&atual->anterior, registro);
				}
			}
		}
	}
	else
	{
		*pLista = registro;
		return '1';
	}
}

Indice* GetPrimeiro(Indice* indice) {
	if (indice->anterior != NULL) {
		return GetPrimeiro(indice->anterior);
	}
	return indice;
}

void ImprimeIndices(Indice* indice) {
	Indice* atual = NULL;
	printf("Lista de Pessoas: \n");

	if (indice != NULL) {
		for (atual = GetPrimeiro(indice); atual != NULL; atual = atual->proximo)
		{
			ImprimePessoa(atual->registro);
		}
	}
	else {
		printf("Ops, parece que a lista esta vazia....\n");
	}
	system("pause");
}

char inserirIndice(Indice **pIndice, Pessoa *registro)
{
	if (*pIndice != NULL) {
		Indice* indiceAtual = *pIndice;


		int compa = strcmp(indiceAtual->registro->cpf, registro->cpf);
		if (compa == 0) {
			printf("Ja existe este cpf cadastrado");
			//pensar o que fazer, se retira ou nao o registro 
			return '0';
		}
		else if (compa < 0)
		{
			if (indiceAtual->proximo != NULL) {
				compa = strcmp(indiceAtual->proximo->registro->cpf, registro->cpf);
				if (compa > 0) {
					Indice* novo = InicializaIndice(registro);
					novo->anterior = indiceAtual;
					novo->proximo = indiceAtual->proximo;

					indiceAtual->proximo = novo;
					novo->proximo->anterior = novo;

					return '1';
				}
				else
				{
					inserirIndice(&indiceAtual->proximo, registro);
				}
			}
			else
			{
				indiceAtual->proximo = InicializaIndice(registro);
				indiceAtual->proximo->anterior = indiceAtual;
				return '1';
			}
		}
		else
		{
			if (indiceAtual->anterior != NULL) {
				compa = strcmp(indiceAtual->anterior->registro->cpf, registro->cpf);
				if (compa < 0) {
					Indice* novo = InicializaIndice(registro);
					novo->proximo = indiceAtual;
					novo->anterior = indiceAtual->anterior;

					indiceAtual->anterior = novo;
					novo->anterior->proximo = novo;

					return '1';
				}
				else
				{
					inserirIndice(&indiceAtual->anterior, registro);
				}
			}
			else
			{
				indiceAtual->anterior = InicializaIndice(registro);
				indiceAtual->anterior->proximo = indiceAtual;
				return '1';
			}
		}

	}
	else {

		*pIndice = InicializaIndice(registro);
		return '1';
	}

	return '0';
}

void ValidaCPF(char * cpf) {

	int tam = strlen(cpf);
	char temp[12];


	if (tam < 11) {

		int Stam = 11 - tam;
		int i;
		for (i = 0; i < Stam; i++)
		{
			temp[i] = '0';
		}
		for (int j = 0; j <= tam; j++)
		{
			temp[i] = cpf[j];
			i++;
		}
		strcpy(cpf, temp);
	}

}

void PesquisaCpf(Pessoa *pessoa) {
	char cpf[12];
	printf("Digite o cpf: \n");
	scanf("%s", cpf);
	ValidaCPF(cpf);
	Pessoa *p = NULL;
	p = buscaPorCPF(pessoa, cpf);
	if (p == NULL) {
		printf("Ops, nao encontramos esse cpf!!!!");
	}
	else
	{
		ImprimePessoa(p);
	}
	system("pause");
}

void PesquisaPorNome(Pessoa * pessoa) {
	char nome[100];
	printf("Digite o nome: \n");
	scanf("%s", nome);

	Pessoa * p = NULL;
	p = BuscaPorNome(pessoa, nome);

	if (p == NULL) {
		printf("Ops, nao encontramos esse nome!!!!");
	}
	else
	{
		ImprimePessoa(p);
	}
	system("pause");
}

//implementações
void cadastrar(Pessoa** listaDupla, Indice** indice) {
	Pessoa *pessoa = (Pessoa *)malloc(sizeof(Pessoa));

	pessoa->anterior = NULL;
	pessoa->proximo = NULL;

	system("cls");
	printf("Nome:");
	scanf("%s", &pessoa->nome);
	printf("CPF:");
	scanf("%s", &pessoa->cpf);
	printf("Altura:");
	fflush(stdin);
	scanf("%f", &pessoa->altura);
	printf("Peso:");
	fflush(stdin);
	scanf("%f", &pessoa->peso);
	fflush(stdin);

	ValidaCPF(pessoa->cpf);

	Pessoa * p = NULL;
	p = buscaPorCPF(GetPrimeiro(*listaDupla), pessoa->cpf);
	if (p != NULL) {
		printf("JA temos esse cpf cadastrado...");
		return;
	}
	p = BuscaPorNome(GetPrimeiro(*listaDupla), pessoa->nome);
	if (p != NULL) {
		printf("JA temos esse Nome cadastrado...");
		return;
	}

	printf("Inserindo: %c", inserir(listaDupla, pessoa));
	printf("Inserindo: %c", inserirIndice(indice, pessoa));
	system("pause");

}

void inicializacao(Pessoa **pLista, Indice **pIndice) {
	//valores para randomizaусo
	//FILE *arquivo = fopen("c:\\temp\\teste.arq", "w");
	char nome[MAX][20] = { "Roberto","Catupyan","Saturnino","Terezinha","Sincero","Sudario","Soubrasil","Tarzan","Terezinha","Antonio","Berta","Cafiaspirina","Chevrolet","Clarisbadeu","Daniel","Darcy","Darkson","Deolinda","Disney","Dolores","Erisonia","Joao","Kaelisson","Valentim","Vera","Victor","Virtuosa","Voltaire","Waldemar","Washington","Wladimir","Xilderico","Xisto","Yoisalva","Yolanda","Zelia","Zitelman","Ziuton","Zurivel","Alma","Tom","Epilogo","Espere","Eva","Evaldo","Exuperia","Felicidade","Franklinberg","Francisco","Frankstein","Free","Generosa","Gengis","Getulio","Getulio","Gilete","Graciosa","Hamilton","Haroldo","Helio","Herbert","Zyvane","Amavel","Catupyan","Antonio","Boaventura","Brucili","Selenio","Carlos","Hermenegildo","Horacio","Isabel","Ivanhoe","Ivete","Izabel","Izuperiu","Janice","Jesus","Joaquim","Brasil","Kevinson","Kung","Leidi","Leonardo","Liberalino","Lirio","Luis","Maiquel","Maycom","Marcos","Marilia","Nair","Napoleao","Alrirwertom","Newton","Nisia","Bem_Hur","Nisia","Oceano","Olga","Otavio","Otelino","Otima","Outubrino","Pacifico","Patrick","Paulo","Catupyan","Pedro","Pombinha","Recemvindo","Remo","Rivon","Tranquilino","Tropicao","Ubiratan","Universo","Urano","Ursino","Yale","Kaelisson","Juvelino" };
	float altura[MAX] = { 1.74,1.21,1.97,1.42,1.61,1.74,1.29,1.85,1.15,1.67,1.37,1.23,1.89,1.72,1.36,1.45,1.29,1.85,1.20,1.67,1.12,1.34,1.56,1.48,1.54,1.65,1.48,1.45,1.62,1.45,1.62,1.15,1.67,1.49,1.85,1.19,1.73,1.12,1.91,1.65,1.46,1.51,1.24,1.97,1.21,1.56,1.74,1.29,1.81,1.26,1.74,1.21,1.89,1.74,1.21,1.97,1.42,1.19,1.75,1.42,1.18,1.97,1.42,1.19,1.74,1.21,1.97,1.42,1.61,1.74,1.29,1.85,1.15,1.67,1.37,1.23,1.89,1.72,1.36,1.45,1.29,1.85,1.20,1.67,1.12,1.34,1.56,1.48,1.54,1.65,1.48,1.45,1.62,1.45,1.62,1.15,1.67,1.49,1.85,1.19,1.73,1.12,1.91,1.65,1.46,1.51,1.24,1.97,1.21,1.56,1.74,1.29,1.81,1.26,1.74,1.21,1.89,1.74,1.21,1.97,1.42,1.19 };
	char cpf[MAX][12] = { "12345648546","54845624562","15674985197","31291654651","24972156742","98126742189","74219742197","54218974219","74219742617","42985156737","23897236452","98520671234","56485465484","56245621567","49851973129","16546512497","21567429812","67421897421","97421975421","89742197421","97426174298","51567372389","72364529852","06712345648","54654845624","56215674985","19731291654","65124972156","74298126742","18974219742","19754218974","21974219742","61742985156","73723897236","45298520671","23456485465","48456245621","56749851973","12916546512","49721567429","81267421897","42197421975","42189742197","42197426174","29851567372","38972364529","85206712345","64854654845","62456215674","98519731291","65465124972","15674298126","74218974219","74219754218","97421974219","74261742985","15673723897","23645298520","67123456485","46548456245","62156749851","97312916546","51249721567","42981267421","89742197421","97542189742","19742197426","17429851567","37238972364","52985206712","34564854654","84562456215","67498519731","29165465124","97215674298","12674218974","21974219754","21897421974","21974261742","98515673723","89723645298","52067123456","48546548456","24562156749","85197312916","54651249721","56742981267","42189742197","42197542189","74219742197","42617429851","56737238972","36452985206","71234564854","65484562456","21567498519","73129165465","12497215674","29812674218","97421974219","75421897421","97421974261","74298515673","72389723645","29852067123","45648546548","45624562156","74985197312","91654651249","72156742981","26742189742","19742197542","18974219742","19742617429","85156737238","97236452985","20671234564","85465484562","45621567498","51973129165","46512497215","24972154458" };
	float peso[MAX] = { 74,21,97,42,61,74,29,85,15,67,37,23,89,72,36,45,29,85,20,67,12,34,56,48,54,65,48,45,62,45,62,15,67,49,85,19,73,12,91,65,46,51,24,97,21,56,74,29,81,26,74,21,89,74,21,97,42,19,75,42,18,97,42,19,74,21,97,42,61,74,29,85,15,67,37,23,89,72,36,45,29,85,20,67,12,34,56,48,54,65,48,45,62,45,62,15,67,49,85,19,73,12,91,65,46,51,24,97,21,56,74,29,81,26,74,21,89,74,21,97,42,19 };
	//inicializa os gerador de nЩmeros randЗmicos
	srand((unsigned)time(NULL));


	unsigned char incluidos = 0;
	do {
		//gera um número randômico de 0 a MAX-1 
		unsigned char x = rand() % MAX;
		//cria um registro e salva no arquivo
		Pessoa *pessoa = (Pessoa *)malloc(sizeof(Pessoa));
		x = rand() % MAX;
		strcpy(pessoa->nome, nome[x]);
		x = rand() % MAX;
		strcpy(pessoa->cpf, cpf[x]);
		x = rand() % MAX;
		pessoa->altura = altura[x];
		x = rand() % MAX;
		pessoa->peso = peso[x];
		pessoa->anterior = NULL;
		pessoa->proximo = NULL;
		ValidaCPF(pessoa->cpf);
		inserir(pLista, pessoa);


		incluidos++;
		inserirIndice(pIndice, pessoa);

	} while (incluidos != TAMANHOINICIAL);
}

Pessoa* InicializaListaVazia() {
	Pessoa *listaDupla = (Pessoa *)malloc(sizeof(Pessoa));
	listaDupla->anterior = NULL;
	listaDupla->proximo = NULL;
	strcpy(listaDupla->nome, "");
	strcpy(listaDupla->cpf, "");

	return listaDupla;
}

Indice* InicializaIndice(Pessoa *registro) {
	Indice* indice = InicializaIndiceVazio();
	indice->registro = registro;

	return indice;
}

Indice* InicializaIndiceVazio() {
	Indice* indice = (Indice *)malloc(sizeof(Indice));
	indice->registro = NULL;
	indice->proximo = NULL;
	indice->anterior = NULL;

	return indice;
}

void ExcluirPorNome(Indice* indice, char* nome) {
	if (indice != NULL) {
		Indice* atual = GetPrimeiro(indice);
		int compa;
		for (atual = GetPrimeiro(indice); atual != NULL; atual = atual->proximo) {
			compa = strcmp(atual->registro->nome, nome);
			if (compa == 0) {
				if (atual->anterior != NULL) {
					atual->anterior->proximo = atual->proximo;
				}
				if (atual->proximo != NULL) {
					atual->proximo->anterior = atual->anterior;
				}
				Pessoa* p = atual->registro;

				if (p != NULL) {
					if (p->anterior != NULL) {
						p->anterior->proximo = p->proximo;
					}
					if (p->proximo != NULL) {
						p->proximo->anterior = p->anterior;
					}
					atual->registro == NULL;
					free(p);
				}
				free(atual);
				break;
			}
		}
	}
}

void Excluir(Indice* indice, char* cpf) {
	if (indice != NULL) {
		Indice* atual = GetPrimeiro(indice);
		int compa;
		for (atual = GetPrimeiro(indice); atual != NULL; atual = atual->proximo) {
			compa = strcmp(atual->registro->cpf, cpf);
			if (compa == 0) {
				if (atual->anterior != NULL) {
					atual->anterior->proximo = atual->proximo;
				}
				if (atual->proximo != NULL) {
					atual->proximo->anterior = atual->anterior;
				}
				Pessoa* p = atual->registro;

				if (p != NULL) {
					if (p->anterior != NULL) {
						p->anterior->proximo = p->proximo;
					}
					if (p->proximo != NULL) {
						p->proximo->anterior = p->anterior;
					}
					atual->registro == NULL;
					free(p);
				}
				free(atual);
				break;
			}
		}
	}
}

//principal
int main(void) {

	Pessoa *listaDupla = NULL;

	Indice *indiceCPF = NULL;
	char invalida = 'N';

	//inicializacao(&listaDupla, &indiceCPF);
	char op;
	do {
		system("cls");
		printf("\t\t\t\tMenu\n\n");
		printf("\tI\t - Incluir\n");
		printf("\tB\t - Buscar por Nome\n");
		printf("\tC\t - Buscar por CPF\n");
		printf("\tN\t - Listar por Nome\n");
		printf("\tL\t - Listar por CPF\n");
		printf("\tESC\t - Sair\n");
		if (invalida == 'S') {
			printf("\n\nOpcao invalida!");
		}
		op = toupper(getch());
		invalida = 'N';
		switch (op) {
		case 'I':
			cadastrar(&listaDupla, &indiceCPF);
			break;
		case 'B':
			PesquisaPorNome(GetPrimeiro(listaDupla));
			char nomeExclu[12];
			printf("Digite o cpf: \n");
			scanf("%s", nomeExclu);
			
			ExcluirPorNome(indiceCPF, nomeExclu);
			break;
		case 'C':
			PesquisaCpf(GetPrimeiro(listaDupla));
			char cpfExclu[12];
			printf("Digite o cpf: \n");
			scanf("%s", cpfExclu);
			ValidaCPF(cpfExclu);
			Excluir(indiceCPF, cpfExclu);
			break;
		case 'N':
			ImprimeCrescente(listaDupla);
			break;
		case 'L':
			ImprimeIndices(indiceCPF);
			break;
		case 27:

			break;
		default: invalida = 'S';
		}
	} while (op != 27);
	return 0;
}