#include <stdio.h>
#include <stdlib.h>

int arr[2000050];
int size = 0;

void josephus(int n, int m) {
    if (m <= 0) {
        fprintf(stderr, "Invalid step value m: %d\n", m);
        return;
    }

    int *people = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        people[i] = i + 1;
    }

    int idx = 0;
    for (int count = n; count > 0; count--) {
        idx = (idx + m - 1) % count;
        arr[size++] = people[idx];
        for (int j = idx; j < count - 1; j++) {
            people[j] = people[j + 1];
        }
    }
    free(people);
}

int main() {
    int n, id, m;
    scanf("%d %d %d", &n, &id, &m);
    if (m <= 0) {
        printf("Step value m must be greater than 0.\n");
        return 1;
    }
    josephus(n, m);
    if (arr[n - 1] == id) printf("You never die\n");
    else {
        for (int i = 0; i < n; i++) {
            if (arr[i] == id) {
                printf("%d\n", (i + 1) * m);
                break;
            }
        }
    }
    return 0;
}
