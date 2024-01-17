#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum MY_INTERF_EN
{
    INTERF_PUSH = 1,
    INTERF_POP,
    INTERF_FIND_LASTNAME,
    INTERF_DISPLAY,
    INTERF_COUNT,
    INTERF_CLEAR,
    INTERF_STOP,
    INTERF_TOT
};


struct Student {
    char name[50];
    char surname[50];
    int yearOfBirth;
    struct Student* next;
    struct Student* prev;
};


struct Stack {
    struct Student* head;
    struct Student* tail;
};


void initialize(struct Stack* stack) {
    stack->head = NULL;
    stack->tail = NULL;
}


int isEmpty(struct Stack* stack) {
    return stack->head == NULL;
}


void push(struct Stack* stack, struct Student student) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    if (newStudent == NULL) {
        fprintf(stderr, "Could not allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    *newStudent = student;
    newStudent->next = NULL;

    if (isEmpty(stack)) {
        stack->head = newStudent;
        stack->tail = newStudent;
        newStudent->prev = NULL;
    }
    else {
        stack->tail->next = newStudent;
        newStudent->prev = stack->tail;
        stack->tail = newStudent;
    }
}


struct Student pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        struct Student emptyStudent = { "", "", 0, NULL, NULL };
        printf("Stack is empty. Returning empty student.\n");
        return emptyStudent;
    }

    struct Student* poppedStudent = stack->tail;
    stack->tail = stack->tail->prev;

    if (stack->tail != NULL) {
        stack->tail->next = NULL;
    }
    else {
        stack->head = NULL;
    }

    struct Student student = *poppedStudent;
    free(poppedStudent);
    printf("Popped student: %s %s %d \n", student.name, student.surname, student.yearOfBirth);
    return student;
}


void pushnew(struct Stack* stack) {
    struct Student newStudent;
    printf("Enter student data: (format: name surname yearOfBirth)\n");
    if (scanf("%s %s %d", newStudent.name, newStudent.surname, &newStudent.yearOfBirth) != 3)
        fprintf(stderr, "Read error\n");

    push(stack, newStudent);
}

void displayStack(struct Stack* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty.\n");
        return;
    }

    printf("Elements in the stack:\n");
    struct Student* current = stack->tail;
    while (current != NULL) {
        printf("%s %s (Year of Birth: %d)\n", current->name, current->surname, current->yearOfBirth);
        current = current->prev;
    }
}

int countElements(struct Stack* stack) {
    int count = 0;
    struct Student* current = stack->head;
    while (current != NULL) {
        count++;
        current = current->next;
        
    }
    return count;
}

void searchStack(struct Stack* stack, const char* field, const char* value) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty.\n");
        return;
    }
    int found = 0;
    struct Student* current = stack->tail;
    while (current != NULL) {
        if (strcmp(field, "name") == 0 && strcmp(current->name, value) == 0) {
            printf("Student found:\n");
            printf("Name: %s\nSurname: %s\nYear of Birth: %d\n", current->name, current->surname, current->yearOfBirth);
            found = 1;
        }
        else if (strcmp(field, "surname") == 0 && strcmp(current->surname, value) == 0) {
            printf("Student found:\n");
            printf("Name: %s\nSurname: %s\nYear of Birth: %d\n", current->name, current->surname, current->yearOfBirth);
            found = 1;
        }
        else if (strcmp(field, "yearofbirth") == 0 && current->yearOfBirth == atoi(value)) {
            printf("Student found:\n");
            printf("Name: %s\nSurname: %s\nYear of Birth: %d\n", current->name, current->surname, current->yearOfBirth);
            found = 1;
        }

        current = current->prev;
    }

    if (!found) {
        printf("Student not found.\n");
    }
}

void deleteStack(struct Stack* stack) {
    struct Student* current = stack->head;
    while (current != NULL) {
        struct Student* next = current->next;
        free(current);
        current = next;
    }
    stack->head = NULL;
    stack->tail = NULL;
}

void cleanupAndExit(struct Stack* stack) {
    struct Student* current = stack->head;
    while (current != NULL) {
        struct Student* next = current->next;
        free(current);
        current = next;
    }
    printf("Exiting program.\n");
    exit(EXIT_SUCCESS);
}

int main() {
    struct Stack stack;
    initialize(&stack);
    enum MY_INTERF_EN choice;

    do {
        printf("\n-- Menu --\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Find by Last Name\n");
        printf("4. Display\n");
        printf("5. Count Elements\n");
        printf("6. Clear Stack\n");
        printf("7. Stop\n");

        printf("\nEnter your choice (1-%d): ", INTERF_TOT - 1);

        if (scanf("%d", (int*)&choice) != 1) {
            fprintf(stderr, "Read error\n");
        }
        switch (choice) {
        case INTERF_PUSH:
            pushnew(&stack);
            break;
        case INTERF_POP:
            pop(&stack);
            break;
        case INTERF_FIND_LASTNAME:
        {
            char lastname[50];
            printf("Enter last name to search: ");
            if (scanf("%s", lastname) != 1) {
                fprintf(stderr, "Read error\n");
            }
            searchStack(&stack, "surname", lastname);
        }
        break;
        case INTERF_DISPLAY:
            displayStack(&stack);
            break;
        case INTERF_COUNT:
            printf("Number of elements in the stack: %d\n", countElements(&stack));
            break;
        case INTERF_CLEAR:
            deleteStack(&stack);
            printf("Stack cleared.\n");
            break;
        case INTERF_STOP:
            cleanupAndExit(&stack);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != INTERF_STOP);
    return 0;
}