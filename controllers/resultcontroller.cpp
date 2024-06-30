#include "resultcontroller.h"
#include "election.h"
#include "pairwisecontest.h"
#include "resultservice.h"
#include "objects/option.h"
#include "pairwisecontestservice.h"

static ResultService resultService;
static PairwiseContestService pairwiseContestService;

bool ResultController::preFilter()
{
    if (!isUserLoggedIn()) {
        redirect(url("Account", "form"));
        return false;
    }
    return true;
}

void ResultController::show(const QString &id)
{
    resultService.show(id.toInt());
    render();
}

void ResultController::create(const QString &id)
{
    switch (request().method()) {
    case Tf::Post:
        {
          auto electionId = id.toInt(); 
          auto options = Option::getByElectionId(electionId);
          for(qsizetype i=0; i < options.size(); i++) {
              for(qsizetype j = i+1; j < options.size(); j++) {
                  int res = pairwiseContestService.create(electionId, options[i].id(), options[j].id());            
                  if (res < 1) {
                      rollbackTransaction();
                      QString error = "Failed to generate results.";
                      texport(error);
                      break;
                  }
              }
          }
          
          auto pairwiseContestList = PairwiseContest::get(electionId);
          
          // find condorcet winner
          for(const auto& candidate: options) {
              bool isWinner = true;
              for(const auto& opponent : options) {
                  if(candidate.id() != opponent.id()) {
                      bool lost = false;
                      for(const auto& contest: pairwiseContestList) {
                          if ((contest.optionAId() == candidate.id()
                               && contest.optionBId() == opponent.id()
                               && contest.optionACount() < contest.optionBCount())
                              ||
                              (contest.optionAId() == opponent.id()
                               && contest.optionBId() == candidate.id()
                               && contest.optionACount() > contest.optionBCount())) {
                              lost = true;
                              break;
                          }
                      }
                      if(lost) {
                          isWinner = false;
                          break;
                      }
                  }
              }
              if (isWinner) {
                  auto election = Election::get(electionId);
                  election.setWinnerOptionId(candidate.id());
                  election.save();
              }
          }
          redirect(urla("show", id));
        }
        break;
    default:
        renderErrorResponse(Tf::NotFound);
        break;
    }
}

// Don't remove below this line
T_DEFINE_CONTROLLER(ResultController)
