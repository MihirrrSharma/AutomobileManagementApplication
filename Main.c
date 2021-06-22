#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#define clrscr() printf("\e[1;1H\e[2J")

void SetColor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}

void ClearConsoleToColors(int ForgC, int BackC)
 {
 WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
               //Get the handle to the current output buffer...
 HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
                     //This is used to reset the carat/cursor to the top left.
 COORD coord = {0, 0};
                  //A return value... indicating how many chars were written
                    //   not used but we need to capture this since it will be
                      //   written anyway (passing NULL causes an access violation).
  DWORD count;

                               //This is a structure containing all of the console info
                      // it is used here to find the size of the console.
 CONSOLE_SCREEN_BUFFER_INFO csbi;
                 //Here we will set the current color
 SetConsoleTextAttribute(hStdOut, wColor);
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                          //This fills the buffer with a given character (in this case 32=space).
      FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

      FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
                          //This will set our cursor position for the next print statement.
      SetConsoleCursorPosition(hStdOut, coord);
 }
 return;
}
  
// Structure to store the user details
// i.e., Signup details
struct details {
    char uname[100];
    int age;
    char password[100];
    char email[100];
    char mobile[10];
};
  
// Structure to store the hotels
// and their food details
struct hotels {
    char hotel[100];
    char first_food[50];
    char second_food[50];
    char third_food[50];
    char fourth_food[50];
    char fifth_food[50];
    int first, second, third, fourth,fifth;
};
  
// Initialize the hotels and details
struct hotels m[10];
struct details s[100];
  
// Function to get the input for
// a new account
void signup();
  
// Function to check whether account
// is already existed or not
void account_check();
  
// Function to validate all input fields
int validate();
void login();
void userSetting();
void cart();
void search_by_hotels();
void search_by_food();
void food_order(int food);
  
// Function to initialize the hotels and
// food structure dynamically
void hotel_initialize();
void hotels(int hotel_choice);
  
int flag = 1, i, j = 0, count = 0, caps = 0;
int small = 0, special = 0, numbers = 0;
int success = 0, x, choice;
char temp_name[100], temp_password1[100];
char temp_password2[100], temp_email[100];
char temp_mobile[100];
  
int temp_age, total = 0, food_choice, n;
int hotel_choice, search_choice, confirm;
int ch, food, hotel_id;

int main(){

	ClearConsoleToColors(0,4);
	SetColor(14);
    while (1) {
        printf(""
               "\n\n\t\t\t\t\tWelcome to Online ");
        printf("Food Order - OFO\n\n\n\t\t\t\t1)SIGNUP\n");
        printf("\t\t\t\t2)LOGIN\n\t\t\t\t3)EXIT\n\n");
        printf("\t\t\t\tEnter Your Choice:\t");
        scanf("%d", &choice);
        switch (choice) {
        case 1: {
            signup();
            break;
        }
        case 2: {
            login();
            break;
        }
        case 3: {
            exit(0);
            return 0;
        }
        default: {
            printf("\nPlease Enter the ");
            printf("valid choice\n");
            break;
        }
        }
    }
    
	
	getch();
	return 0;
}


void signup()
{
	system("cls");
	
    printf("\n\n\t\t\t\t\tEnter Your Name: \t");
    scanf("%s", temp_name);
    //scanf("%[^\n]%*c", temp_name);
    //fgets(temp_name, 100, stdin);
  
    printf("\n\n\t\t\t\t\tEnter Your Age: \t");
    scanf("%d", &temp_age);
  
    printf("\n\n\t\t\t\t\tEnter Your Email: \t");
    scanf("%s", temp_email);
  
    printf("\n\n\t\t\t\t\tEnter Password: \t");
    scanf("%s", temp_password1);
  
    printf("\n\n\t\t\t\t\tConfirm Password: \t");
    scanf("%s", temp_password2);
  
    printf("\n\n\t\t\t\t\tEnter Your Contact Number: \t");
    scanf("%s", temp_mobile);
  
    // Function Call to validate
    // the user creation
    x = validate();
    if (x == 1)
        account_check();
}


