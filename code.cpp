#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> //για τη bool
#include <ctype.h>
#define STR_SIZE 2009999 //το μέγιστο επιτρεπόμενο μέγεθος string ανά πληκτρολόγηση
#include<unistd.h>
#include <locale.h>
#include <time.h>
#include <conio.h> //για να δουλεύει η αναζητηση στα ελληνικά

typedef struct {
    char name[50];
    char surname[50];
    float vGrade;
    float wGrade;
    float average;
} Student;



const char* dashes = "--------------------------------------------------------------------------------------";

void swapStudents(Student* a, Student* b) 
{
    Student temp = *a;
    *a = *b;
    *b = temp;
}
void checkString(char *msg, char *temp) 
{
    bool flag;

    do {
        flag = true;

        printf("%s", msg);
        gets(temp);

        if (strlen(temp) == 0) // Έλεγχος αν η είσοδος είναι κενή
		{
            flag = false; // flag false για να ζητηθεί εκ νέου είσοδος
            printf("\n\nΔεν δώσατε καμία είσοδο!\a\nΠαρακαλώ προσπαθήστε ξανά!\n\n");
        } 
		else 
		{
            for (int i = 0; i < strlen(temp); i++) // Έλεγχος κάθε χαρακτήρα της εισόδου
			{
                if (!isalpha(temp[i])) // Αν ο χαρακτήρας δεν είναι γράμμα
				{
					flag = false;
                    printf("\n\nΔεν γινεται να σε λένε %s ...\a\nΠαρακαλώ προσπαθήστε ξανά!\n\n",temp);
                    break;
				}
            }
        }

        if (!flag) // Αν χρειάζεται να ζητηθεί εκ νέου είσοδος, καθυστέρηση και καθαρισμός της οθόνης
		{
            system("pause");
            system("cls");
        }

    } while (!flag); // Συνέχιση της επανάληψης εάν flag είναι false
     
}
void printStudent(const Student* students) 
{
    int i; //Τα %-__ είναι για την στοίχηση του κειμένου
	printf("|  %-15s   %-15s   %-15.2f   %-15.2f   %-12.2f|\n", students[i].name, students[i].surname, students[i].vGrade, students[i].wGrade, students[i].average);
	
}
void bubbleSort(Student* students, int numberOfStudents) 
{
    for (int i = 0; i < numberOfStudents - 1; i++) {
        for (int j = 0; j < numberOfStudents - i - 1; j++) {
            if (students[j].average < students[j + 1].average) {
                swapStudents(&students[j], &students[j + 1]);
            }
        }
    }
}
int intAfterCheck(char *msg)
{
	char temp[STR_SIZE];
	int i, arith;
	bool flag;
	
	do
	{
		flag = 1;
		
		printf("%s", msg);
		gets(temp);
		
		if(strlen(temp)==0)	//Αν πατήσει αμέσως ENTER
			flag=0;	//η flag γίνεται false ώστε να ξαναζητήσει input
		
		else if((temp[0]=='+' || temp[0]=='-') && strlen(temp)==1)
			flag=0;
		
		else if(temp[0]!='+' && temp[0]!='-') //Αν ΔΕΝ πατήσει πρώτα + ή/και - να το δεχτεί ως επιτρεπτό
		{
			for(i=0; i<strlen(temp); i++)
			{
				if(isdigit(temp[i])!=0) //αν κάθε πλήκτρο είναι από 0 ώς και 9 τότε η flag να παραμείνει true
					flag = flag & 1;//bitwise and (κάνει and bit προς bit)
				else				//αλλιώς να γίνει false
					flag = flag & 0;//bitwise and (κάνει and bit προς bit)
			}
		}
		
		//Αν δώσει ++3 ή +-3 ή -+3 ή --3 να μην επιτραπεί
		else if((temp[0]=='+'&&temp[1]=='+')|| (temp[0]=='+'&&temp[1]=='-') || (temp[0]=='-'&&temp[1]=='+') || (temp[0]=='-'&&temp[1]=='-')) //Αν πατήσει πρώτα + ή/και - να το δεχτεί ως επιτρεπτό
			flag = 0; //η flag να γίνει false
		
		//Αν δώσει + ή - στην αρχή αλλά το δεύτερο πλήκτρο δεν είναι ούτε + ούτε -	
		else if((temp[0]=='+'&&temp[1]!='+')|| (temp[0]=='+'&&temp[1]!='-')||(temp[0]=='-'&&temp[1]!='+') || (temp[0]=='-'&&temp[1]!='-')) //Αν πατήσει πρώτα + και δεν πατήσει μετά - (ή το ανάποδο) να το δεχτεί ως επιτρεπτό 
		{	
			for(i=1; i<strlen(temp); i++)
			{
				if(isdigit(temp[i])!=0) //αν κάθε πλήκτρο είναι από 0 ώς και 9 τότε η flag να παραμείνει true
					flag = flag & 1;//bitwise and (κάνει and bit προς bit)
				else				//αλλιώς να γίνει false
					flag = flag & 0;//bitwise and (κάνει and bit προς bit)
			}
		}		
		
		if(flag==0) //Αν η flag έγινε false, τότε θα ζητήσει εκ νέου αριθμό
		{
			printf("\n\nΔεν δώσατε αριθμό!\a\nΠαρακαλώ προσπαθήστε ξανά!\n\n");
			system("pause");
			system("cls");
		}
	}while(flag==0); //Όσο η flag παραμένει false το πρόγραμμα θα ζητάει εκ νέου αριθμό
	
	return atoi(temp);//Μόλις βγει από τη while σίγουρα θα έχει πάρει αριθμούς σε όλο το string, 
					  //οπότε μετατρέπουμε το string σε αριθμό
}
float floatAfterCheck(char *msg)
{
	char temp[STR_SIZE];
	int i, count, flag=0;
	float arith;
	
	do
	{
		flag=1; //Η flag είναι αρχικά true
		count=0;
		
		printf("%s", msg);
		gets(temp);
		
		if(strlen(temp)==0)	//Αν πατήσει αμέσως ENTER
			flag=0;	//η flag γίνεται false ώστε να ξαναζητήσει input
		else
		{
			//έλεγχος αν υπάρχουν 2 ή περισσότερες τελείες
			for(i=0; i<strlen(temp)-1; i++)
				if(temp[i]=='.')
					count++;
			
			if (count>=2)//Αν υπάρξουν τελειές (.) περισσότερες της μίας, δηλαδή από 2 και πάνω,
				flag=0; //κάνε τη flag false
				
			if(temp[0] == '.' || temp[strlen(temp)-1] == '.')	//έλεγχος αν η είσοδος ξεκινά ή τελειώνει με τελεία(.)
				flag=0;
			
			if((temp[0]=='+' || temp[0]=='-') && strlen(temp)==1)
				flag=0;
				
			if(temp[0]!='+' && temp[0]!='-')
			{
				//έλεγχος αν όλα τα υπόλοιπα πλήκτρα είναι αριθμοί	
				if(count<=1)//αν υπάρχει ή μία ή καμμία τελεία (.)
				{
					for(i=0; i<strlen(temp); i++)
					{
						if(temp[i]=='.')//αν δεις οποιοδήποτε πλήκτρο με τελεία (.)
							continue;   //αγνόησε το
						else
						{
							if(isdigit(temp[i])!=0) //αν κάθε πλήκτρο είναι από 0 ώς και 9 τότε η flag να παραμείνει true
								flag = flag * 1;//bitwise and (κάνει and bit προς bit)
							else					//αλλιώς να γίνει false
								flag = flag * 0;//bitwise and (κάνει and bit προς bit)
						}
					}
				}	
			}
			
			//Αν δώσει ++3 ή +-3 ή -+3 ή --3 να μην επιτραπεί
			if((temp[0]=='+'&&temp[1]=='+') || (temp[0]=='+'&&temp[1]=='-') || (temp[0]=='-'&&temp[1]=='+') || (temp[0]=='-'&&temp[1]=='-')) //Αν πατήσει πρώτα + ή/και - και μετά + ή/και - να μην το δεχτεί ως επιτρεπτό
				flag = 0; //η flag να γίνει false
			
			if((temp[0]=='+'&&temp[1]=='.') || (temp[0]=='-'&&temp[1]=='.')) //Αν πατήσει πρώτα + ή/και - και μετά . να μην το επιτρέψει
				flag = 0; //η flag να γίνει false
				
			//Αν δώσει + ή - στην αρχή αλλά το δεύτερο πλήκτρο δεν είναι ούτε + ούτε -	
			if((temp[0]=='+'&&temp[1]!='+') || (temp[0]=='+'&&temp[1]!='-') || (temp[0]=='-'&&temp[1]!='+') || (temp[0]=='-'&&temp[1]!='-')) //Αν πατήσει πρώτα + και δεν πατήσει μετά - (ή το ανάποδο) να το δεχτεί ως επιτρεπτό 
			{	
				for(i=1; i<strlen(temp); i++)
				{
					if(temp[i]=='.')//αν δεις οποιοδήποτε πλήκτρο με τελεία (.)
						continue;   //αγνόησε το
					else
					{
						if(isdigit(temp[i]) != 0) //αν κάθε πλήκτρο είναι από 0 ώς και 9 τότε η flag να παραμείνει true
							flag = flag * 1;//bitwise and (κάνει and bit προς bit)
						else					//αλλιώς να γίνει false
							flag = flag * 0;//bitwise and (κάνει and bit προς bit)
					}
				}
			}
		}
		
		if(flag==0) //Αν η flag έγινε false, τότε θα ζητήσει εκ νέου αριθμό
		{
			printf("\n\nΔεν δώσατε αριθμό! \a\nΠαρακαλώ προσπαθήστε ξανά!\n\n");
			system("pause");
			system("cls");
		}
	}while(flag==0); //Όσο η flag παραμένει false το πρόγραμμα θα ζητάει εκ νέου αριθμό
	
	return atof(temp);//Μόλις βγει από τη while σίγουρα θα έχει πάρει αριθμούς σε όλο το string, 
					  //οπότε μετατρέπουμε το string σε αριθμό
}
void searchForStudentEn(Student students[], int numberOfStudents) 
{
	char wannaSearch;
    
				do 
				{
       	 			printf("\n\nΘέλετε να πραγματοποιήσετε κάποια αναζήτηση μέσα στη Βάση Δεδομένων; (y/n)");
       	 			printf("\nΑπάντηση: ");
        			scanf(" %c", &wannaSearch);
        			getchar(); //Καθαρισμός του buffer

        			wannaSearch = toupper(wannaSearch); //Μετατροπή της εισόδου σε κεφαλαία

					while (wannaSearch != 'Y' && wannaSearch != 'N') // Επανάληψη μέχρι να λάβει έγκυρη απάντηση
        			{
            			printf("\nΛάθος εισαγωγή. Παρακαλώ εισάγετε 'y' ή 'n'.\n");
            			printf("\nΑπάντηση: ");
            			scanf(" %c", &wannaSearch);
            			getchar();
           				wannaSearch = toupper(wannaSearch);
       				}
        			if (wannaSearch == 'Y') 
					{
           				system("cls");
            			printf("Παρακαλώ δώστε το ονοματεπώνυμο ενός μαθητή προς αναζήτηση\n");

            			char nameOfStudent[50];
            			char surnameOfStudent[50];
						checkString("Εισάγετε Όνομα: ", nameOfStudent); // Κλήση συνάρτησης για είσοδο ονόματος
						checkString("Εισάγετε Επίθετο: ", surnameOfStudent); // Κλήση συνάρτησης για είσοδο επιθέτου
					
            	
            			int studentFound = 0; // Μεταβλητή για τον έλεγχο αν βρέθηκε ο μαθητής
            			for (int i = 0; i < numberOfStudents; i++) 
						{
                			if (strcmp(nameOfStudent, students[i].name) == 0 && strcmp(surnameOfStudent, students[i].surname) == 0) 
							{
                    		printf("\nStudent found:\n\n");
                    		printf("Name: %s\n", students[i].name);
                    		printf("Surname: %s\n", students[i].surname);
                    		printf("V.Grade: %.2f\n", students[i].vGrade);
                    		printf("W.Grade: %.2f\n", students[i].wGrade);
                    		printf("Average: %.2f\n\n", students[i].average);
                    		studentFound = 1;
                    		break; // Έξοδος από την επανάληψη αν βρεθεί ο μαθητής
                			}
            			}
						if (!studentFound) 
							printf("\nΟ μαθητής %s %s δεν υπάρχει...\n\n",nameOfStudent,surnameOfStudent);
            		
        			} 
					else if (wannaSearch != 'N') 
						printf("Invalid input. Please enter 'y' or 'n'.\n");
        		

    			} while (wannaSearch == 'Y'); // Συνέχιση της διαδικασίας εάν ο χρήστης επιλέξει να συνεχίσει την αναζήτηση
}
void searchForStudentGr(Student students[], int numberOfStudents) 
{    
	char wannaSearch;
    
				do                     //////Δεν περιέχει ελέγχους//////
				{
       	 			printf("\n\nΘέλετε να πραγματοποιήσετε κάποια αναζήτηση μέσα στη Βάση Δεδομένων; (y/n)");
       	 			printf("\nΑπάντηση: ");
        			scanf(" %c", &wannaSearch);
        			getchar(); //Καθαρισμός του buffer

        			wannaSearch = toupper(wannaSearch); //Μετατροπή της εισόδου σε κεφαλαία

					while (wannaSearch != 'Y' && wannaSearch != 'N') // Επανάληψη μέχρι να λάβει έγκυρη απάντηση
        			{
            			printf("\nΛάθος εισαγωγή. Παρακαλώ εισάγετε 'y' ή 'n'.\n");
            			printf("\nΑπάντηση: ");
            			scanf(" %c", &wannaSearch);
            			getchar();
           				wannaSearch = toupper(wannaSearch);
       				}
        			if (wannaSearch == 'Y') 
					{
           				system("cls");
            			printf("Παρακαλώ δώστε το ονοματεπώνυμο ενός μαθητή προς αναζήτηση\n");

            			char nameOfStudent[50];
            			char surnameOfStudent[50];
            			printf("Όνομα: ");
            			scanf("%s", nameOfStudent);
						printf("Επίθετο: ");
						scanf("%s", surnameOfStudent);
						
            			int studentFound = 0; // Μεταβλητή για τον έλεγχο αν βρέθηκε ο μαθητής
            			for (int i = 0; i < numberOfStudents; i++) 
						{
                			if (strcmp(nameOfStudent, students[i].name) == 0 && strcmp(surnameOfStudent, students[i].surname) == 0) 
							{
                    		printf("\nStudent found:\n\n");
                    		printf("Name: %s\n", students[i].name);
                    		printf("Surname: %s\n", students[i].surname);
                    		printf("V.Grade: %.2f\n", students[i].vGrade);
                    		printf("W.Grade: %.2f\n", students[i].wGrade);
                    		printf("Average: %.2f\n\n", students[i].average);
                    		studentFound = 1;
                    		break; // Έξοδος από την επανάληψη αν βρεθεί ο μαθητής
                			}
            			}
						if (!studentFound) 
							printf("\nΟ μαθητής %s %s δεν υπάρχει...\n\n",nameOfStudent,surnameOfStudent);
            		
        			} 
					else if (wannaSearch != 'N') 
						printf("Invalid input. Please enter 'y' or 'n'.\n");
        		

    			} while (wannaSearch == 'Y'); // Συνέχιση της διαδικασίας εάν ο χρήστης επιλέξει να συνεχίσει την αναζήτηση
}
void statusBar() 
{
    system("chcp 437 > nul"); //Αλλαγή του κωδικού system για να δουλέψει το σωστό ASCII  
    system("cls");  

    for (int i = 0; i <= 100; ++i) {
        
        printf("\rStatus: %3d%% [", i); // Εκτύπωση του ποσοστού προόδου
        int pos = i / 2; 				// Υπολογισμός της θέσης της μπάρας προόδου
        for (int j = 0; j < 50; ++j) { // Επανάληψη για την εκτύπωση της μπάρας
            if (j < pos) {
                printf("%c", 219); // Εκτύπωση του γεμάτου τετραγώνου όταν η θέση είναι μέσα στο καλυπτόμενο εύρος
            } else {
                printf(" "); // Εκτύπωση κενού όταν η θέση είναι εκτός του καλυπτόμενου εύρους
            }
        }
        printf("]"); 
        usleep(9000); // Παύση
    }

    printf("\nDone! Press any key to continue...");
    getchar(); // Αναμονή για οποιοδήποτε πλήκτρο για να συνεχίσει
    system("cls");  
    system("chcp 1253 > nul");  //Αλλαγή του κωδικού system για να δουλέψουν τα υπόλοιπα 
}
void loopAndPrintEn(Student students[], int numberOfStudents)
{
	for (int i = 0; i < numberOfStudents; i++) 
				{
					printf("%dος Μαθητής",i+1);
					printf("\n__________________");
       				checkString("\n\tΌνομα: ",students[i].name); // Καλεί τη συνάρτηση για τον έλεγχο και εισαγωγή ονόματος
       				checkString("\tΕπώνυμο: ",students[i].surname); // Καλεί τη συνάρτηση για τον έλεγχο και εισαγωγή επιθέτου 
					        
					// Επανάληψη για την εισαγωγή του προφορικού βαθμού με έλεγχο ορίων
					do{
						printf("\tΠροφορικός βαθμός του/της %s %s στη C++ (από 0 ώς και 10):",students[i].name,students[i].surname);
            			students[i].vGrade = floatAfterCheck(" "); // Καλεί τη συνάρτηση για την εισαγωγή και έλεγχο του βαθμού
            			if (students[i].vGrade < 0 || students[i].vGrade > 10) 
                			printf("\nΛάθος εισαγωγή. Ο βαθμός πρέπει να είναι μεταξύ 0 και 10.\n");
            			} while (students[i].vGrade < 0 || students[i].vGrade > 10);

					do {
						printf("\tΓραπτός βαθμός του/της %s %s στη C++ (από 0 ώς και 10):",students[i].name,students[i].surname);
            			students[i].wGrade = floatAfterCheck(" ");
            			if (students[i].wGrade < 0 || students[i].wGrade > 10) 
                		
                			printf("\nΛάθος εισαγωγή. Ο βαθμός πρέπει να είναι μεταξύ 0 και 10.\n");
						
            			} while (students[i].wGrade < 0 || students[i].wGrade > 10);

					students[i].average = (students[i].vGrade * 0.4 + students[i].wGrade * 0.6); // Υπολογισμός του μέσου όρου
					
					printf("\n");
				
    			
    			}
        		statusBar(); // Καλεί τη συνάρτηση για την εμφάνιση μπάρας προόδου
        	
				printf("\n\n");
   				 				//Εκτυπώνει τον πίνακα με τα στοιχεία των μαθητών πριν την ταξινόμηση
    			printf(" %s \n", dashes);
				printf("|\t\t\t   ΜΗ ΤΑΞΙΝΟΜΗΜΈΝΟΣ ΠΊΝΑΚΑΣ\t\t\t\t       |\n");
				printf(" %s \n", dashes); 
    			printf("|                                    Πίνακας %d μαθητών                                 |\n",numberOfStudents);
    			printf(" %s \n", dashes);
    			printf("| Όνομα            Επώνυμο           Πρ.Βαθμός          Γρ.Βαθμός          Μ.Όρος      |\n");
   				 printf(" %s \n", dashes);
    			for (int i = 0; i < numberOfStudents; i++) 
				{
        			printStudent(&students[i]); // Καλεί τη συνάρτηση για την εκτύπωση των στοιχείων κάθε μαθητή
   				}
				printf("|                                                                                      |\n");
    			printf(" %s \n\n\n\n", dashes);
	
    			bubbleSort(students, numberOfStudents); // Καλεί τη συνάρτηση για την ταξινόμηση των μαθητών
    
				printf("\n");  
				 				// Εκτυπώνει τον πίνακα με τα στοιχεία των μαθητών μετά την ταξινόμηση
				printf(" %s \n", dashes);
    			printf("|\t\t\t      ΤΑΞΙΝΟΜΗΜΈΝΟΣ ΠΊΝΑΚΑΣ\t\t\t\t       |\n");
				printf(" %s \n", dashes); 
    			printf("|                                    Πίνακας %d μαθητών                                 |\n",numberOfStudents);
    			printf(" %s \n", dashes);
    			printf("| Όνομα            Επώνυμο           Πρ.Βαθμός          Γρ.Βαθμός          Μ.Όρος      |\n");
   				 printf(" %s \n", dashes);
    			for (int i = 0; i < numberOfStudents; i++) 
				{
        			printStudent(&students[i]);
    			}
				printf("|                                                                                      |\n");
    			printf(" %s \n\n\n\n", dashes);
				
}

