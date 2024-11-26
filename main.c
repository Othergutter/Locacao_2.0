#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//estrutura de dados dos clientes
struct customerData {
       char name[150];
       char cpf [15];
       char cep[10];
       char addressStreet[50];
       char addressCity[25];
       char state[5];
       char car[32];
       bool status;
       struct customerData *next;
       struct customerData *prior;
}list_length;

struct userData {
       char nameUser[50];
       char passUser[50];
       char userMat[30];
       int acessLevel; // n�vel de acessso no aplicativo
       struct userData *next;
       struct userData *prior;
}user_length;

struct customerData *start; //ponteiro para a primeira entrada da lista
struct customerData *last; //ponteiro para o registro anteriror

struct userData *userStart;
struct userData *userLast;

//Cria uma lista duplamente encadeada para guardar os dados
void initializeListCustomer (struct customerData *i, /*novo elemento*/ 
                     struct customerData **start, /*primeiro elemento da lista*/
                     struct customerData **last /*�ltimo elemento da lista*/);

void initializeListUser (struct userData *i,
                     struct userData **userStart, 
                     struct userData **userLast);

void clearBuffer(); //limpa o buffer de scanf at� encontrar um \n, evita repeti��o desnecess�ria

void startMenu(char * userName, char *userPass); // Menu de do Login do usuario

void menuCustomer(char * userName); // Menu para ferramentas voltadas ao cliente

void menuUser(char * useName); // Menu para ferramentas voltadas � gest�o de funcion�rios

struct customerData *find(char *name); // usada para comparar e achar nomes em algumas estruturas

void display(struct customerData*customerInfo); // Imprime os campos dos clientes

//void listCustomers(); //lista todos os clientes

void changeData (struct customerData *customerInfo); // Respons�vel por acessar o estrutura que ter� os dados modificados

void editCustomer (); // editar� os dados de um cliente

void changeStatus(struct customerData *customerInfo); // Respons�vel por acessar o estrutura que ter� o status modificado

void disableEnableCustomer(); // fun��o respons�vel por habilitar e desabilitar uma conta do cliente

void searchCustomer (); // fun��o que procurar� um cliente j� cadastrado

bool searchUser (char * userName, char *userPass); // fun��o que procurar� se o usu�rio est� cadastrado

struct userData * findUser (char * userName); // Procura os dados do usuario na lista pelo nome do usu�rio

void userInputs (char *prompt, char *s, int count); // Pega as entradas do usu�rio

void accurateInput (char *prompt, char *s, int count); //Pega precisamente as entrada do usu�rio

void stateInput (char *prompt, char *s, int count); // fun��o de entrada para a silga do estado

void registerUser (); //fun��o que cadastrar� os usu�rios com menor n�vel de acesso

void registerCustomer (); // fun��o que cadastrar� o cliente

