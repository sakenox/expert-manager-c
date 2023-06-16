/*project - programming
//Program that has a database of citizen information
/*Functions that the program should have

1)Register a new citizen.
Required information: name, surname, ID, address, phone number, email
2)Modify the data of a citizen. (Use a function to find the data of the citizen first)
3)Delete the data of a citizen
4)Search by a) name b) surname (display all persons with this surname) c) ID d) phone number
5)Print on screen all the data of the citizens: a) by registration order 
6) alphabetically by name 
7) alphabetically by surname
0)Exit the program
*/

//Main headers 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX 10000 //nr i qytetareve ne qytetin X
int struktura =  0;
FILE *fptr;

//deklarimi i funksioneve
void find();
void modifiko();
void menu();
void kthim();
void load_info();
void export_info();
void welcome_screen();
void printall();
void find_id();
void find_nr();
void shto();
void fshi();
void find_mbiemri();
void find_emri();
int id_print();
void radhit_emri();
void radhit_mbiemri();

// struktura
struct Qytetar{
	char emri[50];
	char mbiemri[50];
	char id[10];
	char numer[12];
	char adresa[50];
	char email[50];
};
struct Qytetar db[MAX];
struct Qytetar db2[MAX];

int main() {
	welcome_screen();
	load_info();
	sleep(3);
	menu();
	return 0;
}

void welcome_screen()
{
	printf(" __ __|     _ _|       \\  |       ___|       | \n");
	printf("    |         |       |\\/ |     \\___ \\       | \n");
	printf("    |         |       |   |           |     _| \n");
	printf("   _|       ___|     _|  _|     _____/      _) \n");
	printf("\nMiresevini ne programin TIMS. Programi po hapet (~)...");
}


void load_info(){
	fptr = fopen("db.txt", "r");
	if (fptr == NULL) {
        fptr = fopen("db.txt", "w");
    }
	fscanf(fptr, "%d", &struktura);
	for(int i = 0; i < struktura;i++){
		fscanf(fptr, "%s ", &db[i].emri);
		fscanf(fptr, "%s ", &db[i].mbiemri);
		fscanf(fptr, "%s ", &db[i].id);
		fscanf(fptr, "%s ", &db[i].numer);
		fscanf(fptr, "%s ", &db[i].adresa);
		fscanf(fptr, "%s ", &db[i].email);
	}
	fclose(fptr);
}

void export_info() {
	fptr = fopen("db.txt", "w");
	if (fptr == NULL) {
        printf("File nuk mund te hapet.\n");
        return;
    }
	fprintf(fptr, "%d\n", struktura);
	for(int i = 0; i < struktura; i++){
		fprintf(fptr, "%s %s %s %s %s %s\n", db[i].emri, db[i].mbiemri, db[i].id, db[i].numer, db[i].adresa, db[i].email);
	}
	fclose(fptr);
}

void menu()
{
	system("cls");
	while (true){
		printf("Opsionet:\n");
		printf("1-Shto nje te dhene\n2-Modifiko nje te dhene\n3-Fshi nje te dhene\n4-Kerko qyetetarin\n5-Printo database-in\n6-Radhit databazen sipas emrit\n7-Radhit databazen sipas mbiemrit\n0.Dil");
		int opsioni;
		printf("\n\n|~|:");
		scanf("%d", &opsioni);
		switch(opsioni){
			case 1:
				shto();
				kthim();
			case 2:
				modifiko();
				kthim();
			case 3:
				fshi();
				kthim();
			case 4:
				find();
				kthim();
			case 5:
				printall();
				kthim();
			case 6:
				radhit_emri();
				kthim();
			case 7:
				radhit_mbiemri();
				kthim();
			case 0:
				kthim();
			default:
				printf("\nOpsion i gabuar");
				break;
		}
	}
}

void shto() {
	    if (struktura < MAX) {
        printf("\nEmri:");
        scanf("%s", db[struktura].emri);
        printf("Mbiemri:");
        scanf("%s", db[struktura].mbiemri);
        printf("ID:");
        scanf("%s", db[struktura].id);
        printf("Numri:");
        scanf("%s", db[struktura].numer);
        printf("Adresa:");
        scanf("%s", db[struktura].adresa);
        printf("Email:");
        scanf("%s", db[struktura].email);
        struktura++;
        export_info();
        printf("\nQytetari u shtua me sukses.");
    } else {
        printf("\nDatabaza eshte e mbushur!");
    }
}

