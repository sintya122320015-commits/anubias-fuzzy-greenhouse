#include <Fuzzy.h>
#include "DHT.h"

// ===== PIN =====
#define DHTPIN 4
#define DHTTYPE DHT22

#define FAN_PIN 18
#define MIST_PIN 19

DHT dht(DHTPIN, DHTTYPE);

Fuzzy *fuzzy = new Fuzzy();

void setup() {

Serial.begin(115200);
dht.begin();

pinMode(FAN_PIN, OUTPUT);
pinMode(MIST_PIN, OUTPUT);


// ===== INPUT SUHU =====
FuzzyInput *temperature = new FuzzyInput(1);

FuzzySet *dingin = new FuzzySet(18,20,20,22);
FuzzySet *normal = new FuzzySet(22,25,25,28);
FuzzySet *panas = new FuzzySet(28,30,32,35);

temperature->addFuzzySet(dingin);
temperature->addFuzzySet(normal);
temperature->addFuzzySet(panas);

fuzzy->addFuzzyInput(temperature);


// ===== INPUT KELEMBAPAN =====

FuzzyInput *humidity = new FuzzyInput(2);

FuzzySet *kering = new FuzzySet(60,70,70,80);
FuzzySet *nyaman = new FuzzySet(80,85,85,90);
FuzzySet *tinggi = new FuzzySet(90,95,100,100);

humidity->addFuzzySet(kering);
humidity->addFuzzySet(nyaman);
humidity->addFuzzySet(tinggi);

fuzzy->addFuzzyInput(humidity);


// ===== OUTPUT KIPAS =====

FuzzyOutput *fan = new FuzzyOutput(1);

FuzzySet *fanLow = new FuzzySet(0,50,50,100);
FuzzySet *fanMed = new FuzzySet(80,120,120,180);
FuzzySet *fanHigh = new FuzzySet(160,200,255,255);

fan->addFuzzySet(fanLow);
fan->addFuzzySet(fanMed);
fan->addFuzzySet(fanHigh);

fuzzy->addFuzzyOutput(fan);


// ===== RULE 1 =====

FuzzyRuleAntecedent *ifColdDry = new FuzzyRuleAntecedent();
ifColdDry->joinWithAND(dingin,kering);

FuzzyRuleConsequent *thenLow = new FuzzyRuleConsequent();
thenLow->addOutput(fanLow);

FuzzyRule *rule1 = new FuzzyRule(1, ifColdDry, thenLow);
fuzzy->addFuzzyRule(rule1);

}


void loop() {

float suhu = dht.readTemperature();
float hum = dht.readHumidity();

fuzzy->setInput(1,suhu);
fuzzy->setInput(2,hum);

fuzzy->fuzzify();

float fanPWM = fuzzy->defuzzify(1);

analogWrite(FAN_PIN,fanPWM);

Serial.print("Suhu: ");
Serial.println(suhu);

Serial.print("Kelembapan: ");
Serial.println(hum);

delay(2000);

}
