#include <stdio.h>
#include <math.h>

int const BESKONECHNOMNOGO = 3;

//-----------------------------------------------------------------------------

int Poisk_kornei (double a, double b, double c, double* x1, double* x2)
{
   if (a==0)
   {
      if (b==0)
      {
         if (c==0)
         {
            return BESKONECHNOMNOGO;
         }
         else
         {
            return 0;
         }
      }
      else /*b != 0*/
      {
         *x1 = -c/b;
         return 1;
      }
   }
   else /*a != 0*/
   {
      double diskriminant = b*b-4.0*a*c;
      //printf ("%lg\n", diskriminant);

      if (diskriminant < 0)
      {
         return 0;
      }
      else if (diskriminant == 0)
           {
              *x1 = *x2 = -b/(2*a);
              return 1;
           }
           else
           {
              *x1 = (-b + sqrt (diskriminant))/(2*a);
              *x2 = (-b - sqrt (diskriminant))/(2*a);
              return 2;
           }
   }
}

//-----------------------------------------------------------------------------

int main()
{
   printf ("# Rehenie kvadratnogo uravnenia\n"
           "# 27.08.2020\n\n");
   printf ("#Vvedite a, b, c: ");

   double a=0, b=0, c=0;
   scanf ("%lg %lg %lg", &a, &b, &c);

   double x1=0, x2=0;
   int Korni = Poisk_kornei (a, b, c, &x1, &x2);

   switch (Korni)
   {
      case 0: printf ("Net kornei\n");
              break;

      case 1: printf ("x = %lg\n", x1);
              break;

      case 2: printf ("x1 = %lg, x2 = %lg\n", x1, x2);
              break;

      case BESKONECHNOMNOGO: printf ("x - luboe chislo");
                             break;

      default: printf ("main(): ohibka vvoda dannyh");
               return 1;
               break;
   }

   return 0;
}
