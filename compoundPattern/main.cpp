#include "MallardDuck.cpp"
#include "RedheadDuck.cpp"
#include "OtherDuck.cpp"
#include "GooseAdapter.cpp"
#include "QuackCounter.cpp"
#include "AbstractDuckFactory.cpp"
#include "Flock.cpp"

class DuckSimulator
{
public:
    void simulate(QuackableInterface* duck) {
        duck->quack(); 
    }

    void simulate(AbstractDuckFactory* duckFactory) {
        QuackableInterface* mallardDuck = duckFactory->createMallardDuck();
        QuackableInterface* redheadDuck = duckFactory->createRedheadDuck();
        QuackableInterface* duckCall = duckFactory->createDuckCall();
        QuackableInterface* rubberDuck = duckFactory->createRubberDuck();
        QuackableInterface* gooseDuck = new GooseAdapter(new Goose());
        cout << "\nDuck Simulator: With Composite - Flocks\n";

        Flock* flockOfDucks = new Flock();
        flockOfDucks->add(redheadDuck);
        flockOfDucks->add(duckCall);
        flockOfDucks->add(rubberDuck);
        flockOfDucks->add(gooseDuck);

        Flock* flockOfMallards = new Flock();
        QuackableInterface* mallardOne = duckFactory->createMallardDuck();
        QuackableInterface* mallardTwo = duckFactory->createMallardDuck();
        QuackableInterface* mallardThree = duckFactory->createMallardDuck();
        QuackableInterface* mallardFour = duckFactory->createMallardDuck();
        flockOfMallards->add(mallardOne);
        flockOfMallards->add(mallardTwo);
        flockOfMallards->add(mallardThree);
        flockOfMallards->add(mallardFour);
        flockOfDucks->add(flockOfMallards);

        // cout << "\nDuck Simulator: Whole Flock Simulation\n";
        // simulate(flockOfDucks);

        // cout << "\nDuck Simulator: Mallard Flock Simulation\n";
        // simulate(flockOfMallards);

        cout << "\nDuck Simulator: With Observer\n";
        Quackologist* quackologist = new Quackologist();
        flockOfDucks->registerObserver(quackologist);
        simulate(flockOfDucks);

        cout << "\nThe ducks quacked " << QuackCounter::getQuacks() << " times\n";
    }
};


int main() {
    DuckSimulator* simulator = new DuckSimulator();
    AbstractDuckFactory* duckFactory = new CountingDuckFactory();
    simulator->simulate(duckFactory);
}