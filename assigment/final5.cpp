#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#pragma warning(disable :4996)
#define MAX_ACCOUNT 100
#define  Max_staff 150
#define MAX_TRAIN 100
#define MAX_STATION_LENGTH 50
#define MAX_BOOKING 100

//minru
struct phone {
    char phone[12];
    char phone2[12];
};
typedef struct {
    char name[25];
    char position[30];
    char mycard[19];
    int age;
    int staffID;
    char password[25], password2[25];
    char email[35];
    struct phone p_num;
    char gender;
}staff;
//minru

//siew ian
struct Address {
    char address[50];
    int postcode;
    char country[20];
};
typedef struct {
    char name[40], user_name[20], phone[20], email[40], member_category[12];
    char gender;
    char mycard[13];
    struct Address add;
    char password[20], password2[20];
    int  member_ID, Membership_points;
    float credit_balance;
}member;
//siew ian

//clarisse
struct date {
    int year, month, day;
};
struct TrainSchedule {
    char trainID[10], departStation[MAX_STATION_LENGTH], arrStation[MAX_STATION_LENGTH], departTime[10], arrTime[10];
    int  availableSeats, seat[4][40];
    float price;
    struct date departdate;
};
//clarisse

//weile
struct ticket {
    int  seat[4][40], quantity, booking_id = 0;
    char train_id[10], depstation[MAX_STATION_LENGTH], arrstation[MAX_STATION_LENGTH], tic_status[10], deptime[10], arrtime[10], cus_name[100][20], cus_ic[100][20];
    float amount;
    struct date departdate;
};
typedef struct {
    int mem_id;
    float credit;
    char password[20];
    char mem_category[10];
    struct ticket t_detail[MAX_BOOKING];

}booking;
booking bookings_a[MAX_ACCOUNT];
booking modify[MAX_ACCOUNT];
booking display;
booking cancel[MAX_ACCOUNT];
//weile

void mainmenu();

//minru
void staff_module();
int login();
void add_staff_function();
void search_staff_account();
void display_staff_account(int id);
int delete_staff_function(int id);
void modify_staff_funtion(int id);
void menu();
//minru

//siew ian
void member_module();
void add_member_info();
void search_member_info(int mem_id);
void modify_member_info(int mem_id);
void display_member_info(int mem_id);
void search_ticket_status(int mem_id);
void delete_member_info(int mem_id);
void log_in();
void handel_menu(int login_mem_id);
int general_memberID();
booking mem_m[MAX_ACCOUNT];
booking mem_d[MAX_ACCOUNT];
booking member_status;
//siew ian

//clarisse
void schedule_module();
int staffLogin();
void addTrainSchedule(struct TrainSchedule trainSchedules[], int* numTrains);
void searchTrainSchedule(struct TrainSchedule trainSchedules[], int numTrains, char trainID[]);
void modifyTrainSchedule(char trainID[]);
void displayTrainSchedule();
void seat(int seat_[4][40]);
void deleteTrainSchedule(char trainID[]);
booking del_schedule[MAX_ACCOUNT];
//clarisse

//wei le
void booking_module();
int booking_login();
int booking_menu();
void add_ticket_booking(int mem_id);
void search_schedule();
void modify_ticket_booking(int mem_id);
void display_booking_records(int mem_id);
void cancel_ticket_booking(int mem_id);
float cal_payment(char mem_category[10], float price, int quantity);
int general_id();;

//wei le

void logo();


int main() {
    int select;
    do {
        system("cls");
        logo();
        mainmenu();
        scanf("%d", &select);
        system("cls");

        if (select == 1) {
            staff_module();
        }
        else if (select == 2) {
            member_module();
        }
        else if (select == 3) {
            schedule_module();
        }
        else if (select == 4) {
            booking_module();
        }
        else if (select == 5) {
            printf("Thank you for using Silver Arrow Express");
        }
        else {
            printf("Invalid select,Please select again");
        }

    } while (select != 5);


}

void mainmenu() {
    printf("**************************************************************************************************************\n");
    printf("*  1.Staff Module                                                                                            *\n");
    printf("*  2.Member Module                                                                                           *\n");
    printf("*  3.Schedule Module                                                                                         *\n");
    printf("*  4.Booking Module                                                                                          *\n");
    printf("*  5.Exit                                                                                                    *\n");
    printf("**************************************************************************************************************\n");
    printf("   Please enter your selection : ");
}

//minru
void staff_module() {
    int choose, id, delete_ = 0;
    logo();
    printf("=======================================================\n");
    printf("|                                                     |\n");
    printf("|                Welcome to Staff page                | \n");
    printf("|                                                     |\n");
    printf("=======================================================\n");
    printf("1.Register\n");
    printf("2.Login in Account\n");
    printf("Please enter your selection :");
    scanf("%d", &choose);

    if (choose == 1) {
        add_staff_function();
        system("pause");
        system("cls");
        id = login();
    }
    else if (choose == 2) {
        system("cls");
        id = login();
    }

    if (id == 0) {
        return;
    }
    else {
        do {
            system("cls");
            menu();
            scanf("%d", &choose);
            system("cls");

            if (choose == 1) {
                add_staff_function();
                system("pause");
                system("cls");
            }
            else if (choose == 2) {
                search_staff_account();
                system("pause");
                system("cls");
            }
            else if (choose == 3) {
                modify_staff_funtion(id);
                system("pause");
                system("cls");
            }
            else if (choose == 4) {
                display_staff_account(id);
                system("pause");
                system("cls");
            }
            else if (choose == 5) {
                delete_ = delete_staff_function(id);
                system("pause");
                system("cls");
                if (delete_ == 1) {
                    return;
                }
            }
        } while (choose != 6);

    }

}

