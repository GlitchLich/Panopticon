#include "ide/include/core/FilePanel.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QAction>
#include "ide/include/style/StyleGlobals.h"

namespace panopticon
{

namespace ide
{

FilePanel::FilePanel(QWidget *parent) :
    QToolBar("File Pane", parent),
    lastPressed(9999) // arbitrarily large number to prevent initial uncheck
{
    //setFixedHeight(20);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Normal, QPalette::Base, ide::style->clearColor());
    palette.setColor(QPalette::Normal, QPalette::Window, ide::style->clearColor());
    palette.setColor(QPalette::Normal, QPalette::Background, ide::style->clearColor());
    palette.setColor(QPalette::Normal, QPalette::Button, ide::style->clearColor());
    setPalette(palette);
    setAllowedAreas(Qt::LeftToolBarArea | Qt::BottomToolBarArea | Qt::TopToolBarArea);
    setFloatable(false);
    setMovable(false);
}

void FilePanel::addEditBuffer(unsigned int buffer)
{
    QToolButton* panelEntry = new QToolButton();
    panelEntry->setFont(ide::style->toolFont);
    panelEntry->setText("Unsaved");
    panelEntry->setProperty("id", buffer);
    panelEntry->setCheckable(true);
    panelEntry->setChecked(true);
    panelEntry->setMaximumWidth(100);
    panelEntry->connect(panelEntry, SIGNAL(clicked()), this, SLOT(fileButtonPressed()));
    fileButtons[buffer] = panelEntry;

    if(fileButtons.contains(lastPressed))
        fileButtons[lastPressed]->setChecked(false);

    lastPressed = buffer;

    addWidget(panelEntry);
}

void FilePanel::setFileName(unsigned int buffer, const QString& fileName)
{
    fileButtons[buffer]->setText(fileName);
}

void FilePanel::removeEditBuffer(unsigned int buffer)
{
    if(fileButtons.contains(buffer))
    {
        QToolButton* button = fileButtons[buffer];
        fileButtons.remove(buffer);
        delete button;
        update();
    }
}

void FilePanel::fileButtonPressed()
{
    QToolButton* button = ((QToolButton*) sender());

    if(button)
    {
        unsigned int id = button->property("id").toUInt();
        emit showEditBuffer(id);

        if(fileButtons.contains(lastPressed))
            fileButtons[lastPressed]->setChecked(false);

        lastPressed = id;
    }
}

void FilePanel::checkButton(unsigned int buffer)
{
    if(fileButtons.contains(lastPressed))
        fileButtons[lastPressed]->setChecked(false);

    if(fileButtons.contains(buffer))
        fileButtons[buffer]->setChecked(true);

    lastPressed = buffer;
}

} // ide namespace

} // panopticon namespace
