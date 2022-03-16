/*
 a game of (random) darts
*/

#include <FPT.h>

int main()
{
  double swidth, sheight;
  double q;
  double point[2];
  int k; // counter
  int darts; //dots
  char words[100];
  int ptct[8]; //array for different slots on target
  double distance; //find where dart landed from origin
  int x, y;
  double dist[10]; // array to save distance of each dart
  int fakescore;
  int sum = 0;
  srand48(time(NULL));

  //graphical tasks
  swidth = 400;
  sheight = 400;
  G_init_graphics(swidth, sheight);

  //draw the target
  for (k=175; k>=25; k=k-50)
  {
    G_rgb(1, 0, 0);
    G_circle(200, 200, k);
  }
  for(k=150; k>=25; k=k-50)
  {
    G_rgb(0, 0, 1);
    G_circle(200, 200, k);
  }

  //print value for each target loop, unfortunately i could not figure out
  // a loop so i had to type out each spot :,)
  G_rgb(0.4, 0.2, 0.1);
  G_draw_string("10", 192, 193);
  G_rgb(0.4, 0.2, 0.1);
  G_draw_string("9", 193, 230);
  G_draw_string("9", 230, 193);
  G_draw_string("9", 160, 193);
  G_draw_string("9", 193, 160);
  G_rgb(0.4, 0.2, 0.1);
  G_draw_string("8", 193, 255);
  G_draw_string("8", 255, 193);
  G_draw_string("8", 135, 193);
  G_draw_string("8", 193, 135);
  G_rgb(0.4, 0.2, 0.1);
  G_draw_string("7", 193, 280);
  G_draw_string("7", 280, 193);
  G_draw_string("7", 110, 193);
  G_draw_string("7", 193, 110);
  G_rgb(0.4, 0.2, 0.1);
  G_draw_string("6", 193, 305);
  G_draw_string("6", 305, 193);
  G_draw_string("6", 85, 193);
  G_draw_string("6", 193, 85);
  G_rgb(0.4, 0.2, 0.1);
  G_draw_string("5", 193, 330);
  G_draw_string("5", 330, 193);
  G_draw_string("5", 60, 193);
  G_draw_string("5", 193, 55);
  G_rgb(0.4, 0.2, 0.1);
  G_draw_string("4", 193, 355);
  G_draw_string("4", 365, 193);
  G_draw_string("4", 35, 193);
  G_draw_string("4", 193, 30);
  G_rgb(0.4, 0.2, 0.1);
  G_draw_string("3", 193, 380);
  G_draw_string("3", 390, 193);
  G_draw_string("3", 15, 193);
  G_draw_string("3", 193, 10);

  //draw random dots (dart)
  for(darts = 1; darts<11; darts++)
  {
    //pause before each dart
    q = G_wait_key();
    //random dart
    G_rgb(0, 0, 0);
    x = 400*drand48();
    y = 400*drand48();
    G_fill_circle(x, y, 5);
    //compute Distance
    distance = sqrt((200-x)*(200-x)+(200-y)*(200-y));
    //change array to save the distance
    dist[darts-1] = distance;


    //fill array with zeros
    for(k=0; k<=7; k++)
    {
      ptct[k]=0;
    }
    //fake score
    fakescore = fabs(floor(distance/25)-10);
    ptct[fakescore]++;
    sum = sum + fakescore;

    //make white rectangle for words to sit on
    G_rgb(1, 1, 1);
    G_fill_rectangle(0, 380, 120, 40);
    //create and print words we want
    G_rgb(0, 0, 0);
    sprintf(words, "Points: %d", sum);
    G_draw_string(words, 0,380);
  }

  //white rectangle
  G_rgb(1, 1, 1);
  G_fill_rectangle(120, 190, 175, 40);
  //prints the final score in the middle of the target
  G_rgb(0, 0, 0);
  sprintf(words, "Final Score:%d!", sum);
  G_draw_string(words, 140, 200);

  // close graphics after mouse is clicked
  q = G_wait_click(point);
  G_close();
}
