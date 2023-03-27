#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



//structure for char
typedef struct { 
	int char_count[39];
	char  cha_store[39];
	float percentage[39];
}charac;


// struct for words
typedef struct _{
	char * wordP;
	int WordOccur;
	float percentageW;
	struct _* next;
} word_str;


word_str * head =NULL;
word_str * wordArray =NULL;
word_str * headNode=NULL;
word_str * lastnode=NULL;


//global variables for char
int no_of_characters=0;
charac chara;
int all =0;
int char_count=0;
int index_char=0;
int count_character=0;

//global variables for word
int count_words=0;

//global variable for both word and char
int defult_w_c=0;
int scaled=0;


//predefined functions for char
void char_percentage(int all_char);
void char_counter(char ch);
void char_order();

//predefined functions for words
void word_pre_process(char word[],int len);
word_str * newWord(char* word);
word_str * serchAndAdd(char * word);
void display(word_str *newH);
void word_order();
void word_percentage();

//predefined for both
int printchart(int quantity, int scale,int word_on);





int main(int argc,char* argv[]){
	int len=0;
	//char filename[100];
	char word[100];
	char ch;
	int k=0;
	int defult_w_c=0; //defult =0  words; defult =1 char
	//int l=10;   //length for default print
	//int scaled=0;  //scaled=0, scaled off scaled=1 scaled on
	


	    int len_for_print=10, filenum =0;
    char filenames[10][70];// files to read

    int j=0;


    if(argc==1){
        printf("No input files were given\n");
        printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
        return 0;
    }

    if(argc==2){
        
        if(argv[1][0]=='-' ){
            
            if((strcmp(argv[1], "-w") == 0) || (strcmp(argv[1], "-c") == 0) || (strcmp(argv[1], "--scaled") == 0) ){
                printf("No input files were given\n");
                printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]); 
                return 0;               
            }else if( (strcmp(argv[1], "-l") == 0) ){
                printf("Not enough options for [-l]\n");
                printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);  
                return 0;                  
            }else{
                printf("Invalid option [%s] \n",argv[1]);
                printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                return 0;                
            }               
        }else{           
            strcpy(filenames[j++],argv[1]);
        }
    }else{
        int cflag=0;
        int wflag=0;
        int isNum=0;
        for(int i=1;i<argc;i++){

            if(argv[i][0]=='-'){
                if((strcmp(argv[i], "-l") != 0)&&(strcmp(argv[i], "-w") != 0)&&(strcmp(argv[i], "-c") != 0)&&(strcmp(argv[i], "--scaled") != 0)){
                    printf("Invalid option [%s] \n",argv[i]);
                    printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                    return 0;

                }if((strcmp(argv[i], "-l") == 0)){
                    if(i+1==argc){
                        printf("Not enough options for [-l]\n");
                        printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                        return 0;

                    }i++;
                    for(int k=1;k<strlen(argv[i]);k++){
                        if(isdigit(argv[i][k])==0){
                            isNum=1;
                            printf("Invalid options for [-l]\n");
                            printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                            return 0;
                        }
                    }if(isNum==0 && (argv[i][0]=='-') ){
                        isNum=1;
                        printf("Invalid option(negative) for [-l]\n");
                        printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                        return 0;

                    
                    }if(isNum==0 ){
                        sscanf(argv[i],"%d",&len_for_print);
                        if(len_for_print==0){
                            return 0;
                        }
                        
                    }
                }
            }
        }
        for(int i=1;i<argc;i++){
            if(argv[i][0]=='-'){
                if(strcmp(argv[i], "-w") == 0){

                    wflag=1;
                    if(cflag==0){
                        defult_w_c=0;
               
                    }if(cflag==1){
                        printf("[-c] and [-w] cannot use together\n");
                        printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                        return 0;
                    }
                }else if(strcmp(argv[i], "-c") == 0){
                    cflag=1;
                    if(wflag==0){
                       
                        defult_w_c=1;

                    }if(wflag==1){
                        printf("[-c] and [-w] cannot use together\n");
                        printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                        return 0;
                    }               

                }else if(strcmp(argv[i], "--scaled") == 0){
                    scaled=1;

                }else if(strcmp(argv[i], "-l") == 0){
                    i++;
                    //continue;
                }
            }
            else if((strcmp(argv[i-1], "-l") != 0) ){
                strcpy(filenames[j++],argv[i]);
    
            }
        }
    }

        if (len_for_print==0){
        return 0;
    }
    filenum=j;//no of files
    if(filenum==0){
        printf("No input files were given\n");
        printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
        return 0; 
    }


    FILE *fptr;
    for( j=0; j<filenum; j++){ 

        char* filename = filenames[j];
        fptr = fopen(filename, "r");  //open file in read 
    
        if (fptr==0) {
            printf("Cannot open one or more given files\n");
            return 0;
        }
        //**********************************WORD PROCES******************************************************

//for words	
	else if(defult_w_c==0)
		{
			while(fscanf(fptr,"%s",word) !=EOF ){
			len = strlen(word);
			word_pre_process(word, len);
			

			if(strcmp(word,"")!=0){ 
			//printf("%s\n", word);
			//word which have to be store


			count_words++;// count of the no of words
			char* wordPtr = strdup(word);
			serchAndAdd(wordPtr); //search for the word and if its not add to the ll

			}		
		}
		
		//printf("%d\n", count_words);
		//print of no of words
		//display(wordArray);


		word_order();
		word_percentage(count_words);

		//display(headNode);
		//displaying full linked list
	
	

	}


//********************************CHAR PROCESS****************************************************************
//for characters
	else if(defult_w_c==1)
		{
//character stiring process 
			while( ( ch= fgetc(fptr)) != EOF)
			{
				if (isalpha(ch) || isdigit(ch))
				{
					no_of_characters++;
					ch=tolower(ch);
					char_counter(ch);
				}
			}

			


			//count no of chars
			while(k<index_char){
			char_count = chara.char_count[k] + char_count;
			k++;
			}

			
			//end of character storing process

			char_order();
			char_percentage(char_count);
			

			//printf("%d\n", index_char);
		

			/*
			printf("all char = %d\n", char_count);
			for(int p =0; p < index_char ; p++)
			{
			printf("%c  -> %d   -> %.2f   \n    ", chara.cha_store[p], chara.char_count[p] ,chara.cha_percentage[p] );
			}
			printf("%d\n", index_char);
			printf("%c %d \n \n %c %d ", chara.cha_store[index_char-1], chara.char_count[index_char-1],chara.cha_store[index_char+1], chara.char_count[index_char+1] );
			*/
			

		}
	




	printchart(len_for_print,scaled,defult_w_c);
	//printing chart (size / no of bars, scaled on =1, scaled of = 0, defult word= 0/ defult char = 1)



			return 0;



        fclose(fptr);
    }





}