// Function to validate the user
// for signup process
int validate()
{
    // Validate the name
    for (i = 0; temp_name[i] != '\0'; i++) {
        if (!((temp_name[i] >= 'a' && temp_name[i] <= 'z')
              || (temp_name[i] >= 'A'
                  && temp_name[i] <= 'Z'))) {
            printf("\n\n\t\t\t\t\tPlease Enter a");
            printf(" valid Name.\n");
            flag = 0;
            break;
        }
    }
    if (flag == 1) {
        count = 0;
  
        // Validate the Email ID
        for (i = 0;
             temp_email[i] != '\0'; i++) {
            if (temp_email[i] == '@'
                || temp_email[i] == '.')
                count++;
        }
        if (count >= 2
            && strlen(temp_email) >= 5) {
            // Validating the Password and
            // Check whether it matches
            // with Conform Password
            if (!strcmp(temp_password1,
                        temp_password2)) {
                if (strlen(temp_password1) >= 8
                    && strlen(temp_password1) <= 12) {
                    caps = 0;
                    small = 0;
                    numbers = 0;
                    special = 0;
                    for (i = 0; temp_password1[i] != '\0';
                         i++) {
                        if (temp_password1[i] >= 'A'
                            && temp_password1[i] <= 'Z')
                            caps++;
                        else if (temp_password1[i] >= 'a'
                                 && temp_password1[i]
                                        <= 'z')
                            small++;
                        else if (temp_password1[i] >= '0'
                                 && temp_password1[i]
                                        <= '9')
                            numbers++;
                        else if (temp_password1[i] == '@'
                                 || temp_password1[i] == '&'
                                 || temp_password1[i] == '#'
                                 || temp_password1[i]
                                        == '*')
                            special++;
                    }
                    if (caps >= 1 && small >= 1
                        && numbers >= 1 && special >= 1) {
                        // Validating the Input age
                        if (temp_age != 0 && temp_age > 0) {
                            // Validating the Input mobile
                            // number
                            if (strlen(temp_mobile) == 10) {
                                for (i = 0; i < 10; i++) {
                                    if (temp_mobile[i]
                                            >= '0'
                                        && temp_mobile[i]
                                               <= '9') {
                                        success = 1;
                                    }
                                    else {
                                        printf("\n\n\t\t\t\t\tPlease ");
                                        printf("Enter Valid ");
                                        printf("Mobile "
                                               "Number.\n\n");
                                        return 0;
                                        break;
                                    }
                                }
  
                                // Success is assigned with
                                // value 1, Once every
                                // inputs are correct.
                                if (success == 1)
                                    return 1;
                            }
                            else {
                                printf("\n\n\t\t\t\t\tPlease Enter the ");
                                printf("10 digit mobile ");
                                printf("number.\n\n");
                                return 0;
                            }
                        }
                        else {
                            printf("\n\n\t\t\t\t\tPlease Enter ");
                            printf("a valid age.\n\n");
                            return 0;
                        }
                    }
                    else {
                        printf("\n\n\t\t\t\t\tPlease Enter a ");
                        printf("strong password, Your ");
                        printf("password must contain ");
                        printf("atleast one uppercase, ");
                        printf("Lowercase, Number and ");
                        printf("special character.\n\n");
                        return 0;
                    }
                }
                else {
                    printf("\n\n\t\t\tYour Password is very ");
                    printf("short. Length must be ");
                    printf("between 8 to 12 letters.\n\n");
                    return 0;
                }
            }
            else {
                printf("\n\n\t\t\t\t\tPassword Mismatch\n\n");
                return 0;
            }
        }
        else {
            printf("\n\n\t\t\t\t\tPlease Enter"
                   " Valid E-Mail\n\n");
            return 0;
        }
    }
}


