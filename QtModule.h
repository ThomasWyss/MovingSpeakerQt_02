/*!
	\file QtModule.h

    \author

    \date
 */

#ifndef QtModule_H_
#define QtModule_H_

//
// Qt includes
//
#include <QToolButton>
#include <QObject>

class QtModule: public QObject
{
	Q_OBJECT

public:

    //! Constructor
	QtModule(QObject * parent = 0, const char * name = 0);
	
    //! Destructor
    virtual ~QtModule();

    //! Returns the module button
	QToolButton * getSelectButton();

    //! Returns the module control widget
	QWidget * getControlsWidget();

    //! Checks conditions to open a module
	virtual bool canActivate();

public slots:

    //! Slot to activate a module
	virtual void activateModuleSlot() = 0;

    //! Slot to deactivate a module
	virtual void deactivateModuleSlot(int&) = 0;

    //! Slot to hide a module
	virtual void hideSlot();

    //! Slot to display a module
	virtual void showSlot();

protected:

	QWidget *						m_moduleControls;
	QToolButton *					m_moduleSelectButton;

};


#endif // end of #ifndef QtModule_H_