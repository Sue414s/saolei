#include <QWidget>
#include <QTimer>

class Table : public QWidget{
    Q_OBJECT
public:
    explicit Table(QWidget *parent = nullptr);
    int getX() const;
    int getY() const;
    int getT() const;
    bool isOK() const;
private:
    bool t;
    int x,y,t_val;
};
    