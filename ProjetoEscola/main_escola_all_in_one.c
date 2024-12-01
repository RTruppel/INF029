//Bibliotecas
#include <stdio.h>
#include <string.h>

//Definições
#define tam 100
#define False 0
#define True 1
#define Desmatriculado -1

//Structs
typedef struct //#Criando struct geral de cadastro para pessoas.
{
    char Nome[tam]; 
    char CPF[tam];
    char genero;

    int  Dia;
    int  Mes;
    int  Ano;
    int  ID;
    int  Atividade; 
} s_pessoa;

typedef struct { //Struct para disciplinas
    char Nome[tam]; 

    int  Professores[tam];
    int  Alunos[tam];
    int  Tam_Alunos;
    int Tam_Professor;

    int  Atividade;
    int  Semestre;
    int  ID;   
} s_disciplina;

//Limpa Buffer
void limparBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

//Exibições
int choose_modulo()
{
    int escolha_modulo;
    printf("Menu: \n1. Área do aluno.\n2. Área do professor.\n3. Área das disciplinas.\nÁrea: ");
    scanf("%d", &escolha_modulo);
    limparBuffer();
    return escolha_modulo;
}

int modulo_operations_pessoas()
{
    int operacao;
    printf("1. Cadastrar Pessoa.\n2. Atualizar Informações Pessoais.\n3. Excluir Pessoas.\n4. Listar Pessoas.\n5. Aniversariantes do Mês.\n6. Buscar por Chave\n7. Sair\n. Operacao: ");
    scanf("%d", &operacao); 
    limparBuffer();
    return operacao;
}

int modulo_operations_disciplinas()
{
    int operacao;
    printf("1. Cadastrar Disciplinas.\n2. Atualizar Informações.\n3. Excluir Disciplinas.\n4. Listar Disciplinas.\n5. Alunos Matrículados em Menos que 3 disciplinas\n6. Sair\n. Operacao: ");
    scanf("%d", &operacao); 
    limparBuffer();
    return operacao;
}

int continue_operation()
{
    int operation_continue;
    printf("\n0 - Não.\n1 - Sim.\nOutro - Inválido, voltar ao menu.\n\nDeseja prosseguir com a operacao?: ");
    scanf("%d", &operation_continue); 
    limparBuffer();
    return operation_continue;
}


int op_atualization()
{
    int op_atualization; 
    printf("\n1 - Nome\n2 - CPF\n3 - Sexo\n4 - Data de Nascimento\n5 - Atividade\nOutro - Opção inválida.\n\nO que deseja atualizar?: ");
    scanf("%d", &op_atualization);
    limparBuffer();
    return op_atualization;
}

int continue_or_cancel()
{
    int continue_or_cancel;

    printf("1 - Cancelar Cadastro\nOutro - Continuar\nDigite a opção: ");
    scanf("%d", &continue_or_cancel);

    return continue_or_cancel;
}

void validation_error()
{
    printf("Dados inválidos. Por favor, insira os dados de forma adequada.\n");
}

//Verificações de Entrada
int valid_data_type_name(char string[tam]) 
{
    int apenas_letras = False, index1; 
    for (index1 = 0; string[index1] != '\0'; index1++) {
        if ( (string[index1] >= 'A' && string[index1] <= 'Z') || 
             (string[index1] >= 'a' && string[index1] <= 'z') || 
             (string[index1] >=  0 && string[index1] <=   31) ||
              string[index1] == ' ') {
            apenas_letras = True;
        }
        else {
            apenas_letras = False;
            break;
        }
    }
    return apenas_letras; 
}

int valid_CPF(char string[tam])
{
    int index1, apenas_numeros = False, tamanho;

    if(tamanho = strlen(string) == 12) {
        for (index1 = 0; string[index1]; index1++) {
            if ( (string[index1] >= '0' && string[index1] <= '9') || (string[index1] >= 0 && string[index1] <= 31)) {
                apenas_numeros = True;
            }
            else {
                apenas_numeros = False;
                break; 
            }
        }
    }
    else {
        apenas_numeros = False;
    }
    return apenas_numeros;
}


int date_verify(int dd, int mm, int yy)
{
    int validade_data = True;

    if ( (yy >= 1900 && yy <= 2018) && (mm >= 0 && mm <= 12) && (dd >= 0 && dd <= 31) ) { 

        if (yy%4 == 0) {
            if (mm == 2) {
                if (dd > 29) {
                    validade_data = False;
                }
            }
            else if (mm == 4 || mm == 6 || mm == 9 || mm == 11) {
                if (dd > 30) {
                    validade_data = False;
                }
            }
        }
        else {
            if (mm == 2) {
                if (dd > 28) {
                    validade_data = False;
                }
            }
            else if (mm == 4 || mm == 6 || mm == 9 || mm == 11) {
                if (dd > 30) {
                    validade_data = False;
                }
            }
        }

    }
    else {
        validade_data = False;
    }
    return validade_data;
}

//Pré-Processamento
void standardize_names(char string[tam]) {
    char str_copy[tam];
    int index1 = 0, index2 = 0; 


    while (string[index1] == ' ') {
        index1++; 
    }


    int pradronize_proxima = 1; 
    while (string[index1] != '\0') {
        if (string[index1] == ' ') {
            str_copy[index2++] = string[index1++];
            pradronize_proxima = 1; 
        } else if ((string[index1] >= 'A' && string[index1] <= 'Z') ||
                   (string[index1] >= 'a' && string[index1] <= 'z')) {
            if (pradronize_proxima && string[index1] >= 'a' && string[index1] <= 'z') {
                str_copy[index2++] = string[index1++] - 32;
            } else if (!pradronize_proxima && string[index1] >= 'A' && string[index1] <= 'Z') {
                str_copy[index2++] = string[index1++] + 32;
            } else {
                str_copy[index2++] = string[index1++];
            }
            pradronize_proxima = 0;
        } else {
            index1++; 
        }
    }

    str_copy[index2] = '\0'; 
    strcpy(string, str_copy); 
}