void loopAndPrintGr(Student students[], int numberOfStudents)
{
	for (int i = 0; i < numberOfStudents; i++) 
				{
					printf("%dος Μαθητής",i+1);
					printf("\n__________________");
       												//Εισαγωγή στοιχείων//
				   	printf("\n\tΌνομα: ");
        			scanf("%s", students[i].name);
					printf("\tΕπώνυμο: ");
        			scanf("%s", students[i].surname);
  					printf("\tΠροφορικός βαθμός του/της %s %s στη C++ (από 0 ώς και 10): ",students[i].name,students[i].surname);
    				scanf("%f", &students[i].vGrade);
			
				 	printf("\tΓραπτός βαθμός στη C++ (από 0 ώς και 10): ");
    				scanf("%f", &students[i].wGrade);
					students[i].average = (students[i].vGrade * 0.4 + students[i].wGrade * 0.6);// Υπολογισμός του μέσου όρου
					printf("\n");
    			}
        		statusBar(); // Καλεί τη συνάρτηση για την εμφάνιση μπάρας προόδου
        
				printf("\n\n");
				//Εκτυπώνει τον πίνακα με τα στοιχεία των μαθητών πριν την ταξινόμηση
    			printf(" %s \n", dashes);	
				printf("|\t\t\t   ΜΗ ΤΑΞΙΝΟΜΗΜΈΝΟΣ ΠΊΝΑΚΑΣ\t\t\t\t       |\n");
				printf(" %s \n", dashes); 
    			printf("|                                    Πίνακας %d μαθητών                                 |\n",numberOfStudents);
    			printf(" %s \n", dashes);
    			printf("| Όνομα            Επώνυμο           Πρ.Βαθμός          Γρ.Βαθμός          Μ.Όρος      |\n");
   				printf(" %s \n", dashes);
   				
    			for (int i = 0; i < numberOfStudents; i++) 
				{
        			printStudent(&students[i]);// Καλεί τη συνάρτηση για την εκτύπωση των στοιχείων κάθε μαθητή
   				}
				printf("|                                                                                      |\n");
    			printf(" %s \n\n\n\n", dashes);
	
				

    			bubbleSort(students, numberOfStudents);// Καλεί τη συνάρτηση για την ταξινόμηση των μαθητών
    
				printf("\n");
								// Εκτυπώνει τον πίνακα με τα στοιχεία των μαθητών μετά την ταξινόμηση
				printf(" %s \n", dashes);
    			printf("|\t\t\t      ΤΑΞΙΝΟΜΗΜΈΝΟΣ ΠΊΝΑΚΑΣ\t\t\t\t       |\n");
				printf(" %s \n", dashes); 
    			printf("|                                    Πίνακας %d μαθητών                                 |\n",numberOfStudents);
    			printf(" %s \n", dashes);
    			printf("| Όνομα            Επώνυμο           Πρ.Βαθμός          Γρ.Βαθμός          Μ.Όρος      |\n");
   				printf(" %s \n", dashes);
    			for (int i = 0; i < numberOfStudents; i++) 
				{
        			printStudent(&students[i]);
    			}
				printf("|                                                                                      |\n");
    			printf(" %s \n\n\n\n", dashes);			
				
}

