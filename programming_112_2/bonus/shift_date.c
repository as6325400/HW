#include <stdio.h>

int isLeapYear(long long year) {
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
        return 1;
    }
    return 0;
}

int main() {
    long long year, month, day, daysToAdd;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Input the date in the format YYYY/MM/DD and the number of days to add
    scanf("%lld/%lld/%lld", &year, &month, &day);
    scanf("%lld", &daysToAdd);

    while (daysToAdd > 0) {
        // Adjust February days for leap year
        if (month == 2) {
            daysInMonth[1] = isLeapYear(year) ? 29 : 28;
        }

        // Determine if adding days will cross to a new month
        if (day + daysToAdd <= daysInMonth[month - 1]) {
            day += daysToAdd;
            break;
        } else {
            daysToAdd -= (daysInMonth[month - 1] - day + 1);
            day = 1;  // Start at day 1 of the next month
            month++;  // Increment the month
        }

        // Check if the new month value has exceeded December, reset to January and increment year
        if (month > 12) {
            year++;
            month = 1;
        }
    }

    // Output the calculated date
    printf("%lld/%lld/%lld\n", year, month, day);
    return 0;
}
