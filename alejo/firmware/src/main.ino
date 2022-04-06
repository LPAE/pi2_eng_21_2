#include<LiquidCrystal_I2C.h>
#include <DHT.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>


enum {
    HUMIDITY,
    TEMPERATURE
};
enum Sonar{
    RISE,
    FALL
};
//MCU ============================
#define MCU_FREQ            16000000.0
//GAS sensor =====================
#define GAS_PIN             A0
//DHT11 ==========================
#define DHT_PIN             2
#define DHT_TYPE            DHT11
//BUZZER =========================
#define BUZZER_PIN          6
#define DISABLE_BUZZER      pinMode(BUZZER_PIN, INPUT)
#define ENABLE_BUZZER       pinMode(BUZZER_PIN, OUTPUT)
//SONAR ==========================
#define TRIGGER_SONAR_PIN   13  
#define TRIGGER_PORT        PORTD
#define TRIGER_AVR_PIN      3
#define ECHO_SONAR_PIN      12  //Not change
//PIR ============================
#define PIR_PIN             24
//GROUND HUMIDITY ================
#define GROUNDHUMIDITY_PIN  11
//PUMP ===========================
#define PUMP_PIN            12
//SERVO ==========================
#define SERVO_PIN           5

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHT_PIN, DHT_TYPE);

volatile uint32_t timer_miliseconds;
volatile uint8_t timer_run_machine;
volatile uint16_t sonar_time[2];
volatile uint8_t sonar_ready;

struct Sensor
{
    float sum;
    uint16_t samples;
    float avg;
    uint8_t triggered;
};

struct BinSensor
{
    uint16_t sum;
    uint16_t samples;
    uint8_t avg;
    uint8_t triggered;
};

Sensor gas;
Sensor dht11[2];
Sensor sonar;
BinSensor pir;
BinSensor groundhumidity;

void clear_sensor(Sensor *sensor)
{
    sensor->sum = 0;
    sensor->samples = 0;
}

void clear_bin_sensor(BinSensor *sensor)
{
    sensor->sum = 0;
    sensor->samples = 0;
}

void gas_read(void)
{
    gas.sum += analogRead(GAS_PIN);
    gas.samples ++;
}

void gas_calculate_avg(void)
{
    if (!gas.samples)
        gas_read();
    gas.avg = gas.sum/gas.samples;
    clear_sensor(&gas);
}

void dht11_read(void)
{
    dht11[HUMIDITY].sum += dht.readHumidity();
    dht11[HUMIDITY].samples ++;
    dht11[TEMPERATURE].sum += dht.readTemperature();
    dht11[TEMPERATURE].samples ++;
}

void dht11_calculate_avg(void)
{
    if (!dht11[HUMIDITY].samples || !dht11[TEMPERATURE].samples)
        dht11_read();
    dht11[HUMIDITY].avg = dht11[HUMIDITY].sum/dht11[HUMIDITY].samples;
    clear_sensor(&dht11[HUMIDITY]);
    dht11[TEMPERATURE].avg = dht11[TEMPERATURE].sum/dht11[TEMPERATURE].samples;
    clear_sensor(&dht11[TEMPERATURE]);
}

void task_gas(void)
{
    static uint32_t gas_alarm_milis = timer_miliseconds + 50000;
    gas_calculate_avg();

    if(gas.avg >= 200){
        gas_alarm_milis = timer_miliseconds;
        gas.triggered = 1;
    }

    if((timer_miliseconds - gas_alarm_milis) >= 50000){
        gas.triggered = 0;
    }
}

void task_buzzer(void)
{
    static float step = +10;
    static float freq = 500;

    freq += step;
    if(freq >= 500)
        step = -50;
    if(freq <= 300)
        step = 20;

    if(gas.triggered){
        tone(6,freq);
        ENABLE_BUZZER;
    }
    else{
        noTone(6);
        DISABLE_BUZZER;
    }
}

void task_humidity_temp(void)
{
    static uint8_t open = 0;
    dht11_calculate_avg();
}

void sonar_read(void)
{
    //calculate delta time of sonar
    float duration = (float)sonar_time[Sonar::FALL] - (float)sonar_time[Sonar::RISE];
    //convert duration in cm
    sonar.sum += abs(duration * 0.073972);
    sonar.samples ++;
}

