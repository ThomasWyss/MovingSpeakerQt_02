/*!
	\file QtStatusBar.h
	\author Nicolas Gerber <nicolas.gerber@istb.unibe.ch>
	\date 2010/10/05
 */

#ifndef __QtStatusBar_H
#define __QtStatusBar_H

//
// Qt includes
//
#include <QWidget>


//
// Forward declarations
//
class QLabel;
class QProgressBar;


//! Main class for a status bar.
class QtStatusBar
	: public QWidget
{
	Q_OBJECT

	//! Shortcut for base class
	typedef QWidget BaseClass;

public:
    //! Returns the single instance of this class.
    static QtStatusBar* getInstance( QWidget* parent = 0 );

    //! Destruction of the instance.
    static void kill();

    //! Displays the status bar with the text defined previously.
    static void showMessage();

    //! Displays the message in the status bar.
    static void showMessage( const QString& status );

    //! Displays the error message in red in the status bar.
    static void showError( const QString& error );

	static void activateLevel(int mode);
	static void updateLevel(int level0, int level1, int level2, int level3);

signals:
    //! Signal emitted when a progress event has been started.
    void startProgressEventSig();

    //! Signal emitted when a progress event has been ended.
    void endProgressEventSig();

private:

    static QtStatusBar* m_instance;
    QLabel*             m_label;

	QProgressBar*		m_levelCH0;
    QProgressBar*       m_levelCH1;
	QProgressBar*		m_levelCH2;
    QProgressBar*       m_levelCH3;

    bool                m_wasPreviousErrorMessage;

    //! Constructor
    QtStatusBar( QWidget* parent = 0 );

    //! Destructor
    virtual ~QtStatusBar();

    //! Creates the user interface.
    void createInterface();

	//! Copy constructor and assignment operator are disabled.
    QtStatusBar( const QtStatusBar& other );
    QtStatusBar& operator=( const QtStatusBar& other );
};

#endif // __QtStatusBar_H