void modifiko(){
	int vendi = id_print();
	if (vendi == -1) {
        printf("\nQytetari nuk u gjet. Provoni perseri.");
    }
	printf("\nModifiko:\n1.Emri\n2.Mbiemri\n3.ID\n4.Numri\n5.Adresa\n6.Email\n\n|~|:");
	int opsioni;
	scanf("%d", &opsioni);
	switch(opsioni){
			case 1:
				printf("\nEmri:");
				scanf("%s", db[vendi].emri);
				break;
			case 2:
				printf("\nMbiemri:");
				scanf("%s", db[vendi].mbiemri);
				break;
			case 3:
				printf("\nID:");
				scanf("%s", db[vendi].id);
				break;
			case 4:
				printf("\nNumri:");
				scanf("%s", db[vendi].numer);
				break;
			case 5:
				printf("\nAdresa:");
				scanf("%s", db[vendi].adresa);
				break;
			case 6:
				printf("\nEmail:");
				scanf("%s", db[vendi].email);
				break;
			default:
				printf("\nOpsion i gabuar.");
				break;
		}
	
}

void fshi() {
	int vendi = id_print();
	if (vendi == -1) {
        printf("\nQytetari nuk u gjet. Provoni perseri.");
    }
	for(int i = vendi; i < struktura; i++){
		strcpy(db[i].id, db[i+1].id);
		strcpy(db[i].emri, db[i+1].emri);
		strcpy(db[i].mbiemri, db[i+1].mbiemri);
		strcpy(db[i].adresa, db[i+1].adresa);
		strcpy(db[i].email, db[i+1].email);
		strcpy(db[i].numer, db[i+1].numer);
		}
	struktura--;
	export_info();
}

void printall(){
	printf("\nPrintimi i databazes:\n");
		for(int i = 0; i < struktura;i++){
		printf("Qytetari %d\n", i+1);
		printf("Emri: %s\n", db[i].emri);
		printf("Mbiemri: %s\n", db[i].mbiemri);
		printf("ID: %s\n", db[i].id);
		printf("Numri: %s\n", db[i].numer);
		printf("Adresa: %s\n", db[i].adresa);
		printf("Email: %s\n\n", db[i].email);
	}
}

void find()
{
	printf("\n1.Sipas emrit\n2.Sipas mbiemrit\n3.Sipas ID-se\n4.Sipas numrit\n\n|~|:");
	int opsioni;
	scanf("%d", &opsioni);
	switch(opsioni){
		case 1:
			find_emri();
			break;
		case 2:
			find_mbiemri();
			break;
		case 3:
			find_id();
			break;
		case 4:
			find_nr();
			break;
		default:
			printf("\nOpsion i gabuar\n");
			break;
		}
}

void find_emri() {
	printf("Vendos emrin e qytetarit:");
	char prove[50];
	scanf("%s", prove);
	printf("\nDetaje\n");
	for(int i = 0; i < (struktura); i++){
		if(strcmp(prove, db[i].emri) == 0) {
			printf("Emri: %s\n", db[i].emri);
			printf("Mbiemri: %s\n", db[i].mbiemri);
			printf("ID: %s\n", db[i].id);
			printf("Numri: %s\n", db[i].numer);
			printf("Adresa: %s\n", db[i].adresa);
			printf("Email: %s\n", db[i].email);
			printf("\n");
		}
	}
}


void find_mbiemri(){
	printf("Vendos mbiemrin e qytetarit:");
	char prove[50];
	scanf("%s", prove);
	printf("\nDetaje\n");
	for(int i = 0; i < (struktura); i++){
		if(strcmp(prove, db[i].mbiemri) == 0) {
			printf("Emri: %s\n", db[i].emri);
			printf("Mbiemri: %s\n", db[i].mbiemri);
			printf("ID: %s\n", db[i].id);
			printf("Numri: %s\n", db[i].numer);
			printf("Adresa: %s\n", db[i].adresa);
			printf("Email: %s\n", db[i].email);
			printf("\n");
		}
	}
}


void find_id(){
	int vendi = id_print();
	if (vendi == -1) {
        printf("\nQytetari nuk u gjet. Provoni perseri.");
    }
	printf("Emri: %s\n", db[vendi].emri);
	printf("Mbiemri: %s\n", db[vendi].mbiemri);
	printf("ID: %s\n", db[vendi].id);
	printf("Numri: %s\n", db[vendi].numer);
	printf("Adresa: %s\n", db[vendi].adresa);
	printf("Email: %s\n", db[vendi].email);
}

