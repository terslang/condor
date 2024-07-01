#include "optioncontroller.h"
#include "optionservice.h"
#include "tfnamespace.h"
#include "tglobal.h"
#include <TreeFrogController>

static OptionService service;

bool
OptionController::preFilter()
{
  if (!isUserLoggedIn()) {
    redirect(url("Account", "form"));
    return false;
  }
  return true;
}

void
OptionController::index()
{
  service.index();
  render();
}

void
OptionController::show(const QString& id)
{
  service.show(id);
  render();
}

void
OptionController::create(const QString& electionId)
{
  switch (request().method()) {
    case Tf::Get:
      texport(electionId);
      render();
      break;
    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

void
OptionController::create()
{
  QString id;

  switch (request().method()) {
    case Tf::Get:
      render();
      break;
    case Tf::Post:
      id = service.create(request());
      if (!id.isEmpty()) {
        redirect(urla("show", id));
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
OptionController::save(const QString& id)
{
  int res;

  switch (request().method()) {
    case Tf::Get:
      service.edit(session(), id);
      render();
      break;
    case Tf::Post:
      res = service.save(request(), session(), id);
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
OptionController::remove(const QString& id)
{
  switch (request().method()) {
    case Tf::Post:
      service.remove(id);
      redirect(urla("index"));
      break;
    default:
      renderErrorResponse(Tf::NotFound);
      break;
  }
}

// Don't remove below this line
T_DEFINE_CONTROLLER(OptionController)