void writeToFile(Student *students, int numberOfStudents, char *filename) 
{
    FILE *file = fopen(filename, "w"); // Ανοίγει ένα αρχείο για εγγραφή (w)
    
    if (file == NULL) // Έλεγχος αν το αρχείο δεν άνοιξε σωστa
	{
        printf("Failed to open file");
        return;
    }
	// Εκτύπωση επικεφαλίδων του πίνακα με τα στοιχεία των μαθητών	
    fprintf(file, " %s \n", dashes);
    fprintf(file, "|                                 Πίνακας %d μαθητών                                    |\n",numberOfStudents);
    fprintf(file, " %s \n", dashes);
    fprintf(file, "| Όνομα            Επώνυμο           Πρ.Βαθμός          Γρ.Βαθμός          Μ.Όρος      |\n");
    fprintf(file, " %s \n", dashes);
    
    for (int i = 0; i < numberOfStudents; i++) 
	{
        fprintf(file, "|  %-15s   %-15s   %-15.2f   %-15.2f   %-12.2f|\n", 
        students[i].name, students[i].surname, students[i].vGrade, students[i].wGrade, students[i].average);
    }
    
    fprintf(file, " %s \n", dashes);
    fclose(file);// Κλείσιμο του αρχείου μετά την ολοκλήρωση της εγγραφής
}
void saveRandomStudentList(Student students[], int numberOfStudents)
{
	srand(time(NULL));//Για να δουλέψει η rand
    int randomChoice = rand() % 2; // Δημιουργία ενός τυχαίου αριθμού 0 ή 1

    if (randomChoice == 0) 
	{
		// Εκτύπωση μηνύματος για την αποθήκευση της βάσης δεδομένων χωρίς ταξινόμηση
        printf("Η Βάση Δεδομένων αποθηκεύτηκε στον τρέχοντα φάκελο, με αύξουσα ταξινόμηση ώς προς το Μέσο Όρο.\n");
        writeToFile(students, numberOfStudents, "_students.txt");// Καλεί τη συνάρτηση για την αποθήκευση των δεδομένων σε αρχείο
    } 
	else 
	{
		// Εκτύπωση μηνύματος για την αποθήκευση της βάσης δεδομένων μετά από ταξινόμηση
        printf("Η Βάση Δεδομένων αποθηκεύτηκε στον τρέχοντα φάκελο, με αύξουσα ταξινόμηση ώς προς το Μέσο Όρο.\n");
        bubbleSort(students, numberOfStudents); // Καλεί τη συνάρτηση για την ταξινόμηση των μαθητών ανάλογα με τον μέσο όρο
        writeToFile(students, numberOfStudents, "_students.txt");// Καλεί τη συνάρτηση για την αποθήκευση των δεδομένων σε αρχείο
    }
}

