#include <Adafruit_NeoPixel.h>
#define PIN 6 // номер порта к которому подключен модуль
#define count_led 12 // количество светодиодов 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(count_led, PIN, NEO_GRB + NEO_KHZ800); //first number change does distance between colors

const int buttonPin = D23; // вывод кнопки 0 нажата 1 нет
uint32_t last_millis; // переменные: последний  millis

uint8_t botton() {

  /* Обратите внимание!  При первом вызове этой функции last_millis = millis() в Setup
    потом в last_millis будет запоминаться прошедшее время для нового отсчета в этой
      функции при
      выходе из функции */

  // Правильнее запоминать в самом начале этой функции  last_millis = millis()

  if (digitalRead(buttonPin) == 1) { //если кнопка не нажата,
    last_millis = millis();             //то запоминаем время и
    return 0;
  }             //выход из функции с возвратом кода 0

  /* запоминать прошедшее время для нового отсчета  не следует при выходе из функции,
      потому что будет сильно отставать от millis()
            т.е last_millis = millis() в то время как millis() увеличивает свое значение
            в loop или в другой функции
            до вызова botton() соответственно всегда будет millis() больше last_millis

    /* Получается, в данном коде, для корректной работы перед вызовом botton() нужно
            запоминать текущее время last_millis = millis(), иначе значение millis() будет больше
      и условие не сработает
      if (last_millis+300 > millis()) */

  //предполагаем, что кнопка нажата
  delay(30); // * приостановить программу на 30 миллисекунд
  // это будет программное подавление дребезга кнопки * /
  /* в цикле while подождать пока не будет отжата а кнопка,
            но кнопка  может быть нажата сколько угодно долго */
  while (digitalRead(buttonPin) == 0);
  delay(30); /* приостановить программу на 30 миллисекунд это будет программное подавление
                           дребезга после отжатия кнопки */
  //Кнопка уже отжата, delay - лишнее
  //поэтому  это условие не сработает, еще 2 х delay(30) дадут задержку 60 миллисекунд

  if (last_millis + 65 > millis()) { // ложное срабатывание
    //Serial.println(millis()-last_millis);
    last_millis = millis();
    return 0;
  }

  //не правильное условие, что если last_millis+300 > millis() будет меньше
  if (last_millis + 300 > millis()) { // короткое нажатие меньше 0.30 сек
    //Serial.println(millis()-last_millis);
    last_millis = millis();
    return 1;
  }
  //Serial.println(millis()-last_millis);
  last_millis = millis(); // длинное нажатие больше 0.30 сек
  return 2;
};

void setup()
{
  strip.begin();      //инициализация ленты
  strip.show();
  Serial.begin(9600); // Запускаем последовательный порт
  pinMode(buttonPin, INPUT_PULLUP); // вывод на ввод с подтягивающим резистром
  last_millis = millis();
}

void loop()
{
  switch (botton()) {
    case 1:
      Serial.println("Правый поворот");
      turnRight();
      break;
    case 2:
      Serial.println("Левый поворот");
      turnLeft();
      break;
  }

}
void turnRight() {
  for (int j = 0; j < 3; j++) {  // 3 раза зажигаем и гасим светодиоды
    // включаем светодиоды
    for (int i = 0; i < count_led + 1; i++) {       //count_led = количество светодиодов
      strip.setPixelColor(i, strip.Color(255, 150, 0));      //последовательно , от 0 до 11 зажигаем i-й светодиод желтым цветом
      delay(30);          //задержка между зажиганием светодиода
      strip.show(); //горим на ленте
    }
    for (int i = 0; i < count_led + 1; i++) {   //послдовательно "гасим" светодиоды
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.show();
      delay(30);
    }
  }
}
void turnLeft() {
  for (int j = 0; j < 3; j++) {  // 3 раза зажигаем и гасим светодиоды
    // включаем светодиоды
    for (int i = 0; i < count_led; i++) {       //count_led = количество светодиодов
      strip.setPixelColor(count_led - i, strip.Color(255, 150, 0));      //последовательно , от 0 до 11 зажигаем i-й светодиод желтым цветом
      delay(30);          //задержка между зажиганием светодиода
      strip.show(); //горим на ленте
    }
    for (int i = 0; i < count_led; i++) {   //послдовательно "гасим" светодиоды
      strip.setPixelColor(count_led - i, strip.Color(0, 0, 0));
      strip.show();
      delay(30);
    }
  }
}