//Busca relacionadas a Pessoas
int existence_verify(s_pessoa v_pessoas[tam], int ID)
{
  int existe = -1, index1;
  for (index1 = 0; index1 < tam; index1++) {
      if (v_pessoas[index1].ID == ID) {
          existe = index1;
          break; 
      }
  }
  return existe; 
}

int search_index(s_pessoa v_pessoas[tam], int busca)
{
  int index1;
  for (index1 = 0; index1 < tam; index1++) {
      if (v_pessoas[index1].ID == busca) {
          break; 
      } 
  }
  return index1;
}

int verify_uniqueness_of_cpf(s_pessoa v_pessoas[tam], int index)
{
    int another_equal_cpf, index1;

    for (index1 = 0; index1 < index; index1++) {
        another_equal_cpf = strcmp(v_pessoas[index1].CPF, v_pessoas[index].CPF);
    }
    return another_equal_cpf; 
}

int verify_in_people_folder(s_pessoa v_pessoas[tam], int t_v_pessoas, int ID)
{
    int in_folder = False, index;
    for (index = 0; index < t_v_pessoas; index++) {
        if (v_pessoas[index].ID == ID) {
            in_folder = True;
            break;
        }
    }
    return in_folder;
}

//Buscas relacionadas à disciplinas 
int verify_people_id_in_vector(s_disciplina v_disciplinas[tam], int index_disciplina, int index_pessoa, int classe_pessoa) 
{
    int not_repeated_id = True, index1;
    int aluno = 1, professor = 2;

    if (classe_pessoa = aluno) {
        for (index1 = 0; index1 < index_pessoa; index1++) {
            if (v_disciplinas[index_disciplina].Alunos[index1] == v_disciplinas[index_disciplina].Alunos[index_pessoa]) {
                not_repeated_id = False;
                break;
            }
        }
    }
    else {
        for (index1 = 0; index1 < index_pessoa; index1++) {
            if (v_disciplinas[index_disciplina].Professores[index1] == v_disciplinas[index_disciplina].Professores[index_pessoa]) {
                not_repeated_id = False;
                break;
            }
        }
    }

    return not_repeated_id;
}

int search_people_in_vector(s_disciplina *v_disciplinas, int index_disciplina, int ID, int QTD, int tipo_pessoa)
{
    int aluno = 1, professor = 0, existe = False, index_1;

    if (tipo_pessoa = aluno) {
        for (index_1 = 0; index_1 < QTD; index_1++) {
            if (v_disciplinas[index_disciplina].Alunos[index_1] == ID) {
                existe = True;
                break;
            }
        }
    }
    else {
        for (index_1 = 0; index_1 < QTD; index_1++) {
            if (v_disciplinas[index_disciplina].Professores[index_1] == ID) {
                existe = True;
                break;
            }
        }
    }
    return existe;
}

int existence_verify_discipline(s_disciplina v_disciplinas[tam], int ID)
{
  int existe = -1, index1;
  for (index1 = 0; index1 < tam; index1++) {
      if (v_disciplinas[index1].ID == ID) {
          existe = index1;
          break; 
      }
  }
  return existe; 
}

int verify_uniqueness_of_id_disciplines(s_disciplina v_disciplinas[tam], int index)
{
    int single_id = True, index1;
    for (index1 = 0; index1 < index; index1++) {
        if (v_disciplinas[index1].ID == v_disciplinas[index].ID) {
            single_id = False;
            break;
        }
    }

    return single_id; 
}

int verify_in_discipline_folder(s_pessoa v_disciplinas[tam], int t_v_disciplinas, int ID)
{
    int in_folder = False, index;
    for (index = 0; index < t_v_disciplinas; index++) {
        if (v_disciplinas[index].ID == ID) {
            in_folder = True;
            break;
        }
    }
    return in_folder;
}

//Processamento
void position_swap(s_pessoa v_pessoas[tam], int index_1, int index_2) //#Troca posição
{
    char str_aux[tam], aux_1;
    int aux_2;

    //Troca de posição do Nome
    strcpy(str_aux, v_pessoas[index_1].Nome);
    strcpy(v_pessoas[index_1].Nome, v_pessoas[index_2].Nome);
    strcpy(v_pessoas[index_2].Nome, str_aux);

    //Troca de posição do CPF
    strcpy(str_aux, v_pessoas[index_1].CPF);
    strcpy(v_pessoas[index_1].CPF, v_pessoas[index_2].CPF);
    strcpy(v_pessoas[index_2].CPF, str_aux);

    //Troca de posição do Genero
    aux_1 = v_pessoas[index_1].genero;
    v_pessoas[index_1].genero = v_pessoas[index_2].genero;
    v_pessoas[index_2].genero = aux_1;

    //Troca de posição da ID
    aux_2 = v_pessoas[index_1].ID;
    v_pessoas[index_1].ID = v_pessoas[index_2].ID;
    v_pessoas[index_2].ID = aux_2;

    //Troca de posição do dia de Nascimento
    aux_2 = v_pessoas[index_1].Dia;
    v_pessoas[index_1].Dia = v_pessoas[index_2].Dia;
    v_pessoas[index_2].Dia = aux_2;

    //Troca de posição do mes de Nascimento
    aux_2 = v_pessoas[index_1].Mes;
    v_pessoas[index_1].Mes = v_pessoas[index_2].Mes;
    v_pessoas[index_2].Mes = aux_2;

    //Troca de posição do ano de Nascimento
    aux_2 = v_pessoas[index_1].Ano;
    v_pessoas[index_1].Ano = v_pessoas[index_2].Ano;
    v_pessoas[index_2].Ano = aux_2;

}

