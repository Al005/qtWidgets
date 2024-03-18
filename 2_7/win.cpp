#include "win.h"
Win::Win(QWidget *parent):QWidget(parent)
{
    setWindowTitle("Возведение в квадрат");  // Заголовок окна

    //this->setMinimumWidth(375);

    frame = new QFrame(this);
    frame->setFrameShadow(QFrame::Raised);
    frame->setFrameShape(QFrame::Panel);
    inputLabel = new QLabel("Введите число:", this);
    inputEdit = new QLineEdit("",this);
    StrValidator *v=new StrValidator(inputEdit);
    inputEdit->setValidator(v);
    outputLabel = new QLabel("Результат:", this);
    outputEdit = new QLineEdit("", this);
    nextButton = new QPushButton("Следующее", this);
    exitButton = new QPushButton("Выход", this);
    // компоновка приложения выполняется согласно рисунку 2
    QVBoxLayout *vLayout1 = new QVBoxLayout(frame);
    vLayout1->addWidget(inputLabel);
    vLayout1->addWidget(inputEdit);
    vLayout1->addWidget(outputLabel);
    vLayout1->addWidget(outputEdit);
    vLayout1->addStretch();
    QVBoxLayout *vLayout2 = new QVBoxLayout();
    vLayout2->addWidget(nextButton);
    vLayout2->addWidget(exitButton);
    vLayout2->addStretch();
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(frame);
    hLayout->addLayout(vLayout2);
    begin();
    /*
    connect(exitButton,SIGNAL(clicked(bool)),
            this,SLOT(close()));
    connect(nextButton,SIGNAL(clicked(bool)),
            this,SLOT(begin()));
    connect(inputEdit,SIGNAL(returnPressed()),
            this,SLOT(calc()));
    */
    connect(exitButton, &QPushButton::clicked,   // 2 способ сигнально-слотовой связи
            this, &Win::close);
    connect(nextButton, &QPushButton::clicked,
            this, &Win::begin);
    connect(inputEdit, &QLineEdit::returnPressed,
            this, &Win::calc);
}
void Win::begin()
{
    inputEdit->clear();  // очищение строки ввода
    nextButton->setEnabled(false);  // недоступность нажатия кнопки "Следующее"
    nextButton->setDefault(false);  // убираем выделение кнопки "Следующее"
    inputEdit->setEnabled(true);  // доступность редактирования строки ввода
    outputLabel->setVisible(false); // скрываем метку вывода
    outputEdit->setVisible(false); // скрываем строку вывода
    outputEdit->setEnabled(false);  // значение false для доступа к редактированию строки вывода
    inputEdit->setFocus();  // возможность сразу вводить число
}
void Win::calc()
{
    bool Ok=true; float r,a;
    QString str=inputEdit->text();
    a=str.toDouble(&Ok);
    if (Ok)
    {
        r=a*a;
        str.setNum(r);
        outputEdit->setText(str); // выводит в строке вывода наш результат
        inputEdit->setEnabled(false); // значение false для доступа к редактированию строки ввода
        outputLabel->setVisible(true); // видимость метки вывода
        outputEdit->setVisible(true); // видимость строки вывода
        nextButton->setDefault(true); // добавляем выделение кнопки "Следующее"
        nextButton->setEnabled(true); // кнопка "Следующее" доступно для нажатия
        nextButton->setFocus(); // нажатие кнопки "Следующее" с помощью Enter
    }
    else
        if (!str.isEmpty())
        {
            QMessageBox msgBox(QMessageBox::Information,
                               ("Возведение в квадрат."),
                               ("Введено неверное значение."),
                               QMessageBox::Ok);
        msgBox.exec();
    }
}
