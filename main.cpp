#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int MAX_BUCKETS = 30;
const int MAX_CHARACTER = 1000;
const int MAX_MENU = 1000;
char hashtable[MAX_BUCKETS][MAX_CHARACTER];
int hashPrice[MAX_BUCKETS];
int hashQuan[MAX_BUCKETS];
int hashQuanOrang[MAX_BUCKETS];
char hashname[MAX_BUCKETS][MAX_CHARACTER];
char hashMAKANAN[MAX_BUCKETS][MAX_MENU][MAX_CHARACTER];
int hashJUMLAHMAKANAN[MAX_BUCKETS][MAX_MENU];

struct Node {
  char foodName[255];
  int foodPrice;
  int foodQuantity;
  Node *next;
};

struct NodeName {
  char name[1000];
  Node *next;
};

struct pesenanOrang{
    char name[1000];
    char foodName[1000];
    int foodQuantity;
};

unsigned long djb2(char str[]) {
  unsigned long key = 5381;

  for(int i = 0; str[i] != '\0'; i++) {
    int ascii = int(str[i]);
    key = (key << 5) + key + ascii;
}

  return key % MAX_BUCKETS;
};

Node *createNode(char name[], int price, int quan){
  Node *newNode = (Node*)malloc(sizeof(Node));
  strcpy(newNode->foodName, name);
  newNode->foodPrice = price;
  newNode->foodQuantity = quan;
  newNode->next = NULL;
  return newNode;
}

NodeName *createNodeName(char name[]){
  NodeName *newNode = (NodeName*)malloc(sizeof(Node));
  strcpy(newNode->name, name);
  return newNode;
}

pesenanOrang *createNodePesan(char name[], char food[], int quan){
    pesenanOrang *newNode = (pesenanOrang*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->foodName, food);
    newNode->foodQuantity = quan;
  return newNode;
}

void read(){
    int index = 1;
    printf("              Menu\n");
    printf("==============================\n");
    printf("No.      Name         Quantity     Price\n");
    for (int i = 0; i < MAX_BUCKETS; i++){
        if(hashtable[i][0] != '\0'){
            printf("%d.     %s         %03d        Rp.%d\n", index, hashtable[i], hashQuan[i], hashPrice[i]);
            index++;
        }
    }
    printf("==============================\n");
}

void checkName(char name[]){
    int idx = djb2(name);
    
    if(hashname[idx][0] != '\0'){
        printf("%s is present.\n", name);
        // printf("%d", idx);
    }
    else{
        printf("%s is not present.\n", name);
        // printf("%d", idx);
    }

    printf("Press Any Key to Continue\n");  
    getchar(); 

}

void printName(){
    for (int i = 0; i < MAX_BUCKETS; i++){
        if(hashname[i][0] != '\0'){
            printf("%d. %s\n", i, hashname[i]);
        }
    }

    printf("Press Any Key to Continue\n");  
    getchar(); 
}

void order(){
    char name[1000];
    int quan;
    int idx;
    // printf("Domo ada di index: %d\n", idx);
    printf("Insert the customer name: ");
    scanf("%s", name);
    getchar();
    printf("Insert the amount of dish: ");
    scanf("%d", &quan);
    getchar();
    idx = djb2(name); 
    hashQuanOrang[idx] = quan;
    printf("hashQuanOrang[%d] = %d\n",idx, quan );
    printf("%d\n", hashQuanOrang[25]);

    int quanbeli;
    char food[1000];

    for(int i = 1;i<=quan;i++){
        printf("[%d] Insert the dish name and quantity: ", i);
        scanf("%[^x]x%d", food, &quanbeli);
        getchar();
        hashJUMLAHMAKANAN[idx][i] = quanbeli;
        strcpy(hashMAKANAN[idx][i], food);
    }
    printf("Order success!\n");
    printf("Press Any Key to Continue\n");  
    getchar(); 
}

void payment(){
    int idx;
    int index = 0;
    long long int sum = 0;
    int indexfood;

    printf("Insert the customer index: ");
    scanf("%d", &idx);
    getchar();

        printf("%s\n", hashname[idx]);

        for(int i=1;i<=hashQuanOrang[idx];i++){
            printf("[%d] %s x%d\n",i, hashMAKANAN[idx][i],hashJUMLAHMAKANAN[idx][i]);
            indexfood = djb2(hashMAKANAN[idx][i]);
            sum = sum + hashPrice[indexfood] * hashJUMLAHMAKANAN[idx][i];
        }
        printf("Total = Rp.%lld\n", sum);
    

    printf("Press Any Key to Continue\n");  
    getchar(); 
}

void removeDish(char name[]){
    int idx = djb2(name);

    hashPrice[idx] = NULL;
    hashQuan[idx] = NULL;
    hashtable[idx][0] = NULL;

}


