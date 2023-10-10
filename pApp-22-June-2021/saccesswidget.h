#ifndef SACCESSWIDGET_H
#define SACCESSWIDGET_H

class sAccessWidget
{
public:
    sAccessWidget();

    virtual bool getWaitACKStatus(void);
    virtual void setWaitACKStatus(bool tmp);
    virtual void hideAfterACK(bool tmp);
    virtual bool getHideAfterACK(void);



};

#endif // SACCESSWIDGET_H
