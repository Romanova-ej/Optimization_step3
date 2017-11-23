#ifndef RSOPTIONS_H
#define RSOPTIONS_H

#include <QDialog>

namespace Ui {
class RSOptions;
}

class RSOptions : public QDialog
{
    Q_OBJECT

public:
    explicit RSOptions(QWidget *parent = 0);
    ~RSOptions();

private:
    Ui::RSOptions *ui;
};

#endif // RSOPTIONS_H
