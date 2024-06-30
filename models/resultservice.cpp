#include "resultservice.h"
#include "objects/election.h"
#include "objects/option.h"
#include "pairwisecontest.h"
#include <TreeFrogModel>
#include <numeric>
#include <qglobal.h>

void ResultService::show(int electionId)
{
    auto election = Election::get(electionId);
    auto optionList = Option::getByElectionId(electionId);
    auto pairwiseContestList = PairwiseContest::get(electionId);

    QList<QVariantMap> pairwiseResults {};

    // must use back_inserter. QList.begin() won't work
    std::transform(pairwiseContestList.begin(), pairwiseContestList.end(),
                   std::back_inserter(pairwiseResults),
                   [](PairwiseContest pwc){ return pwc.toVariantMap(); });
    
    for(auto it = pairwiseResults.begin(); it != pairwiseResults.end(); it++)
    {
        auto optionAIter = std::find_if(optionList.begin(), optionList.end(),
                                   [&it](const Option& o){ return o.id() == (*it)["optionAId"]; });
        auto optionBIter = std::find_if(optionList.begin(), optionList.end(),
                                   [&it](const Option& o){ return o.id() == (*it)["optionBId"]; });
        if(optionAIter != optionList.end() && optionBIter != optionList.end())
        {
            (*it)["optionAName"] = (*optionAIter).name();
            (*it)["optionBName"] = (*optionBIter).name();
            (*it)["winnerId"] =
                (*it)["optionACount"].toInt() > (*it)["optionBCount"].toInt() ?
                (*it)["optionAId"] : (*it)["optionBId"];
            (*it)["delta"] = std::abs((*it)["optionACount"].toInt() - (*it)["optionBCount"].toInt());
        }
        else
        {
          qDebug() << "Failed to find option" << *it;
        }
    }
    
    texport(election);
    texport(optionList);
    texport(pairwiseResults);
}

int ResultService::create(int electionId)
{
    QString notice = "Created successfully.";
    tflash(notice);
    return electionId;
}