void linearProbing(int idx, const char *str)
{
  // loop dari idx sampai N, kemudian dari 0 sampai idx-1 (basically loop biasa, tapi startnya bukan 0)
  for (int i = (idx + 1) % MAX_BUCKETS; i != idx; i = (i + 1) % MAX_BUCKETS)
  {
    if (!hashtable[i][0])
    { // if specified index is empty
      strcpy(hashtable[i], str);
      return;
    }
  }
}

void linearProbingName(int idx, const char *str)
{
  // loop dari idx sampai N, kemudian dari 0 sampai idx-1 (basically loop biasa, tapi startnya bukan 0)
  for (int i = (idx + 1) % MAX_BUCKETS; i != idx; i = (i + 1) % MAX_BUCKETS)
  {
    if (!hashname[i][0])
    { // if specified index is empty
      strcpy(hashname[i], str);
      return;
    }
  }
}

void insert(char name[], int price, int quan){
    Node *newNode = createNode(name, price, quan);
    int idx = djb2(name);
        if (!hashtable[idx][0]){
        strcpy(hashtable[idx], name);
        hashPrice[idx] = price;
        hashQuan[idx] = quan;
        }
        else{
        linearProbing(idx, name);
        }
    }

void insertName(){
    char name[1000];
    printf("Insert the customer's name [Without space]: ");
    scanf("%s", name);
    getchar();
    NodeName *newNode = createNodeName(name);
    int idx = djb2(name);
        if (!hashtable[idx][0]){
        strcpy(hashname[idx], name);
        }
        else{
        linearProbingName(idx, name);
        }
        printf("Customer has been added!\n");
        printf("Press any key to continue:");
        getchar();
    }

void printOS(){
    #ifdef _WIN32
        printf("System: Windows OS\n");

    #elif _WIN64
        printf("Syetem: Windows OS\n");

    #elif __APPLE__
        printf("System: Mac OS\n");

    #elif __linux__
        printf("System: Linux OS\n");

    #endif
    return;
}

void printTime(){
    time_t t = time(NULL);
    printf("%s", ctime(&t));
    return;
}

void printMenu(){
    printf("1. Add Dish\n");
    printf("2. Remove Dish\n");
    printf("3. Add Customer\n");
    printf("4. Seach Customer\n");
    printf("5. View Warteg\n");
    printf("6. Order\n");
    printf("7. Payment\n");
    printf("8. Exit Warteg\n");
}

int input(){

    int value;

    printf(">> ");
    scanf("%d", &value);
    getchar();

    while(value < 1 || value > 8){
        printf("Please input a valid number: ");
        scanf("%d", &value);
        getchar();
    }
    return value;
}

int check(char str[], int len){
    int mark = 0;
    for(int i=0;i<len;i++){
        if((str[i] >= 'a' && str[i] <= 'z') || str[i] == ' '){
            mark++;
        }
    }
    if (mark == len){
        return 1;
    }
    else{
        return 0;
    }
}


void addDish (){
    char name[1000];
    printf("Insert the name of the dish [Lowercase letters]: ");
    scanf("%[^\n]", name);
    getchar();
    int len = strlen(name);
    while(check(name,len) == 0){
        printf("Insert the name of the dish [Lowercase letters]: ");
        scanf("%[^\n]", name);
        getchar();
    }
    
    int price;
    printf("Insert the price of the dish [1000..50000]: ");
    scanf("%d", &price);
    getchar();

    while(price < 1000 || price > 50000){
        printf("Insert the price of the dish [1000..50000]: ");
        scanf("%d", &price);
        getchar();
    }

    int quan;
    printf("Insert the quantity of the dish [1..999]: ");
    scanf("%d", &quan);
    getchar();

    while(quan < 1 || quan > 999){
        printf("Insert the quantity of the dish [1..999]: ");
        scanf("%d", &quan);
        getchar();
    }

    insert(name,price,quan);
    printf("The dish has been added!\n");

    printf("Press Any Key to Continue\n");  
    getchar();  

}

int main(){
    int inputs;

    do{
        system("clear");
        printOS();
        printTime();
        printMenu();
        printf("%s\n", hashname[25]);
        inputs = input();

        if(inputs == 1){
            addDish();
        }
        else if(inputs == 2){\
            char name[1000];
            read();
            printf("Insert dish's name to be deleted:");
            scanf("%[^\n]", name);
            getchar();
            removeDish(name);
        }
        else if(inputs == 3){
            insertName();
        }
        else if(inputs == 4){
            char name[1000];
            printf("Insert the customer name: ");
            scanf("%s", name);
            getchar();
            checkName(name);           
        }
        else if(inputs == 5){
            printName();
        }
        else if(inputs == 6){
            order();
        }
        else if(inputs == 7){
            payment();
        }
        else if(inputs == 8){
            return 0;
        }
        system("clear");
    }while(inputs != 8);

    return 0;
}