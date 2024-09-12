#include "skeypad.h"
#include "ui_skeypad.h"

sKeypad::sKeypad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sKeypad)
{
    ui->setupUi(this);
    cLocal = NULL;
    cType = KAYPAD_NUMERIC;
    cZeroLength = false;

    ui->leInput->setProperty("error", false);

    connect(ui->leInput, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
    connect(ui->leNinputSP, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
    connect(ui->leNinput, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));

    connect(ui->leInput_4, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));

    connect(ui->pbA, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbB, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbC, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbD, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbE, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbF, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbG, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbH, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbI, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbJ, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbK, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbL, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbM, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbO, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbQ, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbR, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbS, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbT, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbU, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbV, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbW, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbX, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbY, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbZ, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbSpace, SIGNAL(clicked()), this, SLOT(on_pbSpaceClicked()));
    connect(ui->pbBack, SIGNAL(clicked()), this, SLOT(on_pbBackClicked()));
    connect(ui->pbCancel, SIGNAL(clicked()), this, SLOT(on_pbCancelClicked()));
    connect(ui->pbEnter, SIGNAL(clicked()), this, SLOT(on_pbEnterClicked()));
    connect(ui->pb123, SIGNAL(clicked()), this, SLOT(on_pb123Clicked()));
    connect(ui->pbCap, SIGNAL(clicked()), this, SLOT(on_pbCapsClicked()));

    connect(ui->pbN1SP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN2SP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN3SP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN4SP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN5SP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN6SP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN7SP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN8SP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN9SP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN0SP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbNdotSP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbNplusSP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbNminusSP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbNastricsSP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbNunderSP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbNequalSP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbNhashSP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbNpercentageSP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbNopenbracketSP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbNclosebracketSP, SIGNAL(clicked()), this, SLOT(on_pbClicked()));

    connect(ui->pbNspaceSP, SIGNAL(clicked()), this, SLOT(on_pbSpaceClicked()));
    connect(ui->pbNbackSP, SIGNAL(clicked()), this, SLOT(on_pbBackClicked()));
    connect(ui->pbNcancelSP, SIGNAL(clicked()), this, SLOT(on_pbCancelClicked()));
    connect(ui->pbNenterSP, SIGNAL(clicked()), this, SLOT(on_pbEnterClicked()));
    connect(ui->pbNabcSP, SIGNAL(clicked()), this, SLOT(on_pbABCClicked()));


    connect(ui->pbN1, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN2, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN3, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN4, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN5, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN6, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN7, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN8, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN9, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbN0, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbNdot, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbNplus, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbNminus, SIGNAL(clicked()), this, SLOT(on_pbClicked()));
    connect(ui->pbNback, SIGNAL(clicked()), this, SLOT(on_pbBackClicked()));
    connect(ui->pbNcancel, SIGNAL(clicked()), this, SLOT(on_pbCancelClicked()));
    connect(ui->pbNenter, SIGNAL(clicked()), this, SLOT(on_pbEnterClicked()));

    ui->frEnglishAlpha->move(0, 380);

    ui->frNumSpecial->move(ui->frEnglishAlpha->x(), ui->frEnglishAlpha->y());
    ui->frNum->move(ui->frEnglishAlpha->x()+130, ui->frEnglishAlpha->y());
    ui->frOtherAlpha->move(ui->frEnglishAlpha->x(), ui->frEnglishAlpha->y());

    ui->frEnglishAlpha->hide();
    ui->frNumSpecial->hide();
    ui->frNum->hide();
    ui->frOtherAlpha->hide();
}

sKeypad::~sKeypad()
{
    delete ui;
}

void sKeypad::ShowKeyPad()
{
   
}

void sKeypad::ShowKeypad(QObject *tobj, int Type, bool ZeroLength)
{
    cLocal = tobj;
    cType = Type;
    cZeroLength = ZeroLength;

    if(cType == KAYPAD_ALPHA_NUMERIC)
    {
        ui->frEnglishAlpha->show();

        cleInput = ui->leInput;

        ui->pbCap->setText("small");
        on_pbCapsClicked();
        cleInput->setFocus();
        this->show();

        if(cLocal)
        {
            QLineEdit *tle = qobject_cast<QLineEdit *>(cLocal);

            if(tle)
            {
                cleInput->setValidator(tle->validator());
                cleInput->setText(tle->text());
                cleInput->setCursorPosition(tle->cursorPosition());
                onTextChanged("");
            }
        }
    }
    else if(cType == KAYPAD_NUMERIC)
    {
        ui->frNum->show();

        cleInput = ui->leNinput;

        cleInput->setFocus();
        this->show();

        if(cLocal)
        {
            QLineEdit *tle = qobject_cast<QLineEdit *>(cLocal);

            if(tle)
            {
                cleInput->setValidator(tle->validator());
                cleInput->setText(tle->text());
                cleInput->setCursorPosition(tle->cursorPosition());
                onTextChanged("");
            }
        }
    }
}

void sKeypad::setData(QString rData)
{
    if(rData == "\b")
    {
        QString tmp = cleInput->text();
        int cp = cleInput->cursorPosition();
        if(cp > 0)
        {
            tmp.remove(cleInput->cursorPosition()-1, 1);
            cleInput->setText(tmp);
            cleInput->setFocus();
            cleInput->setCursorPosition(cp-1);
        }
        else
        {
            cleInput->setFocus();
            cleInput->setCursorPosition(cp-1);
        }
    }
    else
    {
        cleInput->insert(rData);
    }

}