int main(int argc, char *argv[])
{
  
  char * userName, * userPass;
  userName = (char *)  malloc(50 * sizeof(char));
  userPass = (char *)  malloc(50 * sizeof(char));
  char userIn = ' '; // escolha do usu�rio
  bool loopState = true; // vari�vel bool para controlar o do while
  
  struct userData *userInfoA = NULL;
  
  //Inicizliza��o dos funcion�rios com n�vel total de acesso � �rea de gest�o do aplicativo
  
  userInfoA = (struct userData *)malloc(sizeof(struct userData));
  if (!userInfoA) {
     printf("\nSem memoria");
     free(userName);
     free(userPass);
     return 1;
  }
  
  strcpy(userInfoA->nameUser, "FLAVIEIRA");
  strcpy(userInfoA->passUser, "123321");
  strcpy(userInfoA->userMat, "001");
  userInfoA->acessLevel = 2;
  
  initializeListUser(userInfoA, &userStart, &userLast);
  
  struct userData *userInfoB = NULL;
  
  userInfoB = (struct userData *)malloc(sizeof(struct userData));
  if (!userInfoB) {
     printf("\nSem memoria");
     free(userName);
     free(userPass);
     return 1;
  }
  
  strcpy(userInfoB->nameUser, "MAURIOSO");
  strcpy(userInfoB->passUser, "pimba123");
  strcpy(userInfoB->userMat, "002");
  userInfoB->acessLevel = 2;
  
  initializeListUser(userInfoB, &userStart, &userLast);
   
  startMenu(userName, userPass);
  
  do{ // loop do sistema, rodar� no m�nimo uma vez
     printf("\nSistema locacao 2.0, bem-vindo %s\n", userName); // apresenta��o, ao usu�rio
     printf("-Aperte 1 para acessar a aba dos clientes\n");
     printf("-Aperte 2 para acessar a aba de gestao\n");
     printf("-Aperte 3 para sair do aplicativo\n");
     printf("-Aperte 4 para alterar conta de usuario\n");
     //printf("-Aperte 3 para listar todos os clientes\n");     
     scanf(" %c", &userIn); // coleta a escolha e a armaezena
     clearBuffer();
  
     switch (userIn) {
         case '1':
            menuCustomer(userName); // se for 1, vai para a aba de clientes
            loopState = true;       
            break;
         case '2':
            if(findUser(userName)->acessLevel == 2) {
               menuUser(userName);
               loopState = true;
            } else {
               printf("\nVoce nao possui acesso a area de gestao\n");
            }    
            break;
         case '3':
            loopState = false;  
            break;
         case '4':
            startMenu(userName, userPass);
            loopState = true;
            break;
         default:
            printf("\nPor favor, insira um valor valido.\n");
            break;
      } 
     
  }while(loopState); // final do loop 

  free(userInfoA);
  free(userInfoB);
  free(userName);
  free(userPass);
  
  
  return 0;
}

void initializeListUser (struct userData *i, struct userData **userStart, struct userData **userLast) {
     struct userData *old, *p;
     
     if(*userLast==NULL) { //primeiro elemento da lista
         i->next = NULL;
         i->prior = NULL;
         *userLast = i;
         *userStart = i;
         return;
     }
     
     p = *userStart; //come�a no topo da lista
     
     old = NULL;
     while(p) {
         if(strcmp(p->nameUser, i->nameUser)<0) {
             old = p;
             p = p->next;                   
         } else {
             if(p->prior) {
                p->prior->next = i;
                i->next = p;
                i->prior = p->prior;
                p->prior = i;
                return;
             }
             i->next = p; // novo primeiro elemento
             i->prior = NULL;
             p->prior = i;
             *userStart = i;
             return;         
         }              
     }
     old->next = i; //coloca no final
     i->next = NULL;
     i->prior = old;
     *userLast - i;
}


void initializeListCustomer (struct customerData *i, struct customerData **start, struct customerData **last) {
     struct customerData *old, *p;
     
     if(*last==NULL) { //primeiro elemento da lista
         i->next = NULL;
         i->prior = NULL;
         *last = i;
         *start = i;
         return;
     }
     
     p = *start; //come�a no topo da lista
     
     old = NULL;
     while(p) {
         if(strcmp(p->name, i->name)<0) {
             old = p;
             p = p->next;                   
         } else {
             if(p->prior) {
                p->prior->next = i;
                i->next = p;
                i->prior = p->prior;
                p->prior = i;
                return;
             }
             i->next = p; // novo primeiro elemento
             i->prior = NULL;
             p->prior = i;
             *start = i;
             return;         
         }              
     }
     old->next = i; //coloca no final
     i->next = NULL;
     i->prior = old;
     *last - i;
}

void clearBuffer() {
     int c = 0;
     
     while ((c = getchar()) != '\n' && c != EOF) {} // para ao achar uma quebra de linha ou EOF (final do aqruivo)
}

void startMenu(char * userName, char *userPass) {
     bool loopState = true;
     do{ // loop login
        printf("\nSistema locacao 2.0\n"); // apresenta��o, ao usu�rio
        printf("\nFaca o seu Login:\n");
        userInputs("-Nome do usuario: ", userName, 50);
        userInputs("-Senha do usuario: ", userPass, 50);
        if(!searchUser (userName, userPass)){
             printf("\nSenha ou usuario incorretos!\n");
        } else {
             loopState = false;    
     }
  }while(loopState);
}