int main() 
{
	system("chcp 1253 > nul");
	
	int numberOfStudents;
//  Ζητά από τον χρήστη να εισάγει τον αριθμό των μαθητών που θα έχει η τάξη
	do
	{
		numberOfStudents = intAfterCheck("Πόσους μαθητές θα έχει η τάξη σας; ");// Καλεί τη συνάρτηση για την εισαγωγή ενός ακεραίου με έλεγχο
		if(numberOfStudents==0) // Εάν δοθεί 0, εμφανίζεται μήνυμα λάθους και ζητείται εκ νέου η εισαγωγή
			printf("\nΠρέπει να δωθεί θετικός αριθμός...\n\n");
					
	}while(numberOfStudents <= 0);	// Η επανάληψη συνεχίζεται μέχρι να ληφθεί ένας θετικός αριθμός	
	
   //Χρήση συνάρτησης calloc γαι την δέσμευση μνήμης
    Student *students = (Student*) calloc(numberOfStudents, sizeof(Student));
     
	printf("\nΘα πληκτρολογήσετε ονοματεπώνυμα με ΑΜΙΓΩΣ λατινικά γράμματα ή θα περιέχονται και ελληνικά γράμματα? \n\nΠατήστε 1 για Λατινικά ή 0 για Ελληνικά \n\nΣΗΜΕΙΩΣΗ: Σε περίπτωση που επιλέξετε Ελληνικά, δε θα είναι δυνατός κανένας έλεγχος για εκυρότητα ονομάτων.\n");

	int langChoice;
     do {
     	langChoice = intAfterCheck("\nΕισάγεται την επιλογή σας: ");
       
        // Ελέγχει αν η είσοδος είναι είτε 0 είτε 1
        if (langChoice == 0 || langChoice == 1) {
            break;  // Βγαίνει από την επανάληψη αν η είσοδος είναι έγκυρη
        }

        printf("Μη έγκυρη επιλογή. Οι επιτρεπτές τιμές είναι το 0 και το 1.\n");
    } while (1);  // Συνεχίζει να ζητάει είσοδο μέχρι να ληφθεί έγκυρη τιμή



	
	switch(langChoice)
	{
		case 1:
			{
				
				setlocale(LC_ALL, "en_US.utf8"); //Εντολή για αγγλικά
				system("cls");
				loopAndPrintEn(students, numberOfStudents);
				saveRandomStudentList(students, numberOfStudents);
				searchForStudentEn(students, numberOfStudents);
				printf("\nGoodbye!\n");
            	break;
			}
			
			case 0:
				{
				setlocale(LC_ALL, "el_GR.utf8"); //Εντολή για ελληνικά
				system("cls");
				loopAndPrintGr(students, numberOfStudents);
				saveRandomStudentList(students, numberOfStudents);
    			searchForStudentGr(students, numberOfStudents);
				printf("\nGoodbye!\n");
				break;
				}
			default:
            	printf("Invalid choice.\n");
           		return 1; 
            
	}
	free(students); //Αποδέσμευση μνήμης
	return 0;
}



