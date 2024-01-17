#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

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
};


struct Stack {
    struct Student* data;
    int top;
    int capacity;
};


void initialize(struct Stack* stack) {
    stack->data = (struct Student*)malloc(MAX_SIZE * sizeof(struct Student));
    if (stack->data == NULL) {
        fprintf(stderr, "Could not allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    stack->top = -1;
    stack->capacity = MAX_SIZE;
}


int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}


void push(struct Stack* stack, struct Student student) {
    if (isFull(stack)) {
        stack->capacity *= 2;
        struct Student* newData = (struct Student*)realloc(stack->data, stack->capacity * sizeof(struct Student));
        if (newData == NULL) {
            fprintf(stderr, "Could not allocate memory.\n");
            exit(EXIT_FAILURE);
        }
        stack->data = newData;
    }

    stack->data[++stack->top] = student;
}


struct Student pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        struct Student emptyStudent = { "", "", 0 };
        printf("Stack is empty. Returning empty student.\n");
        return emptyStudent;
    }
    printf("Popped student: %s %s %d \n", stack->data[stack->top].name, stack->data[stack->top].surname, stack->data[stack->top].yearOfBirth);
    return stack->data[stack->top--];
}


void pushnew(struct Stack* stack) {
    struct Student newStudent;
    printf("Enter student data: (format: name surname yearOfBirth)\n");
    if (scanf("%s %s %d", newStudent.name, newStudent.surname, &newStudent.yearOfBirth) != 3)
        printf("Read error\n");

    push(stack, newStudent);
}

void displayStack(struct Stack* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty.\n");
        return;
    }

    printf("Elements in the stack:\n");
    for (int i = stack->top; i >= 0; i--) {
        struct Student student = stack->data[i];
        printf("%s %s (Year of Birth: %d)\n", student.name, student.surname, student.yearOfBirth);
    }
}

int countElements(struct Stack* stack) {
    return stack->top + 1;
}

void searchStack(struct Stack* stack, const char* field, const char* value) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty.\n");
        return;
    }

    int found = 0;
    for (int i = stack->top; i >= 0; i--) {
        struct Student student = stack->data[i];
        if (strcmp(field, "name") == 0 && strcmp(student.name, value) == 0) {
            printf("Student found:\n");
            printf("Name: %s\nSurname: %s\nYear of Birth: %d\n", student.name, student.surname, student.yearOfBirth);
            found = 1;

        }
        else if (strcmp(field, "surname") == 0 && strcmp(student.surname, value) == 0) {
            printf("Student found:\n");
            printf("Name: %s\nSurname: %s\nYear of Birth: %d\n", student.name, student.surname, student.yearOfBirth);
            found = 1;

        }
        else if (strcmp(field, "yearofbirth") == 0 && student.yearOfBirth == atoi(value)) {
            printf("Student found:\n");
            printf("Name: %s\nSurname: %s\nYear of Birth: %d\n", student.name, student.surname, student.yearOfBirth);
            found = 1;

        }
    }

    if (!found) {
        printf("Student not found.\n");
    }
}

void deleteStack(struct Stack* stack) {
    for (int i = stack->top; i >= 0; i--) {
        struct Student* student = &(stack->data[i]);
        memset(student->name, 0, sizeof(student->name));
        memset(student->surname, 0, sizeof(student->surname));
        student->yearOfBirth = 0;
    }

    free(stack->data);
    stack->data = NULL;
    stack->top = -1;
    stack->capacity = 0;
}

void cleanupAndExit(struct Stack* stack) {
    deleteStack(stack);
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
            fprintf(stderr, "Blad odczytu");
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
                fprintf(stderr, "Blad odczytu");
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