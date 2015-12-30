#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>

class QMenuBar;
class QVBoxLayout;

class ApplicationPrivate;
class Application : public QWidget
{
    Q_OBJECT

public:
    Application();
    ~Application();

    QMenuBar * menuBar() const;
    void setMenuBar(QMenuBar *menuBar);
    void keyPressEvent(QKeyEvent *event);

private:
    QVBoxLayout *_layout;

protected:
    ApplicationPrivate * const d_ptr;
private:
    Q_DECLARE_PRIVATE(Application);
};

#endif // APPLICATION_H
