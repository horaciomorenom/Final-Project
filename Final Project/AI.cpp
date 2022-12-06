/*
 * Copyright 2022 University of Michigan EECS183
 *
 * AI.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "AI.h"
#include <cassert>
#include <string>

// This file is used only in the Reach, not the Core.
// You do not need to make any changes to this file for the Core

double getPointForecast(const BuildingState& buildingState, int floorID, int currentTime, int endTime) {

    int next_ang_inc = currentTime + (5 - (currentTime % 5));
    int anger_increase = 0;
    int points = 0;
    int people_on_floor = buildingState.floors[floorID].numPeople;
    int max_travel_time = max(9 - floorID, floorID);
    int people_exploded = 0;
    double ppt = 0; //points per tick

    if (endTime >= next_ang_inc) {
        anger_increase = 1;

        anger_increase += (endTime - next_ang_inc) / 5;
    }

    for (int i = 0; i < people_on_floor; i++) {
        points += MAX_ANGER - buildingState.floors[floorID].people[i].angerLevel;
        if (buildingState.floors[floorID].people[i].angerLevel + anger_increase >= 10) {
            points -= 10 - buildingState.floors[floorID].people[i].angerLevel; // take off points had they not exploded
            people_exploded += 1;
        }
    }

    points = points - (people_on_floor - people_exploded) * anger_increase; // take off points lost from people that didn't explode and increased anger

    if (buildingState.floors[floorID].hasUpRequest &&
        buildingState.floors[floorID].hasDownRequest) {

        points /= 2; // take avg points going one direction
    }

    points -= 10 * people_exploded; // Take 10 points per person blown up off


    return static_cast<double>(points) / (endTime - currentTime + max_travel_time);


}

bool getAlreadyServicing(const BuildingState& buildingState, int floorID, int elevID) { //Check if a floor is being servivced by other elevators

    for (int i = 0; i < 3; i++) {
        if (i != elevID) {
            if (buildingState.elevators[i].isServicing && buildingState.elevators[i].targetFloor == floorID) {
                return true;
            }
        }
    }

    return false;

}

int getTotalPeople(const BuildingState& buildingState) {
    int sum = 0;

    for (int i = 0; i < NUM_FLOORS; i++) {
        sum += buildingState.floors[i].numPeople;
    }

    return sum;
}

string getAIMoveString(const BuildingState& buildingState) {

    int availableElev[3];
    int numAvailableElev = 0;
    int bestElev = -1;
    int bestFloor;
    double max_points = 0;
    string move = "";

    if (buildingState.turn < 3) { // Wait for some turns 
        return "";
    }

    if (getTotalPeople(buildingState) == 0) { // If no people, pass 
        return "";
    }

    for (int i = 0; i < 3; i++) { // check for elevators that moving at the moment
        if (!buildingState.elevators[i].isServicing) {
            availableElev[numAvailableElev] = buildingState.elevators[i].elevatorId;
            numAvailableElev += 1;
        }
    }

    if (numAvailableElev == 0) { // Pass if no elevators are available. 
        return "";
    }

    double possiblePoints[3][10]; // Create array to store elevator-floor scores


    for (int j = 0; j < numAvailableElev; j++) {
        for (int i = 0; i < 10; i++) {

            int travel_time = abs(buildingState.elevators[availableElev[j]].currentFloor - i); // get distance from floor to elevator

            possiblePoints[j][i] = getPointForecast(buildingState, i, buildingState.turn, travel_time + buildingState.turn); // calculate and store scores
            
            cout << availableElev[j] << ' ' << i << " pts: " << possiblePoints[j][i] << endl;
        }
    }


    for (int j = 0; j < numAvailableElev; j++) {
        for (int i = 0; i < 10; i++) {
            double score = possiblePoints[j][i];
            if (score > max_points) {
                if (!getAlreadyServicing(buildingState, i, availableElev[j])) {
                    bestElev = availableElev[j];
                    bestFloor = i;
                    max_points = score;
                    cout << "best elevator, floor = " << bestElev << " " << bestFloor << endl;
                    cout << "max points = " << max_points << endl;
                }                   
            }
            if (score != 0) {
                cout << "e " << availableElev[j] << " floor " << i << " pts: " << score << endl;
            }

        }
    }

    if (bestElev == -1) { // Catch if there is nothing to do
        return "";
    }

    if (buildingState.elevators[bestElev].currentFloor == bestFloor) {
        move.append("e");
        move += to_string(bestElev);
        move.append("p");
        return move;
    }
    
    move.append("e");
    move += to_string(bestElev);
    move.append("f");
    move += to_string(bestFloor);

    return move;
    
}

string getAIPickupList(const Move& move, const BuildingState& buildingState, 
                       const Floor& floorToPickup) {

    int pickupList[MAX_PEOPLE_PER_FLOOR];
    int numPeople = floorToPickup.getNumPeople();
    int goingUp[MAX_PEOPLE_PER_FLOOR];
    int numGoingUp = 0;
    int goingDown[MAX_PEOPLE_PER_FLOOR];
    int numGoingDown = 0;
    string peopleToPickup = "";

    if (floorToPickup.getHasUpRequest() && floorToPickup.getHasDownRequest()) {
        for (int i = 0; i < numPeople; i++) {
            int request = floorToPickup.getPersonByIndex(i).getTargetFloor() -
                floorToPickup.getPersonByIndex(i).getCurrentFloor();
            if (request > 0) {
                goingUp[numGoingUp] = i;
                numGoingUp += 1;
            }
            else {
                goingDown[numGoingDown] = i;
                numGoingDown += 1;
            }
        }

        if (numGoingUp - numGoingDown > 0) { // More people going up
            for (int i = 0; i < numGoingUp; i++) {
                peopleToPickup += to_string(goingUp[i]);
            }
            return peopleToPickup;
        }
        else {
            for (int i = 0; i < numGoingDown; i++) {
                peopleToPickup += to_string(goingDown[i]);
            }
            return peopleToPickup;
        }

    }

    for (int i = 0; i < numPeople; i++) {
        peopleToPickup += to_string(i);
    }
    return peopleToPickup;

}

