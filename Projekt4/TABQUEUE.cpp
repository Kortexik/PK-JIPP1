#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

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

// Structure to represent a student
struct Student {
    char name[50];
    char surname[50];
    int yearOfBirth;
};

// Structure to represent the queue
struct Queue {
    struct Student* data;
    int front;
    int rear;
    int capacity;
};


void initialize(struct Queue* queue) {
    queue->data = (struct Student*)malloc(MAX_SIZE * sizeof(struct Student));
    if (queue->data == NULL) {
        fprintf(stderr, "Could not allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    queue->front = -1;
    queue->rear = -1;
    queue->capacity = MAX_SIZE;
}


int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}


int isFull(struct Queue* queue) {
    return (queue->rear + 1) % queue->capacity == queue->front;
}

void enqueue(struct Queue* queue, struct Student student) {
    if (isFull(queue)) {
       
        int newCapacity = queue->capacity * 2;
        struct Student* newData = (struct Student*)realloc(queue->data, newCapacity * sizeof(struct Student));
        if (newData == NULL) {
            fprintf(stderr, "Could not allocate memory.\n");
            exit(EXIT_FAILURE);
        }
        queue->data = newData;
        queue->capacity = newCapacity;
    }

    if (isEmpty(queue)) {
        queue->front = 0;
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = student;
}


struct Student dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        struct Student emptyStudent = { "", "", 0 };
        printf("Queue is empty. Returning empty student.\n");
        return emptyStudent;
    }

    struct Student dequeuedStudent = queue->data[queue->front];

    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    }
    else {
        queue->front = (queue->front + 1) % queue->capacity;
    }

    printf("Dequeued student: %s %s %d \n", dequeuedStudent.name, dequeuedStudent.surname, dequeuedStudent.yearOfBirth);
    return dequeuedStudent;
}


void enqueueNew(struct Queue* queue) {
    struct Student newStudent;
    printf("Enter student data (format: name surname yearOfBirth): \n");
    if (scanf("%s %s %d", newStudent.name, newStudent.surname, &newStudent.yearOfBirth) != 3) {
        fprintf(stderr, "Read error.\n");
        return;
    }

    enqueue(queue, newStudent);
}

void displayQueue(struct Queue* queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "Queue is empty.\n");
        return;
    }
    printf("Elements in the queue:\n");
    int i = queue->front;
    while (i != queue->rear) {
        struct Student student = queue->data[i];
        printf("%s %s (Year of Birth: %d)\n", student.name, student.surname, student.yearOfBirth);
        i = (i + 1) % queue->capacity;
    }
    struct Student student = queue->data[queue->rear];
    printf("%s %s (Year of Birth: %d)\n", student.name, student.surname, student.yearOfBirth);
}

int countElements(struct Queue* queue) {
    if (isEmpty(queue)) {
        return 0;
    }
    if (queue->front <= queue->rear) {
        return queue->rear - queue->front + 1;
    }
    else {
        return queue->capacity - queue->front + queue->rear + 1;
    }
}

void searchQueue(struct Queue* queue, const char* field, const char* value) {
    if (isEmpty(queue)) {
        fprintf(stderr, "Queue is empty.\n");
        return;
    }
    int i = queue->front;
    int found = 0;

    while (i != queue->rear) {
        struct Student student = queue->data[i];
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

        i = (i + 1) % queue->capacity;
    }

    if (i == queue->rear) {
        struct Student student = queue->data[i];
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

void deleteQueue(struct Queue* queue) {
    free(queue->data);
    queue->data = NULL;
    queue->front = -1;
    queue->rear = -1;
    queue->capacity = 0;
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
            fprintf(stderr, "Read error.\n");
        }
        switch (choice) {
        case INTERF_ENQUEUE:
            enqueueNew(&queue);
            break;
        case INTERF_DEQUEUE:
            dequeue(&queue);
            break;
        case INTERF_FIND_LASTNAME: {
            char lastname[50];
            printf("Enter last name to search: ");
            if (scanf("%s", lastname) != 1) {
                fprintf(stderr, "Read error.\n");
            }
            searchQueue(&queue, "surname", lastname);
            break;
        }
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


