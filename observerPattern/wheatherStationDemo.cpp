#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

class Observer {
public:
    virtual void update(float temp, float humidity, float pressure){}
};

class Subject {
public:
    virtual void registerObserver(Observer *o){}
    virtual void removeObserver(Observer *o){}
    virtual void notifyObserver(){}
};

class DisplayElement {
public:
    virtual void display(){}
};

class WeatherData: public Subject {
private:
    vector<Observer *> observers;
    float temperature;
    float humidity;
    float pressure;

public:
    WeatherData() {
        observers.clear();
    }
    virtual void registerObserver(Observer *o) {
        observers.push_back(o);
    }
    virtual void removeObserver(Observer *o) {
        auto i = std::find(observers.begin(), observers.end(), o);
        if (i != observers.end()){
            observers.erase(i);
        }
    }
    virtual void notifyObserver() {
        for (auto observer : observers){
            observer->update(temperature, humidity, pressure);
        }
    }
    void measurementsChanged() {
        notifyObserver();
    }
    void setMeasurements(float temperature, float humidity, float pressure) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        measurementsChanged();
    }
};

class CurrentConditionsDisplay: public Observer, public DisplayElement {
private:
    float temperature;
    float humidity;
    Subject *weatherData;
public:
    CurrentConditionsDisplay(Subject *weatherData) {
        this->weatherData = weatherData;
        weatherData->registerObserver(this);
    }
    virtual void update(float temp, float humidity, float pressure) {
        this->temperature = temp;
        this->humidity = humidity;
        display();
    }
    virtual void display() {
        cout << "Current Conditions: " << temperature << "F degress and " << humidity << "% humidity" << endl; 
    }
};

class StatisticsDisplay: public Observer, public DisplayElement {
private:
    float temperatureAvg;
    float temperatureMax;
    float temperatureMin;
    Subject *weatherData;
public:
    StatisticsDisplay(Subject *weatherData) {
        this->weatherData = weatherData;
        weatherData->registerObserver(this);
    }
    virtual void update(float temp, float humidity, float pressure) {
        std::default_random_engine random(time(NULL));
        std::uniform_real_distribution<float> dis(0, 3);
        temperatureMax = temp + dis(random);
        temperatureMin = temp - dis(random);
        temperatureAvg = temp;
        display();
    }
    virtual void display() {
        cout << setiosflags(ios::fixed) << setprecision(1);
        cout << "Avg/Max/Min temperature = " << temperatureAvg << "/" << temperatureMax << "/" << temperatureMin << endl;
    }
};

class ForecastDisplay: public Observer, public DisplayElement {
private:
    string forecast;
    Subject *weatherData;
public:
    ForecastDisplay(Subject *weatherData) {
        this->weatherData = weatherData;
        weatherData->registerObserver(this);
    }
    virtual void update(float temp, float humidity, float pressure) {
        if (temp == 80) {
            forecast = "Improving weather on the way!";
        }else if (temp < 80) {
            forecast = "More of the same";
        }else{
            forecast = "Watch out for cooler, rainy weather";
        }
        display();
    }
    virtual void display() {
        cout << "Forecast: " << forecast << endl;
    }
};

int main() {
    WeatherData *weatherData = new WeatherData();

    CurrentConditionsDisplay *currentDisplay = new CurrentConditionsDisplay(weatherData);
    StatisticsDisplay *statisticsDisplay = new StatisticsDisplay(weatherData);
    ForecastDisplay *forecastDisplay = new ForecastDisplay(weatherData);

    weatherData->setMeasurements(80, 65, 30.4);
    cout << endl;
    weatherData->setMeasurements(82, 70, 29.2);
    cout << endl;
    weatherData->setMeasurements(78, 90, 29.2);
}