void sonar_calculate_avg(void)
{
    if (!sonar.samples)
        return;
    sonar.avg = sonar.sum/sonar.samples;
    clear_sensor(&sonar);
}

void task_sonar(void)
{
    sonar_calculate_avg();
    if(sonar.avg <= 20){
        sonar.triggered = 1;
    } else{
        sonar.triggered = 0;
    }
}

void task_lcd(void)
{
    static uint32_t backlight_milis = timer_miliseconds;
	static uint8_t	backlight_cpl_clk = 0; 
    if(sonar.triggered){
        lcd.backlight();
        backlight_milis = timer_miliseconds;
    }

    if((timer_miliseconds - backlight_milis) >= 5000){
        lcd.noBacklight();
    }

    lcd.setCursor(0,0);
    lcd.print("T: ");
    lcd.print(dht11[TEMPERATURE].avg);
    lcd.print("H: ");
    lcd.print(dht11[HUMIDITY].avg);

    if(gas.triggered){
        if(++backlight_cpl_clk >= 2){
			backlight_cpl_clk = 0;
			lcd.cplBacklight();
		}
        backlight_milis = timer_miliseconds;    // disable backlight auto-disable
        lcd.setCursor(0,1);
        lcd.print("FUGA DE GAS!!");
    } else{
        lcd.setCursor(0,1);
        lcd.print("             ");
    }

}

void task_serial(void)
{
    Serial.print("Temp: ");
    Serial.print(dht11[TEMPERATURE].avg);
    Serial.print(" | Hum");
    Serial.print(dht11[HUMIDITY].avg);
    
    Serial.print(" | pir: ");
    Serial.print(pir.avg);

    Serial.print(" | humidity");
    Serial.print(groundhumidity.triggered);

	Serial.print(" | sonar");
	Serial.print(sonar.avg);

    Serial.print(" | gas ");
    Serial.println(gas.avg);


}

void task_pir(void)
{
    static uint32_t pir_milis = timer_miliseconds;
    pir_calculate_avg();
    if(pir.avg){
        pir_milis = timer_miliseconds;
        pir.triggered = 1;
    } 
    if((timer_miliseconds - pir_milis) >= 7000){
        pir.triggered = 0;
    }
}

void pir_read(void)
{
    pir.sum += digitalRead(PIR_PIN);
    pir.samples ++;
}

void groundhumidity_read(void)
{
    groundhumidity.sum += digitalRead(GROUNDHUMIDITY_PIN);
    groundhumidity.samples ++;
}

void pir_calculate_avg(void)
{
    pir.avg = (pir.sum >= pir.samples/2) ? 1 : 0;
    clear_bin_sensor(&pir);
}

void groundhumidity_calculate_avg(void)
{
    groundhumidity.avg = (groundhumidity.sum >= groundhumidity.samples/2) ? 1 : 0;
    clear_bin_sensor(&groundhumidity);
}

void task_servo(void)
{
    if(gas.triggered && pir.triggered){
        servo_write(180);
    } else{
        servo_write(0);
    }
}

void task_pump(void)
{
    static uint32_t pump_milis = timer_miliseconds;

    if(!groundhumidity.triggered){
        pump_milis = timer_miliseconds;
        digitalWrite(PUMP_PIN, true);
    } 
    if((timer_miliseconds - pump_milis) >= 15000){
		digitalWrite(PUMP_PIN, false);
    }
}

void task_groundhumidity(void)
{
    static uint32_t groundhumidity_milis = timer_miliseconds;
    groundhumidity_calculate_avg();
    groundhumidity.triggered = 0;
    if(groundhumidity.avg){
        groundhumidity.triggered = 1;
    }
}

void servo_write(uint8_t angle)
{
    OCR3A = 5*angle+95;
}

void init_regs(void)
{
    cli();
    TCCR1A = 0;
    TCCR1B = (1<<WGM12) |(1<<CS10); //CTC Prescaler 1
    TIMSK1 = (1<<OCIE1A);
    OCR1A = 7999;   //1ms

    TCCR3A = (1<<COM3A1) | (1<< WGM31); //PWM Phase Correct
    TCCR3B = (1<<WGM33) | (1<<CS31) | (1<<CS30); //Prescaler 64
    TIMSK3 = 0;
    DDRE = 0xff;
    pinMode(5,OUTPUT);
    ICR3 = 4998;
    servo_write(15);

    EIMSK = (1<<INT2);
    EICRA = (1<<ISC20) | (1<<ISC21);

    sei();
}

