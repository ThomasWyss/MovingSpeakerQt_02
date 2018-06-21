/*!
	\file QtMainBar.h

    \author

    \date
 */

#ifndef QtMainBar_H_
#define QtMainBar_H_

//
// Qt includes
//
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QSpacerItem>
#include <QFrame>
#include <QLabel>

class QtMainBar : public QFrame
{
	Q_OBJECT

public:

    //! Constructor
	QtMainBar(QWidget * parent = 0, const char * name = 0, Qt::WindowFlags f = 0);
	
    //! Destructor
	virtual ~QtMainBar();

    //! Adds a module button to the main bar
    void addButton(QToolButton * button);

    //! Adds a spacer between module buttons and general controls
    void addSpacer();

    //! Adds a logo
    void addLogo();

    //! Adds a button to take a screen shot
	void addScreenShotButton();

    //! Add a exit button
    void addExitButton();

	
signals:

    //! Signal after module button has been clicked
	void moduleSelectedSIG(QToolButton*, int&);

    //! Signal after exit button has been clicked
	void exitClickedSIG();

public slots:

    //! Slot if module button has been clicked
	void buttonClickedSlot(QToolButton* button = NULL);
	
    //! Slot to take a screen shot
	void screenShotSlot();

    //! Slot to send a signal to close the application
    void exitMainBarSlot();

private:

    //! Sets up the user interface
	void setupUI();

private:

    QHBoxLayout * m_horizontalLayout;
    QSpacerItem * m_spacer;
    QToolButton * m_exitButton;
    QToolButton * m_screenShotButton;
    QLabel      * m_logo;
	QToolButton * m_lastClickedButton;

};


#endif // end of #ifndef QtMainBar_H_