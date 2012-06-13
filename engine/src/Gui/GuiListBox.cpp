
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include <Gui/GuiListBox.hpp>

#include <Utils/Utils.hpp>

namespace dt {

GuiListBox::GuiListBox(const QString name)
    : GuiWidget(name),
    mListBox(nullptr) {}

MyGUI::Widget* GuiListBox::getMyGUIWidget() {
    return mListBox;
}

void GuiListBox::onInitialize() {
    mListBox = getParent()->getMyGUIWidget()->createWidget<MyGUI::ListBox>("ListBox", 0, 0, 100, 100, MyGUI::Align::Default, dt::Utils::toStdString(getFullName()));
}

void GuiListBox::addItem(const QString& name) {
    dynamic_cast<MyGUI::ListBox*>(getMyGUIWidget())->addItem(dt::Utils::toWString(name));
    emit addItemChanged(name);
}

void GuiListBox::removeItemAt(size_t index) {
    dynamic_cast<MyGUI::ListBox*>(getMyGUIWidget())->removeItemAt(index);
    emit removeItemAtChanged(index);
}

size_t GuiListBox::getIndexSelected() {
    return dynamic_cast<MyGUI::ListBox*>(getMyGUIWidget())->getIndexSelected();
}

size_t GuiListBox::findItemIndexWith(const QString& name) {
    return dynamic_cast<MyGUI::ListBox*>(getMyGUIWidget())->findItemIndexWith(dt::Utils::toStdString(name));
}

QString GuiListBox::getItemNameAt(size_t index) {
    return QString(dynamic_cast<MyGUI::ListBox*>(getMyGUIWidget())->getItemNameAt(index).asUTF8_c_str());
}

}

