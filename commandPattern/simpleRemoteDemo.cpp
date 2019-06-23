#include <iostream>

using namespace std;

class Light
{
public:
    void on() {
        cout << "Light is On\n";
    }
    void off() {}
};

class GarageDoor
{
public:
    void up() {
        cout << "Garage Door is Open\n";
    }
    void down() {}
    void stop() {}
    void lightOn() {}
    void lightOff() {}
};

class Command
{
public:
    virtual void execute() {
        cout << "None\n";
    }
};

class LightOnCommand : public Command
{
private:
    Light* light;
public:
    LightOnCommand(Light* light) {
        this->light = light;
    }
    virtual void execute() {
        light->on();
    }
};

class GarageDoorOpenCommand : public Command
{
private:
    GarageDoor* garageDoor;
public:
    GarageDoorOpenCommand(GarageDoor* garageDoor) {
        this->garageDoor = garageDoor;
    }
    virtual void execute() {
        garageDoor->up();
    }
};

class SimpleRemoteControl
{
private:
    Command* slot;
public:
    SimpleRemoteControl() {}
    void setCommand(Command* command) {
        slot = command;
    }
    void buttonWasPressed() {
        slot->execute();
    }
};

int main() {
    SimpleRemoteControl* remote = new SimpleRemoteControl();
    Light* light = new Light();
    GarageDoor* garageDoor = new GarageDoor();
    LightOnCommand* lightOn = new LightOnCommand(light);
    GarageDoorOpenCommand* garageDoorOpen = new GarageDoorOpenCommand(garageDoor);

    remote->setCommand(lightOn);
    remote->buttonWasPressed();
    remote->setCommand(garageDoorOpen);
    remote->buttonWasPressed();
    return 0;
}