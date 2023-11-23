#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>

using namespace std;

struct pessoa {
    int cpf;
    string nome;
    char sexo;
    string telefone;
    string email;
};

struct dt_nasc {
    int dia;
    int mes;
    int ano;
};

struct dt_associacao {
    int ass_dia;
    int ass_mes;
    int ass_ano;
};

struct dt_visita {
    int vis_dia;
    int vis_mes;
    int vis_ano;
    int vis_dia_final;
    int vis_mes_final;
    int vis_ano_final;
};

struct associado {
    int cpf;  // Modificado para CPF
    string tipo_socio;
    float mensalidade;
    string codigo_associado;
    static int contadorAssociados;
};

struct dependente {
    string codigo_dependente;
    string codigo_associado;
     string codigo_externo;
    string nome_dependente;
    int cpf;
    char sexo;
     static string codExterno(int ano, int codigo);
    static int contadorDependentes;
};

struct dat_nasc_dependente {
    int dia;
    int mes;
    int ano;
};

struct visitante {
    string codigo_visitante;
    int cpf_associado;
    string nome_visitante;
    int cpf;
    char sexo;
    dt_visita data_visita;
    string codExterno(int ano, int codigo);
    static int contadorVisitantes;
};

struct endereco {
    string bairro;
    string rua;
    string cidade;
    string estado;
    int num;
};

// Função para buscar um associado pelo CPF
int buscarAssociadoPorCPF(associado cad_assos[], int tamanho, int cpf) {
    for (int j = 0; j < tamanho; j++) {
        if (cad_assos[j].cpf == cpf) {
            return j; // Retorna o  ndice do associado se encontrado
        }
    }
    return -1; // Retorna -1 se o associado n o for encontrado
}

void cadastroPessoa(pessoa cad_pessoa[], endereco cad_end[], dt_nasc nascimento[], associado cad_assos[], int &i, int &a);
void cadastroDependente(dependente cad_dependente[], dat_nasc_dependente dat_nasc_dependente[], int &i, int &a, associado cad_assos[], int tamanho);
void cadastroVisitante(visitante cad_visitante[], int &i, int &a, associado cad_assos[], int tamanho);

    int associado::contadorAssociados = 1;
    int dependente::contadorDependentes = 1;
    int visitante::contadorVisitantes = 1;

int main() {

    setlocale(LC_ALL, "portuguese");
    int op = 0;
    int i = 0;
    int a = 1;
    int ano, codigo;
    pessoa cad_pessoa[100];
    dt_nasc nascimento[100];
    endereco cad_end[100];
    associado cad_assos[100];
    dependente cad_dependente[100];
    dat_nasc_dependente dat_nasc_dependente[100];
    visitante cad_visitante[100];
    dt_associacao data_assos[100];

    do {
		cout << "Bem vindo ao menu do Clube Jimin do BTS"<< endl;
		cout << "============================================"<< endl << endl;
		cout << "1- Cadastro ou manutenção de Associados\n";
		cout << "2- Cadastro ou manutenção de Dependentes\n";
		cout << "3- Cadastro ou manutenção de Visitantes\n";
		cout << "4- Consulta de maioridade\n";
		cout << "5- Registro de visitas\n";
		cout << "6- Relatório de dependentes\n";
		cout << "7- Relatório de visitantes\n";
		cout << "8- Sair\n";
		cout << "\nSelecione a opção desejada: ";
		cin >> op;
		cout << "\n";
		cout << "============================================"<< endl;

        switch (op) {
            case 1:
                cadastroPessoa(cad_pessoa, cad_end, nascimento, cad_assos, i, a);
            break;
            case 2:
                cadastroDependente(cad_dependente, dat_nasc_dependente, i, a, cad_assos, 100);
            break;
            case 3:
                cadastroVisitante(cad_visitante, i, a, cad_assos, 100);
            break;
        }

    } while (op != 8);

    return 0;
}

