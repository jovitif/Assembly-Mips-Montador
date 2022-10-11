#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string.h>
#include<string>
#include<stdlib.h>
#include<locale.h>
#include<bitset>
#include<ctype.h>

using namespace std;



struct tabelaSimbolo
{
	string label;
	int endereco;
};

// variaveis globais
tabelaSimbolo* table = new tabelaSimbolo[100];
ofstream fout;


void menuPrincipal() {
	cout << "Seja bem vindo(a) ao montador (assembler) para o MIPS\nIrei converter o código que desejar para linguagem de máquina(0/1)\nEntre com um arquivo com código de montagem(assembly) do MIPS\nDigite o nome do arquivo com sua extensão (Exemplo: mips1.asm)";
	cout << "\nOpção: ";
}

void limparArquivo(char * nomearquivo){
	char arquivonovo[30];
	for (int i = 0; i <= strlen(nomearquivo); i++) {
		arquivonovo[i] = nomearquivo[i];
	}
	int j = 0;
	while (arquivonovo[j] != '.') {
		j++;
	}
	arquivonovo[j] = '\0';
	strcat(arquivonovo, "bin.txt");
	ofstream escreval;
	escreval.open(arquivonovo, ios_base::out | ios_base::trunc);
	escreval << "";
}

void salvarArquivo(string binario, char * nomearquivo) {
	char arquivonovo[30];
	for (int i = 0; i <= strlen(nomearquivo); i++) {
		arquivonovo[i] = nomearquivo[i];
	}
	int j = 0;
	while (arquivonovo[j] != '.') {
		j++;
	}
	arquivonovo[j] = '\0';
	strcat(arquivonovo, "bin.txt");
	ofstream escreval;
	escreval.open(arquivonovo, ios_base::out | ios_base::app);

	if (!escreval.is_open())
	{
		cout << "Arquivo nao pode ser aberto!" << endl;
		system("pause");
	}
	escreval << binario << endl;
	

	escreval.close();
}

string obterLabel(char* linha) {
	string label;
	int z = 0;
	int tam = strlen(linha);
	for (int i = 0; i < tam; i++) {
		if (linha[i] == ':') {
			for (int j = 0; j <= i - 1; j++, z++) {
				if(linha[z]!='\t' && linha[z]!= '\0')
				{
					label=label+linha[z];
				}
			}
			label[z] = '\0';
		}
	} 
	return label;
}

string obterOpCode(char* linha)
{
		if (strstr(linha, "beq")) {
				return "000100";
			}
			else if (strstr(linha, "sltiu")) {
				return "001011";
			}
			else if (strstr(linha, "slti")) {
				return "001010";
			}
			else if (strstr(linha, "bne")) {
				return "000101";
			}
			else if (strstr(linha, "addiu")) {
				return "001001";
			}
			else if (strstr(linha, "addi")) {
				return "001000";
			}
			else if (strstr(linha, "andi")) {
				return "001100";
			}
			else if (strstr(linha, "ori")) {
				return "001101";
			}
			else if (strstr(linha, "lui")) {
				return "001111";
			}
			else if (strstr(linha, "lw")) {
				return "100011";
			}
			else if (strstr(linha, "sw")) {
				return "101011";
			}
			else if (strstr(linha, "jal")) {
				return "000011";
			}
			else if (strstr(linha, "sll") || strstr(linha, "srl") || strstr(linha, "jr") || strstr(linha, "mfhi") || strstr(linha, "mflo") || strstr(linha, "mult") || strstr(linha, "multu") || strstr(linha, "div") || strstr(linha, "divu") || strstr(linha, "add") || strstr(linha, "addu") || strstr(linha, "sub") || strstr(linha, "subu") || strstr(linha, "and") || strstr(linha, "or") || strstr(linha, "slt") || strstr(linha, "sltu")) {
				return "000000";
			}
			else if (strstr(linha, "mul")) {
				return "011100";
			}
			else if (strstr(linha, "j")) {
				return "000010";
			}
}

string DecPraBin5(int n) {
	char bits[50];
	int c =5;
	string binario;
	int i = 0;
	while (n > 0) {
	  bits[i] = (n % 2) +48;
	  n = n / 2;
	  i++;
	}
	c = c-i;
	for(int i = 0; i < c;i++ )
	{
		binario = binario+ '0';
	}
	for (int j = i - 1; j >= 0; j--)
	{ 
		binario = binario+ bits[j];
	}
	return binario;
}

string DecPraBin16(int n) {
	char bits[50];
	int c =16;
	string binario;
	int i = 0;
	while (n > 0) {
	  bits[i] = (n % 2) +48;
	  n = n / 2;
	  i++;
	}
	c = c-i;
	for(int i = 0; i < c;i++ )
	{
		binario = binario+ '0';
	}
	for (int j = i - 1; j >= 0; j--)
	{ 
		binario = binario+ bits[j];
	}
	return binario;
}

