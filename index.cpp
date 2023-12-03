#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
#include <time.h>

using namespace std;

struct associado {
    string tipo_socio;
    float mensalidade;
    int num_dependentes;
    string codigo_associado;
    static int contadorAssociados;
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

struct dt_visita {
    int vis_dia;
    int vis_mes;
    int vis_ano;
    int vis_dia_final;
    int vis_mes_final;
    int vis_ano_final;
};

struct dependente {
    string codigo_dependente;
    string codigo_associado;
    string codigo_externo;
    string nome_dependente;
    int cpf;
    int cpfConsulta;
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

struct dat_nasc_visitante{
    int dia;
    int mes;
    int ano;
};

struct endereco {
    string bairro;
    string rua;
    string cidade;
    string estado;
    string num;
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

void cadastroPessoa(endereco cad_end[], dt_nasc nascimento[], associado cad_assos[], int &i, int &a);
void alterarAssociado(endereco cad_end[], associado cad_assos[], dt_nasc nascimento[], int i, int tamanho);
void cadastroDependente(dependente cad_dependente[], dat_nasc_dependente dat_nasc_dependente[], int &i, int &a, associado cad_assos[], int tamanho);
void alterarDependente();
void cadastroVisitante(visitante cad_visitante[], int &i, int &a, associado cad_assos[], int tamanho, dat_nasc_visitante dat_nasc_visitante[]);
void alterarVisitante();
void isMaior(dependente cad_dependente[], dat_nasc_dependente dat_nasc_dependente[]);
void registroVisitas();
void relatorioDependente();
void relatorioVisitante();

int associado::contadorAssociados = 1;
int dependente::contadorDependentes = 1;
int visitante::contadorVisitantes = 1;

int main() {

    setlocale(LC_ALL, "portuguese");
    int op = 0;
    int i = 0;
    int a = 1;
    associado cad_assos[100];
    dt_nasc nascimento[100];
    endereco cad_end[100];
    dependente cad_dependente[100];
    dat_nasc_dependente dat_nasc_dependente[100];
    visitante cad_visitante[100];
    dat_nasc_visitante dat_nasc_visitante[100];

    do {
        cout << "\n============================================"<< endl;
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
                int op1;
                cout << "Deseja realizar um novo cadastro ou manutenção de um dado existente?\n";
                cout << "1- Novo Cadastro\n";
                cout << "2- Manutenção de dados\n";
                cout << "Opção: ";
                cin >> op1;
                cout << "============================================"<< endl;

                if(op1 == 1){
                    cadastroPessoa(cad_end, nascimento, cad_assos, i, a);
                } else if(op1 == 2){
                    alterarAssociado(cad_end, cad_assos, nascimento, i, 100);
                } else{
                    cout << "Opção inválida! Tente novamente.";
                }
            break;

            case 2:
                int op2;
                cout << "Deseja realizar um novo cadastro ou manutenção de um dado existente?\n";
                cout << "1- Novo Cadastro\n";
                cout << "2- Manutenção de dados\n";
                cout << "Opção: ";
                cin >> op2;
                cout << "============================================"<< endl;

                if(op2 == 1){
                    cadastroDependente(cad_dependente, dat_nasc_dependente, i, a, cad_assos, 100);
                } else if(op2 == 2){
                    alterarDependente();
                } else{
                    cout << "Opção inválida! Tente novamente.";
                }
            break;

            case 3:
                int op3;
                cout << "Deseja realizar um novo cadastro ou manutenção de um dado existente?\n";
                cout << "1- Novo Cadastro\n";
                cout << "2- Manutenção de dados\n";
                cout << "Opção: ";
                cin >> op3;
                cout << "============================================"<< endl;

                if(op3 == 1){
                    cadastroVisitante(cad_visitante, i, a, cad_assos, 100, dat_nasc_visitante);
                } else if(op3 == 2){
                    alterarVisitante();
                } else{
                    cout << "Opção inválida! Tente novamente.";
                }
            break;

            case 4:
                isMaior(cad_dependente, dat_nasc_dependente);
            break;

            case 5:
                registroVisitas();
            break;

            case 6:
                relatorioDependente();
            break;

            case 7:
                relatorioVisitante();
            break;
        }

    } while (op != 8);

