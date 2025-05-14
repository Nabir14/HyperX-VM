// HyperX VM nade by Nabur14
// version 0.1

#include <stdio.h>

// Machine Specs Init
#define HMX_MEM_SIZE 128
#define HMX_DISPLAY_LIMIT 3

char dBuffer[4][4];
int mem[128];
int reg[3];
char cSet[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

// Test Rom
char rom[13] = {
	'm', 'x', '1',
	'm', 'y', '2',
	'a', 'x', 'y',
	'd', '0', 'x', ';',
};

// Machine Components Functions
void logMem(){
	printf("HMX_LOG: Memory: ");
	for(int i = 0; i <= HMX_MEM_SIZE; i++){
		printf("%x", mem[i]);
		if(mem[i] == 0xf){			
			break;
		}
	}
	printf("\n");
}

void display(){
	for(int x = 0; x <= HMX_DISPLAY_LIMIT; x++){
		for(int y = 0; y <= HMX_DISPLAY_LIMIT; y++){
			printf("%c", dBuffer[x][y]);
			if(y == 3){
				printf("\n");
			}
		}
	}
}

void dbAlloc(int x, int y, int c){
	dBuffer[x][y] = cSet[c];
}

// Machine Methods
void HMX_Start(){
	printf("[hmX v0.1]\n");
	printf("HMX_LOG: Allocating Display Buffer...\n");
	for(int i = 0; i <= HMX_MEM_SIZE; i++){
		mem[i] = 0x0;
	}
	for(int x = 0; x <= HMX_DISPLAY_LIMIT; x++){
		for(int y = 0; y <= HMX_DISPLAY_LIMIT; y++){
			dbAlloc(x, y, 0);
		}
	}
	display();
}
void HMX_Load(){
	for(int i = 0; i <= 128; i++){
		if(rom[i] == 'm'){
			mem[i] = 0xe;
		}else if(rom[i] == 'd'){
			mem[i] = 0xd;
		}else if(rom[i] == 'a'){
			mem[i] = 0xa;
		}else if(rom[i] == '0'){
			mem[i] = 0x0;
		}else if(rom[i] == '1'){
			mem[i] = 0x1;
		}else if(rom[i] == '2'){
			mem[i] = 0x2;
		}else if(rom[i] == '3'){
			mem[i] = 0x3;
		}else if(rom[i] == '4'){
			mem[i] = 0x4;
		}else if(rom[i] == '5'){
			mem[i] = 0x5;
		}else if(rom[i] == '6'){
			mem[i] = 0x6;
		}else if(rom[i] == '7'){
			mem[i] = 0x7;
		}else if(rom[i] == 'x'){
			mem[i] = 0x8;
		}else if(rom[i] == 'y'){
			mem[i] = 0x9;
		}else if(rom[i] == ';'){
			mem[i] = 0xf;
			break;
		}else{
			printf("HMX_ERROR: Illegal Instruction'%c'\n", rom[i]);
			break;
		}
	}
	logMem();
}
void HMX_Execute(){
	for(int i = 0; i <= HMX_MEM_SIZE; i++){
		if(mem[i] != 0xf){
			if(mem[i] == 0xe){
				if(mem[i+1] == 0x8 && mem [i+2] == 0x9){
					reg[0] = reg[1];
				}else if(mem[i+1] == 0x9 && mem[i+2] == 0x8){
					reg[1] = reg[0];
				}else{
					if(mem[i+1] == 0x8){
						reg[0] = mem[i+2];
					}else if(mem[i+1] == 0x9){
						reg[1] = mem[i+2];
					}
				}
			}else if(mem[i] == 0xa){
				if(mem[i+1] == 0x8 && mem[i+2] == 0x9){
					reg[0] = reg[0] + reg[1];
				}else if(mem[i+1] == 0x9 && mem[i+2] == 0x8){
					reg[1] = reg[0] + reg[1];
				}else if(mem[i+1] == 0x8){
					reg[0] = reg[0] + mem[i+2];
				}else{
					reg[1] = reg[1] + mem[i+2];
				}
			}else if(mem[i] == 0xd){
				if(mem[i+2] == 0x8){
					dbAlloc(mem[i+1], mem[i+1], reg[0]);
				}else if(mem[i+2] == 0x9){
					dbAlloc(mem[i+1], mem[i+1], reg[1]);
				}else{
					dbAlloc(mem[i+1], mem[i+1], mem[i+2]);
				}
				printf("HMX_LOG: Re-allocating Display Buffer...\n");
			}
		}
	}
	display();
}

int main(){
	HMX_Start();
	HMX_Load();
	HMX_Execute();
	return 0;
}
