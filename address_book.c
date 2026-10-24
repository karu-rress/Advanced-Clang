// Sample address book program

#include <conio.h>
#include <malloc.h>
#include <process.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define FILE_NAME "phone.buk"

typedef struct tagPhone {
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
void RemoveList(Phone *phone);
void List(int forward);
void FreeList(void);

void Message(char *pFormat, ...);

Phone *head, *tail;
char message[256] = "Choose an option : ";

int main(void) {
    const char *pmenu[] = {
        "1. Load",
        "2. Save",
        "3. Register",
        "4. Find",
        "5. Modify",
        "6. Remove",
        "7. List",
        "Q. Exit\n"};

    while (1) {
        system("cls");
        for (int i = 0; i < sizeof(pmenu) / sizeof(char *); i++) {
            puts(pmenu[i]);
        }

        printf("%s", message);

        int ch = getchar();
        getchar(); // Consume the newline character

        switch (ch) {
        case '1':
            Read();
            break;

        case '2':
            Write();
            break;

        case '3':
            Register();
            break;

        case '4':
            Find();
            break;

        case '5':
            Modify();
            break;

        case '6':
            Remove();
            break;

        case '7':
            List(1);
            break;

        case 'q':
        case 'Q':
            FreeList();
            exit(0);
        }
    }
}

void Message(char *pFormat, ...) {
    va_list arglist;

    va_start(arglist, pFormat);
    vsprintf(message, pFormat, arglist);
    va_end(arglist);

    strcat(message, "Choose an option : ");
}

void Read(void) {
    int read_block;
    int count = 0;
    FILE *fp;
    Phone phone;

    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        Message("Cannot open file.\n\n");
        return;
    }

    while (1) {
        read_block = fread(&phone, sizeof(Phone), 1, fp);
        if (read_block == 1) {
            Phone *tmp = (Phone *)malloc(sizeof(Phone));
            memset(tmp, 0, sizeof(Phone));

            strcpy(tmp->name, phone.name);
            strcpy(tmp->tel, phone.tel);

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
    Message("%d items have been read.\n\n", count);
}

void Write(void) {
    int count = 0;
    FILE *fp;
    Phone *phone = head;

    fp = fopen(FILE_NAME, "w+b");
    if (fp == NULL) {
        Message("Cannot open file.\n\n");
        return;
    }

    while (phone) {
        fwrite(phone, sizeof(Phone), 1, fp);
        phone = phone->next;
        count++;
    }

    fclose(fp);
    Message("%d items have been saved.\n\n", count);
}

void Register(void) {
    Phone phone;

    memset(&phone, 0, sizeof(Phone));

    printf("\nName : ");
    gets(phone.name);

    printf("Phone : ");
    gets(phone.tel);

    if (head == NULL) {
        head = tail = (Phone *)malloc(sizeof(Phone));
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
    strcpy(tail->tel, phone.tel);

    Message("%s has been added.\n\n", phone.name);
}

void Find(void) {
    Phone *phone = head;
    char name[30];

    printf("\nSearch for a name : ");
    gets(name);

    while (phone) {
        if (!strcmp(name, phone->name)) {
            Message("Name : %s \n"
                    "Phone : %s \n\n",
                phone->name, phone->tel);
            return;
        }

        phone = phone->next;
    }
}

void Modify(void) {
    char name[30];
    Phone *phone = head;

    printf("Name to modify : ");
    gets(name);

    while (phone) {
        if (!strcmp(name, phone->name)) {
            char tel[20];

            printf("New phone number : ");

            gets(tel);
            strcpy(phone->tel, tel);

            Message("Modified name : %s \n"
                    "Modified phone number : %s \n\n",
                phone->name, phone->tel);

            return;
        }
        phone = phone->next;
    }
}

void Remove(void) {
    char name[30];
    Phone *phone = head;

    printf("Name to delete : ");
    gets(name);

    while (phone) {
        if (!strcmp(name, phone->name)) {
            RemoveList(phone);

            Message("%s has been deleted. \n\n", name);

            return;
        }
        phone = phone->next;
    }
}

void RemoveList(Phone *phone) {
    if (phone == head) {
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
        Phone *prev;
        Phone *next;

        prev = phone->prev;
        next = phone->next;

        prev->next = next;
        next->prev = prev;
    }
    free(phone);
}

void List(int forward) {
    Phone *phone;
    int count = 0;

    phone = forward ? head : tail;

    while (phone) {
        printf("Name : %s \n", phone->name);
        printf("Phone : %s \n", phone->tel);

        if (++count % 10 == 0) {
            printf("\nPress any key to continue...\n");
            getch();
        }
        phone = forward ? phone->next : phone->prev;
    }

    printf("\nAll items have been displayed. \n");
    printf("\nPress any key to continue... \n");

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
