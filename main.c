#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINESIZE 200
#define _CRT_SECURE_NO_WARNINGS 1

/*
 grupo:duarte olival nr:21701080
 Joao martins nr:21701951
 Andre Vieira nr:21701639
 */

struct Empresa{
        int ID;
        int Acompanhantes;
        char Tipo[11];
        int Entrada;
        int Saida;
        int Servico;
};
struct Empresa pessoas[100];
int quantidadePessoas=0;

int verificarSeValorInteiro(float valor) {
    if (valor == (int) valor) {  //casting da variável para inteiro
        return 1; // Caso seja inteiro, retorna 1
    } else {
        return 0; // Caso nao seja inteiro, retorna 0
    }
}


void escreveFicheirosOutput() { //Funcao que escreve as estatisticas para os ficheiros pedidos no enunciado

        FILE *fp;
        int i;

        if ((fp = fopen("estatisticas.txt", "w")) == NULL) {
            printf("ERRO A ABRIR O FICHEIRO DAS ESTATISTICAS \n");
            exit(1);
        }
/*acabar o que escrever no ficheiro estatisticas.txt
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    fprintf(fp,"%d\n", );
    */



    fclose(fp);

}



void LerFicheiroImput() {
    struct Empresa pessoas[100];
    int indice = 0;
    char teste[MAXLINESIZE];
    char *auxiliar[6] = {0};
    char *pointer;
    FILE *Imput;

    if((Imput=fopen("input.txt", "r"))==NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
        exit(1);
    }
    while (!feof(Imput)){   //feof le o ficheiro ate ao fim;retorna 0 se chegar ao fim
        if(fgets(teste, MAXLINESIZE, Imput)==NULL){
            break;//fim do ficheiro
        }
        pointer = strtok(teste,";");
        while (pointer!=NULL){
            if(indice ==1 && (pointer=="visitante"||pointer=="diretor"||pointer=="funcionario")){
                auxiliar[indice]="NULL";
                indice++;
            }else {
                auxiliar[indice] = pointer;
                pointer = strtok(NULL, ";");
                indice++;
            }
        }
        pessoas[quantidadePessoas].ID=isdigit(auxiliar[0]);
        pessoas[quantidadePessoas].Acompanhantes=(int)auxiliar[1];
        strcpy(pessoas[quantidadePessoas].Tipo, auxiliar[2]);
        pessoas[quantidadePessoas].Entrada=(int)auxiliar[3];
        pessoas[quantidadePessoas].Saida=(int)auxiliar[4];
        pessoas[quantidadePessoas].Servico=(int)auxiliar[5];
        quantidadePessoas++;
    }
}

int linha1(void){
    int i, pessoasValidas=0,ID,Tipo,Acompanhantes,Entrada,Saida,Servico;
    for(i=0;i<100;i++){
        ID=0,Tipo=0,Acompanhantes=0,Entrada=0,Saida=0,Servico=0;
        if(pessoas[i].ID>0) {
            ID += verificarSeValorInteiro(pessoas[i].ID);
            if (pessoas[i].Tipo == "visitante" || pessoas[i].Tipo == "diretor" || pessoas[i].Tipo == "funcionario") {
                Tipo++;
                if (pessoas[i].Acompanhantes>=0 && (pessoas[i].Tipo=="funcionario" || pessoas[i].Tipo == "diretor" )) {
                    Acompanhantes += verificarSeValorInteiro(pessoas[i].Acompanhantes);
                }

                if (pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida >= 0 && pessoas[i].Saida <= 24){
                    Entrada += verificarSeValorInteiro(pessoas[i].Entrada);
                    Saida += verificarSeValorInteiro(pessoas[i].Saida);

                    if (pessoas[i].Servico > 0) {
                        for (int pos = 0; pos < 100; pos++) {
                            if (pessoas[pos].ID == pessoas[i].Servico) {
                                Servico++;
                                break;
                            }
                        }
                        if (ID == 1 && Tipo == 1 && Acompanhantes == 1 && Entrada == 1 && Saida == 1 && Servico == 1) {
                            pessoasValidas++;
                        }
                    }
                }
            }
        }
    }
    printf("linhas validas= %d", pessoasValidas);
}