// Function to check if the account
// already exists or not
void account_check()
{
    for (i = 0; i < 100; i++) {
        // Check whether the email
        // and password are already
        // matched with existed account
        if (!(strcmp(temp_email, s[i].email)
              && strcmp(temp_password1,
                        s[i].password))) {
            printf("\n\n\t\t\t\t\tAccount Already ");
            printf("Existed. Please Login !!\n\n");
            main();
            break;
        }
    }
    // if account does not already
    // existed, it creates a new
    // one with new inputs
    if (i == 100) {
        strcpy(s[j].uname, temp_name);
        s[j].age = temp_age;
        strcpy(s[j].password, temp_password1);
        strcpy(s[j].email, temp_email);
        strcpy(s[j].mobile, temp_mobile);
        j++;
        printf("\n\n\t\t\t\t\tAccount Successfully ");
        printf("Created!!\n\n");
    }
}


// Function to Login the users
void login()
{   
    system("cls");
    printf("\n\n\t\t\t\t\t\t\tLOGIN\n\n");
    printf("\n\n\t\t\t\t\tEnter Your Email: \t");
    scanf("%s", temp_email);
    printf("\n\n\t\t\t\t\tEnter Your Password: \t");
    scanf("%s", temp_password1);
    for (i = 0; i < 100; i++) {
        // Check whether the input
        // email is already existed or not
        if (!strcmp(s[i].email, temp_email)) {
            // Check whether the password
            // is matched with the email or not
            if (!strcmp(s[i].password, temp_password1)) {
                printf("\n\n\t\t\t\t Welcome %s, ", s[i].uname);
                printf("Your are successfully ");
                printf("logged in.\n\n\t\t\t\t\tWe Provide ");
                printf("two ways to search:\n\n\t\t\t\t\t1) ");
                printf("Search By Hotels\n\n\t\t\t\t\t2) ");
                printf("Search by Food\n\n\t\t\t\t\t3) ");
                printf("User Setting\n\n\t\t\t\t\tPlease Enter");
                printf(" your choice: ");
                scanf("%d", &search_choice);
  
                // Getting the input whether
                // the user are going to search
                // /Order by hotels or search/
                // order by food.
                switch (search_choice) {
                case 1: {
                	clrscr();
                    search_by_hotels();
                    break;
                }
                case 2: {
                	clrscr();
                    search_by_food();
                    break;
                }
                case 3: {
                	clrscr();
                    userSetting();
                    break;
                }
                default: {
                    printf("\n\n\t\t\t\t\tPlease Enter ");
                    printf("the valid choice\n\n");
                    break;
                }
                }
                break;
            }
            else {
                printf("\n\n\t\t\t\t\tInvalid Password! ");
                printf("Please Enter the ");
                printf("correct password\n\n");
                main();
                break;
            }
        }
        else {
            printf("\n\n\t\t\t\t\tAccount doesn't ");
            printf("exist, Please signup!!\n\n");
            main();
            break;
        }
    }
}

void userSetting(){
     
	 system("cls");
	 char old[100];
     printf("\n\n\t\t\t\t\tEnter New Email:\t");
     scanf("%s", temp_email);
	 printf("\n\n\t\t\t\t\tEnter Old Password:\t");
	 scanf("%s", old);
     printf("\n\n\t\t\t\t\tEnter New Password:\t");
     scanf("%s", temp_password1);
     printf("\n\n\t\t\t\t\tConfirm Password:\t");
     scanf("%s", temp_password2);
     printf("\n\n\t\t\t\t\tEnter New Contact Number:\t");
     scanf("%s", temp_mobile);
    // Function Call to validate
    // the user creation
    x = validate();
    if (x == 1)
        account_check();
 	
}


