#include "homeservice.h"
#include "objects/election.h"
#include <TreeFrogModel>


void HomeService::index()
{
    // would a getByCriteria be better? 
    auto ongoingElections = Election::getOngoing();
    auto decidedElections = Election::getDecided();
    texport(ongoingElections);
    texport(decidedElections);
}
