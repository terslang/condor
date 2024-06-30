#include "pairwisecontestservice.h"
#include "ballotchoice.h"
#include "objects/pairwisecontest.h"
#include <TreeFrogModel>


void PairwiseContestService::index()
{
    auto pairwiseContestList = PairwiseContest::getAll();
    texport(pairwiseContestList);
}

void PairwiseContestService::show(int electionId)
{
    auto pairwiseContest = PairwiseContest::get(electionId);
    texport(pairwiseContest);
}

int PairwiseContestService::create(int electionId, const QString &optionAId, const QString &optionBId)
{
    int optionACount = BallotChoice::getOutrankingCount(optionAId, optionBId);
    int optionBCount = BallotChoice::getOutrankingCount(optionBId, optionAId);
    
    auto model = PairwiseContest::create(electionId, optionAId, optionBId, optionACount, optionBCount);

    if (model.isNull()) {
        QString error = "Failed to create.";
        texport(error);
        return -1;
    }

    QString notice = "Created successfully.";
    tflash(notice);
    return model.electionId();
}

void PairwiseContestService::edit(TSession& session, int electionId)
{
    // not implemented yet
}

int PairwiseContestService::save(THttpRequest &request, TSession &session, int electionId)
{
    // not implemented yet
}

bool PairwiseContestService::remove(int electionId)
{
    // not implemented yet
}