string ComplementoDe2Para16(int n)
{
	char bits[50];
	int c =16;
	string binario;
	int i = 0;
	int z=16;
	bool inverte = false;
	
	while (n > 0) {
	  bits[i] = (n % 2) +48;
	  n = n / 2;
	  i++;
	}
	c = c-i;
	for(int i = 0; i < c;i++ )
	{
		binario = binario+ '0';
	}
	for (int j = i - 1; j >= 0; j--)
	{ 
		binario = binario+ bits[j];
	}
	while(inverte == false)
	{
		if(binario[z]=='1')
	  	{
	  		inverte = true;
		}
		z--;
	}
	for(z;z >-1;z--)
	{
		if(inverte==true && binario[z]=='1')
		{
			binario[z]= '0';
		}
		else if(inverte==true)
		{
			binario[z]='1';
		}
		else
		{
			binario[z]=binario[z];
		}
	}
	return binario;
}

string DecPraBin26(int n) {
	char bits[50];
	int c =26;
	string binario;
	int i = 0;
	while (n > 0) 
	{
	  bits[i] = (n % 2) +48;
	  n = n / 2;
	  i++;
	}
	c = c-i;
	for(int i = 0; i < c;i++ )
	{
		binario = binario+ '0';
	}
	for (int j = i - 1; j >= 0; j--)
	{ 
		binario = binario+ bits[j];
	}
	return binario;
}