    return 0;
}

void cadastroPessoa(endereco cad_end[], dt_nasc nascimento[], associado cad_assos[], int &i, int &a) {
    fstream arquivo;
    int val_fix = 200;
    arquivo.open("Associados_Cadastrados.txt", fstream::in | fstream::out | fstream::app);

    if (arquivo.is_open()) {
        cout << "\nOpção cadastro de associados\n\nCPF: ";
        cin >> cad_assos[i].cpf;
        arquivo << "CPF: " << cad_assos[i].cpf << "\n";

        cin.ignore();
        cout << "\nNome: ";
        cin >> ws;
        getline(cin, cad_assos[i].nome);
        arquivo << "Nome: " << cad_assos[i].nome << "\n";

        cout << "\nData de nascimento:\nDia: ";
        cin >> nascimento[i].dia;
        cout << "Mês: ";
        cin >> nascimento[i].mes;
        cout << "Ano: ";
        cin >> nascimento[i].ano;
        arquivo << "Data de Nascimento: " << nascimento[i].dia << "/" << nascimento[i].mes << "/" << nascimento[i].ano << "\n";

        cout << "\nGênero (M/F): ";
        cin >> cad_assos[i].sexo;
        arquivo << "Gênero: " << cad_assos[i].sexo << "\n";

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
        cout << "Cidade: ";
        cin.ignore();
        getline(cin, cad_end[i].cidade);
        arquivo << "Cidade: " << cad_end[i].cidade << "\n";
        cout << "Estado: ";
        getline(cin, cad_end[i].estado);
        arquivo << "Estado: " << cad_end[i].estado << "\n";

        cout << "\nTelefone para contato: ";
        cin >> cad_assos[i].telefone;
        arquivo << "Telefone: " << cad_assos[i].telefone << "\n";

        cout << "\nE-mail: ";
        cin >> cad_assos[i].email;
        arquivo << "E-mail: " << cad_assos[i].email << "\n";

        cout << "\nTipo de sócio (proprietário, contribuinte): ";
        cin >> cad_assos[i].tipo_socio;
        arquivo << "Tipo de sócio: " << cad_assos[i].tipo_socio << "\n";

        cad_assos[i].cpf = cad_assos[i].cpf;
        cout << "\nQuantos dependentes deseja cadastrar? ";
        cin >> cad_assos[i].num_dependentes;

        int val_dep_fix = 30;
        cad_assos[i].mensalidade = val_fix + val_dep_fix * cad_assos[i].num_dependentes;

        cout << "\nMensalidade = " <<cad_assos[i].mensalidade << endl;
        arquivo << "Mensalidade: " << cad_assos[i].mensalidade << "\n";

        struct tm *data_atual;
        time_t agora;
        time(&agora);
        data_atual = localtime(&agora);
        int dia_atual = data_atual->tm_mday;
        int mes_atual = data_atual->tm_mon + 1;
        int ano_atual = data_atual->tm_year + 1900;
        cout << "\nData de associação: ";
        cout << dia_atual << "/" << mes_atual << "/" << ano_atual << endl;
        arquivo << "Data de associação: " << dia_atual << "/" << mes_atual << "/" << ano_atual << endl;

        cad_assos[i].codigo_associado = "A" + to_string(associado::contadorAssociados);

        cout << "\nCódigo do associado: " << cad_assos[i].codigo_associado;
        arquivo << "Código: " << cad_assos[i].cpf << "\n";
        arquivo << "============================================\n";



        a++;
        associado::contadorAssociados++;
        i++;

    } else {
        cout << "Arquivo não encontrado!" << endl;
    }

    arquivo.close();
}

void alterarAssociado(endereco cad_end[], associado cad_assos[], dt_nasc nascimento[], int i, int tamanho) {
    int procura_cpf;

    cout << "Insira o CPF do associado com o qual deseja alterar os dados: ";
    cin >> procura_cpf;

    int index = buscarAssociadoPorCPF(cad_assos, tamanho, procura_cpf);

    if (index != -1) {
        // Solicitando as modificações
        cout << "\nDigite as novas informações:\n";
        cout << "Nome: ";
        cin >> ws;
        getline(cin, cad_assos[index].nome);

        cout << "Data de Nascimento:\nDia: ";
        cin >> nascimento[index].dia;
        cout << "Mês: ";
        cin >> nascimento[index].mes;
        cout << "Ano: ";
        cin >> nascimento[index].ano;

        cout << "Gênero (M/F): ";
        cin >> cad_assos[index].sexo;

        cout << "Endereço:\nRua: ";
        cin.ignore();
        getline(cin, cad_end[index].rua);
        cout << "Número: ";
        cin >> cad_end[index].num;
        cout << "Bairro: ";
        cin.ignore();
        getline(cin, cad_end[index].bairro);
        cout << "Cidade: ";
        getline(cin, cad_end[index].cidade);
        cout << "Estado: ";
        getline(cin, cad_end[index].estado);

        cout << "Telefone: ";
        cin >> cad_assos[index].telefone;

        cout << "E-mail: ";
        cin >> cad_assos[index].email;

        cout << "Tipo de sócio (proprietário, contribuinte): ";
        cin >> cad_assos[index].tipo_socio;

        cout << "Número de dependentes: ";
        cin >> cad_assos[index].num_dependentes;

        // Recalcular a mensalidade com base nas novas informações
        int val_fix = 200;
        int val_dep_fix = 30;
        cad_assos[index].mensalidade = val_fix + val_dep_fix * cad_assos[index].num_dependentes;

        // Abre o arquivo original para leitura e escrita
        fstream arquivo("Associados_Cadastrados.txt", ios::in | ios::out);

        if (!arquivo.is_open()) {
            cout << "Não foi possível abrir o arquivo para leitura e escrita.";
            return;
        }

        // Procura e atualiza as informações no arquivo
        string linha;
        while (getline(arquivo, linha)) {
            if (linha.find("CPF: " + to_string(procura_cpf)) != string::npos) {
                // Atualiza as informações no arquivo
                arquivo.seekp(arquivo.tellg() - linha.length());
                arquivo << "CPF: " << cad_assos[index].cpf << "\n";
                arquivo << "Nome: " << cad_assos[index].nome << "\n";
                arquivo << "Data de Nascimento: " << nascimento[index].dia << "/" << nascimento[index].mes << "/" << nascimento[index].ano << "\n";
                arquivo << "Gênero: " << cad_assos[index].sexo << "\n";
                arquivo << "Rua: " << cad_end[index].rua << "\n";
                arquivo << "Bairro: " << cad_end[index].bairro << "\n";
                arquivo << "Número da casa: " << cad_end[index].num << "\n";
                arquivo << "Cidade: " << cad_end[index].cidade << "\n";
                arquivo << "Estado: " << cad_end[index].estado << "\n";
                arquivo << "Telefone: " << cad_assos[index].telefone << "\n";
                arquivo << "E-mail: " << cad_assos[index].email << "\n";
                arquivo << "Tipo de sócio: " << cad_assos[index].tipo_socio << "\n";
                arquivo << "Mensalidade: " << cad_assos[index].mensalidade << "\n";

                // Cálculos para data de associação e código
                struct tm *data_atual;
                time_t agora;
                time(&agora);
                data_atual = localtime(&agora);
                int dia_atual = data_atual->tm_mday;
                int mes_atual = data_atual->tm_mon + 1;
                int ano_atual = data_atual->tm_year + 1900;
                cad_assos[index].codigo_associado = "A" + to_string(associado::contadorAssociados);

                arquivo << "Data de associação: " << dia_atual << "/" << mes_atual << "/" << ano_atual << endl;
                arquivo << "Código: " << cad_assos[index].codigo_associado << "\n";
                arquivo << "============================================\n";

                cout << "\nDados do associado alterados com sucesso!\n";
                break; // Sai do loop após encontrar e atualizar o associado
            }
        }

        // Fecha o arquivo
        arquivo.close();
    } else {
        cout << "Associado não encontrado.\n";
    }
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
            cin.ignore();

            cout << "\nNome do dependente: ";
            getline(cin, cad_dependente[i].nome_dependente);
            arquivo << "Nome: " << cad_dependente[i].nome_dependente << "\n";

            cad_dependente[i].cpf = cpfAssociado;

            cin.ignore();
            cout << "\nCPF do dependente: ";
            cin >> cad_dependente[i].cpfConsulta;
            arquivo << "CPF do dependente: " << cad_dependente[i].cpfConsulta << "\n";

            cout << "\nCPF do associado: " << cpfAssociado << endl;
            arquivo << "CPF do associado: " << cpfAssociado << "\n";

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

            cad_dependente[i].codigo_dependente = "D" + to_string(dependente::contadorDependentes);
            cad_dependente[i].codigo_externo = dependente::codExterno(2023, dependente::contadorDependentes);

            cout << "\nCódigo do dependente: " <<  cad_dependente[i].codigo_dependente << endl;
            cout << "\nCódigo externo do dependente: " << cad_dependente[i].codigo_externo << endl;


            cout << "\nDependente cadastrado com sucesso!";
            arquivo << "Código do dependente: " << cad_dependente[i].codigo_dependente << "\n";
            arquivo << "Código externo do dependente: " << cad_dependente[i].codigo_externo << "\n";
            arquivo << "============================================\n";

            a++;
            dependente::contadorDependentes++;
            i++;

        } else {
            cout << "Associado não encontrado. Cadastre o associado primeiramente.";
        }
    } else {
        cout << "Arquivo não encontrado!";
    }