// Operações - Pessoas
void exclusion(s_pessoa v_pessoas[tam], int index) //#Exclusão lógica
{
   v_pessoas[index].Atividade = False;
   printf("Exclusão efetuada com sucesso.");
}

void less_than_three(s_pessoa v_alunos[tam], s_disciplina v_disciplinas[tam], int t_v_alunos, int t_v_disciplinas)
{
    int index_v_a, index_v_d, index_a_d, cont_mat;
    for (index_v_a == 0; index_v_a < t_v_alunos; index_v_a++) {
        cont_mat = 0;
        if (v_alunos[index_v_a].ID != Desmatriculado) {
            for (index_v_d = 0; index_v_d < t_v_disciplinas; index_v_d++) {
                if (v_disciplinas[index_v_d].ID != Desmatriculado) {
                    for (index_a_d = 0; index_a_d < v_disciplinas[index_v_d].Tam_Alunos; index_a_d++) {
                        if (v_disciplinas[index_v_d].Alunos[index_a_d] == v_alunos[index_v_a].ID) {
                            cont_mat += 1;
                            break;
                        }
                    }
                }
            }
            if (cont_mat < 3) {
                printf("%s - Matriculado em Menos que 3 disciplinas.\n", v_alunos[index_v_a].Nome);
            }
        }
    }
}

// Listagem Pessoas
void list_alphabetically(s_pessoa v_pessoas[tam], int t_v_pessoas)
{
    char str_aux[tam];
    int index1, index2, index_str1, index_str2;

    for (index1 = 0; index1 < t_v_pessoas; index1++) {
        for (index2 = index1 + 1; index2 < t_v_pessoas; index2++) {
                if (strcmp(v_pessoas[index1].Nome, v_pessoas[index2].Nome) > 0) {
                    position_swap(v_pessoas, index1, index2);
                }
        }
    }
    for (index1 = 0; index1 < t_v_pessoas; index1++) {
        printf("%d - %s", index1 + 1, v_pessoas[index1].Nome);
    }
    printf("\nLista Alfabética Finalizada.\n");
}

void list_by_gender(s_pessoa v_pessoas[tam], int t_v_pessoas)
{
    int index1, index2, continua_listar=True;
    char genero_listar;

    while (continua_listar==True) {
        continua_listar = continue_operation();


        if (continua_listar == True) {
            printf("\nM - Masculino\nF - Feminino\nI - Indefinido\nOutro - Encerrar\nDeseja listar os alunos pertencentes a qual gênero?: ");
            scanf("%c", &genero_listar);

            if (genero_listar == 'M') {
                printf("\n");
                for (index1 = 0; index1 < t_v_pessoas; index1++) {
                    if (v_pessoas[index1].genero == genero_listar) { 
                        printf("%d - %s", index1 + 1, v_pessoas[index1].Nome);
                    }
                }
                printf("Lista Masculina Finalizada.\n");
            }
            else if (genero_listar == 'F') {
                printf("\n");
                for (index1 = 0; index1 < t_v_pessoas; index1++) {
                    if (v_pessoas[index1].genero == genero_listar) { 
                        printf("%d - %s", index1 + 1, v_pessoas[index1].Nome);
                    }
                }
                printf("Lista Feminina Finalizada.\n");
            }
            else if (genero_listar == 'I') {
                printf("\n");
                for (index1 = 0; index1 < t_v_pessoas; index1++) {
                    if (v_pessoas[index1].genero == genero_listar) { 
                        printf("%d - %s", index1 + 1, v_pessoas[index1].Nome);
                    }
                }
                printf("Lista Indefinida Finalizada.\n");
            }
            else {
                printf("\n\nOpção Inválida\n\n");
            }
        }
        else {
            printf("\nListagem por gênero encerrada.\n");
            break;
        }
    }
}

void list_by_birthdate(s_pessoa v_pessoas[tam], int t_v_pessoas)
{
    int index1, index2;

    for (index1 = 0; index1 < t_v_pessoas; index1++) {
        for (index2 = index1 + 1; index2 < t_v_pessoas; index2++) {

            if (v_pessoas[index1].Ano > v_pessoas[index2].Ano ||
                (v_pessoas[index1].Ano == v_pessoas[index2].Ano &&
                 (v_pessoas[index1].Mes > v_pessoas[index2].Mes ||
                  (v_pessoas[index1].Mes == v_pessoas[index2].Mes &&
                   v_pessoas[index1].Dia > v_pessoas[index2].Dia)))) {
                position_swap(v_pessoas, index1, index2);
            }
        }
    }


    for (index1 = 0; index1 < t_v_pessoas; index1++) {
        printf("%d - %s, Data de Nascimento: %d/%d/%d\n", index1 + 1, v_pessoas[index1].Nome, v_pessoas[index1].Dia, v_pessoas[index1].Mes, v_pessoas[index1].Ano);
    }
    printf("\nLista Ordenada por Data de Nascimento Finalizada.\n");
}

void list_birthdays(s_pessoa v_pessoas[tam], int t_v_pessoas, int mes) 
{
    int index1; 

    if (mes >= 1 && mes <= 12) {
        for (index1 = 0; index1 < t_v_pessoas; index1++) {
            if (v_pessoas[index1].Mes == mes) {
                printf("%s - %d/%d/%d\n", v_pessoas[index1].Nome, v_pessoas[index1].Dia, v_pessoas[index1].Mes, v_pessoas[index1].Ano);
            }
        }
    }
    else {
        printf("\nMês inválido!\n"); 
    }
}

int starts_with(char str_1[tam], char str_2[tam]) {
    int i1 = 0, i2 = 0, starts_with;

    for (; str_1[i1] == str_2[i2] && str_1[i1] != '\0' && str_2[i2] != '\0'; i1++, i2++);

    if (str_2[i2] == '\0') { // Verifica se o segundo texto acabou
        starts_with = True;
    } else {
        starts_with = False;
    }
    return starts_with; 
}

