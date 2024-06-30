#include "resultcontroller.h"
#include "resultservice.h"
#include "objects/option.h"
#include "pairwisecontestservice.h"

static ResultService resultService;
static PairwiseContestService pairwiseContestService;

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
