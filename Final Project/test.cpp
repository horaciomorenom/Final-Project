#include <iostream>
#include <fstream>
#include "Person.h"
#include "Elevator.h"
#include "Floor.h"
#include "Move.h"
#include "Utility.h"
using namespace std;

void person_tests();

void elevator_tests();

void file_check();

void move_tests();

void start_tests()
{
    person_tests();
    elevator_tests();
    move_tests();
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

void move_tests()
{
    cout << endl << "Testing Move:" << endl;

    Elevator testElevator[NUM_ELEVATORS];
    Elevator elevatorZero;
    Elevator elevatorOne;
    Elevator elevatorTwo;
    
    testElevator[0] = elevatorZero;
    testElevator[1] = elevatorOne;
    testElevator[2] = elevatorTwo;
    

    // Move(commandString)
    cout << "Testing Move non-default constructor, Quit Move:" << endl;
    Move quitMoveTest("Q");
    cout << endl << "Expecting 1, actual: " << quitMoveTest.isQuitMove();
    Move quitMoveTest2("q");
    cout << endl << "Expecting 1, actual: " << quitMoveTest2.isQuitMove();

    cout << endl << "Testing Move non-default constructor, Save Move:" << endl;
    Move saveMoveTest("S");
    cout << endl << "Expecting 1, actual: " << saveMoveTest.isSaveMove();
    Move saveMoveTest2("s");
    cout << endl << "Expecting 1, actual: " << saveMoveTest2.isSaveMove();

    cout << endl << "Testing Move non-default constructor, Pass Move:" << endl;
    Move passMoveTest("");
    cout << endl << "Expecting 1, actual: " << passMoveTest.isPassMove();

    cout << endl << "Testing Move non-default constructor, Pickup Move:" << endl;
    Move pickupMoveTest("e1p");
    cout << endl << "Expecting 1, actual: " << pickupMoveTest.isPickupMove();
    Move pickupMoveTest2("e2p");
    cout << endl << "Expecting 1, actual: " << pickupMoveTest2.isPickupMove();

    cout << endl << "Testing Move non-default constructor, Service Move 10th floor:" << endl;
    Move serviceMoveTest10("e1f10");
    cout << endl << "Expecting 9, actual: " << serviceMoveTest10.getTargetFloor();

    cout << endl << "Testing Move non-default constructor, Service Move 1 digit floors:" << endl;
    Move serviceMoveTest("e1f2");
    cout << endl << "Expecting 1, actual: " << serviceMoveTest.getTargetFloor();
    Move serviceMoveTest5("e2f5");
    cout << endl << "Expecting 4, actual: " << serviceMoveTest5.getTargetFloor();

    cout << endl << "Testing Move non-default constructor, Service Move not other move types" << endl;
    cout << endl << "Expecting 10000, actual: " << serviceMoveTest.getTargetFloor()
         << serviceMoveTest.isPassMove() << serviceMoveTest.isQuitMove() << serviceMoveTest.isSaveMove()
         << serviceMoveTest.isPickupMove();

    // isValidMove
    cout << endl << "Testing Move isValidMove(): " << endl;
    // invalid cases
    cout << "Invalid Moves:" << endl;
    Move invalidElevator("r");
    cout << endl << "Expecting 0, actual: " << invalidElevator.isValidMove(testElevator);
    Move invalidElevator2("e5p");
    cout << endl << "Expecting 0, actual: " << invalidElevator2.isValidMove(testElevator);
    Move invalidServiceMove("e1d");
    cout << endl << "Expecting 0, actual: " << invalidServiceMove.isValidMove(testElevator);
    Move invalidTargetFloor("e1f11");
    cout << endl << "Expecting 0, actual: " << invalidTargetFloor.isValidMove(testElevator);
    Move invalidTargetFloor2("e2f-2");
    cout << endl << "Expecting 0, actual: " << invalidTargetFloor2.isValidMove(testElevator);

    // valid cases
    cout << endl << "Valid Moves:" << endl;
    cout << endl << "Expecting 1, actual: " << serviceMoveTest.isValidMove(testElevator);
    cout << endl << "Expecting 1, actual: " << serviceMoveTest10.isValidMove(testElevator);
    cout << endl << "Expecting 1, actual: " << pickupMoveTest.isValidMove(testElevator);
    cout << endl << "Expecting 1, actual: " << passMoveTest.isValidMove(testElevator);
    cout << endl << "Expecting 1, actual: " << saveMoveTest.isValidMove(testElevator);
    cout << endl << "Expecting 1, actual: " << quitMoveTest2.isValidMove(testElevator);

    // cout << endl << "Testing Move setPeopleToPickup: " << endl;
    Floor floor1;
    Person person1("7f5t9a3");
    Person person2("2f5t7a1");
    floor1.addPerson(person1,0);
    floor1.addPerson(person2,0);
    string pickList = "01";
    Move defaultMove("e0f9");

    defaultMove.setPeopleToPickup(pickList, 5, floor1);
    cout << endl;
    cout << defaultMove.getTotalSatisfaction() << endl;
    cout << defaultMove.getTargetFloor() << endl;
    cout << defaultMove.getNumPeopleToPickup() << endl;

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