void list_starts_with(s_pessoa v_pessoas[tam], int t_v_pessoas, char Chave[tam])
{
    int index_vp, starts;

    for (index_vp = 0; index_vp < t_v_pessoas; index_vp++) {
        if (v_pessoas[index_vp].ID != Desmatriculado) {
            starts = starts_with(v_pessoas[index_vp].Nome, Chave);
            if (starts == True) {
                printf("%s\n", v_pessoas[index_vp].Nome);
            }
        }

    }
}

//CADASTRAIS - Pessoas;
void name_input(s_pessoa v_pessoas[tam], int index)
{
    int nome_valido = False;
    while (nome_valido == False) {
        printf("\nNome: ");
        fgets(v_pessoas[index].Nome, tam,  stdin); 
        v_pessoas[index].Nome[strcspn(v_pessoas[index].Nome, "\n")] = '\0';

        nome_valido = valid_data_type_name(v_pessoas[index].Nome);
        if (nome_valido == True) {
            standardize_names(v_pessoas[index].Nome);
        }
        else {
            validation_error();
        }
    }
}

void cpf_input(s_pessoa v_pessoas[tam], int index)
{
    int cpf_valido = False, novo_cpf = True;
    while (cpf_valido == False) {
        printf("CPF: ");
        fgets(v_pessoas[index].CPF, tam,  stdin); 

        novo_cpf = verify_uniqueness_of_cpf(v_pessoas, index);
        if ( novo_cpf != False ) {

            cpf_valido = valid_CPF(v_pessoas[index].CPF);
            if(cpf_valido == False) {
                validation_error();
            }
            else {
                cpf_valido = True;
            }

        }
        else {
            printf("CPF já cadastrado. Digite um CPF válido.\n");
        }
    }
}

void gender_input(s_pessoa v_pessoas[tam], int index)
{
    int opsexo;
    printf("1 - Masculino\n2 - Feminino\n3 - Indefinido\nSexo: ");
    scanf("%d", &opsexo);
    limparBuffer();
    if(opsexo == 1){
        v_pessoas[index].genero = 'M';
    }
    else if(opsexo == 2){
        v_pessoas[index].genero = 'F';
    }
    else{
        v_pessoas[index].genero = 'I';
    }
}

void birth_input(s_pessoa v_pessoas[tam], int index)
{
    int data_valida = False;
    while (data_valida == False) {
        printf("Dia do nascimento: ");
        scanf("%d", &v_pessoas[index].Dia);  
        limparBuffer();
        printf("Mês do nascimento: ");
        scanf("%d", &v_pessoas[index].Mes);  
        limparBuffer();
        printf("Ano do nascimento: ");
        scanf("%d", &v_pessoas[index].Ano);  
        limparBuffer();

        data_valida = date_verify(v_pessoas[index].Dia, v_pessoas[index].Mes, v_pessoas[index].Ano); 

        if(data_valida == False) {
                printf("Digite uma data válida.\n");
        }
    }
}

void cadastro_pessoas(s_pessoa v_pessoas[tam], int index) //#Função de cadastro baseada na struct criada.
{
    name_input(v_pessoas, index); //Name input;

    cpf_input(v_pessoas, index); //CPF input;

    gender_input(v_pessoas, index); //Gender input;

    v_pessoas[index].ID = index + 1; //ID generated by the system based on the index summed with one to evite that starts with 0;

    birth_input(v_pessoas, index); //Birth input;

    v_pessoas[index].Atividade = True; //;
}

void atualizacao_pessoas(s_pessoa v_pessoas[tam], int index) //#Atualização de informções
{
    int modulo;
    modulo = op_atualization();
    switch(modulo) {
        case 1:     
            name_input(v_pessoas, index);
        break;

        case 2:
            cpf_input(v_pessoas, index);
        break;

        case 3:
            gender_input(v_pessoas, index);
        break;

        case 4:
            birth_input(v_pessoas, index);
        break;

        case 5: 
            if (v_pessoas[index].Atividade == 1) {
                v_pessoas[index].Atividade = Desmatriculado;
                printf("Cadastro desativado com sucesso.");
            } 
            else {
                v_pessoas[index].Atividade = 1;
                printf("Cadastro ativado com sucesso.");
            }
        default:
            printf("\nOpção inválida.\n");
        break;
    }
}

//Operações - Disciplinas 
void excessive_vacancies(s_disciplina v_disciplinas[tam], int t_v_disciplinas) 
{
    int index_alunos, index_disciplinas, cont_alunos;

    for (index_disciplinas = 0; index_disciplinas < t_v_disciplinas; index_disciplinas++) {
        cont_alunos = 0;
        for (index_alunos = 0; index_alunos < v_disciplinas[index_disciplinas].Tam_Alunos; index_alunos++) {
            if (v_disciplinas[index_disciplinas].Alunos[index_alunos] != Desmatriculado) {
                cont_alunos++;
            }
        }

        if (cont_alunos >= 40) {
            printf("%s: possui 40 ou mais alunos matriculados.", v_disciplinas[index_disciplinas].Nome);
        } 
    }
}

void list_discipline_no_class(s_disciplina v_disciplinas[tam], int t_v_disciplinas)
{
    int index;
    for (index = 0; index < t_v_disciplinas; index++) {
        printf("\n-----%s-----\n", v_disciplinas[index].Nome);
        printf("Disciplina: %s\n", v_disciplinas[index].Nome);
        printf("Código: %d\n\n", v_disciplinas[index].ID);
    }
}

