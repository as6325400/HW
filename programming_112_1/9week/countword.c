#include <stdio.h>
#include <ctype.h>

int countWords()
{
    char ch;
    int wordCount = 0;
    char state = 0; // 0 - outside a word, 1 - inside a word

    while ((ch = getchar()) != EOF)
    {
        if (isalpha(ch))
        {
            if (state == 0)
            {
                state = 1;
                wordCount++;
            }
        }
        else if (ch == '\'' && state == 1 && isalpha(getchar()))
        {
            // handling apostrophes in words
            continue;
        }
        else
        {
            state = 0;
        }
    }

    return wordCount;
}

int main()
{
    int wordCount = countWords();
    printf("%d\n", wordCount);

    return 0;
}
