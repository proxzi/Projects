#include <QApplication>
#include <QScopedPointer>
#include <QStyleFactory>
#include <QSurfaceFormat>
#include <QDebug>
#include <QScreen>

#include <vsn_application.h>

#include "mainwindow.h"

int main(int argc, char** argv)
{
    Math::SetMultithreadedMode(mtm_Off);

    QCoreApplication::setApplicationName("C3DShellCodingTutorial");
    QCoreApplication::setOrganizationName("Moscow Polytech");
    QCoreApplication::setOrganizationDomain("NoDomain");

    //QApplication::setStyle(QStyleFactory::create("Fusion"));
 
    //QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::RoundPreferFloor);

    Application vapp;
    QApplication app(argc, argv);

    if (!QtVision::ActivateLicense()) return 0;
    
    app.setWindowIcon(QIcon(QString(":/res/icons/c3d-labs.jpg")));
    app.setFont(QFont("Segoe UI", 10));

    // Setup OpenGL
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setSamples(4);
    format.setSwapInterval(0);
    QSurfaceFormat::setDefaultFormat(format);

    QScopedPointer<MainWindow> mainWin(new MainWindow);

    mainWin->setWindowTitle("C3D Shell Coding Tutorial");
    mainWin->showPreview();

    return app.exec();
}