#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>
SemaphoreHandle_t Led_mutex; // Deklaracja mutexa
const int ledPIN_RED_TRAFFIC = 12;
const int ledPIN_YELLOW_TRAFFIC = 11;
const int ledPIN_GREEN_TRAFFIC = 10;
const int ledPIN_RED_PEDESTRIAN = 9;
const int ledPIN_GREEN_PEDESTRIAN = 8;
const int ledPIN_RED_TRAFFIC_2 = 4;
const int ledPIN_YELLOW_TRAFFIC_2 = 3;
const int ledPIN_GREEN_TRAFFIC_2 = 2;
const int ledPIN_GREEN_PEDESTRIAN_2 = A0;
const int ledPIN_RED_PEDESTRIAN_2 = A1;
#define TASK_TIME_1 1000
#define TASK_TIME_2 1100
SemaphoreHandle_t Led_semaphor;
SemaphoreHandle_t Led_semaphor_2;


void Task1_Function(void *parametr);
void Task2_function(void *parametr);
void Task3_function(void *parametr);  // Dodane wywołanie Task3_function
void Task4_Function(void *parametr);

TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;
TaskHandle_t Task4;

void setup() {
  Serial.begin(9600);

  pinMode(ledPIN_RED_TRAFFIC, OUTPUT);
  pinMode(ledPIN_YELLOW_TRAFFIC, OUTPUT);
  pinMode(ledPIN_GREEN_TRAFFIC, OUTPUT);
  pinMode(ledPIN_RED_PEDESTRIAN, OUTPUT);
  pinMode(ledPIN_GREEN_PEDESTRIAN, OUTPUT);
  pinMode(ledPIN_GREEN_TRAFFIC_2, OUTPUT);
  pinMode(ledPIN_YELLOW_TRAFFIC_2, OUTPUT);
  pinMode(ledPIN_RED_TRAFFIC_2, OUTPUT);
  pinMode(ledPIN_GREEN_PEDESTRIAN_2, OUTPUT);
  pinMode(ledPIN_RED_PEDESTRIAN_2, OUTPUT);
  Led_semaphor = xSemaphoreCreateBinary();
  Led_semaphor_2 = xSemaphoreCreateBinary();
  xSemaphoreGive(Led_semaphor);

  xTaskCreate(Task1_Function, "TASK nr 1", 128, NULL, 1, &Task1);
  xTaskCreate(Task2_function, "TASK nr 2", 128, NULL, 2, &Task2);
  xTaskCreate(Task3_function, "TASK nr 3", 128, NULL, 1, &Task3);
  xTaskCreate(Task4_function, "TASK nr 4", 128, NULL, 2, &Task4);

  vTaskStartScheduler();
}

void loop() {

}

void Task1_Function(void *pvParametrs) {
  while (1) {
    xSemaphoreTake(Led_semaphor, portMAX_DELAY);

    digitalWrite(ledPIN_GREEN_PEDESTRIAN, 0);
    digitalWrite(ledPIN_RED_TRAFFIC, 1);


    vTaskDelay(100) ;
    digitalWrite(ledPIN_RED_TRAFFIC, 0);
    digitalWrite(ledPIN_YELLOW_TRAFFIC, 1);
    digitalWrite(ledPIN_RED_PEDESTRIAN, 1);
    vTaskDelay(100) ;
    digitalWrite(ledPIN_YELLOW_TRAFFIC, 0);
    digitalWrite(ledPIN_GREEN_TRAFFIC, 1);
    ////
    vTaskDelay(100) ;
    digitalWrite(ledPIN_RED_PEDESTRIAN, 1);
    vTaskDelay(1000) ;
    xSemaphoreGive(Led_semaphor);

    vTaskDelay(1000) ;

  }
}

void Task2_function(void *param)
{
  while (1) {

    xSemaphoreTake(Led_semaphor, portMAX_DELAY) ;
    digitalWrite(ledPIN_RED_PEDESTRIAN, 1);
    vTaskDelay(100) ;
    digitalWrite(ledPIN_GREEN_PEDESTRIAN, 0);
    digitalWrite(ledPIN_GREEN_TRAFFIC, 0);
    digitalWrite(ledPIN_YELLOW_TRAFFIC, 1);
    vTaskDelay(100);
    digitalWrite(ledPIN_YELLOW_TRAFFIC, 0);

    digitalWrite(ledPIN_RED_TRAFFIC, 1);
    digitalWrite(ledPIN_RED_PEDESTRIAN, 0);
    digitalWrite(ledPIN_GREEN_PEDESTRIAN, 1);
    vTaskDelay(1200) ;
    xSemaphoreGive(Led_semaphor) ;
    vTaskDelay(1000) ;
  }
}

void Task3_function(void *param)
{
  while (1)
  {
    xSemaphoreTake(Led_semaphor_2, 1000);
    digitalWrite(ledPIN_GREEN_TRAFFIC_2, 0);
    digitalWrite(ledPIN_GREEN_PEDESTRIAN_2, 0);
    digitalWrite(ledPIN_RED_PEDESTRIAN_2, 1);
    digitalWrite(ledPIN_YELLOW_TRAFFIC_2, 1);
    vTaskDelay(100);
    digitalWrite(ledPIN_YELLOW_TRAFFIC_2, 0);
    digitalWrite(ledPIN_GREEN_TRAFFIC_2, 0);
    digitalWrite(ledPIN_RED_TRAFFIC_2, 1);
    vTaskDelay(1200) ;
    xSemaphoreGive(Led_semaphor_2);
    vTaskDelay(1000);
  }
}

void Task4_function(void*param)
{
  while (1)
    ///
  {
    digitalWrite(ledPIN_RED_PEDESTRIAN_2, 0);
    digitalWrite(ledPIN_RED_TRAFFIC_2, 0);
    digitalWrite(ledPIN_YELLOW_TRAFFIC_2, 1);
    vTaskDelay(100);
    digitalWrite(ledPIN_YELLOW_TRAFFIC_2, 0);
    digitalWrite(ledPIN_GREEN_TRAFFIC_2, 1);
    digitalWrite(ledPIN_GREEN_PEDESTRIAN_2, 1);


    vTaskDelay(1200) ;
    xSemaphoreGive(Led_semaphor_2);
    vTaskDelay(1000);
  }
}
