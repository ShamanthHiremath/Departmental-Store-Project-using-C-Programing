#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#define n 25

//Creating a structure of bill
typedef struct bill{
    int id[50],quantity[50];
    int total;
} bill; 

bill b[10];
char name[50][50],buf[50];
int price[50];
int id[50];
int Tquantity[50];
//initializing the code by copying textfile into the code
void init(){
    id[0]=0;
    price[0]=0;
    Tquantity[0]=0;
    
    int i=0;
    FILE *fp=fopen("itemlist.txt","r");
    fscanf(fp,"%s",buf);
    fscanf(fp,"%s",buf);
    fscanf(fp,"%s",buf);
    fscanf(fp,"%s",buf);
    for(i=1;i<=n;i++){
        fscanf(fp,"%d",&id[i]);
        fscanf(fp,"%s",name[i]);
        fscanf(fp,"%d",&price[i]);
        fscanf(fp,"%d",&Tquantity[i]);
        id[i+1] =-1;
    }

    fclose(fp);
}
//creating a new bill
void Bill(){
    int num=0;
    printf("Enter bill number");
    scanf("%d",&num);
    id[0]=0;price[0]=0;
    char buff[100];
    printf("----Billing----\n");
    int flag=0;
    int i=0;
    while(flag!=-1){
        printf("\n ID:");
        scanf("%d",&b[num].id[i]);
        printf("Item : %s",name[b[num].id[i]]);
        printf("\nEnter Quantity: ");
        scanf("%d",&b[num].quantity[i]);
        if(Tquantity[b[num].id[i]]<b[num].quantity[i]){
            printf("****OUT OF STOCK***** \n");
            continue;
        }
        Tquantity[b[num].id[i]]-=b[num].quantity[i];
        printf("Price: Rs.%d \n",price[b[num].id[i]]*b[num].quantity[i]);
        printf("continue(1) End(-1)");
        scanf("%d",&flag);
        i++;
    }

    b[num].id[i]=-1;
    for(int j=0;j<=i;j++){
        b[num].total+=price[b[num].id[j]]*b[num].quantity[j];
    }
    //reupdating a file
    FILE *fp;
    fp=fopen("itemlist.txt","w");
    fprintf(fp,"ID ");
    fprintf(fp,"Product ");
    fprintf(fp,"Price ");
    fprintf(fp,"Quantity\n");
    for(i=1;id[i]!=-1;i++){
        fprintf(fp,"%d ",id[i]);
        fprintf(fp,"%s ",name[i]);
        fprintf(fp,"%d ",price[i]);
        fprintf(fp,"%d\n",Tquantity[i]);
    }
    printf("Total Amount to be paid: Rs.%d\n\n",b[num].total);
    fclose(fp);
    getchar();
}
//viewing a bill
void viewbill(){
    int num=1,i=0;
    printf("Enter Bill Number: ");
    scanf("%d",&num);
    printf("RIT DEPARTMENTAL STORE\n");
    printf("ID   |ITEM      |PRICE   |Quantity   |NetPrice\n");
    printf("|--------------------------------------------|\n");
    while(b[num].id[i]!=-1){
    printf("%2d   |%-10s|%-3d     |%-3d         |%-d\n",b[num].id[i],name[b[num].id[i]],price[b[num].id[i]],b[num].quantity[i],price[b[num].id[i]]*b[num].quantity[i]);
    i++;
    }
    printf("\nTotal: %d\n\n",b[num].total);
 
    getchar();
}

//generating total sales bill
void totalsales(){
    int total=0;
    int i=0;
    printf("Total number of bills: ");
    scanf("%d",&i);
    for(int j=1;j<=i;j++){
        total+=b[j].total;
    }

    printf("TOTAL SALES OF THE DAY : %d\n\n",total);
    getchar();
}
//displaying the list items
void ListItems(){
    printf("\n\nRIT DEPARTMENTAL STORE\n");
    int i=1;
    printf("ID PRODUCT\n");
    while(id[i]!=-1){
        printf("%d %s\n",id[i],name[i]);
        i++;
    }
   printf("\n\n");
    getchar();
}

//displaying the stocks available on the store
void StockAvailability(){
    printf("\nID|Product   |Quantity\n");
    for(int i=1;id[i]!=-1;i++){
        printf("%2d|%-10s|%-4d\n",id[i],name[i],Tquantity[i]);
    }
    printf("\n\n");
}

//updating the stock
void stockUpdate(){
    int flag=0;
    int ID,quantity;
    while(flag!=-1){
printf("enter ID : ");
scanf("%d",&ID);
printf("\nenter quantity : ");
scanf("%d",&quantity);
printf("1 to continue\n -1 to exit");
scanf("%d",&flag);
}

Tquantity[ID]+=quantity;
FILE *fp=fopen("itemlist.txt","w");
    fprintf(fp,"ID ");
    fprintf(fp,"Product ");
    fprintf(fp,"Price ");
    fprintf(fp,"Quantity\n");
    int i;
    for(i=1;id[i]!=-1;i++){
        fprintf(fp,"%d ",id[i]);
        fprintf(fp,"%s ",name[i]);
        fprintf(fp,"%d ",price[i]);
        fprintf(fp,"%d\n",Tquantity[i]);
    }

    fclose(fp);
    getchar();
}

//calling main function
int main(){
    int option;

    init();
    do{
    printf("\t\t\t----Home----");
    printf("\n\t\t\t1)Bill Generation");
    printf("\n\t\t\t2)Saved Invoices");
    printf("\n\t\t\t3)List Of Products");
    printf("\n\t\t\t4)Stock Availability");
    printf("\n\t\t\t5)Stock Update");
    printf("\n\t\t\t6)Net Sales\n");
    printf("\t\t\t(-1)To Exit\n");
    printf("\t\t\tEnter an option.");
    scanf("%d",&option);
    switch(option){
        case 1: Bill();
                break;
        case 2: viewbill();
                break;
        case 3: ListItems();
                break;
        case 4: StockAvailability();
                break;
        case 5: stockUpdate();
                break;
        case 6: totalsales();
                break;        
    }
    }while(option!=-1);
    printf("\n**********Thank You**********");
    return 0;
}