void ObterLinha(char* linha, int end, string opCode, char * nomeArquivo)
{
	string label=obterLabel(linha);
	string imediatoLabel;
	string registradores[3];
	string stringFinal;
	string bin;
	int c = 0;
	int imediato =0;
	int pc = end;
	bool anotacao = false;
	bool ObteveLabel = false;
	string opcode = opCode;
	string function = "NULL";
	
	for(int i=label.length();i < strlen(linha);i++)
	{
		imediatoLabel = "";
		if(linha[i] == '#')
		{
			anotacao =true;
		}
		else if(anotacao == false)
		{
				if (linha[i] == '$' &&  c ==0 ) 
				{
					registradores[0]=registradores[0] + linha[i];
					if(linha[i+2]==','|| linha[i+2]=='\0')
					{
						registradores[0]=registradores[0] + linha[i+1];
					}
					else
					{
						registradores[0]=registradores[0] + linha[i+1]; registradores[0]=registradores[0] + linha[i+2];
					}
					c++;
				}
				else if (linha[i] == '$' &&  c ==1) 
				{
					registradores[1]=registradores[1] + linha[i];
					if(linha[i+2]==','|| linha[i+2]=='\0' || linha[i+2]==')')
					{
						registradores[1]=registradores[1] + linha[i+1];
					}
					else
					{
						registradores[1]=registradores[1] + linha[i+1]; registradores[1]=registradores[1] + linha[i+2];
					}
					c++;
				}
				else if (linha[i] == '$' &&  c ==2) 
				{
					registradores[2]=registradores[2] + linha[i];
					if(linha[i+2]==','|| linha[i+2]=='\0')
					{
						registradores[2]=registradores[2] + linha[i+1];
					}
					else
					{
						registradores[2]=registradores[2] + linha[i+1]; registradores[2]=registradores[2] + linha[i+2];
					}
					c++;
				}
				else if( isdigit(linha[i]) && linha[i-1] == ' ' ||isdigit(linha[i]) && linha[i-1] == '-' || isdigit(linha[i]) && linha[i-1] == ',')
				{
					if(isdigit(linha[i+1]) && isdigit(linha[i+2]))
					{
						imediato = ((linha[i]-'0')*100) + ((linha[i+1]- '0')*10) +(linha[i+2]-'0');
					}
					else if(isdigit(linha[i+1]))
					{
						imediato = ((linha[i]- '0') * 10) +(linha[i+1]-'0');
					}
					else
					{
						imediato = linha[i]- '0';
					}
					
					if(linha[i-1]== '-' )
					{
						imediato = imediato*-1;
					}
				}
				else if(opcode == "000010" || opcode == "000011" || opcode == "000100" || opcode == "000101" )
				{	
					int z = i;
					while(linha[z]!='\0')
					{
						imediatoLabel = imediatoLabel + linha[z];
						z++;
					}
					
					for(z = 0;z < 100;z++)
					{
						
						if(imediatoLabel == table[z].label)
						{
							ObteveLabel = true;
							imediato = table[z].endereco;
						}
					}
				}
		}
	}
	
	if(strstr(linha,"sll"))
	{
		function= "000000";
	}
	else if(strstr(linha,"srl"))
	{
		function ="000010";
	}
	else if(strstr(linha,"jr"))
	{
		function ="001000";
	}
	else if(strstr(linha,"mfhi"))
	{
		function ="010000";
	}
	else if(strstr(linha,"mflo"))
	{
		function ="010010";
	}
	else if(strstr(linha,"multu"))
	{
		function ="011001";
	}
	else if(strstr(linha,"mult"))
	{
		function ="011000";
	}
	else if(strstr(linha,"divu"))
	{
		function ="011011";
	}
	else if(strstr(linha,"div"))
	{
		function ="011010";
	}
	else if(strstr(linha,"addi"))
	{
		function ="100000";
	}
	else if(strstr(linha,"addu"))
	{
		function ="100001";
	}
	else if(strstr(linha,"add"))
	{
		function = "100000";
	}
	else if(strstr(linha,"subu"))
	{
		function ="100011";
	}
	else if(strstr(linha,"sub"))
	{
		function ="100010";
	}
	else if(strstr(linha,"and"))
	{
		function ="100100";
	}
	else if(strstr(linha,"or"))
	{
		function ="100101";
	}
	else if(strstr(linha,"sltu"))
	{
		function ="101011";
	}
	else if(strstr(linha,"slt"))
	{
		function ="101010";
	}
	else if(strstr(linha,"mul"))
	{
		function ="000010";
	}
	
	for(int j = 0;j < 3;j++)
	{
		if(registradores[j]=="$zero" || registradores[j]== "$0")
		{
			registradores[j]= "00000";
		}
		else if(registradores[j]=="$at" || registradores[j]== "$1")
		{
			registradores[j]= "00001";
		}
		else if(registradores[j]=="$v0" || registradores[j]== "$2")
		{
			registradores[j]= "00010";
		}
		else if(registradores[j]=="$v1" || registradores[j]== "$3")
		{
			registradores[j]= "00011";
		}
		else if(registradores[j]=="$a0" || registradores[j]== "$4")
		{
			registradores[j]= "00100";
		}
		else if(registradores[j]=="$a1" || registradores[j]== "$5")
		{
			registradores[j]== "00101";
		}
		else if(registradores[j]=="$a2" || registradores[j]== "$6")
		{
			registradores[j]= "00110";
		}
		else if(registradores[j]=="$a3" || registradores[j]== "$7")
		{
			registradores[j]= "00111";
		}
		else if(registradores[j]== "$t0" || registradores[j]== "$8")
		{
			registradores[j]= "01000"; 
		}
		else if(registradores[j]== "$t1" || registradores[j]== "$9")
		{
			registradores[j]= "01001";
		}
		else if(registradores[j]== "$t2" || registradores[j]== "$10")
		{
			registradores[j]= "01010";
		}
		else if(registradores[j]== "$t3" || registradores[j]== "$11")
		{
			registradores[j]= "01011";
		}
		else if(registradores[j]== "$t4" || registradores[j]== "$12")
		{
			registradores[j]= "01100";
		}
		else if(registradores[j]== "$t5" || registradores[j]== "$13")
		{
			registradores[j]= "01101";
		}
		else if(registradores[j]== "$t6" || registradores[j]== "$14")
		{
			registradores[j]= "01110";
		}
		else if(registradores[j]== "$t7" || registradores[j]== "$15")
		{
			registradores[j]= "01111";
		}
		else if(registradores[j]== "$s0" || registradores[j]== "$16")
		{
			registradores[j]= "10000";
		}
		else if(registradores[j]== "$s1" || registradores[j]== "$17")
		{
			registradores[j]= "10001";
		}
		else if(registradores[j]== "$s2" || registradores[j]== "$18")
		{
			registradores[j]= "10010";
		}
		else if(registradores[j]== "$s3" || registradores[j]== "$19")
		{
			registradores[j]= "10011";
		}
		else if(registradores[j]== "$s4" || registradores[j]== "$20")
		{
			registradores[j]= "10100";
		}
		else if(registradores[j]== "$s5" || registradores[j]== "$21")
		{
			registradores[j]= "10101";
		}
		else if(registradores[j]== "$s6" || registradores[j]== "$22")
		{
			registradores[j]= "10110";
		}
		else if(registradores[j]== "$s7" || registradores[j]== "$23")
		{
			registradores[j]= "10111";
		}
		else if(registradores[j]== "$t8" || registradores[j]== "$24")
		{
			registradores[j]= "11000";
		}
		else if(registradores[j]== "$t9" || registradores[j]== "$25")
		{
			registradores[j]= "11001";
		}
		else if(registradores[j]== "$k0" || registradores[j]== "$26")
		{
			registradores[j]= "11010";
		}
		else if(registradores[j]== "$k1" || registradores[j]== "$27")
		{
			registradores[j]= "11011";
		}
		else if(registradores[j]== "$gp" || registradores[j]== "$28")
		{
			registradores[j]= "11100";
		}
		else if(registradores[j]== "$sp" || registradores[j]== "$29")
		{
			registradores[j]= "11101";
		}
		else if(registradores[j]== "$fp" || registradores[j]== "$30")
		{
			registradores[j]= "11110";
		}
		else if(registradores[j]== "$ra" || registradores[j]== "$31")
		{
			registradores[j]= "11111";
		}
		
	}
	
	if(opcode =="000010" || opcode =="000011") 
	{
		stringFinal = opcode;
		imediato = imediato/4; 
		stringFinal = stringFinal + DecPraBin26(imediato);
		cout << stringFinal <<endl;
		stringFinal = opcode  + DecPraBin26(imediato);
		salvarArquivo(stringFinal,nomeArquivo);
	}
	else if(registradores[1] == "" && registradores[2] == "")
	{
		if(function == "001000")
		{
			stringFinal= opcode +registradores[0] +"00000" + "00000" + "00000" + function;
			cout << stringFinal <<endl;
			salvarArquivo(stringFinal,nomeArquivo);
		}
		else if(opcode =="001111")
		{
			stringFinal = opcode + "00000" + registradores[0] + DecPraBin16(imediato);
			cout << stringFinal << endl;
			salvarArquivo(stringFinal,nomeArquivo);
		}
		else
		{
		
			stringFinal = opcode + "00000" + "00000" + registradores[0] + "00000" + function;
			cout <<stringFinal << endl;
			salvarArquivo(stringFinal,nomeArquivo);
		}
	}
	else if(registradores[2] == "")
	{
		if(function == "000000" || function == "000010")
		{
			stringFinal = opcode + "00000" + registradores[1] + registradores[0] +  DecPraBin5(imediato)  + function;
			cout << stringFinal << endl;
			salvarArquivo(stringFinal,nomeArquivo);
		}
		else if(function == "011000" || function == "011001" || function == "011010" || function == "011011")
		{
			stringFinal = opcode + registradores[0] + registradores[1] + "00000" + "00000" + function;
			cout << stringFinal << endl;
			salvarArquivo(stringFinal,nomeArquivo);
		}
		else if(opcode == "000100" || opcode == "000101")
		{
			
			stringFinal = opcode + registradores[0] + registradores[1]; 
			imediato = ((pc+4)-imediato) /4;
			
			if(imediato<0)
			{
				imediato = imediato * -1;
				stringFinal = stringFinal +DecPraBin16(imediato);
				cout << stringFinal << endl;
				salvarArquivo(stringFinal,nomeArquivo);
			} 
			else
			{
				stringFinal = stringFinal + ComplementoDe2Para16(imediato);
				cout << stringFinal << endl;
				salvarArquivo(stringFinal,nomeArquivo);
			}
			
		}
		else
		{
			stringFinal = opcode + registradores[1] + registradores[0];
			if(imediato <0)
			{
				imediato = imediato* -1;
				stringFinal = stringFinal + ComplementoDe2Para16(imediato);
				cout << stringFinal << endl;
				salvarArquivo(stringFinal,nomeArquivo);
			}
			else
			{
				stringFinal = stringFinal + DecPraBin16(imediato);
				cout << stringFinal << endl;
				salvarArquivo(stringFinal,nomeArquivo);
			}
		}
	}
	else
	{
	
		stringFinal = opcode + registradores[1] + registradores[2] + registradores[0] + "00000" + function; 
		cout << stringFinal <<endl;
		salvarArquivo(stringFinal,nomeArquivo);
	}
}



int main() {
	setlocale(LC_ALL, "portuguese");
	char linha[50];
	int j=0;
	int end=4194304;
	string opCode;
	ifstream fin;
	char nomeArquivo[30]; menuPrincipal(); cin >> nomeArquivo;
	limparArquivo(nomeArquivo);
	fin.open(nomeArquivo);
	if (!fin.is_open()) { cout << "Erro na abertura do arquivo!\n";}
	while (fin.good()) {
		fin.getline(linha, 50);
		table[j].label= obterLabel(linha);
		table[j].endereco = end;
		j++;
		end = end +4;
		
	}
	fin.close();
	fin.open(nomeArquivo);
	if (!fin.is_open()) { cout << "Erro na abertura do arquivo!\n";}
	end=4194304;
	while(fin.good())
	{
		fin.getline(linha,50);
		opCode=obterOpCode(linha);
		ObterLinha(linha,end,opCode,nomeArquivo);
		end = end +4;
	}
	fin.close();

	system("Pause");
	return 0;
}
