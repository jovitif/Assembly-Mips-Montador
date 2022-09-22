#include<iostream>
#include<fstream>
#include<string.h>
#include<string>
using namespace std;

void obterLabel(char* linha) {
	char label[20];
	int z = 0;
	int tam = strlen(linha);
	for (int i = 0; i < tam; i++) {
		if (linha[i] == ':') {
			for (int j = 0; j <= i - 1; j++, z++) {
				label[j] = linha[z];
			}
			label[z] = '\0';
			cout << "label: " << label << "\n";
		}
	} 
}

int obterTipo(char* linha) {
	char sll[4] = "sll"; //R
	char srl[4] = "srl";
	char jr[3] = "jr";
	char mfhi[5] = "mfhi";
	char mflo[5] = "mflo";
	char mult[5] = "mult";
	char multu[6] = "multu";
	char div[4] = "div";
	char divu[5] = "divu";
	char add[4] = "add";
	char addu[5] = "addu";
	char sub[4] = "sub";
	char subu[5] = "subu";
	char andx[4] = "and";
	char orx[3] = "or";
	char slt[4] = "slt";
	char sltu[5] = "sltu";
	char mul[4] = "mul";

	char beq[4] = "beq"; //I
	char bne[4] = "bne";
	char addi[5] = "addi";
	char addiu[6] = "addiu";
	char slti[5] = "slti";
	char sltiu[6] = "sltiu";
	char andi[5] = "andi";
	char ori[4] = "ori";
	char lui[4] = "lui";
	char lw[3] = "lw";
	char sw[3] = "sw";

	char jay = 'j'; //J
	char jal[4] = "jal";

	int i, j = 0;
	for (i = 0; i < strlen(linha); i++) {
		if (linha[i] == sll[j] || linha[i] == srl[j] || linha[i] == jr[j] || linha[i] == mfhi[j] || linha[i] == mflo[j] || linha[i] == mult[j] || linha[i] == multu[j] || linha[i] == div[j] || linha[i] == divu[j] || linha[i] == add[j] || linha[i] == addu[j] || linha[i] == sub[j] || linha[i] == subu[j] || linha[i] == andx[j] || linha[i] == orx[j] || linha[i] == slt[j] || linha[i] == sltu[j]) {
			j++;
		}
		else {
			j = 0;
		}
		if (j == strlen(sll) || j == strlen(srl)|| j == strlen(jr) || j == strlen(mfhi) || j == strlen(mflo) || j == strlen(mult) || j == strlen(multu) || j == strlen(div) || j == strlen(divu) || j == strlen(add) || j == strlen(addu) || j == strlen(sub) || j == strlen(subu) || j == strlen(andx) || j == strlen(orx) || j == strlen(slt)|| j == strlen(sltu)) {
			return 0;
		}
		else if (j == strlen(mul)) {
			return 28;
		}
	}
	j = 0;
	for (i = 0; i < strlen(linha); i++) {
		if (linha[i] == beq[j] || linha[i] == bne[j] || linha[i] == addi[j] || linha[i] == addiu[j] || linha[i] == slti[j] || linha[i] == sltiu[j] || linha[i] == andi[j] || linha[i] == ori[j] || linha[i] == lui[j] || linha[i] == lw[j] || linha[i] == sw[j]) {
			j++;
		}
		else {
			j = 0;
		}
		if (j == strlen(beq)) {
			return 4;
		}
		else if (j == strlen(bne)) {
			return 5;
		}
		else if (j == strlen(addi)) {
			return 8;
		}
		else if (j == strlen(addiu)) {
			return 9;
		}
		else if (j == strlen(slti)) {
			return 10;
		}
		else if (j == strlen(sltiu)) {
			return 11;
		}
		else if (j == strlen(andi)) {
			return 12;
		}
		else if (j == strlen(ori)) {
			return 13;
		}
		else if (j == strlen(lui)) {
			return 15;
		}
		else if (j == strlen(lw)) {
			return 35;
		}
		else if (j == strlen(sw)) {
			return 43;
		}
	}
}

void obterInfo(char* linha) {
	char registrador[10];
	char registrador1[10];
	char registrador2[10];
	char imediato;
	for (int i = 0; i < strlen(linha); i++) {
		if (linha[i] == '$' && linha[i + 3] == ',' && linha[i - 2] != ',') {
			registrador[0] = '$'; registrador[1] = linha[i + 1]; registrador[2] = linha[i + 2]; registrador[3] = '\0';
			cout << "rs: " << registrador << "\n";
		}
		else if (linha[i] == '$' && linha[i + 3] == ',' && linha[i - 2] == ',') {
			registrador1[0] = '$'; registrador1[1] = linha[i + 1]; registrador1[2] = linha[i + 2]; registrador1[3] = '\0';
			cout << "rt: " << registrador1 << "\n";
		}
		else if (linha[i] == '$' && linha[i + 3] == '\0') {
			registrador2[0] = '$'; registrador2[1] = linha[i + 1]; registrador2[2] = linha[i + 2]; registrador2[3] = '\0';
			cout << "rd: " << registrador2 << "\n";
		}
		else if (linha[i - 1] == ' ' && linha[i + 1] == '\0') {
			imediato = linha[i];
			cout << "immediate: " << imediato << "\n";
		}
	}
}




int main() {
		ifstream fin;
		fin.open("Exemplo01.txt");
		if (!fin.is_open()) { cout << "Erro na abertura do arquivo!\n"; exit(EXIT_FAILURE); }
		char linha[50];
		int val;
		while (fin.good()) {
			fin.getline(linha, 50);
			cout << linha << "\n";
			obterLabel(linha);
			val =obterTipo(linha);
			cout << val << endl;
			obterInfo(linha);
			
		}
}