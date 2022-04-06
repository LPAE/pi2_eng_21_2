
#include <DHT.h>
#include <Servo.h>
#include <MatrizLed.h>
#include <LiquidCrystal_I2C.h>

//
// Mapeamento de Hardware
//

// Water
#define WATER_SENSOR_PIN A1
// DTH-11
#define DHT11_PIN 2
// PIR-2
#define PIR_K_PIN 5
#define PIR_L_PIN 4
// Servo
#define SERVO_PIN 6
// Relay
#define RELAY_PIN 3
// MQ2
#define MQ2_PIN A0
// Matriz
#define MAX_DATA_PIN 51
#define MAX_CLK_PIN 52
#define MAX_CS_PIN 50
// HC-SR04
#define ULT_TRIGGER 18
#define ULT_ECHO 19
// Buzzer
#define BUZZER_PIN 7
// Alarm Control
#define ALARM_CONTROL_PIN 8

//
// Macros
//

#define BEGIN_TASK(delay)   static unsigned long lastRead = millis(); \
                            const unsigned int taskDelay = delay; \
                            if (millis() - lastRead > taskDelay)  \
                            { \
                                lastRead = millis();
#define END_TASK()          }

//
// Definições
//

// LCD Display
#define LCD_WIDTH 16
#define LCD_HEIGHT 2
#define LCD_I2C_ADDRES 0x27
// Display Infos
#define MINIMUM_DISTANCE_FROM_LCD 10
// Moisture
#define MOISTURE_BREAKDOWN_PERCENT 30
// Gas
#define GAS_BREAKDOWN_PERCENT 35

//
// Tipos abstratos
//

struct HouseData
{
    // Alarm Data
    bool RoomPresence;
    bool KitchenPresence;

    bool BuzzerActiveRoom;
    bool BuzzerActiveKitchen;

    // For living room alarm
    bool AlarmArmed = false;

    // For lcd control purpose
    bool ShowInfos;

    // Gas
    unsigned int GasPercent;

    // Garden infos
    int Temperature;
    int Humidity;
    unsigned int MoisturePercent;
} houseData;

//
// Globais
//

MatrizLed matriz;
DHT dht(DHT11_PIN, DHT11);
LiquidCrystal_I2C lcd(0x27, LCD_WIDTH, LCD_HEIGHT);
Servo windowServo;

//
// Forwarding declarations
//

void computeAlarm();
void computeWindow();
void computeMatrix();
void computeMoisture();
void computeLcdInfos();

void updateMq2();
void updatePirs();
void updateDht11();
void updateMoisture();
void updateUltrasonic();
void updateAlarmActivation();

void serialDebug();

void setup()
{
    Serial.begin(57600);

    // Starts DHT library
    dht.begin();

    // Starts LCD library
    lcd.init();
    lcd.backlight();

    // Starts Matriz library
    matriz.begin(MAX_DATA_PIN, MAX_CLK_PIN, MAX_CS_PIN, 1);
    matriz.rotar(false);

    // Attach windows servo to correct pin
    windowServo.attach(SERVO_PIN);

    // Pins mode definition
    pinMode(MQ2_PIN, INPUT);
    pinMode(ULT_ECHO, INPUT);
    pinMode(DHT11_PIN, INPUT);
    pinMode(PIR_K_PIN, INPUT);
    pinMode(PIR_L_PIN, INPUT);
    pinMode(WATER_SENSOR_PIN, INPUT);
    pinMode(ALARM_CONTROL_PIN, INPUT_PULLUP);

    pinMode(RELAY_PIN, OUTPUT);
    pinMode(SERVO_PIN, OUTPUT);
    pinMode(ULT_TRIGGER, OUTPUT);

    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
}

void loop()
{
    // Sensors update
    updateMq2();
    updatePirs();
    updateDht11();
    updateMoisture();
    updateUltrasonic();
    updateAlarmActivation();

    // Tasks update
    computeWindow();
    computeMatrix();
    computeMoisture();
    computeLcdInfos();

    // Debug
    serialDebug();

    // Alarm task
    computeAlarm();
}

// For debug purpose or visualization in Serial Monitor
void serialDebug()
{
    BEGIN_TASK(500)

    Serial.print("\033[2J");

    Serial.println("==================================================");
    Serial.print("RoomPresence: ");
    Serial.println(houseData.RoomPresence);
    Serial.print("KitchenPresence: ");
    Serial.println(houseData.KitchenPresence);
    Serial.print("BuzzerActiveRoom: ");
    Serial.println(houseData.BuzzerActiveRoom);
    Serial.print("BuzzerActiveKitchen: ");
    Serial.println(houseData.BuzzerActiveKitchen);
    Serial.print("AlarmArmed: ");
    Serial.println(houseData.AlarmArmed);
    Serial.print("GasPercent: ");
    Serial.println(houseData.GasPercent);
    Serial.print("Temperature: ");
    Serial.println(houseData.Temperature);
    Serial.print("Humidity: ");
    Serial.println(houseData.Humidity);
    Serial.print("MoisturePercent: ");
    Serial.println(houseData.MoisturePercent);
    Serial.print("ShowInfos: ");
    Serial.println(houseData.ShowInfos);

    if (houseData.BuzzerActiveKitchen && houseData.KitchenPresence)
        Serial.println("Janela Aberta!");
    else
        Serial.println("Janela Fechada!");

    END_TASK()
}

// Update the two PIR2 sensors
void updatePirs()
{
    BEGIN_TASK(100)

    houseData.RoomPresence = (digitalRead(PIR_L_PIN) == HIGH);
    houseData.KitchenPresence = (digitalRead(PIR_K_PIN) == HIGH);

    END_TASK()
}

// Update temperature and humidity from houseData usaing DHT11 sensor
void updateDht11()
{
    BEGIN_TASK(200)

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (!isnan(humidity) && !isnan(temperature))
    {
        houseData.Humidity = humidity;
        houseData.Temperature = temperature;
    } 

    END_TASK()
}

// Update Soil Moisture from houseData using soil water sensor
void updateMoisture()
{
    BEGIN_TASK(500)

    houseData.MoisturePercent = map(
        analogRead(WATER_SENSOR_PIN),
        0, 1023,
        0, 100
    );

    END_TASK()
}

// Update gas percent from houseData using mq2 sensor
void updateMq2()
{
    BEGIN_TASK(200)

    houseData.GasPercent = map(
        analogRead(MQ2_PIN),
        0, 1023,
        0, 100
    );

    END_TASK()
}

// Decide to show or not infos in lcd based on distance from HCSR-04 sensor
void updateUltrasonic()
{
    BEGIN_TASK(100)

    digitalWrite(ULT_TRIGGER, LOW);
    delayMicroseconds(5);
    digitalWrite(ULT_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULT_TRIGGER, LOW);

    float distance = pulseIn(ULT_ECHO, HIGH) * 0.017f;

    houseData.ShowInfos = (distance < MINIMUM_DISTANCE_FROM_LCD);

    END_TASK()
}

// Activate or deactivate living room alarm
// It would be interesting add debounce
void updateAlarmActivation()
{
    BEGIN_TASK(50)

    houseData.AlarmArmed = (digitalRead(ALARM_CONTROL_PIN) == LOW) ? !houseData.AlarmArmed : houseData.AlarmArmed;

    END_TASK()
}

// Checks if buzzer should be activated or not
void computeAlarm()
{
    BEGIN_TASK(50)

    static int step = 10;
    static unsigned int frequency = 500;

    if (frequency > 1000)
        step = -10;
    if (frequency < 500)
        step = 10;

    frequency += step;

    houseData.BuzzerActiveRoom = (houseData.AlarmArmed && houseData.RoomPresence);
    houseData.BuzzerActiveKitchen = (houseData.GasPercent > GAS_BREAKDOWN_PERCENT);
    
    if (houseData.BuzzerActiveKitchen || houseData.BuzzerActiveRoom)
        tone(BUZZER_PIN, frequency);
    else
    {
        noTone(BUZZER_PIN);
        digitalWrite(BUZZER_PIN, HIGH);
    }

    END_TASK()
}

// Window opening system
void computeWindow()
{
    BEGIN_TASK(100)

    if (houseData.BuzzerActiveKitchen && houseData.KitchenPresence)
        windowServo.write(90);
    else
        windowServo.write(0);

    END_TASK()
}

// Automatic watering system
void computeMoisture()
{
    BEGIN_TASK(500)

    if (houseData.MoisturePercent < MOISTURE_BREAKDOWN_PERCENT)
        digitalWrite(RELAY_PIN, LOW);
    else
        digitalWrite(RELAY_PIN, HIGH);

    END_TASK()
}

// Show infos in lcd based on current application context
void computeLcdInfos()
{
    BEGIN_TASK(50)

    lcd.clear();

    if (
        houseData.ShowInfos &&
        (!houseData.BuzzerActiveKitchen) &&
        (!houseData.BuzzerActiveRoom)
    )
    {
        lcd.backlight();
        lcd.setCursor(0, 0);
        lcd.print("Temperature: ");
        lcd.print(houseData.Temperature);
        lcd.setCursor(0, 1);
        lcd.print("Humidity: ");
        lcd.print(houseData.Humidity);
    }
    else
    {
        lcd.noBacklight();
    }

    if (houseData.BuzzerActiveKitchen)
    {
        lcd.backlight();
        lcd.setCursor(0, 0);
        lcd.print("*** PERIGO ***");
        lcd.setCursor(0, 1);
        lcd.print("VAZAMENTO - GAS");
    }

    if (houseData.BuzzerActiveRoom)
    {
        lcd.backlight();
        lcd.setCursor(0, 0);
        lcd.print("*** PERIGO ***");
        lcd.setCursor(0, 1);
        lcd.print("INTRUSO NA CASA");
    }

    END_TASK()
}

// In case of emergency show infos in led matrix
// 
// escribirFraseScroll f**k everithing with timing,
// when it's using it, the other tasks timings stops
// to works properly. Probably it uses delay inside 
void computeMatrix()
{
    BEGIN_TASK(100)

    matriz.borrar();

    if (houseData.BuzzerActiveKitchen)
    {
        matriz.escribirFraseScroll("FUGA DE GAS", 50);
    }
    else if (houseData.BuzzerActiveRoom)
    {
        matriz.escribirFraseScroll("INTRUSO NA CASA", 50);
    }

    END_TASK()
}
