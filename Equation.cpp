#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

//-----------------------------------------------------------------------------

int const LESS_THAN_ZERO        = -1;
int const EQUAL_TO_ZERO         = 0;
int const MORE_THAN_ZERO        = 1;
int const NOROOTS               = -2;
int const INFINITELY            = -3;
int const BEFORE_CHECK          = NAN;
double const ERROR              = 0.001;
double const BEFORE_DETERMINING = NAN;

//-----------------------------------------------------------------------------

int Compare_zero (double value);

int UT_Compare_zero();

int Linear_equation (double coeff_a, double coeff_b, double* result);

int Quadratic_equation (double coeff_a, double coeff_b, double coeff_c, double* result1, double* result2);

int Solve_equation (double coeff_a, double coeff_b, double coeff_c, double* result1, double* result2);

int UT_Solve_equation();

int Checking_coeff (double* coeff_a, double* coeff_b, double* coeff_c);

int Unit_tests();

//-----------------------------------------------------------------------------

/**
    /brief This program allows you to solve linear and quadratic equations
    /version 1.0.4
    /return 0 - luck, 1 - error

    If you enter the coefficients of your equation, you get the roots

    Author: Rusakov AI

    Date: 27.08.2020
*/

int main()
{
    printf ("# Solution of a quadratic equation\n"
            "# 27.08.2020\n\n"
            "# Enter coefficients a, b, c: \n\n");

/*
    printf ("Compare_zero, unit-tests: \n");
    printf ("Number of successfully passed tests: %d", UT_Compare_zero());
    printf ("\n\nSolve_equation, unit-tests: \n");
    printf ("Number of successfully passed tests: %d\n\n", UT_Solve_equation());
*/
    printf("%d\n", Unit_tests());
    return 0;

    double coeff_a = BEFORE_DETERMINING,
           coeff_b = BEFORE_DETERMINING,
           coeff_c = BEFORE_DETERMINING;
    Checking_coeff (&coeff_a, &coeff_b, &coeff_c);

    double result1 = BEFORE_DETERMINING,
           result2 = BEFORE_DETERMINING;

    switch (Solve_equation (coeff_a, coeff_b, coeff_c, &result1, &result2))
    {
        case NOROOTS:
            printf ("No roots\n");
            break;

        case 1:
            printf ("root: %lg\n", result1);
            break;

        case 2:
            printf ("root 1: %lg, root 2: %lg\n", result1, result2);
            break;

        case INFINITELY:
            printf ("root - any number\n");
            break;

        default:
            printf ("main(): data entry error\n");
            return 1;
            break;
    }

    return 0;
}

//-----------------------------------------------------------------------------

/**
    int Compare_zero (double number)

    ! This function carries out an accurate comparison with zero

    \param[in] value is value for exact comparison
    */

int Compare_zero (double value)
{
    if (value <= -ERROR)
        return LESS_THAN_ZERO;  //---value < 0

    if (fabs(value) < ERROR)
        return EQUAL_TO_ZERO;   //---value == 0

    return MORE_THAN_ZERO;   //---value > 0
}


//-----------------------------------------------------------------------------

// int UT_Compare_zero()
// ! This function does unit-tests

int UT_Compare_zero()
{
    int n_luck_tests = 0;
    int solution = 0;

    double value = -1;
    int answer = LESS_THAN_ZERO;
    int num = 1;

    #define TEST                            \
    solution = Compare_zero (value);        \
    if (solution == answer)                 \
    {                                       \
        printf ("Test #%d - luck\n", num);  \
        n_luck_tests++;                     \
    }                                       \
    else                                    \
        printf ("Test #%d - fail: Compare_zero (%lg) == %d, should be %d\n", num, value, solution, answer);

    TEST;

    value = 0;
    answer = EQUAL_TO_ZERO;
    num++;

    TEST;

    value = 1;
    answer = MORE_THAN_ZERO;
    num++;

    TEST;

    value = -ERROR;
    answer = LESS_THAN_ZERO;
    num++;

    TEST;

    value = ERROR;
    answer = MORE_THAN_ZERO;
    num++;

    TEST;

    return n_luck_tests;
}

