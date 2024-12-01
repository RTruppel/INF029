k//Bibliotecas
#include <stdio.h>
#include <string.h>

//headers
#include "structs.h"

//Definições
#define tam 100
#define False 0
#define True 1
#define Desmatriculado -1

//Limpa Buffer
void limparBuffer();

//Exibições
int choose_modulo();

int modulo_operations_pessoas();

int modulo_operations_disciplinas();

int continue_operation();

int op_atualization();

int continue_or_cancel();

void validation_error();

//Verificações de Entrada
int valid_data_type_name(char string[tam]);

int valid_CPF(char string[tam]);

int date_verify(int dd, int mm, int yy);

//Pré-Processamento
void standardize_names(char string[tam]);

//Buscas relativas à Pessoas
int existence_verify(s_pessoa v_pessoas[tam], int ID);

int search_index(s_pessoa v_pessoas[tam], int busca);

int verify_uniqueness_of_cpf(s_pessoa v_pessoas[tam], int index);

int verify_in_people_folder(s_pessoa v_pessoas[tam], int t_v_pessoas, int ID);

//Buscas relativas à Disciplinas

int verify_people_id_in_vector(s_disciplina v_disciplinas[tam], int index_disciplina, int index_pessoa, int classe_pessoa);

int search_people_in_vector(s_disciplina *v_disciplinas, int index_disciplina, int ID, int QTD, int tipo_pessoa);

int existence_verify_discipline(s_disciplina v_disciplinas[tam], int ID);

int verify_uniqueness_of_id_disciplines(s_disciplina v_disciplinas[tam], int index);

int verify_in_discipline_folder(s_pessoa v_disciplinas[tam], int t_v_disciplinas, int ID);

//Processamento
void position_swap(s_pessoa v_pessoas[tam], int index_1, int index_2);

//Operações - Pessoas
void exclusion(s_pessoa v_pessoas[tam], int index);

void less_than_three(s_pessoa v_alunos[tam], s_disciplina v_disciplinas[tam], int t_v_alunos, int t_v_disciplinas);



// Listagem Pessoas
void list_alphabetically(s_pessoa v_pessoas[tam], int t_v_pessoas);

void list_by_gender(s_pessoa v_pessoas[tam], int t_v_pessoas);

void list_by_birthdate(s_pessoa v_pessoas[tam], int t_v_pessoas);

void list_birthdays(s_pessoa v_pessoas[tam], int t_v_pessoas, int mes);

int starts_with(char str_1[tam], char str_2[tam]);

void list_starts_with(s_pessoa v_pessoas[tam], int t_v_pessoas, char Chave[tam]);

//Operações - Disciplinas 
void excessive_vacancies(s_disciplina v_disciplinas[tam], int t_v_disciplinas);

void list_discipline_no_class(s_disciplina v_disciplinas[tam], int t_v_disciplinas);

void list_discipline_with_class(s_disciplina v_disciplinas[tam], int t_v_disciplinas, s_pessoa v_pessoas[tam], int t_v_pessoas);

//CADASTRAIS - Pessoas;
void name_input(s_pessoa v_pessoas[tam], int index);

void cpf_input(s_pessoa v_pessoas[tam], int index);

void gender_input(s_pessoa v_pessoas[tam], int index);

void birth_input(s_pessoa v_pessoas[tam], int index);

void cadastro_pessoas(s_pessoa v_pessoas[tam], int index);

void atualizacao_pessoas(s_pessoa v_pessoas[tam], int index);

//CADASTRAIS - Disciplinas;
void name_input_d(s_disciplina v_disciplinas[tam], int index);

void semester_input(s_disciplina v_disciplinas[tam], int index);

void class_adittion_input(s_disciplina v_disciplinas[tam], int index, s_pessoa v_pessoas[tam], int t_v_pessoas);

void teacher_adittion_input(s_disciplina v_disciplinas[tam], int index, s_pessoa v_pessoas[tam], int t_v_pessoas);

void exclude_people_of_discipline(s_disciplina v_disciplinas[tam], int index);

void cadastro_disciplinas(s_disciplina v_disciplinas[tam], s_pessoa v_alunos[tam], int tam_alunos, s_pessoa v_professores[tam], int tam_professores, int index);

void atualizacao_disciplinas(s_disciplina v_disciplinas[tam], s_pessoa v_alunos[tam], s_pessoa v_professores[tam], int index);