void sKeypad::onTextChanged(QString tmp)
{

    if((!cleInput->hasAcceptableInput()) || ( !cZeroLength && ((!cleInput->text().length()) || (cleInput->text().startsWith(' ')))))
    {
        cleInput->setProperty("error", true);
        cleInput->style()->polish(cleInput);
    }
    else
    {
        cleInput->setProperty("error", false);
        cleInput->style()->polish(cleInput);
    }
}

void sKeypad::on_pbClicked()
{

    QPushButton *tle = qobject_cast<QPushButton *>(QObject::sender());

    if(tle)
      setData(tle->text());

}

void sKeypad::on_pbBackClicked()
{
    setData("\b");
}

void sKeypad::on_pbCapsClicked()
{
    if(ui->pbCap->text() == "small")
    {
        ui->pbCap->setText("CAP");

        ui->pbA->setText("A");
        ui->pbB->setText("B");
        ui->pbC->setText("C");
        ui->pbD->setText("D");
        ui->pbE->setText("E");
        ui->pbF->setText("F");
        ui->pbG->setText("G");
        ui->pbH->setText("H");
        ui->pbI->setText("I");
        ui->pbJ->setText("J");
        ui->pbK->setText("K");
        ui->pbL->setText("L");
        ui->pbM->setText("M");
        ui->pbN->setText("N");
        ui->pbO->setText("O");
        ui->pbP->setText("P");
        ui->pbQ->setText("Q");
        ui->pbR->setText("R");
        ui->pbS->setText("S");
        ui->pbT->setText("T");
        ui->pbU->setText("U");
        ui->pbV->setText("V");
        ui->pbW->setText("W");
        ui->pbX->setText("X");
        ui->pbY->setText("Y");
        ui->pbZ->setText("Z");
    }
    else
    {
        ui->pbCap->setText("small");

        ui->pbA->setText("a");
        ui->pbB->setText("b");
        ui->pbC->setText("c");
        ui->pbD->setText("d");
        ui->pbE->setText("e");
        ui->pbF->setText("f");
        ui->pbG->setText("g");
        ui->pbH->setText("h");
        ui->pbI->setText("i");
        ui->pbJ->setText("j");
        ui->pbK->setText("k");
        ui->pbL->setText("l");
        ui->pbM->setText("m");
        ui->pbN->setText("n");
        ui->pbO->setText("o");
        ui->pbP->setText("p");
        ui->pbQ->setText("q");
        ui->pbR->setText("r");
        ui->pbS->setText("s");
        ui->pbT->setText("t");
        ui->pbU->setText("u");
        ui->pbV->setText("v");
        ui->pbW->setText("w");
        ui->pbX->setText("x");
        ui->pbY->setText("y");
        ui->pbZ->setText("z");
    }

}

void sKeypad::on_pb123Clicked()
{

    if(ui->frEnglishAlpha->isVisible()) ui->frEnglishAlpha->hide();
    if(ui->frOtherAlpha->isVisible()) ui->frOtherAlpha->hide();

    ui->frNumSpecial->show();

    if(cleInput)
    {
        ui->leNinputSP->setValidator(cleInput->validator());
        ui->leNinputSP->setText(cleInput->text());
        ui->leNinputSP->setCursorPosition(cleInput->cursorPosition());
    }

    cleInput = ui->leNinputSP;
    cleInput->setFocus();

    this->show();

}

void sKeypad::on_pbABCClicked()
{

    if(ui->frNumSpecial->isVisible()) ui->frNumSpecial->hide();

    ui->frEnglishAlpha->show();

    if(cleInput)
    {
        ui->leInput->setValidator(cleInput->validator());
        ui->leInput->setText(cleInput->text());
        ui->leInput->setCursorPosition(cleInput->cursorPosition());
    }

    cleInput = ui->leInput;
    cleInput->setFocus();

    this->show();

}


void sKeypad::on_pbCancelClicked()
{
    if(ui->frEnglishAlpha->isVisible()) ui->frEnglishAlpha->hide();
    if(ui->frNum->isVisible()) ui->frNum->hide();
    if(ui->frNumSpecial->isVisible()) ui->frNumSpecial->hide();
    if(ui->frOtherAlpha->isVisible()) ui->frOtherAlpha->hide();

    cleInput->setFocus();

    if(cLocal)
    {
        QLineEdit *tle = qobject_cast<QLineEdit *>(cLocal);

        if(tle)
        {
            tle->setFocus();
        }
    }

    hide();
}

void sKeypad::on_pbEnterClicked()
{

    if((!cleInput->hasAcceptableInput()) || ( !cZeroLength && ((!cleInput->text().length()) || (cleInput->text().startsWith(' ')))))
    {
        cleInput->setProperty("error", true);
        cleInput->style()->polish(cleInput);
    }
    else
    {
        cleInput->setProperty("error", false);
        cleInput->style()->polish(cleInput);

        if(cLocal)
        {
            QLineEdit *tle = qobject_cast<QLineEdit *>(cLocal);

            if(tle)
            {
               tle->setText(cleInput->text());

               if(ui->frEnglishAlpha->isVisible()) ui->frEnglishAlpha->hide();
               if(ui->frNum->isVisible()) ui->frNum->hide();
               if(ui->frNumSpecial->isVisible()) ui->frNumSpecial->hide();
               if(ui->frOtherAlpha->isVisible()) ui->frOtherAlpha->hide();

               hide();
               tle->setFocus();

               QKeyEvent event(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);
               QApplication::sendEvent(tle, &event);

            }
        }
    }
}

void sKeypad::on_pbSpaceClicked()
{
    setData(" ");
}