//-----------------------------------------------------------------------------

/**
    int Linear_equation (double coeff_a, double coeff_b, double* result)

    ! This function solves the linear equation

    \param[in] coeff_a is leading coefficient
    \param[in] coeff_b is free coefficient
    \param[out] result if root of equation
    */

int Linear_equation (double coeff_a, double coeff_b, double* result)    //---Equation ax + b = 0
{
    if (Compare_zero (coeff_a) == EQUAL_TO_ZERO && Compare_zero (coeff_b) == EQUAL_TO_ZERO)
        return INFINITELY;

//--Now not INFINITELY

    if (Compare_zero (coeff_a) == EQUAL_TO_ZERO)
        return NOROOTS;   //---b != 0

    *result = -coeff_b / coeff_a;   //---a != 0
    return 1;
}

//-----------------------------------------------------------------------------

/**
    int Quadratic_equation (double coeff_a, double coeff_b, double coeff_c, double* result1, double* result2)

    ! This function solves the quadratic equation

    \param[in] coeff_a is leading coefficient
    \param[in] coeff_b is middle coefficient
    \param[in] coeff_c is free coefficient
    \param[out] result1 is first root
    \param[out] result2 is second root
    */

int Quadratic_equation (double coeff_a, double coeff_b, double coeff_c, double* result1, double* result2)   //---Equation ax^2 + bx + c = 0
{
    double diskr = coeff_b * coeff_b - 4 * coeff_a * coeff_c;

    if (Compare_zero (diskr) == LESS_THAN_ZERO)
        return NOROOTS;

    if (Compare_zero (diskr) == EQUAL_TO_ZERO)
    {
        *result1 = *result2 = -coeff_b / (2 * coeff_a);
        return 1;
    }

    *result1 = (-coeff_b + sqrt (diskr)) / (2 * coeff_a);
    *result2 = (-coeff_b - sqrt (diskr)) / (2 * coeff_a);
    return 2;
}

//-----------------------------------------------------------------------------

/**
    int Solve_equation (double coeff_a, double coeff_b, double coeff_c, double* result1, double* result2)

    ! This function determines the form of the equation, finds errors and counts the number of roots

    \param[in] coeff_a is leading coefficient
    \param[in] coeff_b is middle coefficient
    \param[in] coeff_c is free coefficient
    \param[out] result1 is first root
    \param[out] result2 is second root
    */

int Solve_equation (double coeff_a, double coeff_b, double coeff_c, double* result1, double* result2)
{
    assert (isfinite (coeff_a));
    assert (isfinite (coeff_b));
    assert (isfinite (coeff_c));
    assert (result1 != NULL);
    assert (result2 != NULL);
    assert (result1 != result2);

    if (Compare_zero (coeff_a) == 0)
        return Linear_equation (coeff_b, coeff_c, result1);

    return Quadratic_equation (coeff_a, coeff_b, coeff_c, result1, result2);
}

//-----------------------------------------------------------------------------

// int UT_Solve_equation()
// ! This function does unit-tests