void menuCustomer(char * userName){
     bool loopState = true;
     char userIn;
     
     do{ // loop da aba cliente, rodar� no m�nimo uma vez
         printf("\nSistema locacao 2.0, usuario: %s\n", userName); // apresenta��o, ao usu�rio
         printf("-Aperte 1 para cadastrar cliente\n");
         printf("-Aperte 2 para consultar cliente\n");
         printf("-Aperte 3 para editar cliente\n");
         printf("-Aperte 4 para habilitar ou desabilitar a conta do cliente\n");
         printf("-Aperte 5 para sair do menu\n");   
         scanf(" %c", &userIn); // coleta a escolha e a armaezena
         clearBuffer();
  
         switch (userIn) {
                case '1':
                    registerCustomer(); // se for 1, o cliente ser� registrado        
                    break;
                 case '2':
                    searchCustomer(); // se for 2, procurar� o cliente
                    break;
                 case '3':
                    editCustomer(); // editar um cliente
                    break;
                 case '4':
                    disableEnableCustomer(); // Apaga um cliente
                    break;
                 case '5':
                    loopState = false; // Sai da aba de cliente
                    break; 
                 default:
                    printf("\nPor favor, insira um valor valido.\n");
                    break;
     }
   }while(loopState); 
}

void menuUser(char * userName){
     bool loopState = true;
     char userIn;
     
     do{ // loop da aba cliente, rodar� no m�nimo uma vez
         printf("\nSistema locacao 2.0, usuario: %s\n", userName); // apresenta��o, ao usu�rio
         printf("-Aperte 1 para cadastrar usuario\n");
         printf("-Aperte 2 para sair do menu\n");   
         scanf(" %c", &userIn); // coleta a escolha e a armaezena
         clearBuffer();
  
         switch (userIn) {
                case '1':
                     registerUser(); // se for 1, o usu�rio ser� registrado        
                     break;
                case '2':
                     loopState = false; // Sai da aba de cliente
                     break; 
                default:
                     printf("\nPor favor, insira um valor valido.\n");
                     break;
     }
   }while(loopState); 

}
struct customerData *find(char *cpf){
     struct customerData *customerInfo;
     customerInfo = start;
     while(customerInfo) {
        if (!strcmp(cpf, customerInfo->cpf)) return customerInfo;
        customerInfo = customerInfo->next; // novo endere�o
     }
     printf("\nCPF nao encontrado.\n");
     return NULL;   
}

void display(struct customerData*customerInfo){
     if (customerInfo->status) {
        printf("\nConta habilitada");
        printf("\nNome: %s\n", customerInfo->name);
        printf("CPF: %s\n", customerInfo->cpf);
        printf("CEP: %s\n", customerInfo->cep);
        printf("Logradouro: %s\n", customerInfo->addressStreet);
        printf("Cidade: %s\n", customerInfo->addressCity);
        printf("Estado: %s\n", customerInfo->state);
        printf("Carro alugado: %s\n", customerInfo->car);
     } else {
        printf("\nConta desabilitada, sem acesso as informacoes\n");
     }
}

/*
void listCustomers(){
     struct customerData *customerInfo;
     
     customerInfo = start;
     while(customerInfo){
         display(customerInfo);
         customerInfo = customerInfo->next; 
     }
     printf("\n\n");
}
*/

bool searchUser (char * userName, char *userPass) {
     struct userData * userInfo;
     userInfo = userStart;
     while(userInfo) {
        if (!strcmp(userName, userInfo->nameUser) && !strcmp(userPass, userInfo->passUser)) {
        
           return true;
        
        }
        userInfo = userInfo->next; // novo endere�o
     }
     
     return false;
}

