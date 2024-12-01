#include "recursos.h"

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
                                      list_by_birthdate(v_professores, qtd_professores);
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