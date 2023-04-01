//VITOR MELO ASSUNCAO; BANDAS DE ROCK; SELECTION SORT; BUSCA BINARIA; GRAVACAO BINARIA.
#include <iostream>
#include <fstream>

using namespace std;

struct Bandas //estrutura de dados a serem registrados
{
    int id;
    char nome[30];
    char estilo_musical[30];
    int ano;
    int musicas_famosas;
};

void selection_sort(Bandas vetorbandas[], int tamanho) //ordenacao dos registros por ID
{
    int menor;
    Bandas aux_troca;
    for (int i = 0; i < tamanho - 1; i++) 
    {
   	 menor = i;
   	 for (int j = i + 1; j < tamanho; j++) 
     {
   		 if (vetorbandas[j].id < vetorbandas[menor].id)
         {
   			 menor = j;
   		 }
   	 }
   	 aux_troca = vetorbandas[i];
   	 vetorbandas[i] = vetorbandas[menor];
   	 vetorbandas[menor] = aux_troca;
    }
}

int buscaBinaria(Bandas *vetorbandas, int l, int r, int id) //buscar registros por ID
{

    if(r >= l)
    { 
        int mid = l + (r - l) / 2;


        if(vetorbandas[mid].id == id)
        {
            return mid;
        }

        if(vetorbandas[mid].id > id)
        {
            return buscaBinaria(vetorbandas, l, mid - 1, id);
        }

        if(vetorbandas[mid].id < id)
        {
            return buscaBinaria(vetorbandas, mid + 1, r, id);
        }
    }

    return -1;
}

void removeDadoOrdenado(Bandas vetorBandas[100], int tam, int pos)
{

    for(int i = pos + 1; i < tam; i++)
    {
        vetorBandas[i - 1] = vetorBandas[i];
    }
}

//FUNCOES DO PROGRAMA

void menu () //Menu de funcoes do programa
{
    cout << "                     MENU                         " << endl;
    cout << "==================================================" << endl;
    cout << "Para registrar uma banda, digite 1" << endl;
    cout << "Para excluir um registro, digite 2" << endl;
    cout << "Para listar todos os registros de bandas, digite 3" << endl;
    cout << "Para alterar algum registro, digite 4" << endl;
    cout << "Para gravar os dados em um arquivo, digite 5" << endl;
    cout << "Para sair do sistema, digite 0" << endl;
    cout << "==================================================" << endl;
}

void incluir(Bandas* vetorbandas, int tamanho) //procedimento de incluir
{
        int id;
        cout << "Insira o ID da banda:" << " ";
        cin >> id;
        int aux;
        aux = buscaBinaria(vetorbandas, 0, tamanho - 1, id);
        if(aux == -1)
        {
            vetorbandas[tamanho].id = id;
            cout << "Insira o nome da banda:" << " ";
            cin.ignore();
            cin.getline(vetorbandas[tamanho].nome,30);
            cout << "Insira o estilo musical:" << " ";
            cin.getline(vetorbandas[tamanho].estilo_musical,30);
            cout << "Insira o ano que a banda foi criada:" << " ";
            cin >> vetorbandas[tamanho].ano;
            cout << "Insira o numero de musicas famosas:" << " ";
            cin >> vetorbandas[tamanho].musicas_famosas;
            cout << "Registro incluido com sucesso!"<< endl; 
        }
        else
        {
            cout << "ERRO: Este id ja existe" << endl;
        } 
}

void excluir(Bandas* vetorbandas, int tamanho) //procedimento de excluir
{
    cout << "Digite o ID da banda que deseja excluir: " << endl;
    int id;
    cin >> id;
    int pos;
    buscaBinaria(vetorbandas, 0, tamanho - 1, id);
    pos = buscaBinaria(vetorbandas, 0, tamanho - 1, id);
    if(pos != -1)
    {
        for(int i = pos; i < tamanho; i++)
        {
            vetorbandas[i] = vetorbandas[i + 1];
        }
        cout << "Registro excluido com sucesso!" << endl; 
    }
    else
    {
        cout << "ERRO: Registro nao encontrado" << endl;
    }
}

void listar(Bandas* vetorbandas, int tamanho) //procedimento de listar os registros
{
    for(int i = 0;i < tamanho; i++)
    {
        cout << "ID: " << vetorbandas[i].id << endl;
        cout << "Nome: " << vetorbandas[i].nome << endl;
        cout << "Estilo Musical: " << vetorbandas[i].estilo_musical << endl;
        cout << "Ano de criacao: " << vetorbandas[i].ano << endl;
        cout << "Numero de musicas famosas: " << vetorbandas[i].musicas_famosas << endl;
    }    
}

