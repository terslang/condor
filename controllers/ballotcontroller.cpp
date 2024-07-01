#include "ballotcontroller.h"
#include "ballotchoiceservice.h"
#include "ballotservice.h"
#include <TreeFrogController>

static BallotService ballotService;
static BallotChoiceService ballotChoiceService;

bool
BallotController::preFilter()
{
  if (!isUserLoggedIn()) {
    redirect(url("Account", "form"));
    return false;
  }
  return true;
}

void
BallotController::index()
{
  ballotService.index();
  render();
}

void
BallotController::show(const QString& id)
{
  ballotService.show(id);
  render();
}

void
BallotController::cast(const QString& id)
{
  int res;
  switch (request().method()) {
    case Tf::Get:
      ballotChoiceService.showOptions(session(), id);
      render();
      break;
    case Tf::Post:
      res = ballotChoiceService.createMany(request(), session(), id);
      if (res > 0) {
        // Save completed
        redirect(urla("show", id));
      } else if (res < 0) {
        // Failed
        qDebug() << "Failed to save ballot" << id;
        rollbackTransaction();
        redirect(urla("cast", id));
      } else {
        // Retry
        redirect(urla("cast", id));
      }
      break;
    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void
BallotController::create()
{
  QString id;

  switch (request().method()) {
    case Tf::Get:
      render();
      break;
    case Tf::Post:
      id = ballotService.create(request());
      if (!id.isEmpty()) {
        redirect(urla("cast", id));
      } else {
        render();
      }
      break;
    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void
BallotController::save(const QString& id)
{
  int res;

  switch (request().method()) {
    case Tf::Get:
      ballotService.edit(session(), id);
      render();
      break;
    case Tf::Post:
      res = ballotService.save(request(), session(), id);
      if (res > 0) {
        // Save completed
        redirect(urla("show", id));
      } else if (res < 0) {
        // Failed
        render();
      } else {
        // Retry
        redirect(urla("save", id));
      }
      break;
    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void
BallotController::remove(const QString& id)
{
  switch (request().method()) {
    case Tf::Post:
      ballotService.remove(id);
      redirect(urla("index"));
      break;
    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

// Don't remove below this line
T_DEFINE_CONTROLLER(BallotController)
