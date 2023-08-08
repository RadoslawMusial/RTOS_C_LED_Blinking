#include <Arduino_FreeRTOS.h> 
#include <task.h>
#include <semphr.h>
//1 - definicja stałych dotyczących czasów 
//2 - deklaracje tasków 
//3 - utwórz uchwyty do tasków 

const int ledPIN = 13; 
#define TASK_TIME_1 1000
#define TASK_TIME_2 1000



void Task1_Function(void *parametr); 
void Task2_function(void *parametr); 
SemaphoreHandle_t Led_semaphor;  // Semafor dla diody led 

TaskHandle_t Task1;
TaskHandle_t Task2; 


void setup ()
{
  Serial.begin(9600); 
pinMode(ledPIN,OUTPUT) ; // pin diody ustawiony jako wyjście 
Led_semaphor = xSemaphoreCreateBinary(); 

xSemaphoreGive(Led_semphor); 


  xTaskCreate(Task1_Function," TASK nr 1",128,NULL,2,&Task1) ;
  xTaskCreate(Task2_function," TASK nr 2",128,NULL,1,&Task2) ;

 
}


void Task1_Function(void *pvParametrs)
{
  while (1) 
  {
    xSemaphoreTake(Led_semaphor,500) ; 

    digitalWrite(ledPIN,1) ; 
    vTaskDelay(pdMS_TO_TICKS(1000)); 
    
    digitalWrite(ledPIN,0) ; 

    xSemaphoreGive(Led_semaphor,1000); 

    vTaskDelay(1000) ; 
  }
}


void Task2(void *Parametrs)
{
  while{
  xSemaphoreTake(Led_semaphor,300) ; 

  digitalWrite(ledPIN,1) ; 
  vTaskDelay(200) ;

  digitalWrite(ledPIN,0) ; 
  vTaskDelay(300); 

  xSemaphoreGive(Led_semaphor, portMAX_DELAY) ; 
  }
}


//int main ()
//{
//  xTaskCreate(Task1_Function," TASK nr 1",128,NULL,2,&Task1) ;
//  xTaskCreate(Task2_function," TASK nr 2",128,NULL,1,&Task2) ;
//  vTaskStartScheduler(); 
//  return 0 ; 
//}