int login() {
    int id, x = 0;
    char pass[25];
    logo();
    printf("\n\n*********************************\n");
    printf("*       WELCOME TO LOGIN        *\n");
    printf("*********************************\n\n");
    printf("Please enter your Staff ID to login:");
    scanf("%d", &id);
    printf("Please enter password   :");
    scanf("%s", &pass);

    FILE* fp;
    staff newStaff;
    fp = fopen("staff.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }
    while (fscanf(fp, "%[^\n]\n%s\n%s\n%s\n%d\n%c\n%s\n%s\n%d\n%s\n", &newStaff.name, &newStaff.email, &newStaff.mycard, &newStaff.position, &newStaff.age, &newStaff.gender, &newStaff.p_num.phone, &newStaff.p_num.phone2, &newStaff.staffID, &newStaff.password2) != EOF) {
        if (newStaff.staffID == id) {
            if (strcmp(newStaff.password2, pass) == 0) {
                x = 1;
                break;
            }
            else {
                printf("Invalid password");
                break;
            }

        }
    }
    fclose(fp);
    if (x == 0) {
        printf("Not found the account");
        return 0;
    }
    else {
        return newStaff.staffID;
    }

}

void menu() {
    printf("=======================================================\n");
    printf("|                                                     |\n");
    printf("|                     Staff Menu                      | \n");
    printf("|                                                     |\n");
    printf("=======================================================\n");
    printf("1.add_staff_function\n");
    printf("2.search_staff_account\n");
    printf("3.modify_staff_funtion\n");
    printf("4.display_staff_account\n");
    printf("5.delete_staff_function\n");
    printf("6.exit\n");
    printf("Please enter your choose:");
}

void add_staff_function() {
    FILE* fp;
    staff newStaff;

    fp = fopen("staff.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }
    printf("=======================================================\n");
    printf("|                                                     |\n");
    printf("|              Add New Staff Information              | \n");
    printf("|                                                     |\n");
    printf("=======================================================\n");
    rewind(stdin);
    printf("Enter your name : ");
    scanf("%[^\n]", &newStaff.name);
    rewind(stdin);
    printf("Enter your email : ");
    scanf("%s", &newStaff.email);
    rewind(stdin);
    printf("Enter your IC   : ");
    scanf("%s", &newStaff.mycard);
    rewind(stdin);
    printf("Enter your position : ");
    scanf("%s", &newStaff.position);
    rewind(stdin);
    printf("Enter your age : ");
    scanf("%d", &newStaff.age);
    rewind(stdin);
    printf("Enter your gender (F/M): ");
    scanf("%c", &newStaff.gender);
    while (toupper(newStaff.gender) != 'F' && toupper(newStaff.gender) != 'M') {
        printf("Invalid,Enter your gender (F/M): ");
        rewind(stdin);
        scanf("%c", &newStaff.gender);
    }
    rewind(stdin);
    printf("Enter your phone number (without (-)) : ");
    scanf("%s", &newStaff.p_num.phone);
    rewind(stdin);
    printf("Enter your spare phone number (without (-)) : ");
    scanf("%s", &newStaff.p_num.phone2);
    rewind(stdin);
    printf("Enter your password : ");
    scanf("%s", &newStaff.password);
    rewind(stdin);
    printf("Please confirmed your password : ");
    scanf("%s", &newStaff.password2);
    rewind(stdin);
    while (strcmp(newStaff.password, newStaff.password2) != 0) {
        printf("Password not same,Please confirmed your password : ");
        scanf("%s", &newStaff.password2);
        rewind(stdin);
    }
    printf("Enter your Staff ID : ");
    scanf("%d", &newStaff.staffID);
    rewind(stdin);

    fprintf(fp, "%s\n%s\n%s\n%s\n%d\n%c\n%s\n%s\n%d\n%s\n", newStaff.name, newStaff.email, newStaff.mycard, newStaff.position, newStaff.age, newStaff.gender, newStaff.p_num.phone, newStaff.p_num.phone2, newStaff.staffID, newStaff.password2);
    printf("Staff account added successfully.\n");
    fclose(fp);
}

void search_staff_account() {

    FILE* fp;
    staff newStaff;
    int id, x = 0;
    fp = fopen("staff.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }
    printf("Please Enter your ID to search: ");
    scanf("%d", &id);
    while (fscanf(fp, "%[^\n]\n%s\n%s\n%s\n%d\n%c\n%s\n%s\n%d\n%s\n", &newStaff.name, &newStaff.email, &newStaff.mycard, &newStaff.position, &newStaff.age, &newStaff.gender, &newStaff.p_num.phone, &newStaff.p_num.phone2, &newStaff.staffID, &newStaff.password2) != EOF) {

        if (newStaff.staffID == id) {
            printf("======================================================================\n");
            printf("|                                                                    |\n");
            printf("|                         Search Information                         |\n");
            printf("|                                                                    |\n");
            printf("======================================================================\n");
            printf("Staff Account Found:\n");
            printf("Staff name     : %s\n", newStaff.name);
            printf("Staff ID       : %d\n", newStaff.staffID);
            printf("Staff's Email  : %s\n", newStaff.email);
            printf("Staff's IC     : %s\n", newStaff.mycard);
            printf("Staff's Phone number : %s\n", newStaff.p_num.phone);
            printf("Staff's spare Phone number: %s\n", newStaff.p_num.phone2);
            printf("Staff's age    : %d\n", newStaff.age);
            printf("Staff's Gender : %c\n", newStaff.gender);
            printf("Staff's position     : %s\n", newStaff.position);
            x = 1;
        }

    }
    if (x != 1) {
        printf("Staff account not found.");
    }
    fclose(fp);
}
void modify_staff_funtion(int id) {
    FILE* fp;
    staff newStaff[100];
    int choice1, subchoice1, x = 0;

    fp = fopen("staff.txt", "r");
    if (fp == NULL) {
        printf("Error to opening file!\n");
        exit(-1);
    }
    while (fscanf(fp, "%[^\n]\n%s\n%s\n%s\n%d\n%c\n%s\n%s\n%d\n%s\n", &newStaff[x].name, &newStaff[x].email, &newStaff[x].mycard, &newStaff[x].position, &newStaff[x].age, &newStaff[x].gender, &newStaff[x].p_num.phone, &newStaff[x].p_num.phone2, &newStaff[x].staffID, &newStaff[x].password2) != EOF) {
        if (newStaff[x].staffID == id) {
            printf("===================================================================\n");
            printf("|                                                                 |\n");
            printf("|                    Modify Staff Profile                         |\n");
            printf("|                                                                 |\n");
            printf("===================================================================\n");
            printf("|                                                                 |\n");
            printf("|                  1. Edit Staff Information                      |\n");
            printf("|                  2. Menu                                        | \n");
            printf("===================================================================\n");
            printf("Please Enter You Choice : ");
            scanf("%d", &choice1);

            if (choice1 == 1) {
                printf("\n\n================================Modify Account Information================================\n\n");
                printf("Which information would you like to modify\n");
                printf("1.Full Name (%s)\n", newStaff[x].name);
                printf("2.IC/Passport (%s)\n", newStaff[x].mycard);
                printf("3.Phone Number (%s)\n", newStaff[x].p_num.phone);
                printf("4.Spare Phone Number (%s)\n", newStaff[x].p_num.phone2);
                printf("5.Email (%s)\n", newStaff[x].email);
                printf("6.Password (%s)\n", newStaff[x].password2);
                printf("7.Back to Menu\n");
                printf("\nEnter your choice :");
                scanf("%d", &subchoice1);

                if (subchoice1 == 1) {
                    printf("Enter new name(Full Name) :");
                    rewind(stdin);
                    scanf("%[^\n]", &newStaff[x].name);
                    printf("Successful update.\n\n");
                }
                else if (subchoice1 == 2) {
                    printf("Enter new IC/Passport     :");
                    rewind(stdin);
                    scanf("%[^\n]", &newStaff[x].mycard);
                    printf("Successful update\n\n");
                }
                else if (subchoice1 == 3) {
                    printf("Enter new Phone Number     :");
                    rewind(stdin);
                    scanf("%s", &newStaff[x].p_num.phone);
                    printf("Successful update\n\n");
                }
                else if (subchoice1 == 4) {
                    printf("Enter new Spare Phone Number     :");
                    rewind(stdin);
                    scanf("%s", &newStaff[x].p_num.phone2);
                    printf("Successful update\n\n");
                }
                else if (subchoice1 == 5) {
                    printf("Enter new Email  :");
                    rewind(stdin);
                    scanf("%[^\n]", &newStaff[x].email);
                }
                else if (subchoice1 == 6) {
                    printf("Enter new password : ");
                    rewind(stdin);
                    scanf("%[^\n]", &newStaff[x].password2);
                }
                else if (subchoice1 == 7) {
                    fclose(fp);
                    return;
                }
            }
            else {
                printf("Invalid choice! Please try again!\n");
                system("pause");
                fclose(fp);
                return;
            }
        }
        x++;
    }
    fclose(fp);
    FILE* fp2;
    fp2 = fopen("staff.txt", "w");
    if (fp2 == NULL) {
        printf("Error to opening file!\n");
        exit(-1);
    }

    for (int y = 0; y < x; y++) {
        fprintf(fp2, "%s\n%s\n%s\n%s\n%d\n%c\n%s\n%s\n%d\n%s\n", newStaff[y].name, newStaff[y].email, newStaff[y].mycard, newStaff[y].position, newStaff[y].age, newStaff[y].gender, newStaff[y].p_num.phone, newStaff[y].p_num.phone2, newStaff[y].staffID, newStaff[y].password2);
    }

    fclose(fp2);

}

void display_staff_account(int id) {
    FILE* fp;
    staff newStaff;
    fp = fopen("staff.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }
    printf("======================================================================\n");
    printf("|                                                                    |\n");
    printf("|                          Staff profile                             |\n");
    printf("|                                                                    |\n");
    printf("======================================================================\n\n\n");

    printf("Staff Account Details\n");
    while (fscanf(fp, "%[^\n]\n%s\n%s\n%s\n%d\n%c\n%s\n%s\n%d\n%s\n", &newStaff.name, &newStaff.email, &newStaff.mycard, &newStaff.position, &newStaff.age, &newStaff.gender, &newStaff.p_num.phone, &newStaff.p_num.phone2, &newStaff.staffID, &newStaff.password2) != EOF)
    {

        if (newStaff.staffID == id) {
            printf("\n===================== profile=====================\n");
            printf("Staff ID          : %d\n", newStaff.staffID);
            printf("Staff Name        : %s\n", newStaff.name);
            printf("IC/Passport       : %s\n", newStaff.mycard);
            printf("Phone Number      : %s\n", newStaff.p_num.phone);
            printf("Spare Phone Number: %s\n", newStaff.p_num.phone2);
            printf("Gender            : %c\n", newStaff.gender);
            printf("Email             : %s\n", newStaff.email);
            printf("Position          : %s\n", newStaff.position);

        }

    }

    fclose(fp);
}

int delete_staff_function(int id) {
    FILE* fp;
    staff newStaff[100];
    int x = 0, confirm;

    fp = fopen("staff.txt", "r");
    if (fp == NULL) {
        printf("Error to opening file!\n");
        exit(-1);
    }

    while (fscanf(fp, "%[^\n]\n%s\n%s\n%s\n%d\n%c\n%s\n%s\n%d\n%s\n", &newStaff[x].name, &newStaff[x].email, &newStaff[x].mycard, &newStaff[x].position, &newStaff[x].age, &newStaff[x].gender, &newStaff[x].p_num.phone, &newStaff[x].p_num.phone2, &newStaff[x].staffID, &newStaff[x].password2) != EOF) {
        if (newStaff[x].staffID == id) {
            printf("Confirm delete account?press 1 to confirm:");
            scanf("%d", &confirm);

            if (confirm == 1) {
                newStaff[x].staffID = 1;
            }
            else {
                fclose(fp);
                return 0;
            }
        }
        x++;
    }
    fclose(fp);
    FILE* fp2;
    fp2 = fopen("staff.txt", "w");
    if (fp2 == NULL) {
        printf("Error to opening file!\n");
        exit(-1);
    }

    for (int y = 0; y < x; y++) {
        if (newStaff[y].staffID == 1) {
            continue;
        }
        else {
            fprintf(fp, "%s\n%s\n%s\n%s\n%d\n%c\n%s\n%s\n%d\n%s\n", newStaff[y].name, newStaff[y].email, newStaff[y].mycard, newStaff[y].position, newStaff[y].age, newStaff[y].gender, newStaff[y].p_num.phone, newStaff[y].p_num.phone2, newStaff[y].staffID, newStaff[y].password2);
        }
    }
    fclose(fp2);
    return confirm;
}
//minru

//siew ian
void member_module() {
    member detail[MAX_ACCOUNT];
    int selection4;
    int numUser = 0;
    int login_again = 0;
    int loggedInIndex = 0;
    do {
        selection4 = 0;
        logo();
        printf("\n-----------------------------\n");
        printf("1.have a member account\n");
        printf("2.Register\n");
        printf("Please select 1 or 2 >");
        rewind(stdin);
        scanf("%d", &selection4);
        if (selection4 == 1) {
            logo();
            log_in();
            system("cls");
        }
        else if (selection4 == 2) {
            add_member_info();
            system("cls");
            logo();
            log_in();
            system("cls");
        }
        else {
            printf("Invalid selection!Please try again!\n");
        }
        printf("Do you want to log in again ?\n");
        printf("(Yes = 1 , No = 0 )  Enter 1 or 0 only :");
        rewind(stdin);
        scanf("%d", &login_again);
        system("cls");
    } while (login_again == 1);
    return;
}

void log_in() {
    member detail[MAX_ACCOUNT];
    int index = 0, numUser;
    FILE* file_input;
    char username[40], user_password[20];
    int validate = 0;
    int i;
    system("cls");
    logo();
    printf("\n\n*********************************\n");
    printf("*       WELCOME TO LOGIN        *\n");
    printf("*********************************\n\n");
    while (validate == 0) {
        file_input = fopen("memberinfo.txt", "r");
        if (file_input == NULL) {
            printf("Error!Cannot open the memberinfo.txt\n");
            exit(-1);
        }
        for (numUser = 0; numUser < MAX_ACCOUNT; (numUser)++) {
            if (fscanf(file_input, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%c\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%[^\n]\n%f\n%[^\n]\n%d\n\n",
                &detail[index].member_ID, &detail[index].name, &detail[index].user_name, &detail[index].mycard, &detail[index].phone, &detail[index].gender,
                &detail[index].email, &detail[index].add.address, &detail[index].add.postcode, &detail[index].add.country, &detail[index].password, &detail[index].credit_balance, &detail[index].member_category, &detail[index].Membership_points) != EOF) {
                index++;
            }
            else {
                break;
            }
        }
        printf("\nUser Name :");
        rewind(stdin);
        scanf("%[^\n]", &username);
        printf("Password  :");
        rewind(stdin);
        scanf("%[^\n]", &user_password);
        rewind(file_input);
        fclose(file_input);
        for (int x = 0; x < index; x++) {
            if (strcmp(username, detail[x].user_name) == 0 && strcmp(user_password, detail[x].password) == 0) {
                handel_menu(detail[x].member_ID);
                validate = 1;
                break;
            }
        }
        if (!validate) {
            printf("Incorrect username or password. Please try again.\n\n");
            return;
        }
        system("cls");
    }
}
void handel_menu(int login_mem_id) {
    int selection;
    int memberID;
    char confirm_del;
    do {
        logo();
        printf("\n=======Member Information Module=======\n");
        printf("1. Resgister New Member Account\n");
        printf("2. Search Member Information\n");
        printf("3. Modify Member Information\n");
        printf("4. Display Member Profile\n");
        printf("5. Display Ticket Status\n");
        printf("6. Delete Member Account\n");
        printf("7. Log Out\n");
        printf("==========================================\n\n\n\n");
        printf("Enter your selection : ");
        scanf("%d", &selection);
        while (getchar() != '\n');
        if (selection == 1) {
            add_member_info();
            system("cls");
        }
        else if (selection == 2) {
            system("cls");
            search_member_info(login_mem_id);
        }
        else if (selection == 3) {
            system("cls");
            modify_member_info(login_mem_id);
        }
        else if (selection == 4) {
            system("cls");
            display_member_info(login_mem_id);
        }
        else if (selection == 5) {
            system("cls");
            search_ticket_status(login_mem_id);
        }
        else if (selection == 6) {
            printf("Are you confirm to delete your memberID?(Y/N) \n");
            scanf("%c", &confirm_del);
            if (toupper(confirm_del) == 'Y')
            {
                system("cls");
                delete_member_info(login_mem_id);
                return;
            }
        }
        else if (selection == 7) {
            return;
        }
        else {
            printf("Invalid Selection! Please selection again!\n");
        }
    } while (selection != 7);
}
int general_memberID() {

    int id, arr, repeat;
    member detail;
    do {
        repeat = 0;
        srand(time(NULL));
        id = rand() % 100000;

        FILE* file_input;
        file_input = fopen("memberinfo.txt", "r");
        if (file_input == NULL) {
            printf("Cannot open memberinfo.txt,Please try again!\n");
            exit(-1);
        }
        while (fscanf(file_input, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%c\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%[^\n]\n%f\n%[^\n]\n%d\n\n",
            &detail.member_ID, &detail.name, &detail.user_name, &detail.mycard, &detail.phone, &detail.gender,
            &detail.email, &detail.add.address, &detail.add.postcode, &detail.add.country, &detail.password, &detail.credit_balance, &detail.member_category, &detail.Membership_points) != EOF) {

            if (detail.member_ID == id) {
                repeat = 1;
            }
        }
        fclose(file_input);
    } while (repeat == 1);
    return id;
}
void add_member_info() {
    member detail;
    FILE* file_input;
    char selection2[5];
    file_input = fopen("memberinfo.txt", "a");
    if (file_input == NULL) {
        printf("Error! Cannot open the memberinfo.txt!\n");
        exit(-1);
    }
    system("cls");
    printf("======================================================================\n");
    printf("|                                                                    |\n");
    printf("|                        Register Member Form                        |\n");
    printf("|                                                                    |\n");
    printf("======================================================================\n\n\n");
    printf("Please enter your information: \n");

    while (strcmp(selection2, "stop") != 0) {
        printf("Full Name             : ");
        rewind(stdin);
        scanf("%[^\n]", &detail.name);
        printf("User Name(for log in) : ");
        rewind(stdin);
        scanf("%[^\n]", &detail.user_name);
        printf("IC/Passport           : ");
        rewind(stdin);
        scanf("%[^\n]", &detail.mycard);
        printf("Phone Number(with '-'): ");
        rewind(stdin);
        scanf("%[^\n]", &detail.phone);
        printf("Gender(M/F)           : ");
        rewind(stdin);
        scanf("%c", &detail.gender);
        int option = 0;
        while (!option) {
            if (toupper(detail.gender) != 'M' && toupper(detail.gender) != 'F') {
                printf("Please enter gender is M or F.\n");
                printf("Gender(M/F)           : ");
                rewind(stdin);
                scanf("%c", &detail.gender);
            }
            else {
                ++option;
            }
        }
        printf("Email                 : ");
        rewind(stdin);
        scanf("%[^\n]", &detail.email);
        printf("Address               : ");
        rewind(stdin);
        scanf("%[^\n]", &detail.add.address);
        printf("Post Code             : ");
        rewind(stdin);
        scanf("%d", &detail.add.postcode);
        printf("Country               : ");
        rewind(stdin);
        scanf("%[^\n]", &detail.add.country);
        printf("Password(max 20 character/digit)               : ");
        rewind(stdin);
        scanf("%[^\n]", &detail.password);
        printf("Confirmation password (must same with password): ");
        rewind(stdin);
        scanf("%[^\n]", &detail.password2);
        int option2 = 0;
        while (!option2) {
            if (strcmp(detail.password2, detail.password) != 0) {
                printf("Password does not match password!\n");
                printf("Confirmation password (must same with password): ");
                rewind(stdin);
                scanf("%[^\n]", &detail.password2);
            }
            else {
                ++option2;
            }
        }
        detail.member_ID = general_memberID();
        printf("\nYour member ID is %d\n\n\n", detail.member_ID);
        detail.credit_balance = 0.00;
        detail.Membership_points = 0;
        strcpy(detail.member_category, "Silver");
        printf("Your account balance : RM %.2f\n", detail.credit_balance);
        printf("Member Category      : %s\n", detail.member_category);
        printf("Membership points    : %d\n\n", detail.Membership_points);
        printf("Member account register successful!\n\n\n");

        printf("Do you want to continue register member?('stop' to exit) : ");
        rewind(stdin);
        scanf("%[^\n]", &selection2);

        fprintf(file_input, "%d\n%s\n%s\n%s\n%s\n%c\n%s\n%s\n%d\n%s\n%s\n%.2f\n%s\n%d\n\n",
            detail.member_ID, detail.name, detail.user_name, detail.mycard, detail.phone, detail.gender, detail.email, detail.add.address, detail.add.postcode, detail.add.country, detail.password, detail.credit_balance, detail.member_category, detail.Membership_points);

        booking mem_a;
        FILE* fp;
        fp = fopen("booking.bin", "ab");
        if (fp == NULL) {
            printf("Error opening file!\n");
            exit(-1);
        }
        mem_a.mem_id = detail.member_ID;
        mem_a.credit = detail.credit_balance;
        strcpy(mem_a.password, detail.password);
        strcpy(mem_a.mem_category, detail.member_category);

        fwrite(&mem_a, sizeof(booking), 1, fp);

        fclose(fp);

    }
    fclose(file_input);

}
void search_member_info(int mem_id) {
    int index;
    member detail;
    FILE* file_input;
    file_input = fopen("memberinfo.txt", "r");
    float MAX_point;
    if (file_input == NULL) {
        printf("Error!Cannot open the memberinfo.txt\n");
        exit(-1);
    }
    while (fscanf(file_input, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%c\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%[^\n]\n%f\n%[^\n]\n%d\n\n",
        &detail.member_ID, &detail.name, &detail.user_name, &detail.mycard, &detail.phone,
        &detail.gender, &detail.email, &detail.add.address, &detail.add.postcode, &detail.add.country, &detail.password, &detail.credit_balance, &detail.member_category, &detail.Membership_points) != EOF) {
        if (mem_id == detail.member_ID) {
            printf("======================================================================\n");
            printf("|                                                                    |\n");
            printf("|                         Search Information                         |\n");
            printf("|                                                                    |\n");
            printf("======================================================================\n");
            int selection2;
            printf("===========================Search Selection===========================\n");
            printf("|1. Search Membership points & category                              |\n");
            printf("|2. Ticket Booking Status                                            |\n");
            printf("|3. Return to Menu                                                   |\n");
            printf("======================================================================\n");
            printf("Please select your choice :");
            rewind(stdin);
            scanf("%d", &selection2);
            switch (selection2) {
            case 1:
                printf("\n\n=========================Search Membership points & category=========================\n\n");
                printf("Hello! Dear %s\n", detail.name);
                printf("\n\n==================================Membership==================================\n\n");
                printf("Your Membership Level  : %s\n", detail.member_category);
                printf("Your Membershio Points : %d\n", detail.Membership_points);
                if (detail.Membership_points == 0 && detail.Membership_points <= 499) {
                    MAX_point = 500 - (float)detail.Membership_points;
                    printf("You will need to top up an additional RM%.2f to upgrade to Gold level.\n\n", MAX_point);
                }
                else if (500 <= detail.Membership_points && 999 >= detail.Membership_points) {
                    MAX_point = 1000 - (float)detail.Membership_points;
                    printf("You will need to top up an additional RM%.2f to upgrade to Diamond level.\n\n", MAX_point);
                }
                else if (1000 <= detail.Membership_points) {
                    strcpy(detail.member_category, "Diamond");
                    printf("You are already at the highest member level! Thank you for supporting us!\n\n");
                }
                break;
            case 2:
                printf("\n\n=========================Ticket Booking Status=========================\n\n\n");
                search_ticket_status(mem_id);
                break;
            case 3:
                fclose(file_input);
                return;
            default:
                printf("Invalid selection!Please try again\n");
                break;
            }
            system("pause");
            system("cls");
            break;
        }

    }
    fclose(file_input);
}
void search_ticket_status(int mem_id) {
    int x;
    char search_depart[20];

    FILE* fp;
    fp = fopen("booking.bin", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }
    printf("Enter Departure Station to search train status :");
    scanf("%s", &search_depart);
    for (int i = 0; i < 20; i++) {
        search_depart[i] = toupper(search_depart[i]);
    }
    while (fread(&member_status, sizeof(booking), 1, fp)) {
        if (mem_id == member_status.mem_id) {
            break;
        }
    }
    for (x = 0; x < MAX_BOOKING; x++) {
        if (strcmp(search_depart, member_status.t_detail[x].depstation) == 0) {
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %-10s | %-20s | %-20s | %-14s | %-12s | %-12s | %-10s |\n", "Booking ID", "Departure Station", "Arrival Station", "Departure Time", "Arrival Time", "Date", "Quantity");
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %-10d | %-20s | %-20s | %-14s | %-12s | %-4d/%-2d/%-4d | %-10d |\n", member_status.t_detail[x].booking_id, member_status.t_detail[x].depstation,
                member_status.t_detail[x].arrstation, member_status.t_detail[x].deptime, member_status.t_detail[x].arrtime, member_status.t_detail[x].departdate.day, member_status.t_detail[x].departdate.month, member_status.t_detail[x].departdate.year, member_status.t_detail[x].quantity);
            printf("------------------------------------------------------------------------------------------------------------------------\n\n");
            break;
        }
    }
    if (x == MAX_BOOKING) {
        printf("Departure Station not found! Please try again!\n");
    }
    fclose(fp);
    memset(&member_status, 0, sizeof(member_status));
}
void modify_member_info(int mem_id) {
    member detail[MAX_ACCOUNT];
    FILE* file_output;
    float  top_up;
    int selection3, subselect1, option = 0, option2 = 0, index = 0;
    int valid_top_up = 0;
    file_output = fopen("memberinfo.txt", "r");
    if (file_output == NULL) {
        printf("Error!Cannot open the memberinfo.txt\n");
        exit(-1);
    }
    while (fscanf(file_output, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%c\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%[^\n]\n%f\n%[^\n]\n%d\n\n",
        &detail[index].member_ID, &detail[index].name, &detail[index].user_name, &detail[index].mycard, &detail[index].phone, &detail[index].gender, &detail[index].email, &detail[index].add.address, &detail[index].add.postcode, &detail[index].add.country, &detail[index].password, &detail[index].credit_balance, &detail[index].member_category, &detail[index].Membership_points) != EOF) {
        if (mem_id == detail[index].member_ID) {
            printf("======================================================================\n");
            printf("|                                                                    |\n");
            printf("|                             Modify Page                            |\n");
            printf("|                                                                    |\n");
            printf("======================================================================\n");
            printf("|                                                                    |\n");
            printf("|1. Modify personal information                                      |\n");
            printf("|2. top up balance                                                   |\n");
            printf("|3. Return to Menu                                                   |\n");
            printf("======================================================================\n");
            printf("Please select your selection :");
            scanf("%d", &selection3);
            switch (selection3) {
            case 1:
                printf("\n\n================================Modify Account Information================================\n\n");
                printf("Which information would you like to modify\n");
                printf("1.Full Name     (%s)\n", detail[index].name);
                printf("2.User Name     (%s)\n", detail[index].user_name);
                printf("3.IC/Passport   (%s)\n", detail[index].mycard);
                printf("4.Tel.No        (%s)\n", detail[index].phone);
                printf("5.Email         (%s)\n", detail[index].email);
                printf("6.Address       (%s)\n", detail[index].add.address);
                printf("7.Postcode      (%d)\n", detail[index].add.postcode);
                printf("8.Country       (%s)\n", detail[index].add.country);
                printf("9.Password      (%s)\n", detail[index].password);
                printf("10.Back to Menu\n");
                printf("\nEnter your choice :");
                scanf("%d", &subselect1);

                switch (subselect1) {
                case 1:
                    printf("Enter new name(Full Name) :");
                    rewind(stdin);
                    scanf("%[^\n]", &detail[index].name);
                    printf("Successful update.\n\n");
                    break;
                case 2:
                    printf("Enter new username        :");
                    rewind(stdin);
                    scanf("%[^\n]", &detail[index].user_name);
                    printf("Successful update.\n\n");
                    break;
                case 3:
                    printf("Enter new IC/Passport     :");
                    rewind(stdin);
                    scanf("%[^\n]", &detail[index].mycard);
                    printf("Successful update.\n\n");
                    break;
                case 4:
                    printf("Enter new phone number    :");
                    rewind(stdin);
                    scanf("%[^\n]", &detail[index].phone);
                    printf("Successful update.\n\n");
                    break;
                case 5:
                    printf("Enter new email           :");
                    rewind(stdin);
                    scanf("%[^\n]", &detail[index].email);
                    printf("Successful update.\n\n");
                    break;
                case 6:
                    printf("Enter new address         :");
                    rewind(stdin);
                    scanf("%[^\n]", &detail[index].add.address);
                    printf("Successful update.\n\n");
                    break;
                case 7:
                    printf("Enter new postcode    :");
                    rewind(stdin);
                    scanf("%d", &detail[index].add.postcode);
                    printf("Successful update.\n\n");
                    break;
                case 8:
                    printf("Enter new country    :");
                    rewind(stdin);
                    scanf("%[^\n]", &detail[index].add.country);
                    printf("Successful update.\n\n");
                    break;
                case 9:
                    printf("Enter new password        :");
                    rewind(stdin);
                    scanf("%[^\n]", &detail[index].password);
                    printf("Confirmation password (must same with password): ");
                    rewind(stdin);
                    scanf("%[^\n]", &detail[index].password2);
                    while (!option2) {
                        if (strcmp(detail[index].password2, detail[index].password) != 0) {
                            printf("Password does not match password!\n");
                            printf("Confirmation password (must same with password): ");
                            rewind(stdin);
                            scanf("%[^\n]", &detail[index].password2);
                        }
                        else {
                            ++option2;
                        }
                    }
                    printf("Successful update.\n\n");
                    break;
                case 10:
                    fclose(file_output);
                    return;
                default:
                    printf("Invalid choice! Please try again!\n");
                    fclose(file_output);
                    system("pause");
                    system("cls");
                    return;
                }
                system("pause");
                break;
            case 2:
                printf("================================Top Up Account Balance================================\n\n\n");
                while (!valid_top_up) {
                    printf("How much do you need to top up your account?\n");
                    printf("Top up amount   :RM ");
                    rewind(stdin);
                    scanf("%f", &top_up);
                    if (top_up < 0) {
                        printf("Error! Please enter a valid top-up amount.\n");
                    }
                    else {
                        valid_top_up = 1;
                    }
                }
                detail[index].credit_balance = detail[index].credit_balance + top_up;
                detail[index].Membership_points = detail[index].Membership_points + (int)top_up;

                if (detail[index].Membership_points == 0 && detail[index].Membership_points <= 499) {
                    strcpy(detail[index].member_category, "Silver");
                }
                else if (500 <= detail[index].Membership_points && 999 >= detail[index].Membership_points) {
                    strcpy(detail[index].member_category, "Gold");
                }
                else if (1000 <= detail[index].Membership_points) {
                    strcpy(detail[index].member_category, "Diamond");
                }
                printf("\nThank You! Your account balance RM%.2f topped up successfully.\n", detail[index].credit_balance);
                system("pause");
                system("cls");
                break;
            case 3:
                fclose(file_output);
                return;
            default:
                printf("Invalid selection! Please try again!\n");
                fclose(file_output);
                return;
            }
            FILE* fp;
            int arr = 0;
            fp = fopen("booking.bin", "rb");
            if (fp == NULL) {
                printf("Error opening file!\n");
                exit(-1);
            }
            while (fread(&mem_m[arr], sizeof(booking), 1, fp)) {
                if (mem_id == mem_m[arr].mem_id) {
                    mem_m[arr].mem_id = detail[index].member_ID;
                    mem_m[arr].credit = detail[index].credit_balance;
                    strcpy(mem_m[arr].password, detail[index].password);
                    strcpy(mem_m[arr].mem_category, detail[index].member_category);
                }
                arr++;
            }
            fclose(fp);

            FILE* fp2;
            fp2 = fopen("booking.bin", "wb");
            if (fp2 == NULL) {
                printf("Error opening file!\n");
                exit(-1);
            }

            for (int i = 0; i < arr; i++) {
                fwrite(&mem_m[i], sizeof(booking), 1, fp2);
            }

            fclose(fp2);
            memset(mem_m, 0, sizeof(mem_m));
        }
        index++;
    }
    fclose(file_output);
    FILE* file_input;
    file_input = fopen("memberinfo.txt", "w");
    for (int y = 0; y < index; y++) {
        fprintf(file_input, "%d\n%s\n%s\n%s\n%s\n%c\n%s\n%s\n%d\n%s\n%s\n%.2f\n%s\n%d\n\n",
            detail[y].member_ID, detail[y].name, detail[y].user_name, detail[y].mycard, detail[y].phone, detail[y].gender, detail[y].email, detail[y].add.address, detail[y].add.postcode, detail[y].add.country, detail[y].password, detail[y].credit_balance, detail[y].member_category, detail[y].Membership_points);
    }
    fclose(file_input);
}
void display_member_info(int mem_id) {
    member detail;
    FILE* file_input;
    file_input = fopen("memberinfo.txt", "r");
    if (file_input == NULL) {
        printf("Error!Cannot open the memberinfo.txt\n");
        exit(-1);
    }
    system("cls");
    printf("======================================================================\n");
    printf("|                                                                    |\n");
    printf("|                          personal profile                          |\n");
    printf("|                                                                    |\n");
    printf("======================================================================\n\n\n");
    while (fscanf(file_input, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%c\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%[^\n]\n%f\n%[^\n]\n%d\n\n",
        &detail.member_ID, &detail.name, &detail.user_name, &detail.mycard, &detail.phone, &detail.gender, &detail.email, &detail.add.address,
        &detail.add.postcode, &detail.add.country, &detail.password, &detail.credit_balance, &detail.member_category, &detail.Membership_points) != EOF) {
        if (mem_id == detail.member_ID) {
            printf("\n\n\nWelcome! %s!\n\n", detail.name);
            printf("=====================Your profile=====================\n");
            printf("Member ID   : %d\n", detail.member_ID);
            printf("User Name   : %s\n", detail.user_name);
            printf("IC/Passport : %s\n", detail.mycard);
            printf("Phone Number: %s\n", detail.phone);
            printf("Gender      : %c\n", detail.gender);
            printf("Email       : %s\n", detail.email);
            printf("Address     : %s\n", detail.add.address);
            printf("Postcode    : %d\n", detail.add.postcode);
            printf("Country     : %s\n", detail.add.country);
            printf("======================================================\n\n");
            printf("Your account balance : RM %.2f\n", detail.credit_balance);
            printf("Member Category      : %s\n", detail.member_category);
            printf("Membership points    : %d\n\n", detail.Membership_points);
            system("pause");
        }
    }
    fclose(file_input);
}
void delete_member_info(int mem_id) {
    member detail[MAX_ACCOUNT];
    int index = 0;
    FILE* file_output;
    int delateID = 0;
    file_output = fopen("memberinfo.txt", "r");
    if (file_output == 0) {
        printf("Error!Cannot open memberinfo.txt\n");
        exit(-1);
    }
    system("cls");
    while (fscanf(file_output, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%c\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%[^\n]\n%f\n%[^\n]\n%d\n\n",
        &detail[index].member_ID, &detail[index].name, &detail[index].user_name, &detail[index].mycard, &detail[index].phone, &detail[index].gender, &detail[index].email,
        &detail[index].add.address, &detail[index].add.postcode, &detail[index].add.country, &detail[index].password, &detail[index].credit_balance, &detail[index].member_category, &detail[index].Membership_points) != EOF) {
        if (mem_id == detail[index].member_ID) {
            detail[index].member_ID = 0;
        }
        index++;
    }
    fclose(file_output);
    FILE* file_input;
    file_input = fopen("memberinfo.txt", "w");
    for (int y = 0; y < index; y++) {
        if (detail[y].member_ID == 0) {
            continue;
        }
        fprintf(file_input, "%d\n%s\n%s\n%s\n%s\n%c\n%s\n%s\n%d\n%s\n%s\n%.2f\n%s\n%d\n\n",
            detail[y].member_ID, detail[y].name, detail[y].user_name, detail[y].mycard, detail[y].phone, detail[y].gender, detail[y].email,
            detail[y].add.address, detail[y].add.postcode, detail[y].add.country, detail[y].password, detail[y].credit_balance, detail[y].member_category, detail[y].Membership_points);
    }
    fclose(file_input);
    printf("Member account successfully deleted.\n\n\n\n");


    FILE* fp;
    int arr = 0;
    fp = fopen("booking.bin", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }
    while (fread(&mem_d[arr], sizeof(booking), 1, fp)) {
        if (mem_id == mem_d[arr].mem_id) {
            mem_d[arr].mem_id = 0;
        }
        arr++;
    }
    fclose(fp);

    FILE* fp2;
    fp2 = fopen("booking.bin", "wb");
    if (fp2 == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    for (int i = 0; i < arr; i++) {
        if (mem_d[i].mem_id == 0) {
            continue;
        }
        else {
            fwrite(&mem_d[i], sizeof(booking), 1, fp2);
        }
    }

    fclose(fp2);
    memset(mem_d, 0, sizeof(mem_d));
}
//siew ian

//clarisse
void schedule_module() {
    struct TrainSchedule trainSchedules[MAX_TRAIN];
    int numTrains = 0;
    int choice, option, login;
    char trainID[10];

    do {
        system("cls");
        logo();
        printf("\nTrain Scheduling Module\n");
        printf("1. Staff Mode\n");
        printf("2. Search Train Schedule\n");
        printf("3. Display All Train Schedules\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf(" %d", &choice);

        if (choice == 1) {
            printf("Staff Mode:\n");
            printf("1. Add Train Schedule\n");
            printf("2. Modify Train Schedule\n");
            printf("3. Delete Train Schedule\n");
            printf("Enter your choice: ");
            scanf(" %d", &option);

            if (option == 1) {
                login = staffLogin();
                if (login == 1) {
                    printf("Login successful!\n");
                }
                else {
                    printf("Login unsuccessful!\n");
                    return;
                }
                system("pause");
                system("cls");
                addTrainSchedule(trainSchedules, &numTrains);
            }
            else if (option == 2) {
                login = staffLogin();
                if (login == 1) {
                    printf("Login successful!\n");
                }
                else {
                    printf("Login unsuccessful!\n");
                    return;
                }
                system("pause");
                system("cls");
                printf("Enter Train ID to modify: ");
                scanf("%s", &trainID);
                modifyTrainSchedule(trainID);
            }
            else if (option == 3) {
                login = staffLogin();
                if (login == 1) {
                    printf("Login successful!\n");
                }
                else {
                    printf("Login unsuccessful!\n");
                    return;
                }
                system("pause");
                system("cls");
                printf("Enter Train ID to delete: ");
                scanf("%s", &trainID);
                deleteTrainSchedule(trainID);
            }
            else {
                printf("Invalid choice!\n");
            }

        }
        else if (choice == 2) {
            system("cls");
            printf("Enter Train ID to search: ");
            scanf("%s", &trainID);
            searchTrainSchedule(trainSchedules, numTrains, trainID);
        }
        else if (choice == 3) {
            system("cls");
            displayTrainSchedule();
            system("pause");
        }
        else if (choice == 4) {
            break;
        }
        else
            printf("Invalid choice. Please try again.\n");
    } while (1);

    return;
}

int staffLogin() {
    int id, x = 0;
    char password[20];
    staff Staff;

    system("cls");
    logo();
    printf("\n\n*********************************\n");
    printf("*       WELCOME TO LOGIN        *\n");
    printf("*********************************\n\n");
    printf("Staff ID: ");
    scanf("%d", &id);
    printf("Password: ");
    scanf("%s", password);

    FILE* fp;
    fp = fopen("staff.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }
    while (fscanf(fp, "%[^\n]\n%s\n%s\n%s\n%d\n%c\n%s\n%s\n%d\n%s\n", &Staff.name, &Staff.email, &Staff.mycard, &Staff.position, &Staff.age, &Staff.gender, &Staff.p_num.phone, &Staff.p_num.phone2, &Staff.staffID, &Staff.password2) != EOF) {
        if (Staff.staffID == id) {
            if (strcmp(Staff.password2, password) == 0) {
                x = 1;
                break;
            }
            else {
                printf("Invalid password");
                break;
            }

        }
    }
    fclose(fp);

    return x;

}

void addTrainSchedule(struct TrainSchedule trainSchedules[], int* numTrains) {
    FILE* fp;
    if (*numTrains < MAX_TRAIN) {
        printf("Enter Train ID(e.g 2000): ");
        scanf("%s", trainSchedules[*numTrains].trainID);
        printf("Enter Departure Station(e.g kampar): ");
        while (getchar() != '\n');
        fgets(trainSchedules[*numTrains].departStation, MAX_STATION_LENGTH, stdin);
        trainSchedules[*numTrains].departStation[strcspn(trainSchedules[*numTrains].departStation, "\n")] = '\0';
        for (int i = 0; i < 50; i++) {
            trainSchedules[*numTrains].departStation[i] = toupper(trainSchedules[*numTrains].departStation[i]);
        }

        printf("Enter Arrival Station(e.g ipoh): ");
        fgets(trainSchedules[*numTrains].arrStation, MAX_STATION_LENGTH, stdin);
        trainSchedules[*numTrains].arrStation[strcspn(trainSchedules[*numTrains].arrStation, "\n")] = '\0';
        for (int i = 0; i < 50; i++) {
            trainSchedules[*numTrains].arrStation[i] = toupper(trainSchedules[*numTrains].arrStation[i]);
        }
        printf("Enter Departure Date:\n");
        printf("                Year(e.g 2024):");
        rewind(stdin);
        scanf("%d", &trainSchedules[*numTrains].departdate.year);
        printf("               Month(e.g 6):");
        scanf("%d", &trainSchedules[*numTrains].departdate.month);
        printf("                 Day(e.g 24):");
        scanf("%d", &trainSchedules[*numTrains].departdate.day);
        printf("Enter Departure Time(e.g 0900): ");
        scanf("%s", trainSchedules[*numTrains].departTime);
        rewind(stdin);
        printf("Enter Arrival Time(e.g 1300): ");
        scanf("%s", trainSchedules[*numTrains].arrTime);
        rewind(stdin);
        printf("Enter Price (RM) : ");
        scanf("%f", &trainSchedules[*numTrains].price);
        rewind(stdin);
        trainSchedules[*numTrains].availableSeats = 160;

        fp = fopen("train_schedule.bin", "ab");
        if (fp == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }

        fwrite(&trainSchedules[*numTrains], sizeof(struct TrainSchedule), 1, fp);

        fclose(fp);

        (*numTrains)++;
        printf("Train schedule added successfully.\n");
    }
    else {
        printf("Maximum number of trains reached. Cannot add more.\n");
    }

    system("cls");
}

void searchTrainSchedule(struct TrainSchedule trainSchedules[], int numTrains, char trainID[]) {
    FILE* fp;
    struct TrainSchedule temp;

    fp = fopen("train_schedule.bin", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int found = 0;
    while (fread(&temp, sizeof(struct TrainSchedule), 1, fp) == 1) {
        if (strcmp(temp.trainID, trainID) == 0) {
            printf("\nTrain ID: %s\n", temp.trainID);
            printf("Departure Station: %s\n", temp.departStation);
            printf("Arrival Station: %s\n", temp.arrStation);
            printf("Departure Date: %d/%d/%d\n", temp.departdate.day, temp.departdate.month, temp.departdate.year);
            printf("Departure Time: %s\n", temp.departTime);
            printf("Arrival Time: %s\n", temp.arrTime);
            printf("Available Seats: %d\n", temp.availableSeats);
            printf("Price(RM): %.2f\n", temp.price);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("Train ID not found.\n");
    }

    system("pause");
    system("cls");
}

void modifyTrainSchedule(char trainID[]) {
    FILE* fp;
    FILE* tempFile;
    struct TrainSchedule temp;
    int modified = 0;

    fp = fopen("train_schedule.bin", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    tempFile = fopen("temp.bin", "wb");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }

    int found = 0;
    while (fread(&temp, sizeof(struct TrainSchedule), 1, fp) == 1) {
        if (strcmp(temp.trainID, trainID) == 0) {
            printf("Enter New Departure Station(e.g kampar): ");
            scanf(" %[^\n]", &temp.departStation);
            for (int i = 0; i < 50; i++) {
                temp.departStation[i] = toupper(temp.departStation[i]);
            }
            printf("Enter New Arrival Station(e.g ipoh): ");
            scanf(" %[^\n]", &temp.arrStation);
            for (int i = 0; i < 50; i++) {
                temp.arrStation[i] = toupper(temp.arrStation[i]);
            }
            printf("Enter Departure Date:\n");
            printf("                Year(e.g 2024):");
            scanf("%d", &temp.departdate.year);
            printf("               Month(e.g 6):");
            scanf("%d", &temp.departdate.month);
            printf("                 Day(e.g 24):");
            scanf("%d", &temp.departdate.day);
            printf("Enter New Departure Time(e.g 1300): ");
            scanf("%s", &temp.departTime);
            printf("Enter New Arrival Time(e.g 1500): ");
            scanf("%s", &temp.arrTime);
            printf("Train schedule modified successfully.\n");
            modified = 1;
            found = 1;
        }
        fwrite(&temp, sizeof(struct TrainSchedule), 1, tempFile);
    }
    fclose(fp);
    fclose(tempFile);

    if (!found) {
        printf("Train ID not found.\n");
        remove("temp.bin");
    }
    else if (!modified) {
        printf("No modifications made to the train schedule.\n");
        remove("temp.bin");
    }
    else {
        if (remove("train_schedule.bin") != 0) {
            printf("Error deleting original file!\n");
            return;
        }
        if (rename("temp.bin", "train_schedule.bin") != 0) {
            printf("Error renaming temporary file!\n");
            return;
        }
    }
    system("pause");
    system("cls");
}

void displayTrainSchedule() {
    FILE* fp;
    struct TrainSchedule temp;

    fp = fopen("train_schedule.bin", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nTrain Schedules:\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-9s | %-20s | %-20s |  %-12s | %-14s | %-12s | %-15s | %-6s |\n", "Train ID", "Departure Station", "Arrival Station", "Departure Date", "Departure Time", "Arrival Time", "Available Seats", "Price");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    while (fread(&temp, sizeof(struct TrainSchedule), 1, fp) == 1) {
        printf("| %-9s | %-20s | %-20s |  %-4d/%-2d/%-4d | %-14s | %-12s | %-15d | %-6.2f |\n", temp.trainID, temp.departStation, temp.arrStation, temp.departdate.day, temp.departdate.month, temp.departdate.year,
            temp.departTime, temp.arrTime, temp.availableSeats, temp.price);
    }

    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    seat(temp.seat);
    fclose(fp);

}

void deleteTrainSchedule(char trainID[]) {
    FILE* fp;
    FILE* tempFile;
    struct TrainSchedule temp;
    int deleted = 0, index = 0, arr = 0;

    fp = fopen("train_schedule.bin", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    tempFile = fopen("temp.bin", "wb");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }

    while (fread(&temp, sizeof(struct TrainSchedule), 1, fp) == 1) {
        if (strcmp(temp.trainID, trainID) == 0) {
            deleted = 1;

            FILE* b_fp;
            b_fp = fopen("booking.bin", "rb");
            if (b_fp == NULL) {
                printf("Error opening file!\n");
                exit(-1);
            }

            while (fread(&del_schedule[index], sizeof(booking), 1, b_fp)) {
                for (int x = 0; x < MAX_BOOKING; x++) {
                    if (strcmp(del_schedule[index].t_detail[x].train_id, trainID) == 0) {
                        if (strcmp(del_schedule[index].t_detail[x].tic_status, "Booked") == 0) {
                            strcpy(del_schedule[index].t_detail[x].tic_status, "Cancelled");
                            del_schedule[index].credit += del_schedule[index].t_detail[x].amount;
                            FILE* m_fp;
                            member detail[MAX_ACCOUNT];

                            m_fp = fopen("memberinfo.txt", "r");
                            if (m_fp == NULL) {
                                printf("Error opening file!\n");
                                exit(-1);
                            }

                            while (fscanf(m_fp, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%c\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%[^\n]\n%f\n%[^\n]\n%d\n\n",
                                &detail[arr].member_ID, &detail[arr].name, &detail[arr].user_name, &detail[arr].mycard, &detail[arr].phone,
                                &detail[arr].gender, &detail[arr].email, &detail[arr].add.address, &detail[arr].add.postcode, &detail[arr].add.country, &detail[arr].password, &detail[arr].credit_balance, &detail[arr].member_category, &detail[arr].Membership_points) != EOF) {
                                if (del_schedule[index].mem_id == detail[arr].member_ID) {
                                    detail[arr].credit_balance = detail[arr].credit_balance + del_schedule[index].t_detail[x].amount;
                                }
                                arr++;
                            }

                            fclose(m_fp);
                            FILE* m_fp2;

                            m_fp2 = fopen("memberinfo.txt", "w");
                            if (m_fp2 == NULL) {
                                printf("Error opening file!\n");
                                exit(-1);
                            }
                            for (int y = 0; y < arr; y++) {
                                fprintf(m_fp2, "%d\n%s\n%s\n%s\n%s\n%c\n%s\n%s\n%d\n%s\n%s\n%.2f\n%s\n%d\n\n",
                                    detail[y].member_ID, detail[y].name, detail[y].user_name, detail[y].mycard, detail[y].phone, detail[y].gender, detail[y].email, detail[y].add.address, detail[y].add.postcode, detail[y].add.country, detail[y].password, detail[y].credit_balance, detail[y].member_category, detail[y].Membership_points);
                            }
                            fclose(m_fp2);
                        }
                    }
                }
                index++;
            }

            fclose(b_fp);
            FILE* b_fp2;

            b_fp2 = fopen("booking.bin", "wb");
            if (b_fp2 == NULL) {
                printf("Error opening file!\n");
                exit(-1);
            }
            for (int i = 0; i < index; i++) {
                fwrite(&del_schedule[i], sizeof(booking), 1, b_fp2);
            }
            fclose(b_fp2);
            memset(del_schedule, 0, sizeof(del_schedule));

            continue;
        }
        fwrite(&temp, sizeof(struct TrainSchedule), 1, tempFile);
    }

    fclose(fp);
    fclose(tempFile);

    if (!deleted) {
        printf("Train ID not found.\n");
        remove("temp.bin");
    }
    else {
        remove("train_schedule.bin");
        rename("temp.bin", "train_schedule.bin");
        printf("Train schedule deleted successfully.\n");
    }
    system("pause");
    system("cls");
}

void seat(int seat_[4][40]) {
    int coach = 0, x, y;

    for (coach = 0; coach < 4; coach++) {
        x = 0;
        printf("Coach %d\n", coach + 1);
        printf("-------------\n");
        while (x < 40) {
            printf("|");
            for (y = 0; y < 4; y++) {
                if (seat_[coach][x] == 1) {
                    printf("X |", x + 1);
                }
                else {
                    printf("%2d|", x + 1);
                }

                x++;
            }
            printf("\n");
        }
        printf("-------------\n");

    }


}
//clarisse

//weile
void booking_module() {
    int mem_id, choose;
    mem_id = booking_login();
    if (mem_id == -1) {
        return;
    }
    choose = booking_menu();
    while (choose != 6) {
        if (choose == 1) {
            search_schedule();
        }
        else if (choose == 2) {
            add_ticket_booking(mem_id);
            system("pause");
            system("cls");
        }
        else if (choose == 3) {
            modify_ticket_booking(mem_id);
            system("pause");
            system("cls");
        }
        else if (choose == 4) {
            display_booking_records(mem_id);
            system("pause");
            system("cls");
        }
        else if (choose == 5) {
            cancel_ticket_booking(mem_id);
            system("pause");
            system("cls");
        }
        else {
            printf("Please choose 1 until 6\n");
        }
        choose = booking_menu();
    }
}

int booking_login() {

    int id, count, x = 0, y;
    char password[20];
    booking mem;


    while (x != -1) {
        count = 0;
        logo();
        printf("\n\n*********************************\n");
        printf("*       WELCOME TO LOGIN        *\n");
        printf("*********************************\n\n");
        printf("MEMBER ID:");
        scanf("%d", &id);
        printf("PASSWORD :");
        scanf("%s", &password);

        FILE* fp;
        fp = fopen("booking.bin", "rb");
        if (fp == NULL) {
            printf("Error opening file!\n");
            return 0;
        }

        while (fread(&mem, sizeof(booking), 1, fp)) {

            if (mem.mem_id == id) {
                if (strcmp(password, mem.password) == 0) {
                    printf("Login Successful\n");
                    system("pause");
                    system("cls");

                    fclose(fp);
                    return id;
                }

            }

        }
        fclose(fp);
        printf("Incorrect id or password\n");
        printf("Please press 0 to continue logging in, press -1 to Exit:");
        scanf("%d", &x);
        system("cls");


    }
    return x;
}

int booking_menu() {
    int x;
    logo();
    printf("\n\n================================================\n");
    printf("| 1.Search Schedule                            |\n");
    printf("| 2.Ticket Booking                             |\n");
    printf("| 3.Modify Ticket Booking                      |\n");
    printf("| 4.Display Ticket Records                     |\n");
    printf("| 5.Cancel Ticket Booking                      |\n");
    printf("| 6.Exit Ticket Booking                        |\n");
    printf("================================================\n");

    printf("Please enter your choose:");
    scanf("%d", &x);
    system("cls");
    return x;
}

void search_schedule() {
    char sta_dep[50];
    int x = 0;
    struct TrainSchedule tem;

    printf("Please enter your station of departure:");
    rewind(stdin);
    scanf("%[^\n]", &sta_dep);
    for (int i = 0; i < 50; i++) {
        sta_dep[i] = toupper(sta_dep[i]);
    }

    FILE* fp;
    fp = fopen("train_schedule.bin", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    while (fread(&tem, sizeof(struct TrainSchedule), 1, fp)) {
        if (strcmp(sta_dep, tem.departStation) == 0) {

            printf("\n\nTrain Schedules:\n");
            printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %-9s | %-20s | %-20s | %-12s | %-14s | %-12s | %-15s | %-6s |\n", "Train ID", "Departure Station", "Arrival Station", "Departure Date", "Departure Time", "Arrival Time", "Available Seats", "Price");
            printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %-9s | %-20s | %-20s | %-4d/%-4d/%-4d | %-14s | %-12s | %-15d | %-6.2f |\n", tem.trainID, tem.departStation, tem.arrStation, tem.departdate.day, tem.departdate.month, tem.departdate.year,
                tem.departTime, tem.arrTime, tem.availableSeats, tem.price);
            printf("---------------------------------------------------------------------------------------------------------------------------------------\n\n\n");
            x++;
        }
    }
    if (x == 0) {
        printf("There is no schedules for this\n");
    }
    else {
        printf("Please remember the train id of the schedule you need\n");
    }
    system("pause");
    system("cls");
}


void add_ticket_booking(int mem_id) {
    char train_id[10];
    struct TrainSchedule tem[MAX_TRAIN];
    int x = 0, quantity, coach = 0, seat_num, confirm, arr, count = 0, train = 0, t_index = -1;


    FILE* fp;
    fp = fopen("train_schedule.bin", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    FILE* fp2;
    fp2 = fopen("booking.bin", "rb");
    if (fp2 == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    while (fread(&bookings_a[count], sizeof(booking), 1, fp2)) {
        if (mem_id == bookings_a[count].mem_id) {

            for (arr = 0; arr < MAX_BOOKING; arr++) {
                if (bookings_a[count].t_detail[arr].booking_id == 0) {
                    break;
                }
            }

            printf("Please enter the train id of the train schedule you want: ");
            scanf("%s", &train_id);

            while (fread(&tem[train], sizeof(struct TrainSchedule), 1, fp)) {
                if (strcmp(train_id, tem[train].trainID) == 0) {
                    t_index = train;
                }
                train++;
            }
            if (x == -1) {
                printf("There is no schedules for this,please try again\n");
                system("pause");
                fclose(fp);
                fclose(fp2);
                memset(bookings_a, 0, sizeof(bookings_a));
                return;
            }

            strcpy(bookings_a[count].t_detail[arr].train_id, tem[t_index].trainID);
            strcpy(bookings_a[count].t_detail[arr].depstation, tem[t_index].departStation);
            strcpy(bookings_a[count].t_detail[arr].arrstation, tem[t_index].arrStation);
            bookings_a[count].t_detail[arr].departdate.day = tem[t_index].departdate.day;
            bookings_a[count].t_detail[arr].departdate.month = tem[t_index].departdate.month;
            bookings_a[count].t_detail[arr].departdate.year = tem[t_index].departdate.year;
            strcpy(bookings_a[count].t_detail[arr].deptime, tem[t_index].departTime);
            strcpy(bookings_a[count].t_detail[arr].arrtime, tem[t_index].arrTime);


            printf("How many tickets do you need:");
            scanf("%d", &bookings_a[count].t_detail[arr].quantity);

            for (int y = 0; y < bookings_a[count].t_detail[arr].quantity; y++) {
                for (coach = 0; coach < 4; coach++) {
                    seat_num = 0;
                    printf("coach %d\n", coach + 1);
                    printf("-------------\n");
                    while (seat_num < 40) {
                        printf("|");
                        for (int z = 0; z < 4; z++) {
                            if (tem[t_index].seat[coach][seat_num] == 1) {
                                printf("X |", seat_num + 1);
                            }
                            else {
                                printf("%2d|", seat_num + 1);
                            }

                            seat_num++;
                        }
                        printf("\n");
                    }
                    printf("-------------\n");

                }
                do {
                    printf("Please select your coach:");
                    scanf("%d", &coach);
                    while (coach < 1 || coach > 4) {
                        printf("Error,please select coach 1-4:");
                        scanf("%d", &coach);
                    }
                    printf("Please select your seat :");
                    scanf("%d", &seat_num);
                    while (seat_num < 1 || seat_num > 40) {
                        printf("Error,please select seat 1-40:");
                        scanf("%d", &seat_num);
                    }
                    if (tem[t_index].seat[coach - 1][seat_num - 1] == 1) {
                        printf("The seat has been chosen or error,please choose again\n\n");
                    }
                } while (tem[t_index].seat[coach - 1][seat_num - 1] == 1);

                tem[t_index].seat[coach - 1][seat_num - 1] = 1;
                bookings_a[count].t_detail[arr].seat[coach - 1][seat_num - 1] = 1;
                printf("Please enter the customer's name:");
                rewind(stdin);
                scanf("%[^\n]", &bookings_a[count].t_detail[arr].cus_name[y]);
                rewind(stdin);
                printf("Please enter the customer's IC/PASSPORT:");
                scanf("%s", &bookings_a[count].t_detail[arr].cus_ic[y]);
                rewind(stdin);
                system("cls");
            }

            tem[t_index].availableSeats = tem[t_index].availableSeats - bookings_a[count].t_detail[arr].quantity;
            bookings_a[count].t_detail[arr].amount = cal_payment(bookings_a[count].mem_category, tem[t_index].price, bookings_a[count].t_detail[arr].quantity);

            printf("Your credit balance is RM%.2f ,do you want to pay?\n(Press 1 to confirm, press 0 or other to cancel)           :", bookings_a[count].credit);
            scanf("%d", &confirm);

            if (confirm == 1) {
                bookings_a[count].credit = bookings_a[count].credit - bookings_a[count].t_detail[arr].amount;
                if (bookings_a[count].credit < 0) {
                    printf("Credit low, please top up");
                    system("pause");
                    fclose(fp2);
                    fclose(fp);
                    memset(bookings_a, 0, sizeof(bookings_a));
                    return;
                }
                else {
                    printf("Thank you for your purchase\n");
                    bookings_a[count].t_detail[arr].booking_id = general_id();
                    fclose(fp);
                    FILE* t_input;
                    t_input = fopen("train_schedule.bin", "wb");
                    if (t_input == NULL) {
                        printf("Error opening file!\n");
                        exit(-1);
                    }

                    for (int a = 0; a < train; a++) {
                        fwrite(&tem[a], sizeof(struct TrainSchedule), 1, fp);
                    }

                    fclose(t_input);
                    strcpy(bookings_a[count].t_detail[arr].tic_status, "Booked");

                    FILE* fp3;
                    member detail[MAX_BOOKING];
                    int index = 0;
                    fp3 = fopen("memberinfo.txt", "r");
                    if (fp3 == NULL) {
                        printf("Error opening file!\n");
                        exit(-1);
                    }
                    while (fscanf(fp3, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%c\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%[^\n]\n%f\n%[^\n]\n%d\n\n",
                        &detail[index].member_ID, &detail[index].name, &detail[index].user_name, &detail[index].mycard, &detail[index].phone, &detail[index].gender, &detail[index].email, &detail[index].add.address, &detail[index].add.postcode, &detail[index].add.country, &detail[index].password, &detail[index].credit_balance, &detail[index].member_category, &detail[index].Membership_points) != EOF) {
                        if (bookings_a[count].mem_id == detail[index].member_ID) {
                            detail[index].credit_balance = bookings_a[count].credit;
                        }
                        index++;
                    }

                    fclose(fp3);
                    FILE* file_input;
                    file_input = fopen("memberinfo.txt", "w");
                    for (int y = 0; y < index; y++) {
                        fprintf(file_input, "%d\n%s\n%s\n%s\n%s\n%c\n%s\n%s\n%d\n%s\n%s\n%.2f\n%s\n%d\n\n",
                            detail[y].member_ID, detail[y].name, detail[y].user_name, detail[y].mycard, detail[y].phone, detail[y].gender, detail[y].email, detail[y].add.address, detail[y].add.postcode, detail[y].add.country, detail[y].password, detail[y].credit_balance, detail[y].member_category, detail[y].Membership_points);
                    }
                    fclose(file_input);
                }
            }
            else {
                fclose(fp);
                fclose(fp2);
                memset(bookings_a, 0, sizeof(bookings_a));
                return;
            }
        }
        count++;
    }
    fclose(fp2);
    FILE* input;
    input = fopen("booking.bin", "wb");
    if (input == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }
    for (int i = 0; i < count; i++) {
        fwrite(&bookings_a[i], sizeof(booking), 1, input);
    }
    fclose(input);
    memset(bookings_a, 0, sizeof(bookings_a));
    return;

}

void modify_ticket_booking(int mem_id) {

    int  arr, count = 0, b_id, index = 0;

    FILE* fp;
    fp = fopen("booking.bin", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&modify[index], sizeof(booking), 1, fp)) {
        if (mem_id == modify[index].mem_id) {


            for (arr = 0; arr < MAX_BOOKING; arr++) {
                if (modify[index].t_detail[arr].booking_id != 0) {
                    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("| %-12s | %-10s | %-20s | %-20s | %-15s | %-15s | %-12s |\n", "Booking ID", "Quantity", "Departure Station", "Arrival Station", "Departure Time", "Arrival Time", "Date");
                    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("| %-12d | %-10d | %-20s | %-20s | %-15s | %-15s | %-4d/%-2d/%-4d |\n", modify[index].t_detail[arr].booking_id, modify[index].t_detail[arr].quantity, modify[index].t_detail[arr].depstation, modify[index].t_detail[arr].arrstation,
                        modify[index].t_detail[arr].deptime, modify[index].t_detail[arr].arrtime, modify[index].t_detail[arr].departdate.day, modify[index].t_detail[arr].departdate.month, modify[index].t_detail[arr].departdate.year);
                    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
                    count++;
                }
            }

            if (count == 0) {
                printf("No booking record");
                fclose(fp);
                system("pause");
                memset(modify, 0, sizeof(modify));
                return;
            }
            else {
                printf("Please enter the booking ID that needs to be modified:");
                scanf("%d", &b_id);

                for (arr = 0; arr < MAX_BOOKING; arr++) {
                    if (modify[index].t_detail[arr].booking_id == b_id) {
                        system("cls");
                        printf("Please enter the new customer information you want to modify");
                        for (int x = 0; x < modify[index].t_detail[arr].quantity; x++) {
                            printf("\nPlease enter the customer's name:");
                            rewind(stdin);
                            scanf("%[^\n]", &modify[index].t_detail[arr].cus_name[x]);
                            printf("Please enter the customer's IC/PASSPORT:");
                            rewind(stdin);
                            scanf("%s", &modify[index].t_detail[arr].cus_ic[x]);
                        }
                        printf("\nSuccessfully modified\n");
                        break;
                    }
                }
                if (arr == MAX_BOOKING) {
                    printf("\nCan't find this id\n");
                    fclose(fp);
                    system("pause");
                    memset(modify, 0, sizeof(modify));
                    return;
                }
            }
        }
        index++;
    }
    fclose(fp);


    FILE* input;
    input = fopen("booking.bin", "wb");
    if (input == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    for (int i = 0; i < index; i++) {
        fwrite(&modify[i], sizeof(booking), 1, input);
    }
    fclose(fp);
    system("pause");
    memset(modify, 0, sizeof(modify));
    return;

}

void display_booking_records(int mem_id) {

    int arr = 0;

    FILE* fp;
    fp = fopen("booking.bin", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&display, sizeof(booking), 1, fp)) {
        if (mem_id == display.mem_id) {
            break;
        }
    }

    while (display.t_detail[arr].booking_id != 0) {
        printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-10s | %-20s | %-20s | %-14s | %-12s | %-12s | %-10s | %13s |\n", "Train ID", "Departure Station", "Arrival Station", "Departure Time", "Arrival Time", "Date", "Quantity", "Ticket Status");
        printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("| %-10s | %-20s | %-20s | %-14s | %-12s | %-4d/%-2d/%-4d | %-10d | %-13s |\n", display.t_detail[arr].train_id, display.t_detail[arr].depstation,
            display.t_detail[arr].arrstation, display.t_detail[arr].deptime, display.t_detail[arr].arrtime, display.t_detail[arr].departdate.day, display.t_detail[arr].departdate.month, display.t_detail[arr].departdate.year, display.t_detail[arr].quantity, display.t_detail[arr].tic_status);
        printf("----------------------------------------------------------------------------------------------------------------------------------------\n\n");
        printf("Booking ID : %d\n", display.t_detail[arr].booking_id);
        printf("Seat:");
        for (int coach = 0; coach < 4; coach++) {
            for (int y = 0; y < 40; y++) {
                if (display.t_detail[arr].seat[coach][y] == 1) {
                    printf("(Coach %d ,Seat %d)", coach + 1, y + 1);
                }
            }
        }
        printf("\nCustomer's Name       :");
        for (int count = 0; count < display.t_detail[arr].quantity; count++) {
            printf("[%s]", display.t_detail[arr].cus_name[count]);
        }
        printf("\nCustomer's IC/PASSPORT:");
        for (int count = 0; count < display.t_detail[arr].quantity; count++) {
            printf("[%s]", display.t_detail[arr].cus_ic[count]);
        }
        printf("\n\n\n");
        arr++;
    }
    fclose(fp);
    memset(&display, 0, sizeof(display));
}

void cancel_ticket_booking(int mem_id) {
    int  arr, count = 0, b_id, index = 0, m_index = 0, t_index = 0;


    FILE* fp;
    fp = fopen("booking.bin", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    while (fread(&cancel[index], sizeof(booking), 1, fp)) {
        if (mem_id == cancel[index].mem_id) {
            for (arr = 0; arr < MAX_BOOKING; arr++) {
                if (cancel[index].t_detail[arr].booking_id != 0) {
                    printf("----------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("| %-12s | %-10s | %-20s | %-20s | %-15s | %-15s | %-12s | %-13s |\n", "Booking ID", "Quantity", "Departure Station", "Arrival Station", "Departure Time", "Arrival Time", "Date", "Ticket Status");
                    printf("----------------------------------------------------------------------------------------------------------------------------------------------\n");
                    printf("| %-12d | %-10d | %-20s | %-20s | %-15s | %-15s | %-4d/%-2d/%-4d | %-13s |\n", cancel[index].t_detail[arr].booking_id, cancel[index].t_detail[arr].quantity, cancel[index].t_detail[arr].depstation, cancel[index].t_detail[arr].arrstation,
                        cancel[index].t_detail[arr].deptime, cancel[index].t_detail[arr].arrtime, cancel[index].t_detail[arr].departdate.day, cancel[index].t_detail[arr].departdate.month, cancel[index].t_detail[arr].departdate.year, cancel[index].t_detail[arr].tic_status);
                    printf("----------------------------------------------------------------------------------------------------------------------------------------------\n\n\n");
                    count++;
                }
            }
            if (count == 0) {
                printf("No booking record");
                fclose(fp);
                system("pause");
                return;
            }
            else {
                printf("Please enter the booking ID that needs to be cancelled:");
                scanf("%d", &b_id);
                for (arr = 0; arr < MAX_BOOKING; arr++) {
                    if (cancel[index].t_detail[arr].booking_id == b_id) {
                        if (strcmp(cancel[index].t_detail[arr].tic_status, "Booked") == 0) {
                            strcpy(cancel[index].t_detail[arr].tic_status, "Cancelled");

                            member detail[MAX_ACCOUNT];
                            FILE* mem;
                            mem = fopen("memberinfo.txt", "r");
                            if (mem == NULL) {
                                printf("Error opening file!\n");
                                exit(-1);
                            }
                            while (fscanf(mem, "%d\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%c\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%[^\n]\n%f\n%[^\n]\n%d\n\n",
                                &detail[m_index].member_ID, &detail[m_index].name, &detail[m_index].user_name, &detail[m_index].mycard, &detail[m_index].phone, &detail[m_index].gender, &detail[m_index].email, &detail[m_index].add.address, &detail[m_index].add.postcode, &detail[m_index].add.country, &detail[m_index].password, &detail[m_index].credit_balance, &detail[m_index].member_category, &detail[m_index].Membership_points) != EOF) {
                                if (cancel[index].mem_id == detail[m_index].member_ID) {
                                    detail[m_index].credit_balance = detail[m_index].credit_balance + cancel[index].t_detail[arr].amount;
                                }
                                m_index++;
                            }
                            fclose(mem);
                            FILE* file_input;
                            file_input = fopen("memberinfo.txt", "w");
                            for (int y = 0; y < m_index; y++) {
                                fprintf(file_input, "%d\n%s\n%s\n%s\n%s\n%c\n%s\n%s\n%d\n%s\n%s\n%.2f\n%s\n%d\n\n",
                                    detail[y].member_ID, detail[y].name, detail[y].user_name, detail[y].mycard, detail[y].phone, detail[y].gender, detail[y].email, detail[y].add.address, detail[y].add.postcode, detail[y].add.country, detail[y].password, detail[y].credit_balance, detail[y].member_category, detail[y].Membership_points);
                            }
                            fclose(file_input);
                            FILE* fp;
                            struct TrainSchedule train[MAX_TRAIN];
                            fp = fopen("train_schedule.bin", "rb");
                            if (fp == NULL) {
                                printf("Error opening file!\n");
                                exit(-1);
                            }
                            while (fread(&train[t_index], sizeof(struct TrainSchedule), 1, fp)) {
                                if (strcmp(train[t_index].trainID, cancel[index].t_detail[arr].train_id) == 0) {
                                    for (int coach = 0; coach < 4; coach++) {
                                        for (int seat_num = 0; seat_num < 40; seat_num++) {
                                            if (cancel[index].t_detail[arr].seat[coach][seat_num] == 1) {
                                                train[t_index].seat[coach][seat_num] = 0;
                                            }
                                        }
                                    }
                                    train[t_index].availableSeats = train[t_index].availableSeats + cancel[index].t_detail[arr].quantity;
                                }
                                t_index++;
                            }
                            fclose(fp);

                            FILE* t_input;
                            t_input = fopen("train_schedule.bin", "wb");
                            if (t_input == NULL) {
                                printf("Error opening file!\n");
                                exit(-1);
                            }
                            for (int t = 0; t < t_index; t++) {
                                fwrite(&train[t], sizeof(struct TrainSchedule), 1, fp);
                            }
                            fclose(t_input);
                            printf("\nSuccessfully cancelled\n");
                            break;
                        }
                    }
                }

                if (arr == MAX_BOOKING) {
                    printf("\nCan't find this id\n");
                    fclose(fp);
                    system("pause");
                    memset(&cancel, 0, sizeof(cancel));
                    return;
                }
            }
        }
        index++;
    }
    fclose(fp);

    FILE* input;
    input = fopen("booking.bin", "wb");
    if (input == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    for (int i = 0; i < index; i++) {
        fwrite(&cancel[i], sizeof(booking), 1, input);
    }
    fclose(fp);
    memset(&cancel, 0, sizeof(cancel));
    return;
}


float cal_payment(char mem_category[10], float price, int quantity) {
    float discount, amount;
    if (strcmp(mem_category, "Silver") == 0) {
        discount = 0.0;
    }
    else if (strcmp(mem_category, "Gold") == 0) {
        discount = 10.0;
    }
    else {
        discount = 20.0;
    }

    amount = +(price * quantity) - (price * quantity * discount / 100);

    printf("Discount based on your membership level\n");
    printf("==================================================================\n");
    printf("%-10s %-10s %-10s %-15s\n", "PRICE", "QUANTITY", "DISCOUNT", "TOTAL AMOUNT");
    printf("==================================================================\n");
    printf("%-10.2f %-10d %-10.2f %.2f\n\n", price, quantity, discount, amount);

    return amount;
}

int general_id() {
    int id, arr, repeat;
    booking bookings;

    do {
        repeat = 0;
        srand(time(NULL));
        id = rand() % 100000;

        FILE* fp;
        fp = fopen("booking.bin", "rb");
        if (fp == NULL) {
            printf("Error opening file!\n");
            exit(-1);
        }

        while (fread(&bookings, sizeof(booking), 1, fp)) {
            for (arr = 0; arr < MAX_BOOKING; arr++) {
                if (bookings.t_detail[arr].booking_id == id) {
                    repeat = 1;
                }
            }
        }

        fclose(fp);
    } while (repeat == 1);


    return id;
}

void logo() {
    printf("          SSS               AAAAA            EEEEEEEEE  \n");
    printf("        SSS  SSS          AAA   AAA          EEE         \n");
    printf("       SSS     SS         AAA   AAA          EEE        \n");
    printf("         SSS              AAA   AAA          EEE        \n");
    printf("          SSS             AAA   AAA          EEE        \n");
    printf("            SSS           AAAAAAAAA          EEEEEEE    XX    XX  PPPPPP     RRRRRR    EEEE     SSSSS    SSSSS    \n");
    printf("             SSSS         AAA   AAA          EEE         XX  XX   PP   PP   RR       EE    EE  SSS   S  SSS   S   \n");
    printf("              SSS         AAA   AAA          EEE           XX     PP    PP  RR       EEEEEEEE    SSSS     SSSS    \n");
    printf("       SSS   SSS          AAA   AAA          EEE         XX  XX   PP   PP   RR       EE        S   SSS  S   SSS   \n");
    printf("          SSSS   ILVER    AAA   AAA RROW     EEEEEEEEE  XX    XX  PPPPPP    RR        EEEEEE    SSSS     SSSS     \n");
    printf("                                                                  PP             \n");
    printf("                                                                  PP            \n");
    printf("                                                                  PP            \n");
    printf("                                                                  PP             \n");
}