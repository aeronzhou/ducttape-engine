
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include <Scene/Component.hpp>

#include <Logic/ScriptManager.hpp>
#include <Scene/Node.hpp>
#include <Utils/Utils.hpp>

namespace dt {

Component::Component(const QString name)
    : mName(name),
      mNode(nullptr),
      mIsEnabled(false),
      mIsInitialized(false) {
    // auto-generate the component name
    if(mName == "") {
        mName = "Component-" + Utils::toString(Utils::autoId());
    }

    mId = QUuid::createUuid();
}

Component::~Component() {}

const QString Component::getName() const {
    return mName;
}

QString Component::getFullName() const {
    return mNode == nullptr ? getName() : mNode->getFullName() + "/" + getName();
}

void Component::onInitialize() {}

void Component::onDeinitialize() {}

void Component::onEnable() {}

void Component::onDisable() {}

void Component::onUpdate(double time_diff) {}

void Component::serialize(IOPacket& packet) {
    // only write type when serializing, it will be read by the Node on deserialization
    if(packet.getDirection() == IOPacket::SERIALIZE) {
        std::string type(metaObject()->className());
        packet.stream(type, "type");
    }

    packet.stream(mId, "uuid");
    packet.stream(mName, "name");
    packet.stream(mIsEnabled, "enabled", true);

    onSerialize(packet);
}

void Component::onSerialize(IOPacket& packet) {}

Node* Component::getNode() {
    return mNode;
}

void Component::setNode(Node* node) {
    if(mNode == nullptr)
        mNode = node;
}

QScriptValue Component::getScriptNode() {
    Node* p_node = getNode();
    // Making QScriptValue from Node. Type conversion in C style only due to limitation of incomplete type.
    // return dt::ScriptManager::GetScriptEngine()->newQObject((QObject*)mNode);
    return p_node == nullptr ? QScriptValue::UndefinedValue : MAKE_SCRIPTABLE(p_node);
}

void Component::initialize() {
    if(!mIsInitialized) {
        mIsInitialized = true;
        onInitialize();
        emit componentInitialized();
        enable();
    }
}

void Component::deinitialize() {
    if(mIsInitialized) {
        mIsInitialized = false;
        disable();
        emit componentUninitialized();
        onDeinitialize();
    }
}

void Component::enable() {
    if(!mIsEnabled && this->getNode()->isEnabled()) {
        mIsEnabled = true;
        emit componentEnabled();
        onEnable();
    }
}

void Component::disable() {
    if(mIsEnabled) {
        mIsEnabled = false;
        emit componentDisabled();
        onDisable();
    }
}

bool Component::isInitialized() {
    return mIsInitialized;
}

bool Component::isEnabled() {
    return mIsEnabled;
}

} // namespace dt
