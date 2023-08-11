#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

const int ledPIN = 13;
const int ledPIN_2 = 11;
#define TASK_TIME_1 1000
#define TASK_TIME_2 1100

void Task1_Function(void *parametr);
void Task2_function(void *parametr);
SemaphoreHandle_t Led_semaphor;

TaskHandle_t Task1;
TaskHandle_t Task2;

void setup() {
  Serial.begin(9600);
  pinMode(ledPIN, OUTPUT);
  pinMode(ledPIN_2, OUTPUT);
  Led_semaphor = xSemaphoreCreateBinary();
  xSemaphoreGive(Led_semaphor);

  xTaskCreate(Task1_Function, "TASK nr 1", 128, NULL, 1, &Task1);
  xTaskCreate(Task2_function, "TASK nr 2", 128, NULL, 2, &Task2);

  vTaskStartScheduler();
}

void loop() {
  // Pusta pętla w loop, ponieważ obsługa zadań jest realizowana przez FreeRTOS
}

void Task1_Function(void *pvParametrs) {
  while (1) {
    xSemaphoreTake(Led_semaphor, portMAX_DELAY);

    digitalWrite(ledPIN, 1);
    digitalWrite(ledPIN_2, 0);
    vTaskDelay(TASK_TIME_1);

    digitalWrite(ledPIN, 0);
    xSemaphoreGive(Led_semaphor);
    vTaskDelay(TASK_TIME_1);
  }
}

void Task2_function(void *pvParametrs) {
  while (1) {
    xSemaphoreTake(Led_semaphor, portMAX_DELAY);

    digitalWrite(ledPIN, 0);
    digitalWrite(ledPIN_2, 1);
    vTaskDelay(TASK_TIME_2);

    digitalWrite(ledPIN_2, 0);
    xSemaphoreGive(Led_semaphor);
    vTaskDelay(TASK_TIME_2);
  }
}