//********************************************functions for char *************************************************************************************************************************************************************************************************************

void char_counter(char ch){
	int i=0, def=0;

	while(chara.cha_store[i] != 0 && i < 36){
		if (chara.cha_store[i] == ch){
			chara.char_count[i]++;
			def=1;
		}
		i++;
	}
	if(!def){
		chara.cha_store[i] =ch;
		chara.char_count[i]=1;
	}
	index_char = i;
chara.cha_store[index_char+1]='\0';
chara.char_count[index_char+1]='\0';
}


void char_percentage(int all_char){
int g=0;

	while(g <36){ 
	chara.percentage[g] = chara.char_count[g]/(float)all_char*100;
	g++;
	}
}


void char_order(){
int i,j,temp;
char tempstore;
for(i=0; i<39; i++)
    {
        for(j=i+1; j<39; j++)
        {
      
            if(chara.char_count[i] < chara.char_count[j])
            {
                temp     			= chara.char_count[i];
                chara.char_count[i] = chara.char_count[j];
                chara.char_count[j] = temp;

                tempstore     		= chara.cha_store[i];
                chara.cha_store[i] 	= chara.cha_store[j];
                chara.cha_store	[j] = tempstore;


            }

        }
    }


}

//*******************************************end of char functions*********************************************************************************************
//-------------------------------------------------------------------------------------------------------------------------------------------------------------





//*******************************************functions for words*************************************************************************************************************************************************************************************************************

void word_percentage(int all_w){

	word_str * tempP=headNode;
while(tempP!= NULL){
	tempP->percentageW=tempP->WordOccur/(float)all_w*100;
	tempP=tempP->next;
}
}




void display(word_str *newH)
{
    while (newH != NULL)
    {
        printf("%d   %s  %.2f \n ", newH->WordOccur, newH->wordP, newH->percentageW );
        newH = newH->next;
    }
    printf("\n");
}


void word_pre_process(char word [], int leng){
	char temp[leng];
	int count_w;
	int i=0;

	for(count_w=0 ; count_w <leng ;count_w++ ){
		if(isalnum(word[count_w])==0){
			continue;
		}
		else{
			temp[i]=tolower(word[count_w]);
			i++;
		}
	}
	int j;
	for(j=0;j<i;j++){
		word[j]=temp[j];

	}
	word[j]='\0';
}



word_str *  newWord(char* wordPoint){
	wordArray= malloc(sizeof(word_str));


	wordArray->wordP=(char *)malloc((strlen(wordPoint))+1);
	strcpy(wordArray->wordP, wordPoint);                 //adding new word to the list
	wordArray->WordOccur=1;       					//asssing word occur as one;

	return wordArray;
}


word_str * serchAndAdd(char * wordpt){

	int prevWord=0;   //become one if it is a previous word
	word_str * temp= headNode;

	if (count_words==1){ 
		headNode=newWord(wordpt);
		lastnode=headNode;
		//printf("%s lastnode\n", lastnode->wordP);
		//printf("%s headNode\n", headNode->wordP);
		//printf("%s wordArray\n", wordArray->wordP);

	
	}

	else{
		while( temp != NULL){
		if(strcmp(temp->wordP, wordpt)==0){
			prevWord=1;
			temp->WordOccur=temp->WordOccur+1;
			//printf("%s lastnode\n", lastnode->wordP);
			//printf("%s headNode\n", headNode->wordP);
			//printf("%s wordArray\n", wordArray->wordP);


			return headNode;
		}
		temp=temp->next;
	}
	if(prevWord == 0){
		lastnode->next=newWord(wordpt);
		lastnode=lastnode->next;
			
			//printf("%s lastnode\n", lastnode->wordP);
			//printf("%s headNode\n", headNode->wordP);
			//printf("%s wordArray\n", wordArray->wordP);

		
		return wordArray;
	}
	}
	
	return headNode;

}