int UT_Solve_equation()
{
    int n_luck_tests = 0;
    int solution = 0;
    double root1 = 0;
    double root2 = 0;
    double sol1 = 0;  //---Variable for calculating the value of the equation when substituting roots
    double sol2 = 0;

    double test_ca = 0;
    double test_cb = 0;
    double test_cc = 0;
    int answer = INFINITELY;
    int num = 1;

    #define TEST                                                                                                                                                    \
    solution = Solve_equation (test_ca, test_cb, test_cc, &root1, &root2);                                                                                          \
    sol1 = test_ca * root1 * root1 + test_cb * root1 + test_cc;                                                                                                     \
    sol2 = test_ca * root2 * root2 + test_cb * root2 + test_cc;                                                                                                     \
                                                                                                                                                                    \
    if (solution == NOROOTS)                                                                                                                                        \
    {                                                                                                                                                               \
        sol1 = 0;                                                                                                                                                   \
        sol2 = 0;                                                                                                                                                   \
    }                                                                                                                                                               \
                                                                                                                                                                    \
    if (solution == 1)                                                                                                                                              \
        sol2 = 0;                                                                                                                                                   \
                                                                                                                                                                    \
    if (solution == answer && sol1 == 0 && sol2 == 0)                                                                                                               \
    {                                                                                                                                                               \
        printf ("Test #%d - luck\n", num);                                                                                                                          \
        n_luck_tests++;                                                                                                                                             \
    }                                                                                                                                                               \
    else                                                                                                                                                            \
        printf ("Test #%d - fail: Solve_equation (%lg, %lg, %lg, %lg, %lg) == %d, should be %d\n", num, test_ca, test_cb, test_cc, root1, root2, solution, answer); \
                                                                                                                                                                    \
    sol1 = sol2 = 0;                                                                                                                                                \
    root1 = root2 = 0;

    TEST;

    test_ca = 5;
    test_cb = 6;
    test_cc = 7;
    answer = NOROOTS;
    num++;

    TEST;

    test_ca = 1;
    test_cb = -2;
    test_cc = 1;
    answer = 1;
    num++;

    TEST;

    test_ca = 2;
    test_cb = 5;
    test_cc = 2;
    answer = 2;
    num++;

    TEST;

    test_ca = 0;
    test_cb = 0;
    test_cc = 1;
    answer = NOROOTS;
    num++;

    TEST;

    test_ca = 0;
    test_cb = 1;
    test_cc = -1;
    answer = 1;
    num++;

    TEST;

    return n_luck_tests;

}

//-----------------------------------------------------------------------------

/**
    int Checking_coeff (double* coeff_a, double* coeff_b, double* coeff_c)

    ! This function processes the coefficients, finds errors and counts the number of entries

    \param[out] coeff_a is leading coefficient
    \param[out] coeff_b is middle coefficient
    \param[out] coeff_c is free coefficient
    */

int Checking_coeff (double* coeff_a, double* coeff_b, double* coeff_c)
{
    assert (coeff_a != NULL);
    assert (coeff_b != NULL);
    assert (coeff_c != NULL);
    assert (coeff_a != coeff_b || coeff_a != coeff_b || coeff_b != coeff_c);

    int n_entries = 1;   //---This is the number of inputs

    while (scanf ("%lg %lg %lg/n", coeff_a, coeff_b, coeff_c) != 3)
    {
        printf ("Incorrect values. Re-enter:\n");
        fflush (stdin);
        n_entries++;
    }

    return n_entries;
}

//-----------------------------------------------------------------------------

int Unit_tests()
{
    srand(time(NULL));
    int n_fail_tests = 0;
    int solution = 0;
    int num = 0;
    double test_ca = 0;
    double test_cb = 0;
    double test_cc = 0;
    double root1 = 0;
    double root2 = 0;
    double sol1 = 0;
    double sol2 = 0;

    for (int i = 0; i < 100; i++)
    {
        test_ca = rand() - RAND_MAX / 2;
        test_cb = rand() - RAND_MAX / 2;
        test_cc = rand() - RAND_MAX / 2;
        num++;

        solution = Solve_equation (test_ca, test_cb, test_cc, &root1, &root2);
        sol1 = test_ca * root1 * root1 + test_cb * root1 + test_cc;
        sol2 = test_ca * root2 * root2 + test_cb * root2 + test_cc;

        if (solution == NOROOTS)    //---If there are no roots
        {
            sol1 = 0;
            sol2 = 0;
        }

        if (solution == 1)  //---If there is only one root
            sol2 = 0;

        if (Compare_zero(sol1) == EQUAL_TO_ZERO && Compare_zero(sol2) == EQUAL_TO_ZERO)
            printf ("Test #%d - luck\n", num);
        else
        {
            n_fail_tests++;
            printf ("Test #%d - fail: Solve_equation (%lg, %lg, %lg, %lg, %lg) == %d\n", num, test_ca, test_cb, test_cc, root1, root2, solution);
        }
        sol1 = sol2 = 0;
        root1 = root2 = 0;

    }

    return n_fail_tests;
}