int linha2(void){
    int i,VisitantesValidos=0,ID,Tipo,EntradaSaida,Servico;
        for(i=0;i<100;i++) {
            ID = 0, Tipo = 0, EntradaSaida=0, Servico = 0;
            if (pessoas[i].Tipo == "visitante" && pessoas[i].Acompanhantes == NULL) {
                Tipo++;
                if (pessoas[i].ID > 0) {
                    ID += verificarSeValorInteiro(pessoas[i].ID);
                    if (pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida >= 0 &&
                        pessoas[i].Saida <= 24) {
                        EntradaSaida = verificarSeValorInteiro(pessoas[i].Entrada) + verificarSeValorInteiro(pessoas[i].Saida);
                        if (pessoas[i].Servico > 0) {
                            for (int pos = 0; pos < 100; pos++) {
                                if (pessoas[pos].ID == pessoas[i].Servico) {
                                    Servico++;
                                    break;
                                }
                            }
                            if (ID == 1 && Tipo == 1 && EntradaSaida==2 && Servico == 1) {
                                VisitantesValidos++;
                            }
                        }
                    }
                }
            }
        }
    printf("visitantes validos= %d", VisitantesValidos);

    return 0;
}

int linha3(void) {
    int i, funcionariosValidos = 0, ID, EntradaSaida,Acompanhantes=0, Servico;
    for (i = 0; i < 100; i++) {
        ID = 0, EntradaSaida = 0, Servico = 0;
        if ((pessoas[i].Tipo == "diretor" || pessoas[i].Tipo == "funcionario") && pessoas[i].Acompanhantes>=0) {
            Acompanhantes += verificarSeValorInteiro(pessoas[i].Acompanhantes);
            if (pessoas[i].ID > 0) {
                ID += verificarSeValorInteiro(pessoas[i].ID);
                if (pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida >= 0 &&
                    pessoas[i].Saida <= 24) {
                    EntradaSaida =
                            verificarSeValorInteiro(pessoas[i].Entrada) + verificarSeValorInteiro(pessoas[i].Saida);
                    if (pessoas[i].Servico > 0) {
                        for (int pos = 0; pos < 100; pos++) {
                            if (pessoas[pos].ID == pessoas[i].Servico) {
                                Servico++;
                                break;
                            }
                        }
                        if (ID == 1 && Acompanhantes == 1 && EntradaSaida == 2 && Servico == 1) {
                            funcionariosValidos++;
                        }
                    }
                }
            }
        }
    }
    printf("Todos funcionarios validos= %d", funcionariosValidos);

    return 0;
}


int linha4(void){
    int i, funcionariosValidos = 0, ID, EntradaSaida,Acompanhantes=0, Servico;
    for (i = 0; i < 100; i++) {
        ID = 0, EntradaSaida = 0, Servico = 0;
        if ((pessoas[i].Tipo == "funcionario") && pessoas[i].Acompanhantes>=0) {
            Acompanhantes += verificarSeValorInteiro(pessoas[i].Acompanhantes);
            if (pessoas[i].ID > 0) {
                ID += verificarSeValorInteiro(pessoas[i].ID);
                if (pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida >= 0 &&
                    pessoas[i].Saida <= 24) {
                    EntradaSaida =
                            verificarSeValorInteiro(pessoas[i].Entrada) + verificarSeValorInteiro(pessoas[i].Saida);
                    if (pessoas[i].Servico > 0) {
                        for (int pos = 0; pos < 100; pos++) {
                            if (pessoas[pos].ID == pessoas[i].Servico) {
                                Servico++;
                                break;
                            }
                        }
                        if (ID == 1 && Acompanhantes == 1 && EntradaSaida == 2 && Servico == 1) {
                            funcionariosValidos++;
                        }
                    }
                }
            }
        }
    }
    printf("funcionarios validos= %d", funcionariosValidos);

    return 0;
}