//word _sorting function
void word_order(){   

    word_str *tempW, *nodeW;
    char *temp_wordP;   
    int temp_WordOccur;   
    

    nodeW = headNode;
    tempW = nodeW->next; 

    while(nodeW->next != NULL && tempW !=NULL){
   
        while(tempW!=NULL){
	
            if(nodeW->WordOccur <= tempW->WordOccur){ 

                temp_WordOccur = nodeW->WordOccur;    
                nodeW->WordOccur = tempW->WordOccur;
                tempW->WordOccur = temp_WordOccur;

                temp_wordP = nodeW->wordP;        
                nodeW->wordP = tempW->wordP;
                tempW->wordP = temp_wordP;

            }
            tempW = tempW->next;
        }
        nodeW = nodeW->next;
        tempW = nodeW->next;
    }
    
}

//*******************************************end word functions*********************************************************************************************



//********************************************printing Function for both word and char*************************************************************************

int printchart(int quantity, int scale,int word_on){
	//for char printing
	




//**********************************************char printing***********************************
	if(word_on==1){
		int l,p,q,r,s,t;

		if(quantity>index_char){
			quantity=index_char;
		}
		printf("\n");
		for(p=0;p<quantity;p++){
			float begin = chara.percentage[p];
			float end 	= chara.percentage[0];
			if(end<10){
				l=71;				
			}
			else if(end>=10){
				l=70;
			}
			else if(end==100){
				l=69;
			}

			if(scale==1){
				q = (l*begin)/end;
			}
			else{
				q = (l*begin)/100;
			}

			int i;
			for(i=0;i<3;i++){
				if(i==1){
					printf(" %c	\u2502", chara.cha_store[p]);

					for(r=0; r<q;r++){
						printf("\u2591");
					}
					printf("%.2f%%", begin);
					printf("\n");
				}
				else{
					printf("\t\u2502");
					for(s=0; s<q;s++){
						printf("\u2591");

					}
					printf("\n");
				}
			}
			printf("\t\u2502");
			printf("\n");

		}
		printf("\t\u2514");
		for(t=0;t<76;t++){
			printf("\u2500");
		}
		printf("\n");
	return 0;
	}
//**************************************end of char printing*****************************************
//*************************************WORD PRINTING************************************************
	//for word printing
else if(word_on ==0){
	word_str * printTemp = headNode;
	int q,L=0,P=0,R,S,T,l,U,V;
	
	
	//asssigning maximum no of bars
	if(quantity>count_words){
		quantity=count_words;
	}


//printf("%d", quantity);

	float first_percentage=headNode->percentageW;

	printf("\n");
	for(P=0;P<quantity;P++){

		//printf("%d ",quantity);
		if(L<strlen(printTemp->wordP)){
			L=strlen(printTemp->wordP);
		}
		printTemp=printTemp->next;
		if(printTemp->next== NULL){
			break;
		}
	}


	for(int Q=0;Q<quantity;Q++){	
		if(first_percentage<10){
			l = 72;		
		}else if(first_percentage>=10){
			l = 71;
		}else if(first_percentage==100){
			l = 70;
		}

	if(scale==1){
		q = ((l-L)*(headNode->percentageW)/first_percentage);
			}
	else{
		q = ((l-L)*(headNode->percentageW)/100);
			}

	for(R=0;R<3;R++){
		if(R==1){
			printf(" %s ",headNode->wordP);
			for(S=0;S<(L-strlen(headNode->wordP));S++){
				printf(" ");
			}
			printf("\u2502");
			for(T=0;T<q;T++){
				printf("\u2591");
			}
			printf("%.2f%%",headNode->percentageW);
			printf("\n");
		}
		else{
			for(S=0;S<(L+2);S++){
				printf(" ");
			}
			printf("\u2502");
			for(T=0;T<q;T++){
				printf("\u2591");
			}
			printf("\n");
		}
	}
	for(U=0;U<L+2;U++){
		printf(" ");
	}
	printf("\u2502");
	printf("\n");

	headNode=headNode->next;
	if(headNode==NULL){
		for(V=0;V<L+2;V++){
			printf(" ");
		}
		printf("\u2514");
		for(U=0;U<(77-L);U++){
			printf("\u2500");
		}
		printf("\n");
		return 0;
	}





	}
	for(V=0;V<L+2;V++){
		printf(" ");
	}
	printf("\u2514");
	for(U=0;U<(77-L);U++){
		printf("\u2500");
	}
	printf("\n");
	
	return 0;

	}
return 0;
}



//@tettolizer