#include <Arduino.h> // Jeśli korzystasz z platformy Arduino, w przeciwnym razie zaimportuj odpowiednie biblioteki dla swojego mikrokontrolera

1 - definicja stałych dotyczących czasów 
2 - deklaracje tasków 
3 - utwórz uchwyty do tasków 


#define TASK_TIME_1 1000
#define TASK_TIME_2 1000



void Task1_Function(void *parametr); 
void Task2_function(void *parametr); 

TaskHandle_t Task1;
TaskHandle_t Task2; 


void setup ()
{
  xTaskCreate(Task1_Function,"Jestem TASK nr 1",128,NULL,&Task1) ;
  xTaskCreate(Task2_function,"Jestem TASK nr 2",128,NULL,&Task2) ;
}
