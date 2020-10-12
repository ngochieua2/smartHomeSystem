#include "mainmenu.h"

// If you want, change all of the QTextStream stuff to std:istream and std::ostream
// to stay with what you are familiar. Just keep in mind that it will not understand
// the various Qt objects that you might try to output.
#include <QTextStream>
#include <QUrl>
#include <QCoreApplication>

MainMenu::MainMenu(QTextStream &display, QTextStream &input, QObject *parent)
  : QObject{parent}, _display{display}, _input{input}
{
}

void MainMenu::displayWelcome(const QString &title, const QString &group, const QStringList &members) const
{
  QString welcomeText{"Welcome to " + title};
  QString groupText{"Developed by " + group + ":"};

  _display << welcomeText << endl
           << groupText << endl;

  for (auto name: members) {
    _display << "- " << name << endl;
  }

  _display << "COMP 3023 Software Development with C++" << endl << endl;

}


void MainMenu::run()
{
  // remove this line, or at least comment it out until you have got it set up yourself
  exampleNetworkManagerUsage();

  _display << "You need to implement the real work" << endl
           << "Type (q) to quit" << endl;

  for (QString selection{_input.read(1)}; selection.toLower() != "q"; selection = _input.read(1)) {
    // TODO: fill this out with something. Prefereably broken down into functions
    if (selection != '\n') {
      _display << "typed something" << selection << endl;
      _input.readLine(); // skip the rest of the line
    }
  }

  // Need to exit the event loop to end the application
  QCoreApplication::instance()->quit();
}



// You can delete all of the below here, this is just for example purposes
#include <QTimer>
#include <QThread>
#include <QSharedPointer>
#include "network/requestmessage.h"
#include "network/responsemessage.h"

void MainMenu::exampleNetworkManagerUsage()
{
  // We need to be a little careful. Since we have moved the menu to a separate thread
  // with its own event loop (which sits reading from the console) we want to move
  // the network manager back to the original thread and event loop, which is basically
  // doing nothing.
  _manager = new network::QtHttpNetworkManager{};
  _manager->moveToThread(QCoreApplication::instance()->thread());

  // Since the manager cannot be child of the menu because they are in different threads,
  // we can hook this up to ensure that when this menu object is destroyed the network manager
  // object will also be destroyed.
  QObject::connect(this, &QObject::destroyed, _manager, &QObject::deleteLater);

  // Hook up the slots for receiving a request and handling responses
  // Note: we want direct connections so that the requests/responses are handled in
  // the manager's thread rather than queued across threads to execute in the menu
  // (which is busy handling user I/O).
  QObject::connect(_manager, &network::NetworkManager::requestReceived,
                   this, &MainMenu::handleRequest, Qt::ConnectionType::DirectConnection);
  QObject::connect(_manager, &network::NetworkManager::responseReceived,
                   this, &MainMenu::handleResponse, Qt::ConnectionType::DirectConnection);

  // To register targets that can be sent message, use 'addConnection'
  // In this case we add one to 'ourself' assuming the server will successfully
  // start up on port 80
  _manager->addConnection("self", {"http://localhost:80/"});

  // Register handlers for converting the lower-level HTTP content into higher-level messages
  _manager->registerHandler({"/state", network::HttpMethod::GET}, [this](const QUrl &url, const QByteArray &data) {
    // Depending on the message you are mapping you would use the url and data parameters
    return _factory.createGetStateRequest();
  });

  _manager->registerHandler({"*", network::HttpMethod::GET}, [](const QUrl &url, [[maybe_unused]] const QByteArray &data) {
    // A catch-all, this is basically what the default behaviour is.
    // But you could customise it if you like.
    return new network::RequestMessage{url};
  });

  // Register handlers for converting the lower-level HTTP content into higher-level messages
  // Same goes for responses as well.
  _manager->registerHandler({"/state", network::HttpMethod::GET}, [this](const QUrl &url, const QByteArray &data) {
    // Depending on the message you are mapping you would use the url and data parameters
    // The factory will return an appropriately configured ResponseMessage for the API result
    return _factory.createGetStateResponse(data, url);
  });

  QEventLoop eventLoop{}; // used to ensure the server has started
  // Don't forget to start the manager. You will want to pass in the real parameters,
  // but there are some default set.
  // The timer is just so we can queue the event on the other thread.
  QTimer::singleShot(1, _manager, [this, &eventLoop] () { _manager->start(); eventLoop.quit(); });
  eventLoop.exec();

  // You can remove connections too. In this case we replace the connection to
  // 'ourself' with a new one to ensure the target is where the server started up.
  _manager->removeConnection("self");
  _manager->addConnection("self", {_manager->boundAdress()});

  // We will also send a message to ourselves to test it out
  _manager->sendRequest("self", network::RequestMessage("/state"));

  // This is a synchronous call you will want to use for proxies later
  auto response{_manager->sendRequestWait("self", network::RequestMessage("/invalid"))};
  _display << "Synchronous request compeleted: " << response->statusCode() << endl;

//  thread()->sleep(1); // some time for the asynch call to complete
  _display << endl << "Try hitting the following address from your browser: "
           << _manager->boundAdress().toString() << "state" << endl << endl;
}

void MainMenu::handleRequest(QSharedPointer<network::RequestMessage> request)
{
  // This is what will be called when this device or controller recieves requests
  // from other sources. Try hitting it with your web browser when this example is
  // running.
  if (request->urlPath() == "/state") {
    auto response{_factory.createGetStateResponse({}, "This actually does nothing")};
    qDebug() << "menu handler sending response:" << response->statusCode();
    _manager->sendResponse(request, *response);
    delete response; // ownership is not transferred so you are resonsible for this
  }
  else {
    // Another way of ensuring deletion: QScopedPointer is Qt's way of doing std::unique_ptr
    QScopedPointer<network::ResponseMessage> response{_factory.createGenericNotFound(request->urlPath())};
    qDebug() << "menu handler sending response:" << response->statusCode();
    _manager->sendResponse(request, *response);
  }
}

void MainMenu::handleResponse(QSharedPointer<network::ResponseMessage> response)
{
  // This is what will be called when this device or controller has sent a request
  // to another and the response has come back.
  // This allows the responses to be handled asynchronously and in the info
  // displayed by hooking up signals and slots.
  // When using proxies you will need to use the synchronous method (sendRequestWait) instead
  _display << "Menu handler received response from: " << response->urlPath() << endl
           << "         status code: " << response->statusCode() << endl
           << "         with value: " << response->entity().toString() << endl;
}