    arquivo.close();
    cout << endl;
}

void alterarDependente(){
 cout << "Opção indisponível no momento!";
}

void cadastroVisitante(visitante cad_visitante[], int &i, int &a, associado cad_assos[], int tamanho, dat_nasc_visitante dat_nasc_visitante[]) {
    fstream arquivoVisitante;
    arquivoVisitante.open("Visitantes_Cadastrados.txt", fstream::in | fstream::out | fstream::app);

    fstream registroVisitas;
    registroVisitas.open("Registro_Visitas.txt", fstream::in | fstream::out | fstream::app);
    string linha;

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
            arquivoVisitante << "CPF: " << cad_visitante[i].cpf << endl;
            cin.ignore();

            arquivoVisitante << "CPF do associado: " << cpfAssociado << endl;

            cout << "\nNome: ";
            cin >> ws;
            getline(cin, cad_visitante[i].nome_visitante);
            arquivoVisitante << "Nome: " << cad_visitante[i].nome_visitante << endl;

            cout << "\nGênero (M/F): ";
            cin >> cad_visitante[i].sexo;
            arquivoVisitante << "Gênero: " << cad_visitante[i].sexo << endl;

            cout << "\nData da visita:\nDia: ";
            cin >> cad_visitante[i].data_visita.vis_dia;
            cout << "Mês: ";
            cin >> cad_visitante[i].data_visita.vis_mes;
            cout << "Ano: ";
            cin >> cad_visitante[i].data_visita.vis_ano;
            arquivoVisitante << "Data da visita inicial: "<< cad_visitante[i].data_visita.vis_dia << "/" << cad_visitante[i].data_visita.vis_mes << "/" << cad_visitante[i].data_visita.vis_ano << endl;

            cout << "\nData da visita final:\nDia: ";
            cin >> cad_visitante[i].data_visita.vis_dia_final;
            cout << "Mês: ";
            cin >> cad_visitante[i].data_visita.vis_mes_final;
            cout << "Ano: ";
            cin >> cad_visitante[i].data_visita.vis_ano_final;
            arquivoVisitante << "Data da visita final: " << cad_visitante[i].data_visita.vis_dia_final << "/" << cad_visitante[i].data_visita.vis_mes_final << "/" << cad_visitante[i].data_visita.vis_ano_final << endl;

            cout << "\nData de nascimento:\nDia: ";
            cin >> dat_nasc_visitante[i].dia;
            cout << "Mês: ";
            cin >> dat_nasc_visitante[i].mes;
            cout << "Ano: ";
            cin >> dat_nasc_visitante[i].ano;
            arquivoVisitante << "Data de nascimento: " << dat_nasc_visitante[i].dia << "/" <<dat_nasc_visitante[i].mes << "/" << dat_nasc_visitante[i].ano << endl;

            cad_visitante[i].codigo_visitante = "V" + to_string(visitante::contadorVisitantes);
            cout << "Código do visitante: " << cad_visitante[i].codigo_visitante << endl;
            arquivoVisitante << "Código: " << cad_visitante[i].codigo_visitante << "\n";
            arquivoVisitante << "============================================\n";

            cout << "Visitante cadastrado com sucesso!";


            //Registro para exibir na opção 5 do menu, de registro de visitas:
            registroVisitas << "CPF: " << cad_visitante[i].cpf << endl;
            registroVisitas << "Data da visita inicial: "<< cad_visitante[i].data_visita.vis_dia << "/" << cad_visitante[i].data_visita.vis_mes << "/" << cad_visitante[i].data_visita.vis_ano << endl;
            registroVisitas << "Data da visita final: " << cad_visitante[i].data_visita.vis_dia_final << "/" << cad_visitante[i].data_visita.vis_mes_final << "/" << cad_visitante[i].data_visita.vis_ano_final << endl;
            registroVisitas << "============================================\n";

            a++;
            visitante::contadorVisitantes++;
            i++;
        } else {
            cout << "Associado não encontrado. Cadastre o associado primeiramente.";
        }
    } else {
        cout << "Arquivo não encontrado!";
    }
    arquivoVisitante.close();
    registroVisitas.close();
}