void changeData (struct customerData *customerInfo) {
     bool loopState = true;
     char userIn;
     do{
        printf("\nSistema locacao 2.0\n"); // apresenta��o, ao usu�rio
        printf("-Aperte 1 para alterar nome\n");
        printf("-Aperte 2 para alterar CPF\n");
        printf("-Aperte 3 para alterar CEP\n");
        printf("-Aperte 4 para alterar logradouro\n");
        printf("-Aperte 5 para alterar cidade\n");
        printf("-Aperte 6 para alterar sigla do Estado\n");
        printf("-Aperte 7 para sair do menu\n");
        scanf(" %c", &userIn); // coleta a escolha e a armaezena
        clearBuffer();
        
        
        switch (userIn) {
           case '1':
              userInputs("\nInsira o nome: ", customerInfo->name, 150);
              break;
           case '2':   
              accurateInput("Insira o CPF: ", customerInfo->cpf, 15);
              break;
           case '3':
              accurateInput("Insira o CEP: ", customerInfo->cep, 10);
              break;
           case '4':
              userInputs("Insira o logradouro do cliente: ", customerInfo->addressStreet, 50);
              break;
           case '5':
              userInputs("Insira a cidade do cliente: ", customerInfo->addressCity, 25);
              break;
           case '6':
              stateInput("Insira a sigla estado: ", customerInfo->state, 5);
              break;
           case '7':
              loopState = false;
              break;
           default:
              printf("\nPor favor, insira um valor valido.\n");
              break;
        }
     }while(loopState);
}

void editCustomer () {
     char cpf[50];
     char userIn = ' ';
     struct customerData *customerInfo;
     
     printf("\nInsira o CPF (nesse padrao 123.234.234-78) que deseja procurar: ");
     fgets(cpf, sizeof(cpf), stdin);
     cpf[strcspn(cpf,"\n")] = '\0';
     customerInfo = find(cpf);
     
     if(!customerInfo){ 
        printf("\nNao encontrado\n");
     } else {
        display (customerInfo);
        
        printf("\nTem certeza que deseja editar esse cliente(s/n)\n");
        scanf(" %c", &userIn);
        if (userIn == 'S' || userIn == 's') {
           changeData (customerInfo);
        }        

     }
} 

void changeStatus(struct customerData *customerInfo) {
     char userIn = ' ';
     if(customerInfo->status) {
        printf("\nA conta esta habilitada, deseja desabilita-la?\n");
     } else {
        printf("\nA conta esta desabilitada, deseja habilita-la?\n");       
     }
     
     clearBuffer();
     scanf("%c", &userIn);
     clearBuffer();
     
     if (userIn == 's' || userIn == 'S') {
     
        customerInfo->status = !customerInfo->status;
        printf("\nStatus da conta alterado\n");
     
     }  else {
        printf("\nNenhuma alteracao foi feita\n");
     }
}

void disableEnableCustomer() {
     char cpf[50];
     char userIn = ' ';
     struct customerData *customerInfo;
     
     printf("\nInsira o CPF (nesse padrao 123.234.234-78) que deseja procurar: ");
     fgets(cpf, sizeof(cpf), stdin);
     cpf[strcspn(cpf,"\n")] = '\0';
     customerInfo = find(cpf);
     
     if(!customerInfo){ 
        printf("\nNao encontrado\n");
     } else {
        display (customerInfo);
        
        printf("\nDeseja habilitar ou desabilitar a contar do cliente?(s/n)\n");
        scanf(" %c", &userIn);
        
        if(userIn == 'S' || userIn == 's') {
           changeStatus(customerInfo);        
        }
     }
}


void searchCustomer () {
     char cpf[50];
     char userIn = ' ';
     struct customerData *customerInfo;
     
     printf("\nInsira o CPF (nesse padrao 123.234.234-78) que deseja procurar:");
     fgets(cpf, sizeof(cpf), stdin);
     cpf[strcspn(cpf,"\n")] = '\0';
     customerInfo = find(cpf);
     
     if(!customerInfo){ 
        printf("\nNao encontrado\n");
     } else {
        display (customerInfo);
        
        //printf("\nDeseja selecionar um veiculo para esse cliente?(s/n)\n");
        //scanf(" %c", &userIn);
        
        //if(userIn == 'S' || userIn == 's') {
             //rentCar(); // Ir� alugar um carro espec�fico para o cliente;
        //}
     }
     //atribuir sistema de loca��o a partir daqui
} 

