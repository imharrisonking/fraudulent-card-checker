#include <cs50.h>
#include <stdio.h>
#include <math.h>

int get_length(long number);
int check_valid(long nu);
int is_visa(long number, int length);
int is_amex(long number, int length);
int is_mastercard(long number, int length);

int main(void)
{
    // Get the card number
    long nu = get_long("Number: ");
    // printf("%li\n", nu);

    // Find and save the length of the card
    int length = get_length(nu);
    // printf("Length = %i\n", length);


    // Check if card is Visa
    if (length == 13 || length == 15 || length == 16)
    {
        if (check_valid(nu) == 0)
        {
            if (is_visa(nu, length) == 1)
            {
                printf("VISA\n");
            }
            else if (is_amex(nu, length) == 1)
            {
                printf("AMEX\n");
            }
            else if (is_mastercard(nu, length) == 1)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}

int get_length(long number)
{
    int count = 0;
    while (number != 0)
    {
        number = number/10;
        ++count;
    }
    return count;
}

// Carry out Luhn's Algorithm
int check_valid(long number)
{
    int end_digit;
    int last_digit;
    int second_last_digit;
    int doubled;
    long sum = 0;
    bool legit_card = false;
    while (number != 0)
    {
        // Get the last and second last digits
        end_digit = number % 10;
        second_last_digit = ((number / 10) % 10);
        doubled = second_last_digit*2;

        // Moving through the loop until all numbers have been parsed, double every
        // other number and add the sums of these and the other numbers
        if (doubled > 9)
        {
            int i = doubled % 10;
            int j = ((doubled / 10) % 10);
            sum = sum + end_digit + i + j;
        }
        else
        {
            sum = sum + end_digit + doubled;
        }

        // Repeat loop for the next two numbers
        number = number / 100;
    }
    return sum % 10;
}

// Return the first two numbers of the card number (using the length)

// Is Visa?
int is_visa(long number, int length)
{
    int starting_digit = number / pow(10, length-1);
    // printf("Visa starting digit: %i\n", starting_digit);
    if (starting_digit == 4)
    {
        return 1;
    } else
    {
        return 0;
    }
}

// Is Amex?
int is_amex(long number, int length)
{
    int starting_digit = number / pow(10, length-2);
    // printf("Amex starting digits: %i\n", starting_digit);
    if (starting_digit == 34 || starting_digit == 37) {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Is MasterCard?
int is_mastercard(long number, int length)
{
    int starting_digit = number / pow(10, length-2);
    // printf("Matercard starting digits: %i\n", starting_digit);
    if (starting_digit == 51 || starting_digit == 52 || starting_digit == 53 || starting_digit == 54 || starting_digit == 55) {
        return 1;
    }
    else
    {
        return 0;
    }
}