void list_discipline_with_class(s_disciplina v_disciplinas[tam], int t_v_disciplinas, s_pessoa v_pessoas[tam], int t_v_pessoas)
{
    int index_D, index_A_D, Busca;

    for (index_D = 0; index_D < t_v_disciplinas; index_D++) {
        printf("\nNome: %s\n", v_disciplinas[index_D].Nome);
        printf("ID: %d\n", v_disciplinas[index_D].ID);
        printf("\nSemestre: %d\n", v_disciplinas[index_D].Semestre);
        printf("Alunos:\n\n");
        for (index_A_D = 0; index_A_D < v_disciplinas[index_D].Tam_Alunos; index_A_D++) {
            if (v_disciplinas[index_D].Alunos[index_A_D] != Desmatriculado) {
                Busca = existence_verify(v_pessoas, v_disciplinas[index_D].Alunos[index_A_D]);
                printf("Nome: %s", v_pessoas[Busca].Nome);
                printf("Matrícula: %d\n", v_disciplinas[index_D].Alunos[index_A_D]);
            }
        }
    }
}

//CADASTRAIS - Disciplinas;

//Inputs cadastrais - Disciplinas;
void name_input_d(s_disciplina v_disciplinas[tam], int index)
{
    int nome_valido = False; 
    while (nome_valido == False) {
        printf("\nNome da Disciplina: ");
        fgets(v_disciplinas[index].Nome, tam, stdin); 

        nome_valido = valid_data_type_name(v_disciplinas[index].Nome);

        if (nome_valido == True) {
            standardize_names(v_disciplinas[index].Nome);
        }
        else {
            validation_error();
        }
    }
}

void semester_input(s_disciplina v_disciplinas[tam], int index)
{
    int semestre_valido = False;
    while (semestre_valido == False) {
        printf("Semestre da disciplina: ");
        scanf("%d", &v_disciplinas[index].Semestre);
        limparBuffer();

        if (v_disciplinas[index].Semestre >= 1 && v_disciplinas[index].Semestre <= 12) {
            semestre_valido = True;
        }
        else {
            printf("Digite um semestre válido.");
        }
    }
}

void class_adittion_input(s_disciplina v_disciplinas[tam], int index, s_pessoa v_pessoas[tam], int t_v_pessoas)
{
    int continue_adicao = True, existence_in_folder, not_repeated_id, index1;
    for (index1 = 0; continue_adicao == True;) {
        printf("\n1 - Continuar\nOutro - Finalizar\nContinuar Adição de ALUNOS à discplina: "); 
        scanf("%d", &continue_adicao); 
        limparBuffer();
        if (continue_adicao == True) {

            existence_in_folder = False;
            not_repeated_id = False;

            printf("ID do aluno: "); 
            scanf("%d", &v_disciplinas[index].Alunos[index1]);
            limparBuffer();

            existence_in_folder = verify_in_people_folder(v_pessoas, t_v_pessoas, v_disciplinas[index].Alunos[index1]);

            if (existence_in_folder == True) {
                not_repeated_id = verify_people_id_in_vector(v_disciplinas, index, index1, 1);
            }

            if (existence_in_folder == False || not_repeated_id == False) {
                if (existence_in_folder == False) {
                    printf("\nCadastro não realizado. ID do aluno não existe.\n");
                }
                else {
                    printf("\nCadastro não realizado. Aluno já cadastrado.\n");
                }
            }
            else {
                index1++;
                printf("\nALUNOS - ID: %d Matriculado em %s com Sucesso!.\n", v_disciplinas[index].Alunos[index1], v_disciplinas[index].Nome);
            }
        }
        else {
            v_disciplinas[index].Tam_Alunos = index1;
            printf("\nMatrícula de ALUNOS finalizada.");
            break;
        }
    }
}

void teacher_adittion_input(s_disciplina v_disciplinas[tam], int index, s_pessoa v_pessoas[tam], int t_v_pessoas)
{
    int continue_adicao = True, existence_in_folder, not_repeated_id, index1;; 
    for (index1 = 0; continue_adicao == True;) {
        printf("\n1 - Continuar\nOutro - Finalizar\nContinuar Adição de PROFESSORES à discplina: "); 
        scanf("%d", &continue_adicao); 
        limparBuffer();
        if (continue_adicao == True) {

            existence_in_folder = False;
            not_repeated_id = False;

            printf("ID do Professor: "); 
            scanf("%d", &v_disciplinas[index].Professores[index1]);
            limparBuffer();

            existence_in_folder = verify_in_people_folder(v_pessoas, t_v_pessoas, v_disciplinas[index].Professores[index1]);

            if (existence_in_folder == True) {
                not_repeated_id = verify_people_id_in_vector(v_disciplinas, index, index1, 1);
            }

            if (existence_in_folder == False || not_repeated_id == False) {
                if (existence_in_folder == False) {
                    printf("\nCadastro não realizado. ID do Professor não existe.\n");
                }
                else {
                    printf("\nCadastro não realizado. Professor já cadastrado.\n");
                }
            }
            else {
                index1++;
                printf("\nPROFESSORES - ID: %d Matriculado em %s com Sucesso!.\n", v_disciplinas[index].Professores[index1], v_disciplinas[index].Nome);
            }
        }
        else {
            v_disciplinas[index].Tam_Professor = index1;
            printf("\nMatrícula de PROFESSORES finalizada.");
            break;
        }
    }
}

void exclude_people_of_discipline(s_disciplina v_disciplinas[tam], int index)
{
    int continuar = True, aluno = 1, professor = 0, exists, pasta, id;
    while (continuar == True) {
                continuar = continue_operation(); 
                if (continuar == True) {
                    printf("1. Aluno\nOutro. Professor\nDeseja remover em qual pasta: ");
                    scanf("%d", &pasta);

                    if (pasta == 1) {
                        while (exists == -1) {
                            printf("Digite o ID que deseja remover da disciplina: ");
                            scanf("%d", &id);

                            exists = search_people_in_vector(v_disciplinas, index, id, v_disciplinas[index].Tam_Alunos, aluno);
                        }
                        v_disciplinas[index].Alunos[exists] = Desmatriculado;
                        printf("Aluno removido da disciplina com sucesso.\n");
                    }
                    else {
                        while (exists == -1) {
                            printf("Digite o ID que deseja remover da disciplina: ");
                            scanf("%d", &id);

                            exists = search_people_in_vector(v_disciplinas, index, id, v_disciplinas[index].Tam_Professor, professor);
                        }
                        v_disciplinas[index].Professores[exists] = Desmatriculado;
                        printf("Professor removido da disciplina com sucesso.\n");
                    }
                }
                else {
                    printf("\nRemoção encerrada.\n");
                    break;
                }
            }
}

