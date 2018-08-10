#include <iostream>
#include "git2.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    git_libgit2_init();
    git_repository *repo = NULL;
    const char *url = "https://github.com/pablospe/cmake-example-library.git";
    const char *path = "/home/igdev/fl";
    int error = git_clone(&repo, url, path, NULL);
    std:: cout << error << std::endl;
    w.show();

    return a.exec();
}