void alterarVisitante(){
    cout << "Opção indisponível no momento!";
}

string dependente::codExterno(int ano, int codigo) {
    return to_string(ano) + "-" + to_string(codigo);
}

string visitante::codExterno(int ano, int codigo) {
    return to_string(ano) + to_string(codigo);
}

void isMaior(dependente cad_dependente[], dat_nasc_dependente dat_nasc_dependente[]) {
    fstream arquivo;
    arquivo.open("Dependentes_Cadastrados.txt", fstream::in);

    if (!arquivo.is_open()) {
        cout << "Não foi possível abrir o arquivo." << endl;
        return;
    }

    bool encontrado = false;
    int cpfDependente;

    cout << "Opção consulta de maioridade\n\nInsira o CPF do dependente: ";
    cin >> cpfDependente;

    for (int i = 0; i < 100; i++) {
        arquivo >> cad_dependente[i].cpfConsulta >> dat_nasc_dependente[i].dia >> dat_nasc_dependente[i].mes >> dat_nasc_dependente[i].ano;

        if (cad_dependente[i].cpfConsulta == cpfDependente) {
            encontrado = true;
            int dia = dat_nasc_dependente[i].dia;
            int mes = dat_nasc_dependente[i].mes;
            int ano = dat_nasc_dependente[i].ano;

            struct tm *data_atual;
            time_t agora;
            time(&agora);
            data_atual = localtime(&agora);
            int dia_atual = data_atual->tm_mday;
            int mes_atual = data_atual->tm_mon + 1; // janeiro corresponde a 0
            int ano_atual = data_atual->tm_year + 1900;

            int idade = ano_atual - ano;

            if (mes > mes_atual || (mes == mes_atual && dia > dia_atual)) {
                idade--;
            }

            if(idade >= 18){
			    cout << "\nDependente atingiu a maioridade!\n";
		    } else{
			    cout << "\nDependente ainda não atingiu a maioridade!\n";
		    }

            break;
        }
    }

    if (!encontrado) {
        cout << "Dependente não encontrado." << endl;
    }

    arquivo.close();
}

void registroVisitas(){
    fstream registroVisitas;
    registroVisitas.open("Registro_Visitas.txt", fstream::in);
    string linha;

	if(registroVisitas.is_open()){
        cout << "\nREGISTRO DE VISITAS:\n\n";
        while(getline(registroVisitas, linha)){
            cout << linha << endl;
        }
        registroVisitas.close();
    }else{
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}

void relatorioDependente(){
    fstream arquivoDependente;
    arquivoDependente.open("Dependentes_Cadastrados.txt", ios::in);
    string linha;

	if(arquivoDependente.is_open()){
        cout << "\nRELATÓRIO DE DEPENDENTES:\n\n";
        while(getline(arquivoDependente, linha)){
            cout << linha << endl;
        }
        arquivoDependente.close();
    }else{
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}

void relatorioVisitante(){
    fstream arquivoVisitantes;
    arquivoVisitantes.open("Visitantes_Cadastrados.txt", ios::in);
    string linha;

	if(arquivoVisitantes.is_open()){
        cout << "\nRELATÓRIO DE VISITANTES:\n\n";
        while(getline(arquivoVisitantes, linha)){
            cout << linha << endl;
        }
        arquivoVisitantes.close();
    }else{
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}
