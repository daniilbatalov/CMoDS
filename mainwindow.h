#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QRegularExpression>
#include <QPair>

#include "subcipher.h"
#include "perms.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_aom_key_clicked();

    void on_aem_key_clicked();

    void on_aom_ck_clicked();

    void on_aem_ck_clicked();


    void on_com_ck_clicked();

    void on_ck_ck_clicked();

    void on_cem_ck_clicked();

    void on_com_key_clicked();

    void on_cem_key_clicked();


    void on_rom_ck_clicked();

    void on_rk_ck_clicked();

    void on_rem_ck_clicked();

    void on_rom_key_clicked();



    void on_rk_key_clicked();

    void on_rem_key_clicked();

private:
    Ui::MainWindow *ui;
    SubCipher *a;
    ParsedPerm checkPermutationSyntax(QString perm, QString message);
    Perms *p = nullptr;
};
#endif // MAINWINDOW_H
