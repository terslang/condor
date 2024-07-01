#include "accountcontroller.h"
#include "user.h"

void
AccountController::form()
{
  userLogout(); // forcibly logged out
  render();     // shows form view
}

void
AccountController::login()
{
  QString username = httpRequest().formItemValue("email");
  QString password = httpRequest().formItemValue("password");

  User user = User::authenticate(username, password);
  if (!user.isNull()) {
    userLogin(&user);
    redirect(url("Home", "index"));
  } else {
    QString message = "Login failed";
    texport(message);
    render("form");
  }
}

void
AccountController::logout()
{
  userLogout();
  redirect(url("Account", "form")); // redirect to a login form
}

// Don't remove below this line
T_DEFINE_CONTROLLER(AccountController)
