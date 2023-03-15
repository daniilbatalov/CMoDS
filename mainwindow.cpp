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

    v = new Vigenere::Vigenere(abc);
    g = new Gronsfeld::Gronsfeld(abc);

    abc.append(" .,\n");

    a = new SubCipher(abc);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete a;
    delete p;
    delete v;
    delete g;
}

void MainWindow::on_aom_key_clicked()
{

    if (this->ui->aom_le->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Исходное сообщение не может быть пустым!");
    }
    else
    {
        QString om = this->ui->aom_le->toPlainText();
        QString::iterator it = om.begin();
        QString res;
        for (; it != om.end(); ++it)
        {
            res += this->a->encrypt((*it), [](qsizetype i, qsizetype n, qsizetype) {return n - i - 1;}, 0);
        }
        this->ui->aem_le->setPlainText(res);
    }
}

void MainWindow::on_aem_key_clicked()
{
    if (this->ui->aem_le->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Зашифрованное сообщение не может быть пустым!");
    }
    else
    {
        QString om = this->ui->aem_le->toPlainText();
        QString::iterator it = om.begin();
        QString res;
        for (; it != om.end(); ++it)
        {
            res += this->a->encrypt((*it), [](qsizetype i, qsizetype n, qsizetype) {return n - i - 1;}, 0);
        }
        this->ui->aom_le->setPlainText(res);
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
    if (this->ui->com_le->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Исходное сообщение не может быть пустым!");
    }
    else
    {
        if (this->ui->ck_le->text().isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Сдвиг не может быть пустым!");
        }
        else
        {
            static QRegularExpression re(R"(\d*)");
            if (re.match(this->ui->ck_le->text()).capturedLength() != this->ui->ck_le->text().length())
            {
                QMessageBox::warning(this, "Ошибка", "Сдвиг должен быть неотрицательным числом!");
            }
            else
            {
                QString om = this->ui->com_le->toPlainText();
                int s = this->ui->ck_le->text().toInt();
                QString::iterator it = om.begin();
                QString res;
                for (; it != om.end(); ++it)
                {
                    res += this->a->encrypt((*it), [](qsizetype i, qsizetype n, qsizetype s) {return (MathAux::euclidean_remainder<qsizetype>(i + s, n));}, s);
                }
                this->ui->cem_le->setPlainText(res);
            }
        }
    }
}

void MainWindow::on_cem_key_clicked()
{
    if (this->ui->cem_le->toPlainText().isEmpty())
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
                QMessageBox::warning(this, "Ошибка", "Сдвиг должен быть неотрицательным числом!");
            }
            else
            {
                QString em = this->ui->cem_le->toPlainText();
                int s = this->ui->ck_le->text().toInt();
                QString::iterator it = em.begin();
                QString res;
                for (; it != em.end(); ++it)
                {
                    res += this->a->encrypt((*it), [](qsizetype i, qsizetype n, qsizetype s) {return (MathAux::euclidean_remainder<qsizetype>(i - s, n));}, s);
                }
                this->ui->com_le->setPlainText(res);
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

ParsedPerm MainWindow::checkPermutationSyntax(const QString &perm, const QString &message)
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
                if ((*i).toInt() > r.length() || (*i).toInt() < 1)
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
    if (this->ui->rom_le->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Исходное сообщение не может быть пустым!");
    }
    else if (this->ui->rk_le->text().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Перестановка не может быть пустой!");
    }
    else
    {
        ParsedPerm res = checkPermutationSyntax(this->ui->rk_le->text(), this->ui->rom_le->toPlainText());
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
            this->ui->rem_le->setPlainText(p->encrypt(this->ui->rom_le->toPlainText()));
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
    if (this->ui->rem_le->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Зашифрованное сообщение не может быть пустым!");
    }
    else if (this->ui->rk_le->text().isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Перестановка не может быть пустой!");
    }
    else
    {
        ParsedPerm res = checkPermutationSyntax(this->ui->rk_le->text(), this->ui->rem_le->toPlainText());
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
            this->ui->rom_le->setPlainText(p->decrypt(this->ui->rem_le->toPlainText()));
        }
    }
}



void MainWindow::on_rot0_rb_clicked()
{
    this->v->setRot(Vigenere::Rot::ROT_0);
}


void MainWindow::on_rot1_rb_clicked()
{
    this->v->setRot(Vigenere::Rot::ROT_1);
}


void MainWindow::on_vom_ck_clicked()
{
    this->ui->vom_le->clear();
}


void MainWindow::on_vk_ck_clicked()
{
    this->ui->vk_le->clear();
}


void MainWindow::on_vem_ck_clicked()
{
    this->ui->vem_le->clear();
}


void MainWindow::on_vom_key_clicked()
{
    QString text = this->ui->vom_le->toPlainText();
    QString key = this->ui->vk_le->toPlainText();
    if (text.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Исходное сообщение не может быть пустым!");
    }
    else
    {
        if (key.isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Ключ не может быть пустым!");
        }
        else
        {
            static QRegularExpression ru_lc(R"(([ёа-я]+[ .,:;\-\t\n]*)+)", QRegularExpression::UseUnicodePropertiesOption);
            static QRegularExpression ru_uc(R"(([ËА-Я]+[ .,:;\-\t\n]*)+)", QRegularExpression::UseUnicodePropertiesOption);
            static QRegularExpression en_lc(R"(([a-z]+[ .,:;\-\t\n]*)+)");
            static QRegularExpression en_uc(R"(([A-Z]+[ .,:;\-\t\n]*)+)");

            bool fullMatchTextRuLc = ru_lc.match(text).capturedLength() == text.length();
            bool fullMatchTextRuUc = ru_uc.match(text).capturedLength() == text.length();
            bool fullMatchTextEnLc = en_lc.match(text).capturedLength() == text.length();
            bool fullMatchTextEnUc = en_uc.match(text).capturedLength() == text.length();

            bool fullMatchKeyRuLc = ru_lc.match(key).capturedLength() == key.length();
            bool fullMatchKeyRuUc = ru_uc.match(key).capturedLength() == key.length();
            bool fullMatchKeyEnLc = en_lc.match(key).capturedLength() == key.length();
            bool fullMatchKeyEnUc = en_uc.match(key).capturedLength() == key.length();

            QVector<QPair<bool, bool>> checkRes {{fullMatchTextRuLc, fullMatchKeyRuLc}, {fullMatchTextRuUc, fullMatchKeyRuUc}, {fullMatchTextEnLc, fullMatchKeyEnLc}, {fullMatchTextEnUc, fullMatchKeyEnUc}};

            for (int i = 0; i < checkRes.length(); ++i)
            {
                if (checkRes.at(i).first && checkRes.at(i).second)
                {
                    this->v->setCurrentAbc(static_cast<Vigenere::Alphabet>(i));
                }
            }

            if (this->v->getCurrentAbc() == Vigenere::Alphabet::INVALID)
            {
                QMessageBox::warning(this, "Ошибка", "Алфавиты исходного текста и ключа не совпадают!");
            }
            else
            {
                this->v->setKey(key);
                this->ui->vem_le->setPlainText(this->v->encrypt(text, [](qsizetype i, qsizetype n, qsizetype s) {return i + n + s;}));
            }
        }
    }
}


void MainWindow::on_greedy_rb_clicked()
{
    this->v->setKeyMode(Vigenere::KeyMode::GREEDY);
}


void MainWindow::on_lazy_rb_clicked()
{
    this->v->setKeyMode(Vigenere::KeyMode::LAZY);
}


void MainWindow::on_vem_key_clicked()
{
    QString text = this->ui->vem_le->toPlainText();
    QString key = this->ui->vk_le->toPlainText();
    if (text.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Исходное сообщение не может быть пустым!");
    }
    else
    {
        if (key.isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Ключ не может быть пустым!");
        }
        else
        {
            static QRegularExpression ru_lc(R"(([ёа-я]+[ .,:;\-\t\n]*)+)", QRegularExpression::UseUnicodePropertiesOption);
            static QRegularExpression ru_uc(R"(([ËА-Я]+[ .,:;\-\t\n]*)+)", QRegularExpression::UseUnicodePropertiesOption);
            static QRegularExpression en_lc(R"(([a-z]+[ .,:;\-\t\n]*)+)");
            static QRegularExpression en_uc(R"(([A-Z]+[ .,:;\-\t\n]*)+)");

            bool fullMatchTextRuLc = ru_lc.match(text).capturedLength() == text.length();
            bool fullMatchTextRuUc = ru_uc.match(text).capturedLength() == text.length();
            bool fullMatchTextEnLc = en_lc.match(text).capturedLength() == text.length();
            bool fullMatchTextEnUc = en_uc.match(text).capturedLength() == text.length();

            bool fullMatchKeyRuLc = ru_lc.match(key).capturedLength() == key.length();
            bool fullMatchKeyRuUc = ru_uc.match(key).capturedLength() == key.length();
            bool fullMatchKeyEnLc = en_lc.match(key).capturedLength() == key.length();
            bool fullMatchKeyEnUc = en_uc.match(key).capturedLength() == key.length();

            QVector<QPair<bool, bool>> checkRes {{fullMatchTextRuLc, fullMatchKeyRuLc}, {fullMatchTextRuUc, fullMatchKeyRuUc}, {fullMatchTextEnLc, fullMatchKeyEnLc}, {fullMatchTextEnUc, fullMatchKeyEnUc}};

            for (int i = 0; i < checkRes.length(); ++i)
            {
                if (checkRes.at(i).first && checkRes.at(i).second)
                {
                    this->v->setCurrentAbc(static_cast<Vigenere::Alphabet> (i));
                }
            }

            if (this->v->getCurrentAbc() == Vigenere::Alphabet::INVALID)
            {
                QMessageBox::warning(this, "Ошибка", "Алфавиты исходного текста и ключа не совпадают!");
            }
            else
            {
                this->v->setKey(key);
                this->ui->vom_le->setPlainText(this->v->encrypt(text, [](qsizetype i, qsizetype n, qsizetype s) {return i - n - s;}));
            }
        }
    }

}


void MainWindow::on_pom_key_clicked()
{
    QString text = this->ui->pom_le->toPlainText().simplified().replace(" ", "").toUpper();
    QString key = this->ui->pk_le->toPlainText().simplified().replace(" ", "").toUpper();
    if (text.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Исходное сообщение не может быть пустым!");
    }
    else
    {
        if (key.isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Ключ не может быть пустым!");
        }
        else
        {
            static QRegularExpression ru_uc(R"([ËА-Я\-.,]+)", QRegularExpression::UseUnicodePropertiesOption | QRegularExpression::CaseInsensitiveOption);
            static QRegularExpression en_uc(R"([A-Z]+)", QRegularExpression::CaseInsensitiveOption);

            bool fullMatchTextRuUc = ru_uc.match(text).capturedLength() == text.length();
            bool fullMatchTextEnUc = en_uc.match(text).capturedLength() == text.length();

            bool fullMatchKeyRuUc = ru_uc.match(key).capturedLength() == key.length();
            bool fullMatchKeyEnUc = en_uc.match(key).capturedLength() == key.length();

            if ((fullMatchKeyEnUc && fullMatchTextRuUc) || (fullMatchKeyRuUc && fullMatchTextEnUc))
            {
                QMessageBox::warning(this, "Ошибка", "Алфавиты ключа и сообщения не совпадают!");
            }
            else if ((fullMatchKeyEnUc && fullMatchTextEnUc) || (fullMatchKeyRuUc && fullMatchTextRuUc))
            {
                if (fullMatchKeyEnUc)
                {
                    this->pf.setCurrentAbc(Playfair::Alphabet::EN);
                }
                else
                {
                    this->pf.setCurrentAbc(Playfair::Alphabet::RU);
                }
                this->pf.generateTable(key);
                this->ui->pem_le->setPlainText(this->pf.encrypt(text));
            }
            else
            {
                QMessageBox::warning(this, "Ошибка", "Недопустимые символы в ключе и/или в сообщении!");
            }

        }
    }

}

void MainWindow::on_pem_key_clicked()
{
    QString text = this->ui->pem_le->toPlainText().simplified().replace(" ", "").toUpper();
    QString key = this->ui->pk_le->toPlainText().simplified().replace(" ", "").toUpper();
    if (text.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Зашифрованное сообщение не может быть пустым!");
    }
    else
    {
        if (key.isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Ключ не может быть пустым!");
        }
        else
        {
            static QRegularExpression ru_uc(R"([ЁА-Я\-.,]+)", QRegularExpression::UseUnicodePropertiesOption | QRegularExpression::CaseInsensitiveOption);
            static QRegularExpression en_uc(R"([A-Z]+)", QRegularExpression::CaseInsensitiveOption);

            bool fullMatchTextRuUc = ru_uc.match(text).capturedLength() == text.length();
            bool fullMatchTextEnUc = en_uc.match(text).capturedLength() == text.length();

            bool fullMatchKeyRuUc = ru_uc.match(key).capturedLength() == key.length();
            bool fullMatchKeyEnUc = en_uc.match(key).capturedLength() == key.length();

            if ((fullMatchKeyEnUc && fullMatchTextRuUc) || (fullMatchKeyRuUc && fullMatchTextEnUc))
            {
                QMessageBox::warning(this, "Ошибка", "Алфавиты ключа и сообщения не совпадают!");
            }
            else if ((fullMatchKeyEnUc && fullMatchTextEnUc) || (fullMatchKeyRuUc && fullMatchTextRuUc))
            {
                if (fullMatchKeyEnUc)
                {
                    this->pf.setCurrentAbc(Playfair::Alphabet::EN);
                }
                else
                {
                    this->pf.setCurrentAbc(Playfair::Alphabet::RU);
                }
                this->pf.generateTable(key);
                this->ui->pom_le->setPlainText(this->pf.decrypt(text));
            }
            else
            {
                QMessageBox::warning(this, "Ошибка", "Недопустимые символы в ключе и/или в сообщении!");
            }

        }
    }
}


void MainWindow::on_pom_ck_clicked()
{
    this->ui->pom_le->clear();
}


void MainWindow::on_pk_ck_clicked()
{
    this->ui->pk_le->clear();
}


void MainWindow::on_pem_ck_clicked()
{
    this->ui->pem_le->clear();
}


void MainWindow::on_gom_key_clicked()
{
    QString text = this->ui->gom_le->toPlainText();
    QString key = this->ui->gk_le->toPlainText();
    if (text.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Исходное сообщение не может быть пустым!");
    }
    else
    {
        if (key.isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Ключ не может быть пустым!");
        }
        else
        {
            static QRegularExpression re(R"(\d*)");
            if (re.match(key).capturedLength() != key.length())
            {
                QMessageBox::warning(this, "Ошибка", "Сдвиг должен быть неотрицательным числом!");
            }
            else
            {
                this->g->setKey(key);
                this->ui->gem_le->setPlainText(this->g->encrypt(text, [](qsizetype i, qsizetype s){return i + s;}));
            }
        }
    }
}


void MainWindow::on_gem_key_clicked()
{
    QString text = this->ui->gem_le->toPlainText();
    QString key = this->ui->gk_le->toPlainText();
    if (text.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Исходное сообщение не может быть пустым!");
    }
    else
    {
        if (key.isEmpty())
        {
            QMessageBox::warning(this, "Ошибка", "Ключ не может быть пустым!");
        }
        else
        {
            static QRegularExpression re(R"(\d*)");
            if (re.match(key).capturedLength() != key.length())
            {
                QMessageBox::warning(this, "Ошибка", "Сдвиг должен быть неотрицательным числом!");
            }
            else
            {
                this->g->setKey(key);
                this->ui->gom_le->setPlainText(this->g->encrypt(text, [](qsizetype i, qsizetype s){return i - s;}));
            }
        }
    }
}


void MainWindow::on_greedy_rb_g_clicked()
{
    this->g->setKeyMode(Gronsfeld::KeyMode::GREEDY);
}


void MainWindow::on_lazy_rb_g_clicked()
{
    this->g->setKeyMode(Gronsfeld::KeyMode::LAZY);
}


void MainWindow::on_gom_ck_clicked()
{
    this->ui->gom_le->clear();
}


void MainWindow::on_gk_ck_clicked()
{
    this->ui->gk_le->clear();
}


void MainWindow::on_gem_ck_clicked()
{
    this->ui->gem_le->clear();
}