void cadastro_disciplinas(s_disciplina v_disciplinas[tam], s_pessoa v_alunos[tam], int tam_alunos, s_pessoa v_professores[tam], int tam_professores, int index)
{
    name_input_d(v_disciplinas, index); //Name input;

    semester_input(v_disciplinas, index); //Semester input;

    v_disciplinas[index].ID = index + 1; //ID generated by the system based on the index summed with one to evite that starts with 0;

    printf("Olá! Você está no espaço para matrícula de ALUNOS na Disciplina - %s\n", v_disciplinas[index].Nome);
    class_adittion_input(v_disciplinas, index, v_alunos, tam_alunos); //Class addition in discipline;

    printf("Olá! Você está no espaço para matrícula de PROFESSORES na Disciplina - %s\n", v_disciplinas[index].Nome);
    teacher_adittion_input(v_disciplinas, index, v_professores, tam_professores); //Teachers addition in discipline;

    v_disciplinas[index].Atividade = 1; //;
}

void atualizacao_disciplinas(s_disciplina v_disciplinas[tam], s_pessoa v_alunos[tam], s_pessoa v_professores[tam], int index)
{
    int nome_valido = False, semestre_valido = False, new_id = False, atividade;
    int aluno = 1, professor = 0;
    int continuar = True, exists = -1;
    int alteracao, mat, pasta;

    printf("1. Nome da Disciplina\n2. Semestre\n3. Remover Matrícula\n4. Disponibilidade da Disciplina\nAtualização: ");
    scanf("%d", &alteracao);

    switch (alteracao) {
        case 1:
            name_input_d(v_disciplinas, index);
        break;
        case 2:
            semester_input(v_disciplinas, index); 
        break;
        case 3:
            exclude_people_of_discipline(v_disciplinas, index);
        break;
        case 4: 
            if (v_disciplinas[index].Atividade == 1) {
                v_disciplinas[index].Atividade = Desmatriculado;
                printf("Cadastro desativado com sucesso.");
            } 
            else {
                v_disciplinas[index].Atividade = 1;
                printf("Cadastro ativado com sucesso.");
            }
        break;
        default:
            printf("\nOpção inválida.\n");
        break;
    }
}

