#include <iostream>
#include <fstream>
#include "Person.h"
#include "Elevator.h"
#include "Floor.h"
#include "Utility.h"
using namespace std;

void person_tests();

void elevator_tests();

void file_check();

void start_tests()
{
    person_tests();
    // elevator_tests();
    // file_check();
          
}
    
void person_tests()
{

    // initialize a person with targetFloor 5, anger 5

    Person p("0f0t5a5");
    
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 5" << endl;
    
    // simulate time being a multiple of TICKS_PER_ANGER_INCREASE
    
    bool exploded = p.tick(TICKS_PER_ANGER_INCREASE);
    
    cout << exploded << " Expected 0" << endl;
    
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;
    
    //simulate time not being a multiple
    
    p.tick(TICKS_PER_ANGER_INCREASE - 1);
    
    // no change
    
    cout << p.getTargetFloor() << " " << p.getAngerLevel() << " Expected 5 6" << endl;
    
    p.tick(TICKS_PER_ANGER_INCREASE); //7 after
    
    p.tick(TICKS_PER_ANGER_INCREASE); //8 after
    
    p.tick(TICKS_PER_ANGER_INCREASE); //9 after
    
    exploded = p.tick(TICKS_PER_ANGER_INCREASE);
    
    cout << exploded << " Expected 1" << endl;

    cout << "Creating new person: " << endl;

    Person p2("2f0t9a2");

    cout << p2.getTargetFloor() << " " << p2.getAngerLevel() << " Expected 9 2" << endl;

    bool exploded2 = p2.tick(TICKS_PER_ANGER_INCREASE);

    cout << exploded2 << " Expected 0" << endl;

    exploded2 = p2.tick(8 * TICKS_PER_ANGER_INCREASE);

    cout << exploded2 << " Expected 1" << endl;

    Person p3("3f0t2a9");

    cout << p3.getTargetFloor() << " " << p3.getAngerLevel() << " Expected 2 9" << endl;

    bool exploded3 = p3.tick(TICKS_PER_ANGER_INCREASE);

    cout << exploded3 << " Expected 1" << endl;

    Person p4("3f6t2a11");

    p4.print(cout);

    cout << " Expected f6t2a11" << endl;

    cout << p4.getTargetFloor() << " " << p4.getAngerLevel() << " Expected 2 11" << endl;

    cout << p4.getCurrentFloor() << " Expected 6" << endl;

    bool exploded4 = p4.tick(TICKS_PER_ANGER_INCREASE);

    cout << exploded3 << " Expected 1" << endl;

}

void elevator_tests()
{

    Elevator e1;

    e1.print(cout);

    e1.tick(TICKS_PER_ELEVATOR_MOVE);
    e1.print(cout);
    e1.tick(TICKS_PER_ELEVATOR_MOVE - 1);
    e1.print(cout);
    e1.tick(TICKS_PER_ELEVATOR_MOVE - 2);
    e1.print(cout);
    e1.tick(TICKS_PER_ELEVATOR_MOVE - 3);
    e1.print(cout);
    e1.tick(TICKS_PER_ELEVATOR_MOVE - 4);
    e1.print(cout);

    cout << e1.isServicing() << " Expected 0" << endl;

    e1.serviceRequest(2);

    e1.tick(TICKS_PER_ELEVATOR_MOVE);

    cout << e1.isServicing() << " Expected 1" << endl;

    Elevator e2;

    e2.setCurrentFloor(3);

    e2.serviceRequest(5);

    e2.tick(TICKS_PER_ELEVATOR_MOVE - 1);

    cout << e2.getCurrentFloor() << " Expected 3 " << endl;

    cout << e2.isServicing() << " Expected 1 " << endl;

    e2.tick(1);

    cout << e2.getCurrentFloor() << " Expected 4 " << endl;

    cout << e2.isServicing() << " Expected 1 " << endl;

    e2.tick(TICKS_PER_ELEVATOR_MOVE);

    cout << e2.getCurrentFloor() << " Expected 5 " << endl;

    cout << e2.isServicing() << " Expected 0 " << endl;


    return; 
}

void file_check()
{
    // open one of the text files that are part of the starter code
    ifstream ins;
    ins.open("new.in");
    // if the file was not in the correct directory, the stream state is fail
    if (ins.fail())
    {
        cout << "Could not open new.in" << endl;
    }
    else
    {
        cout << "Success! Text files are in the right directory." << endl;
    }
    return;
}

void test_floor() {

    cout << "Testing Floor class" << endl << endl;

    Floor f1;

    Person p1("1f2t5a0");

    f1.addPerson(p1, p1.getTargetFloor() - p1.getCurrentFloor());

}
