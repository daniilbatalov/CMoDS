#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVector<QString> abc;
    abc.append("абвгдеёжзийклмнопрстуфхцчшщъыьэюя");
    abc.append("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");
    abc.append("abcdefghijklmnopqrstuvwxyz");
    abc.append("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    abc.append(" .,");

    a = new SubCipher(abc);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete a;
    delete p;
}


void MainWindow::on_aom_key_clicked()
{

    if (this->ui->aom_le->text().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Исходное сообщение не может быть пустым!");
    }
    else
    {
        QString om = this->ui->aom_le->text();
        QString::iterator it = om.begin();
        QString res;
        for (; it != om.end(); ++it)
        {
            res += this->a->encrypt((*it), [](int i, int n, int) {return n - i - 1;}, 0);
        }
        this->ui->aem_le->setText(res);
    }
}


void MainWindow::on_aem_key_clicked()
{
    if (this->ui->aem_le->text().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Зашифрованное сообщение не может быть пустым!");
    }
    else
    {
        QString om = this->ui->aem_le->text();
        QString::iterator it = om.begin();
        QString res;
        for (; it != om.end(); ++it)
        {
            res += this->a->encrypt((*it), [](int i, int n, int) {return n - i - 1;}, 0);
        }
        this->ui->aom_le->setText(res);
    }
}

void MainWindow::on_aom_ck_clicked()
{
    ui->aom_le->clear();
}


void MainWindow::on_aem_ck_clicked()
{
    ui->aem_le->clear();
}


void MainWindow::on_com_ck_clicked()
{
    ui->com_le->clear();
}


void MainWindow::on_ck_ck_clicked()
{
    ui->ck_le->clear();
}


void MainWindow::on_cem_ck_clicked()
{
    ui->cem_le->clear();
}


void MainWindow::on_com_key_clicked()
{
    if (this->ui->com_le->text().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Зашифрованное сообщение не может быть пустым!");
    }
    else
    {
        if (this->ui->ck_le->text().isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Сдвиг не может быть пустым!");
        }
        else
        {
            static QRegularExpression re("\\d*");
            if (re.match(this->ui->ck_le->text()).capturedLength() != this->ui->ck_le->text().length())
            {
                QMessageBox::warning(this, "Ошибка", "Сдвиг должен быть числом!");
            }
            else
            {
                QString om = this->ui->com_le->text();
                int s = this->ui->ck_le->text().toInt();
                QString::iterator it = om.begin();
                QString res;
                for (; it != om.end(); ++it)
                {
                    res += this->a->encrypt((*it), [](int i, int n, int s) {return ((i + s) % n);}, s);
                }
                this->ui->cem_le->setText(res);
            }
        }
    }
}


void MainWindow::on_cem_key_clicked()
{
    if (this->ui->cem_le->text().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Открытое сообщение не может быть пустым!");
    }
    else
    {
        if (this->ui->ck_le->text().isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Сдвиг не может быть пустым!");
        }
        else
        {
            static QRegularExpression re("\\d*");
            if (re.match(this->ui->ck_le->text()).capturedLength() != this->ui->ck_le->text().length())
            {
                QMessageBox::warning(this, "Ошибка", "Сдвиг должен быть числом!");
            }
            else
            {
                QString em = this->ui->cem_le->text();
                int s = this->ui->ck_le->text().toInt();
                QString::iterator it = em.begin();
                QString res;
                for (; it != em.end(); ++it)
                {
                    res += this->a->encrypt((*it), [](int i, int n, int s) {return ((i - s) % n);}, s);
                }
                this->ui->com_le->setText(res);
            }
        }
    }
}


void MainWindow::on_rom_ck_clicked()
{
    this->ui->rom_le->clear();
}


void MainWindow::on_rk_ck_clicked()
{
    this->ui->rk_le->clear();
}


void MainWindow::on_rem_ck_clicked()
{
    this->ui->rem_le->clear();
}

ParsedPerm MainWindow::checkPermutationSyntax(QString perm, QString message)
{
    static QRegularExpression re("(\\((\\d+\\s)*\\d+\\))+");
    if (re.match(perm).capturedLength() != perm.length())
    {
        return ParsedPerm(BadSyntax, QVector<QVector<int>>());
    }
    else
    {
        QVector<QVector<int>> res;
        QVector<QString> tokenized = perm.mid(1, perm.length() - 2).split(")(");
        QVector<QString>::iterator it = tokenized.begin();
        int count = 0;
        for(; it != tokenized.end(); it++)
        {
            QVector<int> result;
            QVector<QString> r = (*it).split(" ");
            QVector<bool> visited = QVector<bool>(r.length());
            QVector<QString>::iterator i = r.begin();
            for(; i != r.end(); i++)
            {
                if ((*i).toInt() > r.length())
                {
                    return ParsedPerm(BadPerm, QVector<QVector<int>>());
                }
                else
                {
                    result.append((*i).toInt());
                    visited[(*i).toInt() - 1] = true;
                    count++;
                }
            }
            if (visited.contains(false))
                return ParsedPerm(BadPerm, QVector<QVector<int>>());
            else
                res.append(result);

        }
        if (count > message.length())
            return ParsedPerm(LongPerm, res);
        else
            return ParsedPerm(OK, res);
    }
}
void MainWindow::on_rom_key_clicked()
{
    if (this->ui->rom_le->text().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Открытое сообщение не может быть пустым!");
    }
    else if (this->ui->rk_le->text().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Перестановка не может быть пустой!");
    }
    else
    {
        ParsedPerm res = checkPermutationSyntax(this->ui->rk_le->text(), this->ui->rom_le->text());
        if (res.result == BadSyntax)
        {
            QMessageBox::warning(this, "Ошибка", "Неправильный синтаксис перестановки!");
        }
        else if (res.result == BadPerm)
        {
            QMessageBox::warning(this, "Ошибка", "Неправильная перестановка!");
        }
        else if (res.result == LongPerm)
        {
            QMessageBox::warning(this, "Ошибка", "Перестановка слишком длинная!");
        }
        else if (res.result == OK)
        {
            p = new Perms(res);
            this->ui->rem_le->setText(p->encrypt(this->ui->rom_le->text()));
        }
    }
}

void MainWindow::on_rk_key_clicked()
{
    if (!p)
    {
        QMessageBox::warning(this, "Ошибка", "Перестановка не может быть пустой!");
    }
    else
    {
        this->ui->rk_le->setText(p->revToQString());
        p->swap();
    }
}


void MainWindow::on_rem_key_clicked()
{
    if (this->ui->rem_le->text().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Зашифрованное сообщение не может быть пустым!");
    }
    else if (this->ui->rk_le->text().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Перестановка не может быть пустой!");
    }
    else
    {
        ParsedPerm res = checkPermutationSyntax(this->ui->rk_le->text(), this->ui->rem_le->text());
        if (res.result == BadSyntax)
        {
            QMessageBox::warning(this, "Ошибка", "Неправильный синтаксис перестановки!");
        }
        else if (res.result == BadPerm)
        {
            QMessageBox::warning(this, "Ошибка", "Неправильная перестановка!");
        }
        else if (res.result == LongPerm)
        {
            QMessageBox::warning(this, "Ошибка", "Перестановка слишком длинная!");
        }
        else if (res.result == OK)
        {
            p = new Perms(res);
            this->ui->rom_le->setText(p->decrypt(this->ui->rem_le->text()));
        }
    }
}

