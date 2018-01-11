#include <iostream.h>
#include <string.h>

class movie
 {
   public:
     char name[64];
     char first_star[64];
     char second_star[64]; 
     void show_movie(void);
     void initialize(char *name, char *first, char *second);
 };

void movie::show_movie(void)
 {
   cout << "Movie name: " << name << endl;
   cout << "Starring: " << first_star << " and " << second_star << endl << endl;
 }

void movie::initialize(char *movie_name, char *first, char *second)
 {
   strcpy(name, movie_name);
   strcpy(first_star, first);
   strcpy(second_star, second);
 }

void main(void)
 {
   movie fugitive, sleepless;

   fugitive.initialize("The Fugitive", "Harrison Ford", "Tommy Lee Jones");
   sleepless.initialize("Sleepless in Seattle", "Tom Hanks", "Meg Ryan");
   fugitive.show_movie();
   sleepless.show_movie();
 }