void alterar(Bandas* vetorbandas, int tamanho) //procedimento de alterar os dados de um registro
{
    int id;
    cout << "Insira o ID do registro: ";
    cin >> id;
    int pos;
    buscaBinaria(vetorbandas, 0, tamanho - 1, id);
    pos = buscaBinaria(vetorbandas, 0, tamanho - 1, id);
    if(pos != -1)
    {
        cout << "========================================" << endl;
        cout << "Digite o campo que voce deseja alterar: " << endl; 
        cout << "1- ID" << endl;
        cout << "2- Nome" << endl;
        cout << "3- Estilo Musical" << endl;
        cout << "4- Ano de criacao" << endl;
        cout << "5- Musicas famosas" << endl;
        cout << "========================================" << endl;
        int campo;
        cin >> campo;
        for (int i = pos;i < tamanho; i++)
        {
            if(campo == 1)
            {
                cout << "Insira o novo ID: ";
                cin >> vetorbandas[i].id;
                cout << "Registro alterado com sucesso!" << endl;
            }
            if(campo == 2)
            {
                cout << "Insira o novo nome: ";
                cin.ignore();
                cin.getline(vetorbandas[i].nome,30);
                cout << "Registro alterado com sucesso!" << endl;
            }
            if(campo == 3)
            {
                cout << "Insira o novo Estilo Musical: ";
                cin.ignore();
                cin.getline(vetorbandas[i].estilo_musical,30);
                cout << "Registro alterado com sucesso!" << endl;
            }
            if(campo == 4)
            {
                cout << "Insira o novo Ano de criacao: ";
                cin >> vetorbandas[i].ano;
                cout << "Registro alterado com sucesso!" << endl;
            }
            if(campo == 5)
            {
                cout << "Insira o novo numero de musicas famosas: ";
                cin >> vetorbandas[i].musicas_famosas;
                cout << "Registro alterado com sucesso!" << endl;
            }
        }
    }
    else
    {
        cout << "ERRO: Registro nao encontrado" << endl;
    }
}

void gravar(Bandas* vetorbandas, int tamanho) //procedimento que grava os dados no arquivo
{
    if(tamanho > 0)
    {
        ofstream saida("arquivo.bin");
        saida.write((const char*) vetorbandas,sizeof(vetorbandas));
        cout <<"Gravacao realizada com sucesso!" << endl;
    }
    else
    {
        cout << "ERRO: Nao possuem registros para gravar" << endl;
    }
}

int main ()                 
{  
    Bandas vetorbandas[100];
    int tamanho = 0;
    menu();
    int op;
    cin >> op;
    int registrar = 1;
    int exclui = 2;
    int lista = 3;
    int altera = 4;
    int grava = 5;
    int sair = 0;
    while(op != sair) //while para controlar as entradas
    {
        if(op == registrar) // if para incluir
        {
            if(tamanho <= 100)
            {
                incluir(vetorbandas, tamanho);
                tamanho++;
            }
            else
            {
                cout << "ERRO: Nao e possivel inserir novo registro" << endl;
            }
        }
        if(op == exclui)  //if para excluir
        {
            selection_sort(vetorbandas, tamanho);
            excluir(vetorbandas, tamanho);
            tamanho--;
        }
        if(op == lista) //if para listar
        {
            if(tamanho > 0)
            {
                selection_sort(vetorbandas, tamanho);
                listar(vetorbandas, tamanho);
            }
            else
            {
                cout << "ERRO: Nao existem registros para listar" << endl;
            }
        }
        if(op == altera) //if para alterar
        {
            selection_sort(vetorbandas, tamanho);
            alterar(vetorbandas, tamanho);
        }
        if(op == grava) //if para gravar
        {
            selection_sort(vetorbandas, tamanho);
            gravar(vetorbandas, tamanho);
        }

        menu();
        cin >> op;
    }
    if(op == sair) //if para perguntar se deseja gravar antes de sair
    { 
        string opcao;
        cout << "Deseja gravar os dados no arquivo? S/N" << endl;
        cin >> opcao;
        if(opcao == "S") 
        {
            selection_sort(vetorbandas, tamanho);
            gravar(vetorbandas, tamanho);
        }      
    }
    return 0;
}