void run_machine(void)
{
    static uint32_t humidity_temp_milis = timer_miliseconds;
    static uint32_t gas_milis = timer_miliseconds;
    static uint32_t buzzer_milis = timer_miliseconds;
    static uint32_t sonar_trigger_milis = timer_miliseconds;
    static uint32_t sonar_task_milis = timer_miliseconds;
    static uint32_t lcd_milis = timer_miliseconds;
    static uint32_t serial_milis = timer_miliseconds;
    static uint32_t pir_milis = timer_miliseconds;
    static uint32_t servo_milis = timer_miliseconds;
    static uint32_t pump_milis = timer_miliseconds;
    static uint32_t groundhumidity_milis = timer_miliseconds;

    

    if ((timer_miliseconds - humidity_temp_milis) >= 500){
        humidity_temp_milis = timer_miliseconds;
        task_humidity_temp();
    }
    if ((timer_miliseconds - gas_milis) >= 250){
        gas_milis = timer_miliseconds;
        task_gas();
    }

    if ((timer_miliseconds - buzzer_milis) >= 50){
        buzzer_milis = timer_miliseconds;
        task_buzzer();  
    }

    if ((timer_miliseconds - lcd_milis) >= 500){
        lcd_milis = timer_miliseconds;
        task_lcd();  
    }

    if ((timer_miliseconds - sonar_trigger_milis)>=50){
        bitSet(TRIGGER_PORT, TRIGER_AVR_PIN); //trigger Sonar
        if ((timer_miliseconds - sonar_trigger_milis)>=60){ //wait 10ms
            sonar_trigger_milis = timer_miliseconds;
            bitClear(TRIGGER_PORT, TRIGER_AVR_PIN); //trigger Sonar
        }
    }

    if ((timer_miliseconds - sonar_task_milis) >= 500){
        sonar_task_milis = timer_miliseconds;
        task_sonar();  
    }

    if ((timer_miliseconds - serial_milis) >= 567){
        serial_milis = timer_miliseconds;
        task_serial();
    }

    if ((timer_miliseconds - pir_milis) >= 500){
        pir_milis = timer_miliseconds;
        task_pir();
    }

    if ((timer_miliseconds - servo_milis) >= 500){
        servo_milis = timer_miliseconds;
        task_servo();
    }

    if ((timer_miliseconds - pump_milis) >= 100){
        pump_milis = timer_miliseconds;
        task_pump();
    }

    if ((timer_miliseconds - groundhumidity_milis) >= 500){
        groundhumidity_milis = timer_miliseconds;
        task_groundhumidity();
    }

}

void setup()
{
    lcd.init();
    lcd.clear();         
    lcd.backlight(); 
    lcd.setContrast(100);
    Serial.begin(9600);
    dht.begin();
    init_regs();
    bitSet(DDRJ, PIN1);
    pinMode(ECHO_SONAR_PIN, INPUT);
    pinMode(TRIGGER_SONAR_PIN, OUTPUT);
    pinMode(PIR_PIN, INPUT);
    pinMode(PUMP_PIN, OUTPUT);
    DISABLE_BUZZER;
    noTone(6);
}
void loop()
{
    dht11_read();
    gas_read();
    pir_read();
    groundhumidity_read();

    if(sonar_ready)
        sonar_read();

    if(timer_run_machine){
        run_machine();
        timer_run_machine = 0;
    }

}
ISR(TIMER1_COMPA_vect)
{
    timer_miliseconds ++;
    timer_run_machine = 1;
}

ISR(INT2_vect)
{
    //capture rising edge of echo signal
    if(bitRead(EICRA,ISC20))
    {
        sonar_time[Sonar::RISE] = TCNT3;
        sonar_ready = 0;
        bitClear(EICRA,ISC20);
    }else
    //capture falling edge of echo signal
    {
        sonar_time[Sonar::FALL] = TCNT3;
        sonar_ready = 1;
        bitSet(EICRA,ISC20);
    }
}