//#Código principal.
int main(void)
{
  s_pessoa v_alunos[tam]; //#Vetor de structs para alunos.
  s_pessoa v_professores[tam]; //#Vetor de structs para professores.
  s_disciplina v_disciplinas[tam]; //#Vetor de structs para disciplinas.
  int qtd_alunos, qtd_professores, qtd_disciplinas; //#Verificadores do tamanho.
  int continuar, continuar_area, continuar_op, continue_atualizacao_pessoas, continue_exclusao, continue_busca_por_chave, listar_aniversariantes, op_list; //#Constância de menus.
  int opcao_menu, opcao_area, opcao_operacao, mes_aniversariantes; //#Acesso a áreas e operações.
  int buscar, existencia, index_busca; //#Achar/Verificar cadastros.
  int tipo_relacao, continue_listar; //Função listar
  int i; //#Auxiliares básicos. 
  int modulo_alteracao, validade_chave;
  int ID, Existe;
  char Chave[tam];

  //Laço constante para oferecimento de opções, sair apenas quando o usuário permitir.

  continuar = True;
  qtd_alunos = 0;
  qtd_professores = 0;
  qtd_disciplinas = 0;
  //#Menu principal.
  while (continuar == True) {
    opcao_menu = choose_modulo();
    printf("\n");

    if (opcao_menu == 1) { //#Área do Aluno.
        continuar_area = True; 
        //#Menu para operações em pasta de alunos.
        while (continuar_area == True) {
          opcao_area = modulo_operations_pessoas();
          printf("\n"); 
          switch (opcao_area) {
            case 1: //#Cadastro de alunos.
              continuar_op = True;
              for (i = qtd_alunos; i < tam && continuar_op == True; i++){

                  continuar_op = continue_operation();
                  if (continuar_op == False) {
                      qtd_alunos = i; 
                      printf("\nCadastro de alunos encerrado.\n\n");
                  }
                  else if (continuar_op == True) {
                    cadastro_pessoas(v_alunos, i);
                    printf("\n");
                  }
                  else {
                    printf("Opção inválida.\n"); 
                  }
             }
             break;
            case 2: //#Atualizar alunos.
              continuar_op = True;
              while (continuar_op == True) {
                  continuar_op = continue_operation();
                  if (continuar_op == False) {
                    printf("Atualização encerrada.\n\n");
                  }
                  else if (continuar_op == True) {
                    printf("\nDigite o ID do aluno: ");
                    scanf("%d", &ID);

                    Existe = existence_verify(v_alunos, ID);

                    if (Existe != -1) {
                        atualizacao_pessoas(v_alunos, Existe);
                    }
                    else {
                        printf("Aluno não existe.\n");
                    }
                  }
                  else {
                    printf("Opção inválida\n");
                  }
              }
            break;
            case 3: //#Excluir aluno
              continue_exclusao = True; 
              while (continue_exclusao == True) {
                    continue_exclusao = continue_operation();

                    if (continue_exclusao == False) {
                        printf("Exclusão de alunos encerrada.\n\n");
                    }
                    else if (continue_exclusao == True) {
                        printf("\nDigite o ID do aluno: ");
                        scanf("%d", &ID);

                        Existe = existence_verify(v_alunos, ID);

                        if (Existe != -1) {
                            v_alunos[Existe].Atividade = Desmatriculado;
                            printf("Exclusão efetuada com sucesso.\n\n");
                        } 
                        else {
                            printf("Aluno não existe.\n");
                        }
                    }
                    else {
                        printf("Opção inválida.\n"); 
                    }
              }
            break;
            case 4: //#Listar alunos.
                continue_listar = True;
                while (continue_listar == True) {
                    continue_listar = continue_operation();

                    if (continue_operation == False) {
                        printf("\nRelação de alunos encerrada.\n");
                    }
                    else if (continue_listar == True) {
                        tipo_relacao = True;
                        while (tipo_relacao == True || tipo_relacao == 2 || tipo_relacao == 3) {
                                printf("\n1 - Alfabética\n2 - Sexo\n3 - Data de Nascimento\nOutro - Sair\nQue tipo de relação deseja listar: ");
                                scanf("%d", &tipo_relacao);
                                switch (tipo_relacao) {
                                    case 1:
                                        list_alphabetically(v_alunos, qtd_alunos);
                                    break;
                                    case 2:
                                        list_by_gender(v_alunos, qtd_alunos);
                                    break;
                                    case 3:
                                        list_by_birthdate(v_alunos, qtd_alunos);
                                    break;
                                    default:
                                        printf("Opção inválida. Menu encerrado.");
                                    break;
                                }
                        }
                    }
                    else {
                        printf("Opção inválida.\n");
                    }
                }
            break;
            case 5: //Aniversariante do Mês
                listar_aniversariantes = True;
                while (listar_aniversariantes == True) {
                    listar_aniversariantes = continue_operation();
                    if (listar_aniversariantes == False) {
                        printf("Listagem de Alunos Aniversariantes do Mês encerrada.\n\n");
                    }
                    else if (listar_aniversariantes == True) {
                        printf("\nDigite o mês que deseja listar: ");
                        scanf("%d", &mes_aniversariantes);
                        list_birthdays(v_alunos, qtd_alunos, mes_aniversariantes);

                    }
                    else {
                        printf("Opção inválida.\n"); 
                    }

                }
            break;
            case 6:
                printf("Chave: ");
                fgets(Chave, tam, stdin);
                Chave[strcspn(Chave, "\n")] = '\0';

                validade_chave = valid_data_type_name(Chave);

                if (validade_chave == True) {
                    standardize_names(Chave);
                    printf("\nResultados para '%s' em ALUNOS:\n", Chave);
                    list_starts_with(v_alunos, qtd_alunos, Chave);
                }
                else {
                    printf("\nDIGITE APENAS LETRAS E ESPAÇOS\n");
                }
            break;
            case 7: //#Sair.
                printf("Voltando ao menu principal.\n\n");
                continuar_area = False;
            break;
          }
        }
    }
    else if (opcao_menu == 2) {
        continuar_area = True; 
        //#Menu para operações em pasta de professores.
        while (continuar_area == True) {
            opcao_area = modulo_operations_pessoas();
            printf("\n"); 

            switch(opcao_area){
                case 1: //#Cadastro de professores.
                    continuar_op = True;
                    for (i = qtd_professores; i<tam && continuar_op == True; i++){

                        continuar_op = continue_operation();
                        if (continuar_op == False) {
                            qtd_professores = i; 
                            printf("Cadastro de professores encerrado.\n\n");
                        }
                        else if (continuar_op == True) {
                            cadastro_pessoas(v_professores, i);
                            printf("\n");
                        }
                        else{
                            printf("Opção inválida.\n"); 
                        }
                    }
                break;
                case 2: //#Atualizar professores.
                    continuar_op = True;
                    while (continuar_op == True) {

                        continuar_op = continue_operation();
                        if (continuar_op == False) {

                            printf("Atualização encerrada.\n\n");

                        }
                        else if (continuar_op == True) {

                            printf("Digite o ID do professor: ");
                            scanf("%d", &ID);

                            Existe = existence_verify(v_professores, ID);

                            if (Existe != -1) {
                                atualizacao_pessoas(v_professores, Existe);
                            }
                            else {
                                printf("Professor não existe.\n");
                            }
                        }
                        else {
                            printf("Opção inválida\n");
                        }
                    }
                break;
                case 3: //#Excluir professor
                    continue_exclusao = True; 
                    while (continue_exclusao == True) {
                        continue_exclusao = continue_operation();

                        if (continue_exclusao == False) {
                            printf("Exclusão de professores encerrada.\n\n");
                        }
                        else if (continue_exclusao == True) {
                            printf("Digite o ID do professor: ");
                            scanf("%d", &ID);

                            Existe = existence_verify(v_professores, ID);

                            if (Existe != -1) {
                                v_alunos[Existe].Atividade = 0;
                                printf("Exclusão efetuada com sucesso.\n\n");
                            } 
                            else {
                                printf("Professor não existe.\n");
                            }
                        }
                        else {
                            printf("Opção inválida.\n"); 
                        }
                    }
                break;
                case 4: //#Listar Professores.
                    continue_listar = True;
                    while (continue_listar == True) {
                        continue_listar = continue_operation();

                        if (continue_operation == False) {
                            printf("\nRelação de professores encerrada.\n");
                        }
                        else if (continue_listar == True) {
                            tipo_relacao = True;
                            while (tipo_relacao == True || tipo_relacao == 2 || tipo_relacao == 3) {
                                printf("\n1 - Alfabética\n2 - Sexo\n3 - Data de Nascimento\nOutro - Sair\n\nQue tipo de relação deseja listar: ");
                                scanf("%d", &tipo_relacao);
                                switch (tipo_relacao) {
                                    case 1:
                                        list_alphabetically(v_professores, qtd_professores);
                                    break;
                                    case 2:
                                        list_by_gender(v_professores, qtd_professores);
                                    break;
                                    case 3:
                                        list_by_birthdate(v_alunos, qtd_alunos);
                                    break;
                                    default:
                                        printf("Opção inválida. Menu encerrado.");
                                    break;
                                }
                            }
                        }
                        else {
                            printf("Opção inválida.\n");
                        }
                        }
                break;
                case 5: //Aniversariante do Mês
                    listar_aniversariantes = True;
                    while (listar_aniversariantes == True) {
                        listar_aniversariantes = continue_operation();
                        if (listar_aniversariantes == False) {
                            printf("Listagem de Professores  Aniversariantes do Mês encerrada.\n\n");
                        }
                        else if (listar_aniversariantes == True) {
                            printf("\nDigite o mês que deseja listar: ");
                            scanf("%d", &mes_aniversariantes);
                            list_birthdays(v_professores, qtd_professores, mes_aniversariantes);

                        }
                        else {
                            printf("Opção inválida.\n"); 
                        }

                    }
                break;
                case 6:
                    printf("Chave: ");
                    fgets(Chave, tam, stdin);
                    Chave[strcspn(Chave, "\n")] = '\0';

                    validade_chave = valid_data_type_name(Chave);

                    if (validade_chave == True) {
                        standardize_names(Chave);
                        printf("\nResultados para '%s' em PROFESSORES:\n", Chave);
                        list_starts_with(v_professores, qtd_professores, Chave);
                    }
                    else {
                        printf("\nDIGITE APENAS LETRAS E ESPAÇOS\n");
                    }
                break;
                case 7: //#Sair.
                    printf("Voltando ao menu principal.\n\n");
                    continuar_area = False;
                break;
            }
        }
    }
    else if (opcao_menu == 3) {
        continuar_area = True; 
        //#Menu para operações em pasta de disciplinas.
        while (continuar_area == True) {
            opcao_area = modulo_operations_disciplinas();
            printf("\n"); 

            switch(opcao_area){
                case 1: //#Cadastro de disciplinas.

                    continuar_op = True;
                    for (i = qtd_disciplinas; i < tam && continuar_op == True; i++){

                        continuar_op = continue_operation();
                        if(continuar_op == False){
                            qtd_disciplinas = i; 
                            printf("\nCadastro de professores encerrado.\n\n");
                        }
                        else if(continuar_op == True){
                            cadastro_disciplinas(v_disciplinas, v_alunos, qtd_alunos, v_professores, qtd_professores, i);
                            printf("\n");
                        }
                        else{
                            printf("Opção inválida.\n"); 
                        }
                    }
                break;
                case 2: //#Atualizar disciplinas.
                    continuar_op = True;
                    while (continuar_op == True) {

                        continuar_op = continue_operation();
                        if (continuar_op == False) {

                            printf("\nAtualização encerrada.\n\n");

                        }
                        else if (continuar_op == True) {

                            printf("\nDigite o ID da disciplina: ");
                            scanf("%d", &ID);

                            Existe = existence_verify_discipline(v_disciplinas, ID);

                            if (Existe != -1) {
                                atualizacao_disciplinas(v_disciplinas, v_alunos, v_professores, Existe);
                            }
                            else {
                                printf("\nDisciplina não existe.\n\n");
                            }
                        }
                        else {
                            printf("\nOpção inválida\n");
                        }
                    }
                break;
                case 3: //#Excluir disciplina
                    continue_exclusao = True; 
                    while (continue_exclusao == True) {
                        continue_exclusao = continue_operation();

                        if (continue_exclusao == False) {
                            printf("\nExclusão de disciplinas encerrada.\n\n");
                        }
                        else if (continue_exclusao == True) {
                            printf("\nDigite o ID da disciplina: ");
                            scanf("%d", &ID);

                            Existe = existence_verify_discipline(v_disciplinas, ID);

                            if (Existe != -1) {
                                v_disciplinas[Existe].Atividade = Desmatriculado;
                                printf("\nExclusão efetuada com sucesso.\n\n");
                            } 
                            else {
                                printf("\nDisciplina não existe.\n");
                            }
                        }
                        else {
                            printf("\nOpção inválida.\n"); 
                        }
                    }
                break;
                case 4: //#Listar disciplnas.
                    continue_listar = True;
                    while (continue_listar == True) {
                        continue_listar = continue_operation();
                        if (continue_listar != True) {
                            printf("\n\nListagem de disciplinas encerrada.\n\n");
                            break;
                        }
                        else {
                            printf("\n1. Com Alunos\n2. Sem Alunos\n3. Disciplinas com mais que 40 Alunos\nComo deseja listar as disciplinas?: ");
                            scanf("%d", &op_list);
                            switch (op_list) {
                                case 1:
                                    list_discipline_with_class(v_disciplinas, qtd_disciplinas, v_alunos, qtd_alunos);
                                break;
                                case 2:
                                    list_discipline_no_class(v_disciplinas, qtd_disciplinas);
                                break;
                                case 3:
                                    excessive_vacancies(v_disciplinas, qtd_disciplinas);
                                break;
                                default:
                                    printf("\nListagem Encerrada\n.");
                                break;
                            }
                            if (op_list > 3 || op_list <= 0) {
                                break;
                            }
                        }
                    }
                break;
                case 5:
                    printf("\nAlunos Matrículados em Mens que 3 Disciplinas:\n");
                    less_than_three(v_alunos, v_disciplinas, qtd_alunos, qtd_disciplinas);
                break;
                case 6: //#Sair.
                    printf("Voltando ao menu principal.\n\n");
                    continuar_area = False;
                break;
            }
        }
    }
    else{
        printf("Opção inválida.\n\n");
    }

  }

}