// Function to implement the Hotel
// initialzer
void hotel_initialize()
{
    // Initializing the structure
    // with Aarya_bhavan hotel and
    // some foods name and
    // their respective costs.
    strcpy(m[1].hotel, "Aarya_Bhavan");
    strcpy(m[1].first_food, "Sandwich");
    strcpy(m[1].second_food, "Pizza");
    strcpy(m[1].third_food, "Fried_Rice");
    strcpy(m[1].fourth_food, "Momos");
    strcpy(m[1].fifth_food, "Chinese Platter");
    m[1].first = 70;
    m[1].second = 160;
    m[1].third = 120;
    m[1].fourth = 90;
    m[1].fifth = 140;
  
    // Initializing the structure with
    // Banu_Hotel and some foods name
    // and their respective costs.
    strcpy(m[2].hotel, "Banu_Hotel");
    strcpy(m[2].first_food, "Aloo Paratha");
    strcpy(m[2].second_food, "Kadhai Paneer");
    strcpy(m[2].third_food, "Dal Makhani");
    strcpy(m[2].fourth_food, "Butter Naan");
    strcpy(m[2].fifth_food, "Coke");
    m[2].first = 40;
    m[2].second = 200;
    m[2].third = 140;
    m[2].fourth = 35;
    m[2].fifth = 40;
  
    // Initializing the structure with
    // SR_Bhavan hotel and some foods
    // name and their respective costs.
    strcpy(m[3].hotel, "SR_Bhavan");
    strcpy(m[3].first_food, "Chicken_Biriyani");
    strcpy(m[3].second_food, "Prawn");
    strcpy(m[3].third_food, "Chicken Changezi");
    strcpy(m[3].fourth_food, "Fish Fry");
    strcpy(m[3].fifth_food, "Coke");
    m[3].first = 200;
    m[3].second = 220;
    m[3].third = 250;
    m[3].fourth = 220;
    m[3].fifth = 40;
    
    // Initializing the structure with
    // Hotel Bliss and some foods
    // name and their respective costs.
    strcpy(m[4].hotel, "Hotel_Bliss");
    strcpy(m[4].first_food, "Grilled Fish with Lemon\n\n\t\t\t\t\tButter Sauce");
    strcpy(m[4].second_food, "Crumbled Fish n Chips");
    strcpy(m[4].third_food, "Blish Rava Fry");
    strcpy(m[4].fourth_food, "Golden Paneer");
    strcpy(m[4].fifth_food, "Mojito");
    m[4].first = 425;
    m[4].second = 450;
    m[4].third = 565;
    m[4].fourth = 400;
    m[4].fifth = 200;
    
    
}

  
// Function to implement the search
// by hotels
void search_by_hotels()
{   
    hotel_initialize();
    printf(""
           "\n\n\t\t\t\t\tPlease Choose the");
    printf(" hotels:\n\n\t\t\t\t\t1) %s\n\n\t\t\t\t\t2) %s\n\n\t\t\t\t\t3) %s\n\n\t\t\t\t\t4) %s",
           m[1].hotel,
           m[2].hotel, m[3].hotel, m[4].hotel);
    printf("\n\n\t\t\t\t\t5) Exit\n\n\t\t\t\t\tPlease ");
    printf("select the hotel: ");
    scanf("%d", &hotel_choice);
    if (hotel_choice > 5) {
        printf("\n\n\t\t\t\t\tPlease Enter the");
        printf(" valid choice:\n\n");
        search_by_hotels();
    }
    else if (hotel_choice == 5){
        login();
        return;
    }
    else
        hotels(hotel_choice);
}
  
