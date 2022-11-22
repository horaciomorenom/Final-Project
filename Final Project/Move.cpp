/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move()
{
    // non-default constructor
    // initialize to default values (changes them below)
    int charConvert = 48;
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;

    // pass move
    if (commandString == "")
    {
        isPass = true;
    }
    // game move quit
    else if (commandString == "Q" || commandString == "q")
    {
        isQuit = true;
    }
    // game move save
    else if (commandString == "S" || commandString == "s")
    {
        isSave = true;
    }
    // service or pickup move
    // requires commandString is valid string, so if gotten this far,
    //  must be "e, elevator ID, f/p, targetFloor if f"
    else if (commandString.at(0) == 'e')
    {
        // set elevator id, there are 3 elevators per building
        elevatorId = static_cast<int>(commandString.at(1)) - charConvert;
        // pickup move
        if (commandString.length() == 3 && commandString.at(2) == 'p')
        {
            isPickup = true;
        }
        // service move
        else if (commandString.at(2) == 'f')
        {

                targetFloor = static_cast<int>(commandString.at(3)) - charConvert;
        }
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const
{
    if (isPass || isQuit || isSave)
    {
        return true;
    }
    else if (elevatorId >= 0 && elevatorId < NUM_ELEVATORS && !(elevators[elevatorId].isServicing()))
    {
        if (isPickup)
        {
            return true;
        }
        else if (targetFloor >= 0 && targetFloor < NUM_FLOORS && targetFloor != elevators[elevatorId].getCurrentFloor())
        {
            return true;
        }
        return false;
    }
    return false;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor)
{
    // set numPeopleToPickup and totalSatisfaction to 0
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    int charConvert = 48;

    // integer to store the most extreme floor of those being picked up
    int furthestFloor = currentFloor;
    
    // loop through all the people being picked up
    for (int i = 0; i < pickupList.length(); i++)
    {
        // adds the indices specified in pickupList to peopleToPickup
        peopleToPickup[i] = pickupList.at(i) - charConvert;
        numPeopleToPickup += 1;

        // adds satisfaction gained from each person picked up to totalSatisfaction
        totalSatisfaction += (MAX_ANGER - pickupFloor.getPersonByIndex(peopleToPickup[i]).getAngerLevel());

        // ensures furthestFloor is the most extreme floor of those being picked up

        if (abs(currentFloor - pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor()) > (abs(currentFloor - furthestFloor)))
        {
            furthestFloor = pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor();
        }
    }

    // sets targetFloor to what was determined to be the furthest
    targetFloor = furthestFloor;
    return;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