int linha5(void){
    int i, diretorValidos = 0, ID, EntradaSaida,Acompanhantes=0, Servico;
    for (i = 0; i < 100; i++) {
        ID = 0, EntradaSaida = 0, Servico = 0;
        if ((pessoas[i].Tipo == "diretor") && pessoas[i].Acompanhantes>=0) {
            Acompanhantes = verificarSeValorInteiro(pessoas[i].Acompanhantes);
            if (pessoas[i].ID > 0) {
                ID += verificarSeValorInteiro(pessoas[i].ID);
                if (pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida >= 0 &&
                    pessoas[i].Saida <= 24) {
                    EntradaSaida = verificarSeValorInteiro(pessoas[i].Entrada) + verificarSeValorInteiro(pessoas[i].Saida);
                    if (pessoas[i].Servico > 0) {
                        for (int pos = 0; pos < 100; pos++) {
                            if (pessoas[pos].ID == pessoas[i].Servico) {
                                Servico++;
                                break;
                            }
                        }
                        if (ID == 1 && Acompanhantes == 1 && EntradaSaida == 2 && Servico == 1) {
                            diretorValidos++;
                        }
                    }
                }
            }
        }
    }
    printf("dirteores validos= %d", diretorValidos);

    return diretorValidos;
}

int linha6(void){
    int i, funcionarioNaEmpresa = 0, ID, EntradaSaida=0,Acompanhantes=0, Servico;
    for (i = 0; i < 100; i++) {
        ID = 0, Servico = 0;
        if ((pessoas[i].Tipo == "funcionario" && pessoas[i].Tipo == "diretor") && pessoas[i].Acompanhantes>=0) {
            Acompanhantes = verificarSeValorInteiro(pessoas[i].Acompanhantes);
            if (pessoas[i].ID > 0) {
                ID += verificarSeValorInteiro(pessoas[i].ID);
                if (pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida==0) {
                    EntradaSaida = verificarSeValorInteiro(pessoas[i].Entrada) + verificarSeValorInteiro(pessoas[i].Saida);
                    if (pessoas[i].Servico > 0) {
                        for (int pos = 0; pos < 100; pos++) {
                            if (pessoas[pos].ID == pessoas[i].Servico) {
                                Servico++;
                                break;
                            }
                        }
                        if (ID == 1 && Acompanhantes == 1 && EntradaSaida == 2 && Servico == 1) {
                            funcionarioNaEmpresa++;
                        }
                    }
                }
            }
        }
    }
    printf("todos os funcionarios ainda na empresa= %d", funcionarioNaEmpresa);

    return funcionarioNaEmpresa;
}

int linha7(void){
    int i,VisitantesNaEmpresa=0,ID,Tipo,EntradaSaida,Servico;
    for(i=0;i<100;i++) {
        ID = 0, Tipo = 0, EntradaSaida=0, Servico = 0;
        if (pessoas[i].Tipo == "visitante" && pessoas[i].Acompanhantes == NULL) {
            Tipo++;
            if (pessoas[i].ID > 0) {
                ID += verificarSeValorInteiro(pessoas[i].ID);
                if (pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida >= 0 &&
                    pessoas[i].Saida <= 24) {
                    EntradaSaida = verificarSeValorInteiro(pessoas[i].Entrada) + verificarSeValorInteiro(pessoas[i].Saida);
                    if (pessoas[i].Servico > 0) {
                        for (int pos = 0; pos < 100; pos++) {
                            if (pessoas[pos].ID == pessoas[i].Servico) {
                                Servico++;
                                break;
                            }
                        }
                        if (ID == 1 && Tipo == 1 && EntradaSaida==2 && Servico == 1) {
                            VisitantesNaEmpresa++;
                        }
                    }
                }
            }
        }
    }
    printf("Todos os visitantes na empresa= %d", VisitantesNaEmpresa);

    return VisitantesNaEmpresa;
}

int linha8(void){

    int visitantesNaEmpresa = linha7();
    int funcionarioNaEmpresa = linha6();
    int diretoresNaEmpresa = linha5();

    int pessoasEmpresa = funcionarioNaEmpresa + diretoresNaEmpresa;

    printf("Todas as pessoas na empresa = %d\n", pessoasEmpresa);
    printf("Todos os visitantes na empresa = %d", visitantesNaEmpresa);

    return 0;
}

