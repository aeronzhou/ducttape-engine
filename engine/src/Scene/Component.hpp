
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_COMPONENT_COMPONENT
#define DUCTTAPE_ENGINE_COMPONENT_COMPONENT

#include <Config.hpp>

#include <Utils/Utils.hpp>
#include <Logic/IScriptable.hpp>
#include <Network/IOPacket.hpp>
#include <Scene/Serializer.hpp>

#include <QObject>
#include <QScriptValue>
#include <QString>

#include <memory>

namespace dt {

// forward declaration due to circular dependency
class Node;

/**
  * Modifier for a Node. This will add all the functionality to an otherwise empty Node,
  * such as a mesh or sound.
  */
class DUCTTAPE_API Component : public QObject, public IScriptable {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName CONSTANT FINAL)
    Q_PROPERTY(QString fullName READ getFullName FINAL)
    Q_PROPERTY(bool isEnabled READ isEnabled FINAL)
    Q_PROPERTY(bool isInitialized READ isInitialized FINAL)
    Q_PROPERTY(QScriptValue node READ getScriptNode)

public:
    
    typedef std::shared_ptr<Component> ComponentSP;

    /**
      * Constructor with set name.
      * @param name The Component name.
      */
    Component(const QString name = "");

    /**
      * Pure virtual destructor makes this class abstract.
      */
    virtual ~Component() = 0;

    /**
      * Called when the Component is activated.
      */
    virtual void onInitialize();

    /**
      * Called when the Component is deactivated.
      */
    virtual void onDeinitialize();

    /**
      * Called when the Component is enabled.
      */
    virtual void onEnable();

    /**
      * Called when the Component is disabled.
      */
    virtual void onDisable();

    /**
      * Called every frame. Update the Node here.
      * @param time_diff The frame delta time.
      */
    virtual void onUpdate(double time_diff);

    void serialize(IOPacket& packet);

    virtual void onSerialize(IOPacket& packet);

    /**
      * Returns the Node of this Component.
      * @returns The Node of this Component.
      */
    Node* getNode();

    /**
      * Initializes the Component.
      */
    void initialize();

    /**
      * Deinitializes the Component.
      */
    void deinitialize();

     /**
       * Sets the node of this component. This is called by the Node to which this Component is attached. Do not call it manually.
       * @param node The node to be set.
       */
     void setNode(Node* node);

     /**
       * Returns a QtScript object.
       * @returns A QtScript object.
       * @see IScriptable
       */
     QScriptValue toQtScriptObject();

public slots:
    /**
      * Returns the name of the Component.
      * @returns The name of the Component.
      */
    const QString getName() const;

    /**
      * Returns the name of the Component, including all parent names. If this Component has not been attached to a Node, it returns the name of the Component only.
      * @returns The name of the Component, including all parent names. If this Component has not been attached to a Node, it returns the name of the Component only.
      */
    QString getFullName() const;

    /**
      * Returns the Node of this Component. Used for scripting access.
      * @returns The Node of this Component. Returns UndefinedValue when this Component has not been attached to a Node.
      */
    QScriptValue getScriptNode();

    /**
      * Returns whether the Component is created.
      * @returns Whether the Component is created.
      */
    bool isInitialized();

    /**
      * Returns whether the Component is enabled.
      * @returns Whether the Component is enabled.
      */
    bool isEnabled();

    /**
      * Enables the Component.
      */
    void enable();

    /**
      * Disables the Component.
      */
    void disable();

signals:
    void componentInitialized();
    void componentUninitialized();
    void componentEnabled();
    void componentDisabled();

protected:
    QString mName;  //!< The Component name.
    Node* mNode;        //!< The parent Node.

private:
    bool mIsEnabled;    //!< Whether the Component is enabled or not.
    bool mIsInitialized;    //!< Whether the Component has been created or not.
    QUuid mId;    //!< The id for the Component.
};

} // namespace dt

#endif
