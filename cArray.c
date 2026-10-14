#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 10
#define INPUT_SIZE 128

static int read_integer(const char *prompt, int *value)
{
    char line[INPUT_SIZE];

    for (;;) {
        char *end;
        long parsed;
        int extra;

        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            return 0;
        }

        if (strchr(line, '\n') == NULL && !feof(stdin)) {
            while ((extra = getchar()) != '\n' && extra != EOF) {
            }
            printf("Input is too long. Please enter one integer.\n");
            continue;
        }

        errno = 0;
        parsed = strtol(line, &end, 10);
        while (isspace((unsigned char)*end)) {
            ++end;
        }

        if (end == line || *end != '\0' || errno == ERANGE ||
            parsed < INT_MIN || parsed > INT_MAX) {
            printf("Invalid input. Please enter one integer.\n");
            continue;
        }

        *value = (int)parsed;
        return 1;
    }
}

static void traverse(const int values[], int count)
{
    int i;

    if (count == 0) {
        printf("Array is empty.\n");
        return;
    }

    printf("Array:");
    for (i = 0; i < count; ++i) {
        printf(" %d", values[i]);
    }
    printf("\n");
}

static void insert_value(int values[], int *count)
{
    int position;
    int value;
    int i;

    if (*count == CAPACITY) {
        printf("Array is full; insertion is not possible.\n");
        return;
    }
    if (!read_integer("Position to insert (1-based): ", &position)) {
        return;
    }
    if (position < 1 || position > *count + 1) {
        printf("Position must be between 1 and %d.\n", *count + 1);
        return;
    }
    if (!read_integer("Value: ", &value)) {
        return;
    }

    for (i = *count; i >= position; --i) {
        values[i] = values[i - 1];
    }
    values[position - 1] = value;
    ++*count;
    printf("Value inserted.\n");
}

static void delete_value(int values[], int *count)
{
    int position;
    int i;

    if (*count == 0) {
        printf("Array is empty; nothing to delete.\n");
        return;
    }
    if (!read_integer("Position to delete (1-based): ", &position)) {
        return;
    }
    if (position < 1 || position > *count) {
        printf("Position must be between 1 and %d.\n", *count);
        return;
    }

    printf("Deleted %d.\n", values[position - 1]);
    for (i = position - 1; i < *count - 1; ++i) {
        values[i] = values[i + 1];
    }
    --*count;
}

static void update_value(int values[], int count)
{
    int position;
    int value;

    if (count == 0) {
        printf("Array is empty; nothing to update.\n");
        return;
    }
    if (!read_integer("Position to update (1-based): ", &position)) {
        return;
    }
    if (position < 1 || position > count) {
        printf("Position must be between 1 and %d.\n", count);
        return;
    }
    if (!read_integer("New value: ", &value)) {
        return;
    }

    values[position - 1] = value;
    printf("Value updated.\n");
}

static void search_value(const int values[], int count)
{
    int target;
    int i;
    int found = 0;

    if (!read_integer("Value to search for: ", &target)) {
        return;
    }
    for (i = 0; i < count; ++i) {
        if (values[i] == target) {
            printf("Found at position %d.\n", i + 1);
            found = 1;
        }
    }
    if (!found) {
        printf("Value not found.\n");
    }
}

int main(void)
{
    int values[CAPACITY] = {10, 15, 20, 25};
    int count = 4;
    int choice;

    for (;;) {
        printf("\nArray operations (capacity %d)\n", CAPACITY);
        printf("1. Traverse\n2. Insert\n3. Delete\n4. Update\n");
        printf("5. Search\n0. Exit\n");
        if (!read_integer("Choose an option: ", &choice)) {
            printf("\nExiting.\n");
            break;
        }

        switch (choice) {
        case 1:
            traverse(values, count);
            break;
        case 2:
            insert_value(values, &count);
            break;
        case 3:
            delete_value(values, &count);
            break;
        case 4:
            update_value(values, count);
            break;
        case 5:
            search_value(values, count);
            break;
        case 0:
            return 0;
        default:
            printf("Choose one of the listed options.\n");
        }
    }

    return 0;
}