int linha9(void){
    int numeroDeFuncionarios = 0;
    for( int i = 0; i < 100 ; i++){
        if(pessoas[i].ID > 0 && verificarSeValorInteiro(pessoas[i].ID == 0){
            if(pessoas[i].Tipo == "funcionario" || pessoas[i].Tipo == "diretor"){
                if(pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida >= 0 && pessoas[i].Saida <= 24){
                    if(verificarSeValorInteiro(pessoas[i].Entrada == 0 && pessoas[i].Saida == 0)){
                        numeroDeFuncionarios ++;
                    }
                }
            }
        }
    }

    printf("Entraram e sairam %d funcionários da empresa", numeroDeFuncionarios);

    return 0;
}

int linha10(void){

     int pessoasInvalidas = 0, ID , Tipo , Servico;
        for( int i=0 ; i < 100 ; i++){

            if(verificarSeValorInteiro(pessoas[i].ID) == 0 ) {
                 pessoasInvalidas ++;
            }
            if (pessoas[i].Tipo != "visitante" || pessoas[i].Tipo != "diretor" || pessoas[i].Tipo != "funcionario") {
                    pessoasInvalidas ++;
            }

            if(verificarSeValorInteiro(pessoas[i].Servico) == 0){
                pessoasInvalidas ++;
            }
        }
        printf("Foram barradas à entrada %d\n", pessoasInvalidas);

        return 0;
}
int linha11(void){
    int horasDentroEmpresa = 0;
    for( int i = 0; i < 100 ; i++){
        if(pessoas[i].Tipo == "funcionario"){
            if(pessoas[i].ID > 0){
                ID = verificarSeValorInteiro(pessoas[i].ID);

                if (pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida >= 0 && pessoas[i].Saida <= 24) {
                    horasDentroEmpresa += (verificarSeValorInteiro(pessoas[i].Saida) - verificarSeValorInteiro(pessoas[i].Entrada));

                    }
            }
        }
    }
    printf("As pessoas do tipo funcionário passaram %d horas na empresa", horasDentroEmpresa);

    return 0;
}

int linha12(void){
    int horasDentroEmpresaFuncionario = 0;
    int horasDentroEmpresaDiretor = 0;

    for( int i = 0; i < 100 ; i++){
        if(pessoas[i].Tipo == "funcionario"){
            if(pessoas[i].ID > 0){
                ID = verificarSeValorInteiro(pessoas[i].ID);

                if (pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida >= 0 && pessoas[i].Saida <= 24) {
                    horasDentroEmpresaFuncionario += (verificarSeValorInteiro(pessoas[i].Saida) - verificarSeValorInteiro(pessoas[i].Entrada));

                    }
            }
        }
    }

    for( int i = 0; i < 100 ; i++){
        if(pessoas[i].Tipo == "diretor"){
            if(pessoas[i].ID > 0){
                ID = verificarSeValorInteiro(pessoas[i].ID);

                if (pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida >= 0 && pessoas[i].Saida <= 24) {
                    horasDentroEmpresaDiretor += (verificarSeValorInteiro(pessoas[i].Saida) - verificarSeValorInteiro(pessoas[i].Entrada));

                }
            }
        }
    }

    int horasTotais = horasDentroEmpresaDiretor + horasDentroEmpresaFuncionario;

    printf("Todos os funcionários da empresa passaram %d horas na empresa", horasTotais);

    return 0;

}

int linha13(void){
    int horasDentroEmpresa = 0;
    for( int i = 0; i < 100 ; i++){
        if(pessoas[i].Tipo == "diretor"){
            if(pessoas[i].ID > 0){
                ID = verificarSeValorInteiro(pessoas[i].ID);

                if (pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida >= 0 && pessoas[i].Saida <= 24) {
                    horasDentroEmpresa += (verificarSeValorInteiro(pessoas[i].Saida) - verificarSeValorInteiro(pessoas[i].Entrada));

                    }
            }
        }
    }
    printf("Os diretores passaram %d horas na empresa", horasDentroEmpresa);

    return 0;
}

int linha14(void){
    int horasDentroEmpresa = 0;
    for( int i = 0; i < 100 ; i++){
        if(pessoas[i].Tipo == "visitante" && pessoas[i].Acompanhantes == NULL){
            if(pessoas[i].ID > 0){
                ID = verificarSeValorInteiro(pessoas[i].ID);

                if (pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida >= 0 && pessoas[i].Saida <= 24) {
                    horasDentroEmpresa += (verificarSeValorInteiro(pessoas[i].Entrada) - verificarSeValorInteiro(pessoas[i].Saida));

                    }
            }
        }
    }
    printf("Os visitantes passaram %d horas na empresa", horasDentroEmpresa);

    return 0;
}

int linha15(void){
    int numeroEntrada = 0; ID;
    for(int i = 0, i<100;i++){
        pessoas[i].Entrada == "Primeiro a entrar"){
            ID = verificarSeValorInteiro(pessoas[i].ID);

            if (pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida >= 0 && pessoas[i].Saida <= 24) {
                    horasDentroEmpresa += (verificarSeValorInteiro(pessoas[i].Entrada) - verificarSeValorInteiro(pessoas[i].Saida));

                    }
        }
    }
    printf("O numero da pessoa que foi o primeiro a entrar e: %d", &numeroEntrada);

    return 0;

}

