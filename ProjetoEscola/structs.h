#define tam 100

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