#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int const INFINITELY = -1;

//-----------------------------------------------------------------------------

int Linear_equation (double coeff_a, double coeff_b, double** result)   //------equation ax + b = 0
{
   if (coeff_a == 0 && coeff_b == 0)
   {
      return INFINITELY;
   }

   if (coeff_a == 0)   //------------------------------------------------------Now not INFINITELY
   {
      return 0;   //-----------------------------------------------------------b != 0
   }

   **result = -coeff_b / coeff_a;   //------------------------------------------a != 0
   return 1;
}

//-----------------------------------------------------------------------------

int Quadratic_equation (double coeff_a, double coeff_b, double coeff_c, double** result1, double** result2)   // equation ax^2 + bx + c = 0
{
   double diskr = coeff_b * coeff_b - 4 * coeff_a * coeff_c;

   if (diskr < -0.0000001)
   {
      return 0;
   }
   if (abs (diskr) < 0.0000001)
   {
      **result1 = **result2 = -coeff_b / (2 * coeff_a);
      return 1;
   }
      **result1 = (-coeff_b + sqrt (diskr)) / (2 * coeff_a);
      **result2 = (-coeff_b - sqrt (diskr)) / (2 * coeff_a);
      return 2;
}

//-----------------------------------------------------------------------------

void Solve_equation (double coeff1, double coeff2, double coeff3, int* Solutions, double* result1, double* result2)
{
   if (abs (coeff1) < 0.0000001)
   {
      *Solutions = Linear_equation (coeff2, coeff3, &result1);
   }
   else
   {
      *Solutions = Quadratic_equation (coeff1, coeff2, coeff3, &result1, &result2);
   }
}

//-----------------------------------------------------------------------------

int main()
{
   printf ("# Solution of a quadratic equation\n"
           "# 27.08.2020\n\n");
   printf ("# Enter coefficients 1, 2, 3: ");

   double coeff1 = 0, coeff2 = 0, coeff3 = 0;
   scanf ("%lg %lg %lg", &coeff1, &coeff2, &coeff3);

   double result1 = 0, result2 = 0;

   int Solutions = 0;
   Solve_equation (coeff1, coeff2, coeff3, &Solutions, &result1, &result2);

   switch (Solutions)
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
