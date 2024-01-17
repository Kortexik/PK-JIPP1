#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum MY_INTERF_EN
{
    INTERF_ENQUEUE = 1,
    INTERF_DEQUEUE,
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


struct Queue {
    struct Student* head;
    struct Student* tail;
};


void initialize(struct Queue* queue) {
    queue->head = NULL;
    queue->tail = NULL;
}

int isEmpty(struct Queue* queue) {
    return queue->head == NULL;
}


void enqueue(struct Queue* queue, struct Student student) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    if (newStudent == NULL) {
        fprintf(stderr, "Could not allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    *newStudent = student;
    newStudent->next = NULL;

    if (isEmpty(queue)) {
        queue->head = newStudent;
        queue->tail = newStudent;
        newStudent->prev = NULL;
    }
    else {
        queue->tail->next = newStudent;
        newStudent->prev = queue->tail;
        queue->tail = newStudent;
    }
}


struct Student dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        struct Student emptyStudent = { "", "", 0, NULL, NULL };
        printf("Queue is empty. Returning empty student.\n");
        return emptyStudent;
    }

    struct Student* dequeuedStudent = queue->head;
    queue->head = queue->head->next;

    if (queue->head != NULL) {
        queue->head->prev = NULL;
    }
    else {
        queue->tail = NULL;
    }

    struct Student student = *dequeuedStudent;
    free(dequeuedStudent);
    printf("Dequeued student: %s %s %d \n", student.name, student.surname, student.yearOfBirth);
    return student;
}

void enqueueNew(struct Queue* queue) {
    struct Student newStudent;
    printf("Enter student data: (format: name surname yearOfBirth)\n");
    if (scanf("%s %s %d", newStudent.name, newStudent.surname, &newStudent.yearOfBirth) != 3)
        fprintf(stderr, "Read error\n");

    enqueue(queue, newStudent);
}

void displayQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "Queue is empty.\n");
        return;
    }

    printf("Elements in the queue:\n");
    struct Student* current = queue->head;
    while (current != NULL) {
        printf("%s %s (Year of Birth: %d)\n", current->name, current->surname, current->yearOfBirth);
        current = current->next;
    }
}

int countElements(struct Queue* queue) {
    int count = 0;
    struct Student* current = queue->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void searchQueue(struct Queue* queue, const char* field, const char* value) {
    if (isEmpty(queue)) {
        fprintf(stderr, "Queue is empty.\n");
        return;
    }
    int found = 0;
    struct Student* current = queue->head;
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

        current = current->next;
    }

    if (!found) {
        printf("Student not found.\n");
    }
}

void deleteQueue(struct Queue* queue) {
    struct Student* current = queue->head;
    while (current != NULL) {
        struct Student* next = current->next;
        free(current);
        current = next;
    }
    queue->head = NULL;
    queue->tail = NULL;
}

void cleanupAndExit(struct Queue* queue) {
    deleteQueue(queue);
    printf("Exiting program.\n");
    exit(EXIT_SUCCESS);
}

int main() {
    struct Queue queue;
    initialize(&queue);
    enum MY_INTERF_EN choice;

    do {
        printf("\n-- Menu --\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Find by Last Name\n");
        printf("4. Display\n");
        printf("5. Count Elements\n");
        printf("6. Clear Queue\n");
        printf("7. Stop\n");

        printf("\nEnter your choice (1-%d): ", INTERF_TOT - 1);

        if (scanf("%d", (int*)&choice) != 1) {
            fprintf(stderr, "Read error");
        }
        switch (choice) {
        case INTERF_ENQUEUE:
            enqueueNew(&queue);
            break;
        case INTERF_DEQUEUE:
            dequeue(&queue);
            break;
        case INTERF_FIND_LASTNAME:
        {
            char lastname[50];
            printf("Enter last name to search: ");
            if (scanf("%s", lastname) != 1) {
                fprintf(stderr, "Read error");
            }
            searchQueue(&queue, "surname", lastname);
        }
        break;
        case INTERF_DISPLAY:
            displayQueue(&queue);
            break;
        case INTERF_COUNT:
            printf("Number of elements in the queue: %d\n", countElements(&queue));
            break;
        case INTERF_CLEAR:
            deleteQueue(&queue);
            printf("Queue cleared.\n");
            break;
        case INTERF_STOP:
            cleanupAndExit(&queue);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != INTERF_STOP);
    return 0;
}
