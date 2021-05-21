
#include <fstream>
#include <string.h>
#include <iostream>
#include <time.h>

using namespace std ;

#define Size_Training 60000
#define Size_Test 10000
#define Size_Image 784
#define Size_Line 28

int Data_Training[Size_Training][Size_Image] ;
int Data_Training_Answers[Size_Training] ;
int Data_Test[Size_Test][Size_Image] ;
int Data_Test_Answers[Size_Test] ;

void read_Data(){
	 
	FILE * fp;
	char * line = NULL;
	size_t len = 0;

	const char *s = " ";
	char *token = NULL;

	fp = fopen("StockTraining.txt", "r");
	if (fp == NULL) {
		printf("Error opening Train\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < Size_Training; i++) {
		getline(&line, &len, fp);

		token = strtok(line, s);
		for (int j = 0; j < Size_Image; j++) {
			Data_Training[i][j] = atoi(token);
			token=strtok(NULL,s);
		}
		Data_Training_Answers[i] = atoi(token);
	}

	fp = fopen("StockTest.txt", "r");
	if (fp == NULL) {
		printf("Error opening test \n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < Size_Test; i++) {
		getline(&line, &len, fp);

		token = strtok(line, s);
		for (int j = 0; j < Size_Image; j++) {
			Data_Test[i][j] = atoi(token);
			token=strtok(NULL,s);
		}
		Data_Test_Answers[i] = atoi(token);
	}
	
cout << "Complete" << endl; 	
	
}

void Noise_Line(){
	int chance = 100 , Spacing = 21 ;
	for(int Image = 0 ; Image < Size_Training ; Image++ ){
		if((rand() % 100) <= chance){
		int Line = rand() % 8 ;
			for(int Pixel = 0 ; Pixel < Size_Line  ; Pixel++ ){
				if(rand() % 100 <= chance) Data_Training[Image][(Line * Size_Line) + Pixel ] = 1 ; 
				if(rand() % 100 <= chance) Data_Training[Image][((Line + Spacing) * Size_Line) + Pixel ] = 1; 
			}
		}
	}
	cout << "Noise lines added to training data" << endl ; 
	
	for(int Image = 0 ; Image < Size_Test ; Image++ ){
		if((rand() % 100) <= chance){
		int Line = rand() % 4 ;
			for(int Pixel = 0 ; Pixel < Size_Line; Pixel++ ){
				if(rand() % 100 >= chance) Data_Test[Image][(Line * Size_Line) + Pixel] = 1 ; 
				if(rand() % 100 >= chance) Data_Test[Image][((Line + Spacing) * Size_Line) + Pixel] = 1; 
			}
		}
	}
	cout << "Noise lines added to test data" << endl ; 
}

void Noise_Rand(){
	int Num = 80 , chance = 50 ;  
	for(int Image = 0 ; Image < Size_Training ; Image ++){
		for(int i = 0 ; i <= Num ; i++ ){
			int Pixel = rand() % Size_Image ;
			if((rand() % 100) <= chance) Data_Training[Image][Pixel] = !Data_Training[Image][Pixel] ; 
		}
	}
	
	for(int Image = 0 ; Image < Size_Test ; Image ++){
		for(int i = 0 ; i <= Num ; i++ ){
			int Pixel = rand() % Size_Image ;
			if((rand() % 100) <= chance) Data_Test[Image][Pixel] = !Data_Test[Image][Pixel] ; 
		}
	}	
}

void Write_Data() {
	
	remove("MNISTTraining.txt");
	remove("MNISTTest.txt");

	//write training file
	fstream Train;
	Train.open("MNISTTraining.txt" , ios::app);
	if(!Train.good()){			
		cerr << "Error opening MNISTTraining.txt (write)" << endl;
		exit(EXIT_FAILURE);
	}	
	
	for(int i = 0 ; i < Size_Training ; i++){
		
		for(int j = 0 ; j < Size_Image ; j++){
			Train << Data_Training[i][j] << " " ; 
		}
		Train << Data_Training_Answers[i] << endl ;
	}
	Train.close() ; 
	
	//write testing file
	fstream Test;
	Test.open("MNISTTest.txt" , ios::app);
	if(!Test.good()){			
		cerr << "Error opening MNISTTest.txt (write)" << endl;
		exit(EXIT_FAILURE);
	}	
	
	for(int i = 0 ; i < Size_Test ; i++){
		
		for(int j = 0 ; j < Size_Image ; j++){
			Test << Data_Test[i][j] << " " ; 
		}
		Test << Data_Test_Answers[i] << endl ;
	}
	Test.close() ; 
}

void output(int Num){
	
	
	cout << "Image #" << Num <<". Example of digit " << Data_Training_Answers[Num] << "."  << endl; 
	for (int y = 0; y < Size_Image/Size_Line ; y++) {
		for (int x = 0; x < Size_Line; x++) {
			if(Data_Training[Num][x+Size_Line*y] == 1) {
				printf("@");
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
	
	cout << endl;
}

int main(){
	
srand(time(NULL)*clock());
	
int Num = rand() % Size_Training ;
 
	read_Data() ;
	
	cout << "read data complete" << endl ; 
	
	output(Num);
	
	Noise_Line();
	cout << "line noise added" << endl ;
	
	//Noise_Rand();
	cout << "Random Noise Added" <<endl ; 
	
	output(Num);
	
	Write_Data(); 
	cout << "write data complete" << endl ; 
	


cout <<"end Program" << endl ; 
return 0 ; 
}