void cadastroPessoa(pessoa cad_pessoa[], endereco cad_end[], dt_nasc nascimento[], associado cad_assos[], int &i, int &a) {
    fstream arquivo;
    arquivo.open("Associados_Cadastrados.txt", fstream::in | fstream::out | fstream::app);

    if (arquivo.is_open()) {
        cout << "\nOpção cadastro de associados\n\nCPF:";
        cin >> cad_pessoa[i].cpf;
        arquivo << "CPF: " << cad_pessoa[i].cpf << "\n";

        cin.ignore();
        cout << "\nNome: ";
        cin >> ws;
        getline(cin, cad_pessoa[i].nome);
        arquivo << "Nome: " << cad_pessoa[i].nome << "\n";

        cout << "\nData de nascimento:\nDia: ";
        cin >> nascimento[i].dia;
        cout << "Mês: ";
        cin >> nascimento[i].mes;
        cout << "Ano: ";
        cin >> nascimento[i].ano;
        arquivo << "Data de Nascimento: " << nascimento[i].dia << "/" << nascimento[i].mes << "/" << nascimento[i].ano << "\n";
        cin.ignore();

        cout << "\nEndereço:\nRua: ";
        getline(cin, cad_end[i].rua);
        arquivo << "Rua: " << cad_end[i].rua << "\n";
        cout << "Bairro: ";
        getline(cin, cad_end[i].bairro);
        arquivo << "Bairro: " << cad_end[i].bairro << "\n";
        cout << "Número: ";
        cin >> cad_end[i].num;
        arquivo << "Número da casa: " << cad_end[i].num << "\n";
        cin.ignore();
        cout << "Cidade: ";
        getline(cin, cad_end[i].cidade);
        arquivo << "Cidade: " << cad_end[i].cidade << "\n";
        cout << "Estado: ";
        getline(cin, cad_end[i].estado);
        arquivo << "Estado: " << cad_end[i].estado << "\n";

        cout << "\nGênero (M/F): ";
        cin >> cad_pessoa[i].sexo;
        arquivo << "Gênero: " << cad_pessoa[i].sexo << "\n";

        cout << "\nTelefone para contato: ";
        cin >> cad_pessoa[i].telefone;
        arquivo << "Telefone: " << cad_pessoa[i].telefone << "\n";

        cout << "\nE-mail: ";
        cin >> cad_pessoa[i].email;
        arquivo << "E-mail: " << cad_pessoa[i].email << "\n";

        cout << "\nTipo de sócio (proprietário, contribuinte): ";
        cin >> cad_assos[i].tipo_socio;

        cad_assos[i].cpf = cad_pessoa[i].cpf;

        cout << "\nMensalidade: ";
        cin >> cad_assos[i].mensalidade;
        arquivo << "Tipo de sócio: " << cad_assos[i].tipo_socio << "\n";
        arquivo << "Mensalidade: " << cad_assos[i].mensalidade << "\n";
        cad_assos[i].codigo_associado = "A" + to_string(associado::contadorAssociados);
        cout << "Código do associado: " << cad_assos[i].codigo_associado << endl;
        arquivo << "Código: " << cad_assos[i].cpf << "\n";
        arquivo << "============================================\n";

        a++;
        associado::contadorAssociados++;
        i++;

    } else {
        cout << "Arquivo não encontrado!" << endl;
    }

    arquivo.close();
    cout << endl;
}