// Function to implement the hotel
void hotels(int hotel_choice)
{ 
    system("cls");
    total = 0;
    while (1) {
        // Displays the list of
        // foods available in
        // selected hotel
        printf("\n\n\t\t\t\t\tList of foods available");
  
        printf(" in %s --\n\n\t\t\t\t\t1) %s\tRs: %d\n\n\t\t\t\t\t2)",
               m[hotel_choice].hotel,
               m[hotel_choice].first_food,
               m[hotel_choice].first);
  
        printf(" %s\tRs: %d\n\n\t\t\t\t\t3) %s\tRs: %d\n\n\t\t\t\t\t4) %s\tRs: %d\n\n\t\t\t\t\t5) %s\tRs: %d\n\n\t\t\t\t\t",
               m[hotel_choice].second_food,
               m[hotel_choice].second,
               m[hotel_choice].third_food,
               m[hotel_choice].third,
               m[hotel_choice].fourth_food,
               m[hotel_choice].fourth,
			   m[hotel_choice].fifth_food,
               m[hotel_choice].fifth);
               
  
        printf("6) Cart\n\n\t\t\t\t\t7) Exit\n\n\t\t\t\t\tPlease Enter");
        printf(" Your Choice: ");
        scanf("%d", &food_choice);
  
        // Get the input for no
        // of foods to calculate
        // the total amount
        if (food_choice == 1) {
            printf("\n\n\t\t\t\t\tPlease Enter the ");
            printf("Count of %s\t",
                   m[hotel_choice].first_food);
            scanf("%d", &n);
            total = total
                    + (n * m[hotel_choice].first);
        }
        else if (food_choice == 2) {
            printf("\n\n\t\t\t\t\tPlease Enter the Count ");
            printf("of %s\t",
                   m[hotel_choice].second_food);
            scanf("%d", &n);
            total = total
                    + (n * m[hotel_choice].second);
        }
        else if (food_choice == 3) {
            printf("\n\n\t\t\t\t\tPlease Enter the Count ");
            printf("of %s\t",
                   m[hotel_choice].third_food);
            scanf("%d", &n);
            total = total
                    + (n * m[hotel_choice].third);
        }
        else if (food_choice == 4) {
            printf("\n\n\t\t\t\t\tPlease Enter the Count ");
            printf("of %s\t",
                   m[hotel_choice].fourth_food);
            scanf("%d", &n);
            total = total
                    + (n * m[hotel_choice].fourth);
        }
        else if (food_choice == 5) {
            printf("\n\n\t\t\t\t\tPlease Enter the Count ");
            printf("of %s\t",
                   m[hotel_choice].fifth_food);
            scanf("%d", &n);
            total = total
                    + (n * m[hotel_choice].fifth);
        }
  
  
        // Once the user, completed their
        // order, they can go to cart
        // by giving choice as 4.
        else if (food_choice == 6) {
            cart();
        }
        else if (food_choice == 7) {
            search_by_hotels();
        }
        else {
            printf("\n\n\t\t\t\t\tPlease Enter a ");
            printf("valid Choice\n\n");
        }
    }
}
  
void search_by_food()
{ 
    system("cls");
    total = 0;
    // Initialize all the
    // hotels and their foods
    hotel_initialize();
    while (1) {
        printf("\n\n\t\t\t\t\tPlease choose the ");
        printf("food\n\n\t\t\t\t\t1) %s\tRs %d\n\n\t\t\t\t\t2) %s\tRs %d",
               m[1].first_food, m[1].first,
               m[1].second_food, m[1].second);
  
        printf("\n\n\t\t\t\t\t3) %s\tRs %d\n\n\t\t\t\t\t4) %s\tRs %d\n\n\t\t\t\t\t5) %s\tRs %d\n\n\t\t\t\t\t",
               m[1].third_food, m[1].third,
               m[1].fourth_food, m[1].fourth,m[1].fifth_food,m[1].fifth);
  
        printf("6) %s\tRs %d\n\n\t\t\t\t\t7) %s\tRs %d\n\n\t\t\t\t\t8) %s\tRs %d\n\n\t\t\t\t\t9) %s\tRs %d\n\n\t\t\t\t\t10) %s\tRs%d\n\n\t\t\t\t\t",
               m[2].first_food, m[2].first,
               m[2].second_food, m[2].second, m[2].third_food, m[2].third,
               m[2].fourth_food, m[2].fourth,m[2].fifth_food,m[2].fifth);
  
        printf("11) %s\tRs %d\n\n\t\t\t\t\t12) %s\tRs %d\n\n\t\t\t\t\t13) %s\tRs %d\n\n\t\t\t\t\t14) %s\tRs %d\n\n\t\t\t\t\t15) %s\tRs %d\n\n\t\t\t\t\t",
               m[3].first_food, m[3].first,
               m[3].second_food, m[3].second, m[3].third_food,
               m[3].third, m[3].fourth_food, m[3].fourth, m[3].fifth_food, m[3].fifth);
               
        printf("16) %s\tRs %d\n\n\t\t\t\t\t17) %s\tRs %d\n\n\t\t\t\t\t18) %s\tRs %d\n\n\t\t\t\t\t19) %s\tRs %d\n\n\t\t\t\t\t20) %s\tRs %d\n\n\t\t\t\t\t",
               m[4].first_food, m[4].first,
               m[4].second_food, m[4].second, m[4].third_food,
               m[4].third, m[4].fourth_food, m[4].fourth, m[4].fifth_food, m[4].fifth);
  
        printf("21) Cart\n\n\t\t\t\t\t");
        printf("22) Exit");
        printf("\n\n\t\t\t\t\tPlease Enter Your Choice:\t");
        scanf("%d", &food);
        if (food > 22) {
            printf("\n\n\t\t\t\t\tPlease Enter the ");
            printf("valid choice\n\n");
            search_by_food();
        }
        // Moves to the cart
        // functionality
        else if (food == 21)
            cart();
        else if (food == 22){
            exit(0);
            return;
		}
        // Call food_order functionality
        // to get the no of foods and
        // to calculat the total
        // amount of the order.
        else
            food_order(food);
    }
}
  