struct userData * findUser (char * userName) {
     struct userData *userInfo;
     userInfo = userStart;
     while(userInfo) {
        if (!strcmp(userName, userInfo->nameUser)) return userInfo;
        userInfo = userInfo->next; // novo endere�o
     }
     return NULL;
} 

void userInputs (char *prompt, char *s, int count) {
     char p[255];
     
     do {
        printf("%s",prompt);
        fgets(p, sizeof(p), stdin);
        p[strcspn(p,"\n")] = '\0';
        if(strlen(p)>count) printf("\nmuito longo\n");
     }  while(strlen(p)>count);
     strcpy(s,p);
}

void accurateInput (char *prompt, char *s, int count) {
     char p[255];
     
     do {
        printf("%s",prompt);
        fgets(p, sizeof(p), stdin);
        p[strcspn(p,"\n")] = '\0';
        if(strlen(p)>count) printf("\nmuito longo\n");
        if(strlen(p)< (count-1)) printf("\nmuito pequeno\n");
     }  while(strlen(p)>count || strlen(p)< (count-1));
     strcpy(s,p);
}

void stateInput (char *prompt, char *s, int count) {
     char p[255];
     
     do {
        printf("%s",prompt);
        fgets(p, sizeof(p), stdin);
        p[strcspn(p,"\n")] = '\0';
        if(strlen(p)>count) printf("\nmuito longo\n");
        if(strlen(p)< (count-3)) printf("\nmuito pequeno\n");
     }  while(strlen(p)>count || strlen(p)< (count-3));
     strcpy(s,p);
}

void registerUser () {
     char userIn = ' ';
     struct userData *userInfo;
     
     for(;;){
        userInfo = (struct userData*)malloc(sizeof(struct userData));
        if(!userInfo) {
           printf("\nsem mem�ria");
           return;                
        }
     
        userInputs("\nInsira o nome (aperte apenas enter para cancelar): ", userInfo->nameUser, 150);
        if(!userInfo->nameUser[0]){
           free(userInfo);
           break;
        } //verifica se houve inser��o, caso n�o, para o loop e libera a memoria
        accurateInput("Insira a matr�cula: ", userInfo->userMat, 4);
        userInputs("Insira a senha: ", userInfo->passUser, 10);
        
        userInfo->acessLevel = 1;
        
        initializeListUser(userInfo, &userStart, &userLast);
        
     }
} // entrada de dados

void registerCustomer () {
     char userIn = ' ';
     struct customerData *customerInfo;
     
     for(;;){
        customerInfo = (struct customerData*)malloc(sizeof(struct customerData));
        if(!customerInfo) {
           printf("\nsem mem�ria");
           return;                
        }
     
        userInputs("\nInsira o nome (aperte apenas enter para cancelar): ", customerInfo->name, 150);
        if(!customerInfo->name[0]){
           free(customerInfo);
           break;
        } //verifica se houve inser��o, caso n�o, para o loop e libera a memoria
        accurateInput("Insira o CPF (neste padrao: 123.232.345-80): ", customerInfo->cpf, 15);
        accurateInput("Insira o CEP: ", customerInfo->cep, 10);
        userInputs("Insira o logradouro do cliente: ", customerInfo->addressStreet, 50);
        userInputs("Insira a cidade do cliente: ", customerInfo->addressCity, 25);
        stateInput("Insira a sigla estado: ", customerInfo->state, 5);
        strcpy(customerInfo->car, "Nenhum carro alugado no momento");
        customerInfo->status = true;
        
        initializeListCustomer(customerInfo, &start, &last);
        
        printf("\nDeseja cadastrar mais algum cliente?(s/n)\n");
        scanf(" %c", &userIn);
        clearBuffer();
        
        if (userIn == 's' || userIn =='S') {
           printf("\nInsira os dados do proximo cliente\n"); 
        } else {
           break;
        }  
     }
} // entrada de dados