void cadastroDependente(dependente cad_dependente[], dat_nasc_dependente dat_nasc_dependente[], int &i, int &a, associado cad_assos[], int tamanho) {
    fstream arquivo;
    arquivo.open("Dependentes_Cadastrados.txt", fstream::in | fstream::out | fstream::app);

    if (arquivo.is_open()) {
        cout << "Opção cadastro de dependente\n\nCPF do associado: ";
        int cpfAssociado;
        cin >> cpfAssociado;

        // Verifica se o associado com o CPF informado existe
        int indexAssociado = buscarAssociadoPorCPF(cad_assos, tamanho, cpfAssociado);

        if (indexAssociado != -1) {
            cin.ignore(); // Limpar o buffer do teclado

            cout << "\nNome do dependente: ";
            getline(cin, cad_dependente[i].nome_dependente);
            arquivo << "Nome: " << cad_dependente[i].nome_dependente << "\n";

            cad_dependente[i].cpf = cpfAssociado;

            cout << "\nData de nascimento:\nDia: ";
            cin >> dat_nasc_dependente[i].dia;
            cout << "Mês: ";
            cin >> dat_nasc_dependente[i].mes;
            cout << "Ano: ";
            cin >> dat_nasc_dependente[i].ano;
            arquivo << "Data de Nascimento: " << dat_nasc_dependente[i].dia << "/" << dat_nasc_dependente[i].mes << "/" << dat_nasc_dependente[i].ano << "\n";
            cin.ignore();

            cout << "\nGênero (M/F): ";
            cin >> cad_dependente[i].sexo;
            arquivo << "Gênero: " << cad_dependente[i].sexo << "\n";

            // Inserir l gica para gerar o c digo externo
            int anoAssociacao=2023; // Coloque o ano de associa  o desejado
            cad_dependente[i].codigo_dependente = "D" + to_string(dependente::contadorDependentes);
           cad_dependente[i].codigo_externo = dependente::codExterno(2023, dependente::contadorDependentes);

           cout << "\nCódigo do dependente: " <<  cad_dependente[i].codigo_dependente << endl;
           cout << "\nCódigo externo do dependente: " << cad_dependente[i].codigo_externo << endl;


            cout << "Dependente cadastrado com sucesso!" << endl;
            arquivo << "Código do dependente: " << cad_dependente[i].codigo_dependente << "\n";
            arquivo << "Código externo do dependente: " << cad_dependente[i].codigo_externo << "\n";
            arquivo << "============================================\n";

            a++;
            dependente::contadorDependentes++;
            i++;

        } else {
            cout << "Associado não encontrado. Cadastre o associado primeiramente." << endl;
        }
    } else {
        cout << "Arquivo não encontrado!" << endl;
    }

    arquivo.close();
    cout << endl;
}

void cadastroVisitante(visitante cad_visitante[], int &i, int &a, associado cad_assos[], int tamanho) {
    fstream arquivoVisitante;
    arquivoVisitante.open("Visitantes_Cadastrados.txt", fstream::in | fstream::out | fstream::app);

    if (arquivoVisitante.is_open()) {
        cout << "Opção cadastro de visitante\n\nCPF do associado: ";
        int cpfAssociado;
        cin >> cpfAssociado;
         cin.ignore();

        // Verifica se o associado com o CPF informado existe
        int indexAssociado = buscarAssociadoPorCPF(cad_assos, tamanho, cpfAssociado);

        if (indexAssociado != -1) {
            cout << "\nCPF do visitante: ";
            cin >> cad_visitante[i].cpf;
            cin.ignore();

            cout << "\nNome: ";
            cin >> ws;
            getline(cin, cad_visitante[i].nome_visitante);

            cad_visitante[i].codigo_visitante = "V" + to_string(visitante::contadorVisitantes);
            cout << "Código do visitante: " << cad_visitante[i].codigo_visitante << endl;

            cout << "\nData da visita:\nDia: ";
            cin >> cad_visitante[i].data_visita.vis_dia;
            cout << "Mês: ";
            cin >> cad_visitante[i].data_visita.vis_mes;
            cout << "Ano: ";
            cin >> cad_visitante[i].data_visita.vis_ano;

            cout << "Visitante cadastrado com sucesso!" << endl;

            arquivoVisitante << "CPF: " << cad_visitante[i].cpf << endl;
            arquivoVisitante << "Nome: " << cad_visitante[i].nome_visitante << endl;
            arquivoVisitante << "Data da visita: "<< cad_visitante[i].data_visita.vis_dia << "/" << cad_visitante[i].data_visita.vis_mes << "/" << cad_visitante[i].data_visita.vis_ano << endl;
            arquivoVisitante << "Código: " << cad_visitante[i].codigo_visitante << "\n";
            arquivoVisitante << "============================================\n";

            a++;
            visitante::contadorVisitantes++;
            i++;
        } else {
            cout << "Associado não encontrado. Cadastre o associado primeiramente." << endl;
        }
    } else {
        cout << "Arquivo não encontrado!" << endl;
    }

    arquivoVisitante.close();
    cout << endl;
}

string dependente::codExterno(int ano, int codigo) {
    return to_string(ano) + "-" + to_string(codigo);
}


string visitante::codExterno(int ano, int codigo) {
    return to_string(ano) + to_string(codigo);
}
