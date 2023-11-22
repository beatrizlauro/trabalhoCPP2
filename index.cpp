#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>

using namespace std;

struct pessoa{
	int cpf;
	string nome;
	char sexo;
	string telefone;
	string email;
};

struct dt_nasc{
	int dia;
	int mes;
	int ano;
};

struct dt_associacao{
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

struct associado{
	int codigo_associado;
	string tipo_socio;
	float mensalidade;
};

struct dependente{
	int codigo_dependente;
	int codexterno;
};

struct visitante{
	int codigo_visitante;
};

struct endereco{
	string bairro;
	string rua;
	string cidade;
	string estado;
	int num;
};

void cadastroPessoa(pessoa cad_pessoa[], endereco cad_end[], dt_nasc nascimento[],associado cad_assos[], int &i, int &a);

int main()
{
	setlocale (LC_ALL, "portuguese");
	int op=0;
	int i=0;
	int a=0;
	pessoa cad_pessoa[100];
	dt_nasc nascimento[100];
	endereco cad_end[100];
	associado cad_assos[100];
	dt_associacao data_assos[100];
	
	
	do{
		cout << "Bem vindo ao cadastro do Clube Jimin do BTS"<<endl;
		cout << "============================================"<<endl;
		cout << "Selecione a opção que você deseja: "<<endl;
		cout << "1- Cadastro de Associado\n";
		cout << "2- Adicionar Dependente\n";
		cout << "3- Adicionar Visitante\n";
		cout << "4- Consulta\n";
		cout << "5- Alterar dados\n";
		cout << "6- Sair\n";
		cin >> op;
		cout << "\n\n\n";
		cout << "============================================"<<endl;
		
		switch (op){
		
		case 1:
			cadastroPessoa(cad_pessoa, cad_end, nascimento, cad_assos, i, a);
			break;
	}
		
	} while(op!=6);
	
	return 0;
}

void cadastroPessoa(pessoa cad_pessoa[], endereco cad_end[], dt_nasc nascimento[], associado cad_assos[], int &i, int &a){

	fstream arquivo;
	arquivo.open("Associados Cadastrados.txt", fstream::in|fstream::out|fstream::app);
	
	if(arquivo.is_open()){//verifica se o arquivo esta aberto
		
		cout << "Insira seu cpf: "<<endl;
		cin >> cad_pessoa[i].cpf;
		arquivo << "CPF: " << cad_pessoa[i].cpf<<"\n";
		
		cin.ignore();
		cout << "Insira seu nome: "<<endl;
		getline(cin, cad_pessoa[i].nome);
		arquivo << "Nome: " << cad_pessoa[i].nome<<"\n";
		
		cout << "Insira o dia que você nasceu: "<<endl;
		cin >> nascimento[i].dia;
		cout << "Insira o mes que você nasceu: "<<endl;
		cin >> nascimento[i].mes;
		cout << "Insira o ano que você nasceu: "<<endl;
		cin >> nascimento[i].ano;
		arquivo << "Data de Nascimento: " << nascimento[i].dia<<"/"<< nascimento[i].mes << "/" << nascimento[i].ano << "/n";
		cin.ignore();
		cout << "Insira o bairro em que você reside: "<<endl;
		getline(cin, cad_end[i].bairro);
		arquivo << "Bairro: "<< cad_end[i].bairro<<"\n";
		cout << "Insira a rua em que você reside: "<<endl;
		getline(cin, cad_end[i].rua);
		arquivo << "Rua "<< cad_end[i].rua<<"\n";
		cout << "Insira a cidade em que você reside: "<<endl;
		getline(cin, cad_end[i].cidade);
		arquivo << "Cidade "<< cad_end[i].cidade<<"\n";
	
		cout << "Insira o estado em que você reside: "<<endl;
		getline(cin, cad_end[i].estado);
		arquivo << "Estado "<< cad_end[i].estado<<"\n";
	
		cout << "Insira o numero da casa em que você reside: "<<endl;
	   	cin >> cad_end[i].num;
		arquivo << "Numero da casa "<< cad_end[i].num<<"\n";
		
		cout << "Insira o seu gênero (M/F): "<<endl;
		cin >> cad_pessoa[i].sexo;
		arquivo<< "Gênero "<< cad_pessoa[i].sexo<<"\n";
	
		cout << "Insira seu telefone para contato: " << endl;
		cin >> cad_pessoa[i].telefone;
		arquivo << "Telefone "<< cad_pessoa[i].telefone<<"\n";
	
		cout << "Insira seu email: "<<endl;
		cin >> cad_pessoa[i].email;
		arquivo<< "Email "<< cad_pessoa[i].email<<"\n";
		
		cout << "Insira o tipo de sócio(proprietário/contribuinte): ";
		cin >> cad_assos[i].tipo_socio;
		arquivo<< "Tipo de sócio: "<< cad_assos[i].tipo_socio<<"\n";
		cout << "Mensalidade: ";
		cin >> cad_assos[i].mensalidade;
		arquivo<< "Tipo de sócio: "<< cad_assos[i].mensalidade<<"\n";
		cout << "Associado cadastrado com sucesso! Código do associado: " << cad_assos[a].codigo_associado << endl;
		arquivo << "Código" << cad_assos[i].codigo_associado;
		arquivo << "\n============================================\n";
		
		a++;
		i++;
	}
	else{
		cout << "Arquivo não encontrado" << endl;
	}
	
	arquivo.close();
	cout << endl;
}