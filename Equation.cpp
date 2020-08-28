#include <stdio.h>
#include <math.h>
#include <assert.h>

//-----------------------------------------------------------------------------

int const INFINITELY            = -1;
int const NOROOTS               = -2;
int const BEFORE_CHECK          = NAN;
double const ERROR              = 0.0000001;
double const BEFORE_DETERMINING = NAN;

//-----------------------------------------------------------------------------

int CompareZero (double number);

int Linear_equation (double coeff_a, double coeff_b, double* result);

int Quadratic_equation (double coeff_a, double coeff_b, double coeff_c, double* result1, double* result2);

void Solve_equation (double coeff_a, double coeff_b, double coeff_c, int* solutions, double* result1, double* result2);

void Checking_coeff (double* coeff_a, double* coeff_b, double* coeff_c);

//-----------------------------------------------------------------------------

int main()
   {
   printf ("# Solution of a quadratic equation\n"
           "# 27.08.2020\n\n");
   printf ("# Enter coefficients a, b, c: ");

   double coeff_a = BEFORE_DETERMINING, coeff_b = BEFORE_DETERMINING, coeff_c = BEFORE_DETERMINING;
   Checking_coeff (&coeff_a, &coeff_b, &coeff_c);
//   scanf ("%lg %lg %lg", &coeff_a, &coeff_b, &coeff_c);
//   printf ("%lg %lg %lg", coeff_a, coeff_b, coeff_c);

   double result1 = BEFORE_DETERMINING, result2 = BEFORE_DETERMINING;

   int solutions = NOROOTS;
   Solve_equation (coeff_a, coeff_b, coeff_c, &solutions, &result1, &result2);

   switch (solutions)
      {
      case 0:
              printf ("No roots\n");
              break;

      case 1:
              printf ("root: %lg\n", result1);
              break;

      case 2:
              printf ("root 1: %lg, root 2: %lg\n", result1, result2);
              break;

      case INFINITELY:
                       printf ("root - any number");
                       break;

      default:
               printf ("main(): data entry error");
               return 1;
               break;
      }

   return 0;
   }

//-----------------------------------------------------------------------------

int CompareZero (double number)
   {
   if (number < -ERROR)
      {
      return -1;   //---number < 0
      }

   if (fabs(number) < ERROR)
      {
      return 0;   //---number == 0
      }

   return 1;   //---number>0
   }

//-----------------------------------------------------------------------------

int Linear_equation (double coeff_a, double coeff_b, double* result)   //---equation ax + b = 0
   {
   if (CompareZero (coeff_a) == 0 && CompareZero (coeff_b) == 0)
      {
      return INFINITELY;
      }

   //---Now not INFINITELY

   if (CompareZero (coeff_a) == 0)
      {
      return 0;   //---b != 0
      }

   *result = -coeff_b / coeff_a;   //---a != 0
   return 1;
   }

//-----------------------------------------------------------------------------

int Quadratic_equation (double coeff_a, double coeff_b, double coeff_c, double* result1, double* result2)   //---equation ax^2 + bx + c = 0
   {
   double diskr = coeff_b*coeff_b - 4*coeff_a*coeff_c;

   if (CompareZero (diskr) == -1)
      {
      return 0;
      }

   if (CompareZero (diskr) == 0)
      {
      *result1 = *result2 = -coeff_b / (2*coeff_a);
      return 1;
      }

      *result1 = (-coeff_b + sqrt (diskr)) / (2 * coeff_a);
      *result2 = (-coeff_b - sqrt (diskr)) / (2 * coeff_a);
      return 2;
    }

//-----------------------------------------------------------------------------

void Solve_equation (double coeff_a, double coeff_b, double coeff_c, int* solutions, double* result1, double* result2)
   {
   assert (isfinite (coeff_a));
   assert (isfinite (coeff_b));
   assert (isfinite (coeff_c));
   assert (coeff_a != NULL);
   assert (coeff_b != NULL);
   assert (coeff_c != NULL);

   if (CompareZero (coeff_a) == 0)
      {
      *solutions = Linear_equation (coeff_b, coeff_c, result1);
      }
   else
      {
      *solutions = Quadratic_equation (coeff_a, coeff_b, coeff_c, result1, result2);
      }
   }

//-----------------------------------------------------------------------------

void Checking_coeff (double* coeff_a, double* coeff_b, double* coeff_c)
   {
   while (true)
      {
      if (scanf ("%lg %lg %lg/n", coeff_a, coeff_b, coeff_c) != 3)
         {
         printf ("Incorrect values. Re-enter:\n");
         fflush (stdin);
         }
      else
         {
         return;
         }
      }
   }
