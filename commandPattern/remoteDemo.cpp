#include <iostream>
#include <sstream>
#include <vector>
#include <typeinfo>

using namespace std;

class Light
{
private:
    string name;
public:
    Light(string name) {
        this->name = name;
    }
    void on() {
        cout << name << " Light is On\n";
    }
    void off() {
        cout << name << " Light is Off\n";
    }
};

class GarageDoor
{
private:
    string name;
public:
    GarageDoor(string name) {
        this->name = name;
    }
    void up() {
        cout << "Garage Door is Open\n";
    }
    void down() {
        cout << "Garage Door is Close\n";
    }
    void stop() {}
    void lightOn() {}
    void lightOff() {}
};

class Stereo
{
private:
    string name;
public:
    Stereo(string name) {
        this->name = name;
    }
    void on() {
        cout << name << " Stereo is On\n";
    }
    void off() {
        cout << name << " Stereo is Off\n";
    }
    void setCd() {
        cout << name << " Stereo set for CD input\n";
    }
    void setDvd() {}
    void setRadio() {}
    void setVolume(unsigned int volume) {
        cout << name << " Stereo Volume set " << volume << endl;
    }
};

enum class Speed {OFF, LOW, MEDIUM, HIGH};

class CeilingFan
{
private:
    string name;
    Speed speed;
public:
    CeilingFan(string name) {
        this->name = name;
        speed = Speed::OFF;
    }
    void high() {
        speed = Speed::HIGH;
        cout << name << " CeilingFan is on High\n";
    }
    void medium() {
        speed = Speed::MEDIUM;
        cout << name << " CeilingFan is on Medium\n";
    }
    void low() {
        speed = Speed::LOW;
    }
    void off() {
        speed = Speed::OFF;
        cout << name << " CeilingFan is Off\n";
    }
    Speed getSpeed() {
        return speed;
    }
};

class Command
{
public:
    virtual void execute() {}
    virtual void undo() {}
};