int linha16(void){
    int numeroSaida = 0, ID;
    for(int i = 0, i<100;i++){
        pessoas[i].Saida == "Ultimo a sair"){
            ID = verificarSeValorInteiro(pessoas[i].ID);

            if (pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida >= 0 && pessoas[i].Saida <= 24) {
                    horasDentroEmpresa += (verificarSeValorInteiro(pessoas[i].Entrada) - verificarSeValorInteiro(pessoas[i].Saida));

                    }
        }
    }
    printf("O numero da pessoa que foi o ultimo a sair e: %d", &numeroSaida);

    return 0;

}

int linha17(void){
    int visitantesNaEmpresa = linha7();
    int funcionarioNaEmpresa = linha6();
    int diretoresNaEmpresa = linha5();
    int PessoasNaImpresa = 0;

    int PessoasNaImpresa = funcionarioNaEmpresa + diretoresNaEmpresa + visitantesNaEmpresa;


    printf("Todos os visitantes na empresa = %d", &visitantesNaEmpresa);
    printf("Todas os funcionarios na empresa = %d\n", &funcionarioNaEmpresa);
    printf("Todos os diretores na empresa = %d", &diretoresNaEmpresa);
    printf("Todas as pessoas na empresa = %d\n", &PessoasNaImpresa);

    return 0;
}


}

int linha18(void){
    int servicoMaior = 0;
    int i, funcionarioNaEmpresa = 0, ID, EntradaSaida=0,Acompanhantes=0, Servico;
    for (i = 0; i < 100; i++) {
        ID = 0, Servico = 0;
        if ((pessoas[i].Tipo == "funcionario" && pessoas[i].Tipo == "diretor") && pessoas[i].Acompanhantes>=0) {
            Acompanhantes = verificarSeValorInteiro(pessoas[i].Acompanhantes);
            if (pessoas[i].ID > 0) {
                ID += verificarSeValorInteiro(pessoas[i].ID);
                if (pessoas[i].Entrada >= 0 && pessoas[i].Entrada <= 24 && pessoas[i].Saida==0) {
                    EntradaSaida = verificarSeValorInteiro(pessoas[i].Entrada) + verificarSeValorInteiro(pessoas[i].Saida);
                    if (pessoas[i].Servico > 0) {
                        for (int pos = 0; pos < 100; pos++) {
                            if (pessoas[pos].ID == pessoas[i].Servico) {
                                Servico++;
                                break;
                            }
                        }
                        if (ID == 1 && Acompanhantes == 1 && EntradaSaida == 2 && Servico == 1) {
                            funcionarioNaEmpresa++;
                        }
                    }
                }
            }
        }
    }
    printf("todos os funcionarios ainda na empresa= %d", funcionarioNaEmpresa);

    return funcionarioNaEmpresa;
}

int linha19(){

}

int linha20(){

}

void main(){
     setlocale (LC_ALL, "");
     linha1();
     linha2();
     linha3();
     linha4();
     linha5();
     linha6();
     linha7();
     linha8();
     linha9();
     linha10();
     linha11();
     linha12();
     linha13();
     linha14();
     linha15();
     linha16();
     linha17();

     return 0;
}
