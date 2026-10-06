#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "ApiClient.h"
#include "AppViewModel.h"
#include "AuthService.h"
#include "LoginViewModel.h"
#include "SessionManager.h"
#include "LicenseService.h"
#include "UserDashboardViewModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // ---- Susun lapisan dari bawah ke atas ----
    SessionManager session; // 1. buat session manager dulu
    ApiClient api(&session); // 2. buat session api dari session manager
    AuthService authService(&api, &session); // 3. buat session authservice, pakai api dan session manager
    LicenseService licenseService(&api, &session);


    LoginViewModel loginViewModel(&authService); // 4. dari authservice kiat buat loginViewModel
    AppViewModel appViewModel(&session, &authService); // 5. dari session dan juga authService kita buat juga appViewModel
    UserDashboardViewModel userDashboardViewModel(&licenseService);

    // ---- Daftarkan ViewModel ke QML (dipakai sebagai singleton) ----
    constexpr const char *uri = "LicensingPortalContent";
    qmlRegisterSingletonInstance(uri, 1, 0, "LoginViewModel", &loginViewModel);
    qmlRegisterSingletonInstance(uri, 1, 0, "AppViewModel", &appViewModel);
    qmlRegisterSingletonInstance(uri, 1, 0, "UserDashboardViewModel", &userDashboardViewModel);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule(uri, "App");

    return app.exec();
}