class NoCommand : public Command
{
public:
    virtual void execute() {}
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
    virtual void undo() {
        light->off();
    }
};
class LightOffCommand : public Command
{
private:
    Light* light;
public:
    LightOffCommand(Light* light) {
        this->light = light;
    }
    virtual void execute() {
        light->off();
    }
    virtual void undo() {
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
class GarageDoorCloseCommand : public Command
{
private:
    GarageDoor* garageDoor;
public:
    GarageDoorCloseCommand(GarageDoor* garageDoor) {
        this->garageDoor = garageDoor;
    }
    virtual void execute() {
        garageDoor->down();
    }
};

class StereoOnCommand : public Command
{
private:
    Stereo* stereo;
public:
    StereoOnCommand(Stereo* stereo) {
        this->stereo = stereo;
    }
    virtual void execute() {
        stereo->on();
        stereo->setCd();
        stereo->setVolume(11);
    }
};

class StereoOffCommand : public Command
{
private:
    Stereo* stereo;
public:
    StereoOffCommand(Stereo* stereo) {
        this->stereo = stereo;
    }
    virtual void execute() {
        stereo->off();
    }
};

class CeilingFanOnCommand : public Command
{
private:
    CeilingFan* ceilingFan;
    Speed prevSpeed;
public:
    CeilingFanOnCommand(CeilingFan* ceilingFan) {    
        this->ceilingFan = ceilingFan;
    }
    virtual void execute() {
        prevSpeed = ceilingFan->getSpeed();
        ceilingFan->high();
    }
    virtual void undo() {
        switch (prevSpeed)
        {
        case Speed::HIGH :
            ceilingFan->high();
            break;
        case Speed::MEDIUM :
            ceilingFan->medium();
            break;
        case Speed::LOW :
            ceilingFan->low();
            break;
        case Speed::OFF :
            ceilingFan->off();
            break;      
        default:
            break;
        }
    }
};
class CeilingFanMediumCommand : public Command
{
private:
    CeilingFan* ceilingFan;
    Speed prevSpeed;
public:
    CeilingFanMediumCommand(CeilingFan* ceilingFan) {    
        this->ceilingFan = ceilingFan;
    }
    virtual void execute() {
        prevSpeed = ceilingFan->getSpeed();
        ceilingFan->medium();
    }
    virtual void undo() {
        switch (prevSpeed)
        {
        case Speed::HIGH :
            ceilingFan->high();
            break;
        case Speed::MEDIUM :
            ceilingFan->medium();
            break;
        case Speed::LOW :
            ceilingFan->low();
            break;
        case Speed::OFF :
            ceilingFan->off();
            break;      
        default:
            break;
        }
    }
};

class CeilingFanOffCommand : public Command
{
private:
    CeilingFan* ceilingFan;
    Speed prevSpeed;
public:
    CeilingFanOffCommand(CeilingFan* ceilingFan) {
        this->ceilingFan = ceilingFan;
    }
    virtual void execute() {
        prevSpeed = ceilingFan->getSpeed();
        ceilingFan->off();
    }
        virtual void undo() {
        switch (prevSpeed)
        {
        case Speed::HIGH :
            ceilingFan->high();
            break;
        case Speed::MEDIUM :
            ceilingFan->medium();
            break;
        case Speed::LOW :
            ceilingFan->low();
            break;
        case Speed::OFF :
            ceilingFan->off();
            break;      
        default:
            break;
        }
    }
};

class MacroCommand : public Command
{
private:
    vector<Command*> commands;
public:
    MacroCommand(vector<Command*> commands) {
        this->commands = commands;
    }
    virtual void execute() {
        for (auto command : commands) {
            command->execute();
        }
    }
    virtual void undo() {
        for (auto command : commands) {
            command->undo();
        }
    }
};

class RemoteControl
{
private:
    vector<Command*> onCommands;
    vector<Command*> offCommands;
public:
    RemoteControl() {
        Command* noCommand = new NoCommand();
        for (int i =0; i<7; i++) {
            onCommands.push_back(noCommand);
            offCommands.push_back(noCommand);
        }
    }
    void setCommand(int solt, Command* onCommand, Command* offCommand) {
        onCommands[solt] = onCommand;
        offCommands[solt] = offCommand;
    }
    void onButtonWasPressed(int solt) {
        onCommands[solt]->execute();
    }
    void offButtonWasPressed(int solt) {
        offCommands[solt]->execute();
    }
    string toString() {
        ostringstream ostr;
        ostr << "\n------------------- Remote ------------------\n";
        for (int i=0; i<onCommands.size(); i++){
            ostr << "[slot " << i << "] " << typeid(*onCommands[i]).name() <<
            "\t" << typeid(*offCommands[i]).name() << endl;
        }
        return ostr.str();
    }
};

class RemoteControlWithUndo
{
private:
    vector<Command*> onCommands;
    vector<Command*> offCommands;
    Command* undoCommand;
public:
    RemoteControlWithUndo() {
        Command* noCommand = new NoCommand();
        for (int i =0; i<7; i++) {
            onCommands.push_back(noCommand);
            offCommands.push_back(noCommand);
        }
        undoCommand = noCommand;
    }
    void setCommand(int solt, Command* onCommand, Command* offCommand) {
        onCommands[solt] = onCommand;
        offCommands[solt] = offCommand;
    }
    void onButtonWasPressed(int solt) {
        onCommands[solt]->execute();
        undoCommand = onCommands[solt];
    }
    void offButtonWasPressed(int solt) {
        offCommands[solt]->execute();
        undoCommand = offCommands[solt];
    }
    void undoButtonWasPushed() {
        undoCommand->undo();
    }
    string toString() {
        ostringstream ostr;
        ostr << "\n------------------- Remote ------------------\n";
        for (int i=0; i<onCommands.size(); i++){
            ostr << "[slot " << i << "] " << typeid(*onCommands[i]).name() <<
            "\t" << typeid(*offCommands[i]).name() << endl;
        }
        ostr << "[undo] " << typeid(*undoCommand).name() << endl;
        return ostr.str();
    }
};

int main() {
    RemoteControlWithUndo* remoteControl = new RemoteControlWithUndo();
    Light* livingRoomLight = new Light("Living Room");
    Light* kitchenLight = new Light("Kitchen");
    CeilingFan* ceilingFan = new CeilingFan("Living Room");
    GarageDoor* garageDoor = new GarageDoor("");
    Stereo* stereo = new Stereo("Living Room");

    LightOnCommand* livingRoomLightOn = new LightOnCommand(livingRoomLight);
    LightOffCommand* livingRoomLightOff = new LightOffCommand(livingRoomLight);
    LightOnCommand* kitchenLightOn = new LightOnCommand(kitchenLight);
    LightOffCommand* kitchenLightOff = new LightOffCommand(kitchenLight);

    CeilingFanOnCommand* ceilingFanOn = new CeilingFanOnCommand(ceilingFan);
    CeilingFanMediumCommand* ceilingFanMedium = new CeilingFanMediumCommand(ceilingFan);
    CeilingFanOffCommand* ceilingFanOff = new CeilingFanOffCommand(ceilingFan);

    GarageDoorOpenCommand* garageDoorOpen = new GarageDoorOpenCommand(garageDoor);
    GarageDoorCloseCommand* garageDoorDown = new GarageDoorCloseCommand(garageDoor);

    StereoOnCommand* steroOnWithCD = new StereoOnCommand(stereo);
    StereoOffCommand* steroOff = new StereoOffCommand(stereo);

    vector<Command*> partyOn = { livingRoomLightOn, steroOnWithCD, ceilingFanOn, kitchenLightOn};
    vector<Command*> partyOff = { livingRoomLightOff, steroOff, ceilingFanOff, kitchenLightOff};
    MacroCommand* partyOnMacro = new MacroCommand(partyOn);
    MacroCommand* partyOffMacro = new MacroCommand(partyOff);

    remoteControl->setCommand(0, livingRoomLightOn, livingRoomLightOff);
    remoteControl->setCommand(1, kitchenLightOn, kitchenLightOff);
    remoteControl->setCommand(2, garageDoorOpen, garageDoorDown);
    remoteControl->setCommand(3, steroOnWithCD, steroOff);
    remoteControl->setCommand(4, ceilingFanOn, ceilingFanOff);
    remoteControl->setCommand(5, ceilingFanMedium, ceilingFanOff);
    remoteControl->setCommand(6, partyOnMacro, partyOffMacro);

    cout << remoteControl->toString() << endl;

    remoteControl->onButtonWasPressed(0);
    remoteControl->offButtonWasPressed(0);
    cout << remoteControl->toString() << endl;
    remoteControl->undoButtonWasPushed();

    remoteControl->offButtonWasPressed(0);
    remoteControl->onButtonWasPressed(0);
    cout << remoteControl->toString() << endl;
    remoteControl->undoButtonWasPushed();

    remoteControl->onButtonWasPressed(1);
    remoteControl->offButtonWasPressed(1);
    remoteControl->onButtonWasPressed(2);
    remoteControl->offButtonWasPressed(2);
    remoteControl->onButtonWasPressed(3);
    remoteControl->offButtonWasPressed(3);

    remoteControl->onButtonWasPressed(5);
    remoteControl->offButtonWasPressed(5);
    cout << remoteControl->toString() << endl;
    remoteControl->undoButtonWasPushed();

    remoteControl->onButtonWasPressed(4);
    cout << remoteControl->toString() << endl;
    remoteControl->undoButtonWasPushed();

    cout << remoteControl->toString() << endl;
    cout << "\n--- Pushing Macro On ---\n";
    remoteControl->onButtonWasPressed(6);
    cout << "\n--- Pushing Macro Off ---\n";
    remoteControl->offButtonWasPressed(6);
    cout << remoteControl->toString() << endl;
    remoteControl->undoButtonWasPushed();

    return 0;
}