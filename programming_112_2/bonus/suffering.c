#include <stdio.h>

int targets[100005]; // Stores the target each person throws at
int results[1005];   // Stores the results of each operation

// Function to find the final target after a number of hits
int find_final_target(int start, long long num_hits) {
    int slow = start, fast = start;

    // Find the cycle using Floyd's Tortoise and Hare algorithm
    do {
        slow = targets[slow];          // Move one step
        fast = targets[targets[fast]]; // Move two steps
    } while (slow != fast);

    // Determine the start of the cycle
    int cycle_start = start;
    while (cycle_start != slow) {
        cycle_start = targets[cycle_start];
        slow = targets[slow];
    }

    // Determine the length of the cycle
    int cycle_length = 1;
    int cycle_node = targets[cycle_start];
    while (cycle_node != cycle_start) {
        cycle_node = targets[cycle_node];
        cycle_length++;
    }

    // Simulate num_hits within the cycle
    int current = cycle_start;
    num_hits %= cycle_length; // Reduce the number of hits by the cycle length
    for (int i = 0; i < num_hits; i++) {
        current = targets[current];
    }
    return current;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // Input each person's target
    for (int i = 0; i < n; i++) {
        int s, t;
        scanf("%d %d", &s, &t);
        targets[s] = t;
    }

    // Process each query and find the final target
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        results[i] = find_final_target(u, v);
    }

    // Output all results
    for (int i = 0; i < m; i++) {
        printf("%d\n", results[i]);
    }

    return 0;
}