void find_nr(){
	printf("Vendos numrin e qytetarit:");
	char prove[12];
	scanf("%s", prove);
	printf("\nDetaje\n");
	for(int i = 0; i < struktura; i++){
		if(strcmp(prove, db[i].numer) == 0) {
			printf("Emri: %s\n", db[i].emri);
			printf("Mbiemri: %s\n", db[i].mbiemri);
			printf("ID: %s\n", db[i].id);
			printf("Numri: %s\n", db[i].numer);
			printf("Adresa: %s\n", db[i].adresa);
			printf("Email: %s\n", db[i].email);
			printf("\n");
		}
	}
}

int id_print(){
	printf("Vendos ID-ne e qytetarit:");
	char prove[10];
	scanf("%s", prove);
    for(int i = 0; i < struktura; i++){
		if(strcmp(prove, db[i].id) == 0) {
		   return i;
		}
	}
	return -1;
}

void radhit_emri(){
	for(int i = 0; i < struktura;i++){	
		strcpy(db2[i].emri, db[i].emri);
		strcpy(db2[i].mbiemri, db[i].mbiemri);
		strcpy(db2[i].email, db[i].email);
		strcpy(db2[i].adresa, db[i].adresa);
		strcpy(db2[i].id, db[i].id);
		strcpy(db2[i].numer, db[i].numer);
	}
	
	printf("\nDuke radhitur databazen sipas emrit");
	for(int i = 0; i < struktura;i++){
		for(int j = i + 1; j < struktura;j++){
			if(strcmp(db2[i].emri, db2[j].emri) > 0) {
				strcpy(db2[i].emri, db2[j].emri);
				strcpy(db2[i].mbiemri, db2[j].mbiemri);
				strcpy(db2[i].email, db2[j].email);
				strcpy(db2[i].adresa, db2[j].adresa);
				strcpy(db2[i].id, db2[j].id);
				strcpy(db2[j].numer, db2[j].numer);
				strcpy(db2[j].emri, db[i].emri);
				strcpy(db2[j].mbiemri, db[i].mbiemri);
				strcpy(db2[j].email, db[i].email);
				strcpy(db2[j].adresa, db[i].adresa);
				strcpy(db2[j].id, db[i].id);
				strcpy(db2[j].numer, db[i].numer);
				
			} 
		}
	for(int i = 0; i < struktura;i++){	
		strcpy(db[i].emri, db2[i].emri);
		strcpy(db[i].mbiemri, db2[i].mbiemri);
		strcpy(db[i].email, db2[i].email);
		strcpy(db[i].adresa, db2[i].adresa);
		strcpy(db[i].id, db2[i].id);
		strcpy(db[i].numer, db2[i].numer);
	}
		
	}
	export_info();
	printf("\nU krye!\n");
}

void radhit_mbiemri(){
	for(int i = 0; i < struktura;i++){	
		strcpy(db2[i].emri, db[i].emri);
		strcpy(db2[i].mbiemri, db[i].mbiemri);
		strcpy(db2[i].email, db[i].email);
		strcpy(db2[i].adresa, db[i].adresa);
		strcpy(db2[i].id, db[i].id);
		strcpy(db2[i].numer, db[i].numer);
	}
	
	for(int i = 0; i < struktura;i++){
		for(int j = i + 1; j < struktura;j++){
			if(strcmp(db2[i].mbiemri, db2[j].mbiemri) > 0) {
				strcpy(db2[i].emri, db2[j].emri);
				strcpy(db2[i].mbiemri, db2[j].mbiemri);
				strcpy(db2[i].email, db2[j].email);
				strcpy(db2[i].adresa, db2[j].adresa);
				strcpy(db2[i].id, db2[j].id);
				strcpy(db2[j].numer, db2[j].numer);
				strcpy(db2[j].emri, db[i].emri);
				strcpy(db2[j].mbiemri, db[i].mbiemri);
				strcpy(db2[j].email, db[i].email);
				strcpy(db2[j].adresa, db[i].adresa);
				strcpy(db2[j].id, db[i].id);
				strcpy(db2[j].numer, db[i].numer);
				
			} 
		}
	for(int i = 0; i < struktura;i++){	
		strcpy(db[i].emri, db2[i].emri);
		strcpy(db[i].mbiemri, db2[i].mbiemri);
		strcpy(db[i].email, db2[i].email);
		strcpy(db[i].adresa, db2[i].adresa);
		strcpy(db[i].id, db2[i].id);
		strcpy(db[i].numer, db2[i].numer);
	}
		
	}
	export_info();
	printf("\nU krye!\n");
}
