
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_GUI_GUILISTBOX
#define DUCTTAPE_ENGINE_GUI_GUILISTBOX

#include <Config.hpp>

#include <Gui/GuiWidget.hpp>

#include <MyGUI.h>

namespace dt {

/**
  * GUI ListBox widget.
  */
class DUCTTAPE_API GuiListBox : public GuiWidget {
    Q_OBJECT
public:
    /**
      * Constructor.
      */
    GuiListBox(const QString name);

    MyGUI::Widget* getMyGUIWidget();
    void onInitialize();

    /** Get index of selected item (ITEM_NONE if none selected) */
	size_t getIndexSelected();

    //! Search item, returns the position of the first occurrence in array or ITEM_NONE if item not found
	size_t findItemIndexWith(const QString& name);

    //! Get item name from specified position
	QString getItemNameAt(size_t index);

public slots:
    //! Add an item to the end of a array
    void addItem(const QString& name);

    //! Remove item at a specified position
	void removeItemAt(size_t _index);

signals:
    void addItemChanged(QString name);
    void removeItemAtChanged(size_t index);

private:
    MyGUI::ListBox* mListBox;

};

}

#endif