// Function to implement the food
// order functionality
void food_order(int food)
{
    if (food >= 1 && food <= 5)
        hotel_id = 1;
    else if (food >= 6 && food <= 10)
        hotel_id = 2;
    else if(food >=11 && food<=15)
        hotel_id = 3;
    else
        hotel_id = 4;
    if ((food % 5) == 1) {
        printf("\n\n\t\t\t\t\tPlease Enter the");
        printf(" Count of %s:\t",
               m[hotel_id].first_food);
        scanf("%d", &n);
        total = total + (n * m[hotel_id].first);
    }
    else if ((food % 5) == 2) {
        printf("\n\n\t\t\t\t\tPlease Enter the ");
        printf("Count of %s:\t",
               m[hotel_id].second_food);
        scanf("%d", &n);
        total = total + (n * m[hotel_id].second);
    }
    else if ((food % 5) == 3) {
        printf("\n\n\t\t\t\t\tPlease Enter the ");
        printf("Count of %s:\t",
               m[hotel_id].third_food);
        scanf("%d", &n);
        total = total + (n * m[hotel_id].third);
    }
    else if ((food % 5) == 4) {
        printf("\n\n\t\t\t\t\tPlease Enter the ");
        printf("Count of %s:\t",
               m[hotel_id].fourth_food);
        scanf("%d", &n);
        total = total + (n * m[hotel_id].fourth);
    }
    else{
    	printf("\n\n\t\t\t\t\tPlease Enter the ");
        printf("Count of %s:\t",
               m[hotel_id].fifth_food);
        scanf("%d", &n);
        total = total + (n * m[hotel_id].fifth);
	}
    
    
}
  
// Function to implement the cart
void cart()
{
    printf("\n\n\n\n\t\t\t\t\t--------------Cart");
    printf("----------------");
    printf("\n\n\t\t\t\t\tYour Total Order ");
    printf("Amount is Rs %d\n", total);
    printf("\n\n\t\t\t\t\tDo You wish to ");
    printf("order (y=1/n=0):  ");
    scanf("%d", &ch);
    if (ch == 1) {
        printf("\n\n\t\t\t\tThank You for your ");
        printf("order!! Your Food is on ");
        printf("the way. Welcome again!!\n\n");
        // exit(1);
        return;
    }
    else if (ch == 0) {
        printf("\n\n\t\t\t\t\tDo You want to exit(1) ");
        printf("or Go back(0):  ");
        scanf("%d", &confirm);
        if (confirm == 1) {
            printf("\n\n\t\t\t\t\tOops! Your order is ");
            printf("cancelled!!\n\n\t\t\t\t\t\t Exiting..");
            printf("\n\n\t\t\t\t\tThank You! Visit Again!\n");
            // exit(1);
            return;
        }
        else {
            printf("\n\n\t\t\t\t\tThank You\n\n");
            login();
        }
    }
    else {
        printf("\n\n\t\t\t\t\tPlease Enter the ");
        printf("correct choice\n\n");
        cart();
    }
}



