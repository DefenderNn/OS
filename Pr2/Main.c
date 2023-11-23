#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

void playSlotMachine(int bet, int length) {
    int i, matchCount = 0, sevenCount = 0;

    int slotNumbers[length];
    for (i = 0; i < length; ++i) {
        slotNumbers[i] = getRandomNumber(0, 9);

        if (slotNumbers[i] == 7) {
            sevenCount++;
        }
    }

    printf("Slot numbers: ");
    for (i = 0; i < length; ++i) {
        printf("%d ", slotNumbers[i]);
    }

    for (i = 1; i < length; ++i) {
        if (slotNumbers[i] == slotNumbers[i - 1]) {
            matchCount++;
        }
    }

    if (sevenCount > 0) {
        printf("\nCongratulations! You got at least one 7. Your bet is returned.\n");
    } else if (matchCount == length - 1) {
        printf("\nCongratulations! All numbers are the same. Your bet is doubled.\n");
        bet *= 2;
    } else if (matchCount == length) {
        printf("\nCongratulations! All numbers are 7. Your bet is tripled.\n");
        bet *= 3;
    } else if (matchCount >= length / 3) {
        printf("\nCongratulations! At least one-third of the numbers are the same. You win!\n");
    } else {
        printf("\nSorry, you didn't win this time. Better luck next time!\n");
        bet = 0; // Гравець втратив ставку
    }

    printf("Your winnings: %d\n", bet);
}

int main() {
    int bet, length;

    srand(time(NULL));

    printf("Enter your bet: ");
    scanf("%d", &bet);

    printf("Enter the length of the slot machine sequence: ");
    scanf("%d", &length);

    if (bet <= 0 || length <= 0) {
        printf("Invalid input. Please enter positive values for bet and length.\n");
        return 1;
    }

    playSlotMachine(bet, length);

    return 0;
}

