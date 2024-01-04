#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <process.h>
#include <stdarg.h>
#include <conio.h>

#define FILE_NAME "phone.buk"

typedef struct tagPhone
{
    char name[20];
    char tel[20];
    struct tagPhone *prev;
    struct tagPhone *next;
} Phone;

void Read(void);
void Write(void);

void Register(void);
void Find(void);
void Modify(void);
void Remove(void);
void RemoveList(Phone* phone);
void List(int forward);
void FreeList(void);

void Message(char *pFormat, ...);

Phone *head, *tail;
char message[256] = "메뉴를 선택하십시오 : ";

int main(void)
{
    char* pmenu[] =
    {
        "1. 읽어오기 (Load)",
        "2. 저장하기 (Save)",
        "3. 등록하기 (Register)",
        "4. 검색하기 (Find)",
        "5. 수정하기 (Modify)",
        "6. 삭제하기 (Remove)",
        "7. 목록보기 (List)",
        "Q. 종료\n"        
    };

    while (1)
    {
        int i;
        int ch;

        system("cls");
        for (i = 0; i<sizeof(pmenu)/sizeof(char*); i++)
        {
            puts(pmenu[i]);
        }

        printf("%s", message);

        ch = getchar();
        getchar();
        
        switch(ch)
        {
        case '1':   // 읽어오기
            Read();
            break;

        case '2':   // 저장하기
            Write();
            break;

        case '3':   // 등록하기
            Register();
            break;

        case '4':   // 검색하기
            Find();
            break;

        case '5':   // 수정하기
            Modify();
            break;

        case '6':   // 삭제하기
            Remove();
            break;

        case '7':   // 목록보기
            List(1);
            break;

        case 'q' :  // 종료
        case 'Q' :
            FreeList();
            exit(0);
        }
    }
}

void Message(char *pFormat, ...)
{
    va_list arglist;

    va_start(arglist, pFormat);
    vsprintf(message, pFormat, arglist);
    va_end(arglist);

    strcat(message, "메뉴를 선택하십시오 : ");
}

void Read(void)
{
    int read_block;
    int count = 0;
    FILE *fp;
    Phone phone;
    
    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        Message("파일을 열 수 없습니다.\n\n");
        return;
    }
    
    while (1) {
        read_block = fread(&phone, sizeof(Phone), 1, fp);
        if (read_block == 1) {
            Phone* tmp = (Phone*)malloc(sizeof(Phone));
            memset(tmp, 0, sizeof(Phone));
            
            strcpy(tmp->name, phone.name);
            strcpy(tmp->tel , phone.tel);

            if (head == NULL)
                head = tail = tmp;    
            else {
                tail->next = tmp;
                tmp->prev = tail;
                tail = tmp;
            }
            count++;
        }
        if (feof(fp))
            break;
    }

    fclose(fp);
    Message("%d의 항목을 읽어 왔습니다.\n\n", count);
}

void Write(void) {
    int count = 0;
    FILE *fp;
    Phone* phone = head;
    
    fp = fopen(FILE_NAME, "w+b");
    if (fp == NULL) {
        Message("파일을 열 수 없습니다. \n\n");
        return;
    }

    while (phone) {
        fwrite(phone, sizeof(Phone), 1, fp);
        phone = phone->next;
        count++;
    }
    
    fclose(fp);
    Message("%d개의 항목을 저장하였습니다. \n\n", count);
}

void Register(void) {
    Phone phone;
    
    memset(&phone, 0, sizeof(Phone));

    printf("\n이름 : ");
    gets(phone.name);

    printf("전화 : ");
    gets(phone.tel);

    if (head == NULL) {
        head = tail = (Phone*)malloc(sizeof(Phone));
        memset(head, 0, sizeof(Phone));
    }
    else {
        Phone *phone = malloc(sizeof(Phone));
        memset(phone, 0, sizeof(Phone));
    
        tail->next = phone;
        phone->prev = tail;
        tail = phone;
    }

    strcpy(tail->name, phone.name);
    strcpy(tail->tel , phone.tel);

    Message("%s이(가) 추가되었습니다.\n\n", phone.name);
}

void Find(void) {
    Phone* phone = head;
    char name[30];

    printf("\n검색할 이름은 : ");
    gets(name);

    while (phone) {
        if (!strcmp(name, phone->name)) {
            Message("이름 : %s \n"
                     "번호 : %s \n\n", 
                     phone->name, phone->tel);
            return;
        }
     
        phone = phone->next;
    }
}

void Modify(void) {
    char name[30];
    Phone *phone = head;

    printf("수정할 이름은 : ");
    gets(name);

    while (phone) {
        if (!strcmp(name, phone->name)) {
            char tel[20];

            printf("수정할 핸드폰 번호는 : ");
            
            gets(tel);
            strcpy(phone->tel, tel);
            
            Message("수정된 이름 : %s \n"
                     "수정된 번호 : %s \n\n", 
                     phone->name, phone->tel);

            return;
        }
        phone = phone->next;
    }
}

void Remove(void) {
    char name[30];
    Phone *phone = head;

    printf("삭제할 이름은 : ");
    gets(name);

    while (phone) {
        if (!strcmp(name, phone->name)) {
            RemoveList(phone);
            
            Message("%s가 삭제되었습니다. \n\n", name);

            return;
        }
        phone = phone->next;
    }
}

void RemoveList(Phone* phone) {
    if (phone == head)     {
        head = head->next;

        if (head)      
            head->prev = NULL;    
        else
            tail = NULL;
        
    }
    else if (phone == tail) {
        tail = tail->prev;
        tail->next = NULL;
    }
    else {
        Phone* prev;
        Phone* next;

        prev = phone->prev;
        next = phone->next;

        prev->next = next;
        next->prev = prev;
    }
    free(phone);
}

void List(int forward) {
    Phone* phone;
    int count = 0;

    phone = forward ? head : tail;

    while (phone) {
        printf("이름 : %s \n", phone->name);
        printf("번호 : %s \n", phone->tel);

        if (++count % 10 == 0) {
            printf("\n계속 보려면 아무키나 누르세요...\n");
            getch();
        }
        phone = forward ? phone->next : phone->prev;
    }

    printf("\n모든 항목이 출력되었습니다. \n");
    printf("\n아무키나 누르세요... \n");

    getch();
    Message("");
}

void FreeList(void) {
    while (head) {
        tail = head->next;
        free(head);
        head = tail;
    }
    head = tail = NULL;
}