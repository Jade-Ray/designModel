#include <iostream>

using namespace std;

class PopcornPopper
{
public:
    void on() {
        cout << "Popcorn Popper on\n";
    }
    void off() {
        cout << "Popcorn Popper off\n";
    }
    void pop() {
        cout << "Popcorn Popper popping popcorn\n";
    }
    void toString() {}
};

class TheaterLights
{
public:
    void on() {
        cout << "Theater Ceiling Lights on\n";
    }
    void off() {}
    void dim(int t) {
        cout << "Theater Ceiling Lights dimming to " << t << "%\n";
    }
    void toString() {}
};

class Screen
{
public:
    void up() {
        cout << "Theater Screen goning up\n";
    }
    void down() {
        cout << "Theater Screen goning down\n";
    }
    void toString() {}
};

class Projector
{
public:
    void on() {
        cout << "Top-O-Line Projector on\n";
    }
    void off() {
        cout << "Top-O-Line Projector off\n";
    }
    void wideScreenMode() {
        cout << "Top-O-Line Projector in widescreen mode (16x9 aspect ratio)\n";
    }
    void toString() {}
};

class DvdPlayer
{
private:
    string dvd;
public:
    void on() {
        cout << "Top-O-Line DVD Player on\n";
    }
    void off() {
        cout << "Top-O-Line DVD Player off\n";
    }
    void play(string dvd) {
        this->dvd = dvd;
        cout << "Top-O-Line DVD Player playing \"" << dvd << "\"\n";
    }
    void stop() {
        cout << "Top-O-Line DVD Player stopped \"" << dvd << "\"\n";
    }
    void eject() {
        cout << "Top-O-Line DVD Player eject\n";
    }
};

class Amplifier
{
private:
    DvdPlayer* dvd;
public:
    void on() {
        cout << "Top-O-Line Amplifier on\n";
    }
    void off() {
        cout << "Top-O-Line Amplifier off\n";
    }
    void setDvd(DvdPlayer* dvd) {
        cout << "Top-O-Line Amplifier setting DVD player to Top-O-Line DVD Player\n";
    }
    void setSurroundSound() {
        cout << "Top-O-Line Amplifier surround sound on (5 speakers, 1 subwoofer)\n";
    }
    void setVolume(int t) {
        cout << "Top-O-Line Amplifier setting volume to " << t << endl;
    }
};

class CdPlayer
{
public:
    void on() {}
    void off() {}
    void pop() {}
    void toString() {}
};

class Tuner
{
public:
    void on() {}
    void off() {}
    void pop() {}
    void toString() {}
};

class HomeTheaterFacade
{
private:
    Amplifier* amp;
    Tuner* tuner;
    DvdPlayer* dvd;
    CdPlayer* cdPlayer;
    Projector* projector;
    TheaterLights* lights;
    Screen* screen;
    PopcornPopper* popper;
public:
    HomeTheaterFacade(Amplifier* amp, Tuner* tuner, DvdPlayer* dvd, CdPlayer* cdPlayer,
                Projector* projector, TheaterLights* lights, Screen* screen, PopcornPopper* popper) {
        this->amp = amp;
        this->cdPlayer = cdPlayer;
        this->dvd = dvd;
        this->lights = lights;
        this->popper = popper;
        this->projector = projector;
        this->screen = screen;
        this->tuner = tuner;
    }
    void watchMovie(string movie)  {
        cout << "Get ready to watch a movie...\n";
        popper->on();
        popper->pop();
        lights->dim(10);
        screen->down();
        projector->on();
        projector->wideScreenMode();
        amp->on();
        amp->setDvd(dvd);
        amp->setSurroundSound();
        amp->setVolume(5);
        dvd->on();
        dvd->play(movie);
    }
    void endMovie() {
        cout << "\nShutting movie theater down...\n";
        popper->off();
        lights->on();
        screen->up();
        projector->off();
        amp->off();
        dvd->stop();
        dvd->eject();
        dvd->off();
    }
};

int main() {
    Amplifier* amp = new Amplifier();
    Tuner* tuner = new Tuner();
    DvdPlayer* dvd = new DvdPlayer();
    CdPlayer* cdPlayer = new CdPlayer();
    Projector* projector = new Projector();
    TheaterLights* lights = new TheaterLights();
    Screen* screen = new Screen();
    PopcornPopper* popper = new PopcornPopper();
    HomeTheaterFacade* homeTheater = new HomeTheaterFacade(amp, tuner, dvd, cdPlayer, projector, lights, screen, popper);

    homeTheater->watchMovie("Raiders of the Lost Ark");
    homeTheater->endMovie();   
}