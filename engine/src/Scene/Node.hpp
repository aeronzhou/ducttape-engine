
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_SCENE_NODE
#define DUCTTAPE_ENGINE_SCENE_NODE

#include <Config.hpp>

#include <Scene/Component.hpp>
#include <Utils/Logger.hpp>
#include <Utils/Utils.hpp>
#include <Network/IOPacket.hpp>

#include <OgreQuaternion.h>
#include <OgreVector3.h>

#include <QObject>
#include <QString>

#include <memory>

namespace dt {

// forward declaration due to circular dependency
class Scene;

/**
  * Basic scene object class.
  * Any object in a scene is described by a Node with a position, scale and rotation
  * and other child Nodes. The Node class is also able to have Components to control
  * its behaviour, e.g. the look or events.
  * @see Component
  */
class DUCTTAPE_API Node : public QObject, IMPLEMENTS IScriptable {
    Q_OBJECT
    Q_ENUMS(RelativeTo)

    Q_PROPERTY(QString name READ getName CONSTANT FINAL)
    Q_PROPERTY(QString fullName READ getFullName FINAL)
    Q_PROPERTY(QScriptValue parent READ getScriptParent WRITE setScriptParent FINAL)
    Q_PROPERTY(QScriptValue scene READ getScriptScene FINAL)
    Q_PROPERTY(bool isEnabled READ isEnabled FINAL)

public:
    
    typedef std::shared_ptr<Node> NodeSP;
    
    /**
      * The coordinates space for getting/setting rotation, position and scale.
      */
    enum RelativeTo {
        PARENT, //!< Relative to the parent Node.
        SCENE   //!< Relative to the scene root Node (i.e. absolute value).
    };

    /**
      * Constructor.
      * @param name The name of the Node.
      */
    Node(const QString name = "");

    /**
      * Initializer.
      */
    void initialize();

    /**
      * Deinitializer. Cleans up the whole mess :D
      */
    void deinitialize();

    /**
      * Called when the Node is initialized.
      */
    virtual void onInitialize();

    /**
      * Called when the Node is deinitialized.
      */
    virtual void onDeinitialize();

    /**
      * Adds a Node as child.
      * @param child The Node to be added as child
      * @returns A pointer to the Node.
      */
    Node::NodeSP addChildNode(Node* child);

    /**
      * Assigns a Component to this Node.
      * @param component The Component to be assigned.
      * @returns A pointer to the new Component.
      */
    template <typename ComponentType>
    std::shared_ptr<ComponentType> addComponent(ComponentType* component) {
        const QString cname = component->getName();
        if(!hasComponent(cname)) {
            std::shared_ptr<Component> ptr(component);
            ptr->setNode(this);
            ptr->initialize();
            std::pair<QString, std::shared_ptr<Component> > pair(cname, ptr);
            mComponents.insert(pair);
            
            if(!mIsEnabled)
                component->disable();

            _updateAllComponents(0);
        } else {
            Logger::get().error("Cannot add component " + cname + ": a component with this name already exists.");
        }
        return findComponent<ComponentType>(cname);
    }

    /**
      * Searches for a Node with the given name and returns a pointer to the first match.
      * @param name The name of the Node searched.
      * @param recursive Whether to search within child Nodes or not.
      * @returns A pointer to the Node with the name or nullptr if none is found.
      */
    Node::NodeSP findChildNode(const QString name, bool recursive = true);

    /**
      * Returns a Component.
      * @param name The name of the Component to find.
      * @returns A pointer to the Component, or nullptr if no Component with the specified name exists.
      */
    template <typename ComponentType>
    std::shared_ptr<ComponentType> findComponent(const QString name) {
        if(!hasComponent(name))
            return std::shared_ptr<ComponentType>();
        return std::dynamic_pointer_cast<ComponentType>(mComponents[name]);
    }

    /**
      * Returns the position of the Node.
      * @param rel Reference point.
      * @returns The Node position.
      */
    Ogre::Vector3 getPosition(RelativeTo rel = PARENT) const;

    /**
      * Sets the position of the Node.
      * @param position The new position of the Node.
      * @param rel Reference point.
      */
    void setPosition(Ogre::Vector3 position, RelativeTo rel = PARENT);

    /**
      * Returns the scale of the Node.
      * @param rel Reference scale.
      * @returns The scale of the Node
      */
    Ogre::Vector3 getScale(RelativeTo rel = PARENT) const;

    /**
      * Sets the scale of the Node.
      * @param scale The new scale.
      * @param rel Reference scale.
      */
    void setScale(Ogre::Vector3 scale, RelativeTo rel = PARENT);

    /**
      * Sets the scale of the Node.
      * @param scale The new scale to use for all axis.
      * @param rel Reference scale.
      */
    void setScale(Ogre::Real scale, RelativeTo rel = PARENT);

    /**
      * Returns the rotation of the Node.
      * @param rel Reference rotation.
      * @returns The Rotation of the Node.
      */
    Ogre::Quaternion getRotation(RelativeTo rel = PARENT) const;

    /**
      * Sets the rotation of the Node.
      * @param rotation The rotation to set.
      * @param rel Reference rotation.
      */
    void setRotation(Ogre::Quaternion rotation, RelativeTo rel = PARENT);

    /**
      * Sets the direction the Node is facing.
      * @param direction The direction the Node is facing.
      * @param front_vector The local direction that specifies the front of the Node (which part of the Node should be facing into the direction).
      */
    void setDirection(Ogre::Vector3 direction, Ogre::Vector3 front_vector = Ogre::Vector3::UNIT_Z);

    /**
      * Rotates the node to look at the target.
      * @param target The point the node should look at.
      * @param front_vector The local direction that specifies the front of the Node (which part of the Node should be facing into the direction).
      * @param rel Reference position.
      */
    void lookAt(Ogre::Vector3 target, Ogre::Vector3 front_vector = Ogre::Vector3::UNIT_Z, RelativeTo rel = PARENT);

    /**
      * Sets the parent Node pointer.
      * @param parent The parent Node pointer.
      */
    void setParent(Node* parent);

    /**
      * Called when the Node is being updated.
      * @param time_diff The frame time.
      */
    virtual void onUpdate(double time_diff);

    void serialize(IOPacket& packet);

    virtual void onSerialize(IOPacket& packet);

    /**
      * Called when the node is enabled.
      */
    virtual void onEnable();

    /**
      * Called when the node is disabled.
      */
    virtual void onDisable();

    /**
      * Returns a pointer to the parent Node.
      * @returns A pointer to the parent Node.
      */
    Node* getParent();

    /**
      * Returns the Scene this Node is attached to.
      * @returns The Scene this Node is attached to.
      */
    Scene* getScene();

    /**
      * Returns a QtScript object.
      * @returns A QtScript object.
      * @see IScriptable
      */
    QScriptValue toQtScriptObject();

public slots:
    /**
      * Returns whether this node has the component assigned.
      * @param name The name of the Component.
      * @returns true if the component is assigned, otherwise false
      */
    bool hasComponent(const QString name);

    /**
      * Returns the name of the Node.
      * @returns The name of the Node.
      */
    const QString getName() const;

    /**
      * Returns the name of the Node, including all parent names. If this Node does not have a parent Node, it returns the name of the Node only.
      * @returns The name of the Node, including all parent names. If this Node does not have a parent Node, it returns the name of the Node only.
      */
    QString getFullName() const;

    /**
      * Returns a pointer to the parent Node. Used for scripting access.
      * @returns A pointer to the parent Node. Returns UndefinedValue when this node does not have a parent Node.
      */
    QScriptValue getScriptParent();

    /**
      * Sets the parent Node pointer. Used for setting the parent in script.
      * @param parent A Node object in script which will become the parent Node.
      */
    void setScriptParent(QScriptValue parent);

    /**
      * Adds a Node as child. Used for adding a child in script.
      * @param child The Node to be added as child.
      * @returns An in-script Node object which has been added as a child of this Node.
      */
    QScriptValue addScriptChildNode(QScriptValue child);

    /**
      * Assigns a Component to this Node. Used for adding a Component in script
      * @param component The Component to be assigned.
      * @returns An in-script Component object which has been attached to this Node.
      */
    QScriptValue addScriptComponent(QScriptValue component);

    /**
      * Returns a Component.
      * @param name The name of the Component to find.
      * @returns An in-script Component object, or UndefinedValue if no Component with the specified name exists.
      */
    QScriptValue findScriptComponent(const QString name);

    /**
      * Searches for a Node with the given name and returns an in-script Node object that is the first match.
      * @param name The name of the Node searched.
      * @param recursive Whether to search within child Nodes or not.
      * @returns An in-script Node object with the name or UndefinedValue if none is found.
      */
    QScriptValue findScriptChildNode(const QString name, bool recursive = true);

    /**
      * Returns the Scene this Node is attached to. Used for scripting access.
      * @returns The Scene this Node is attached to. Returns UndefinedValue when this node does not belong to any scenes.
      */
    QScriptValue getScriptScene();

    /**
      * Removes a child Node with a specific name.
      * @param name The name of the Node to be removed.
      */
    void removeChildNode(const QString name);

    /**
      * Removes a Component with a specific name.
      * @param name The name of the Component to be removed.
      */
    void removeComponent(const QString name);

    /**
      * Sets the position of the Node.
      * @param x The x position.
      * @param y The y position.
      * @param z The z position.
      * @param rel Reference point.
      */
    void setPosition(float x, float y, float z, RelativeTo rel = PARENT);

    /**
      * Sets the death mark to true. Then the node will be kill when it updates.
      */
    void kill();

    /**
      * Enables the node. If a node is enabled, all of its components and child nodes are enabled but
      * its components and child nodes can be disabled manually by the user.
      */
    void enable();

    /**
      * Disables the node. If a node is disabled, all of its components and child nodes are disabled 
      * and its components or child nodes can't be enabled at this situation.
      */
    void disable();

    /**
      * Returns whether the node is enabled.
      * @returns Whether the node is enabled.
      */
    bool isEnabled();

signals:
    void positionChanged();

protected:
    /**
      * Returns whether this Node is a Scene.
      * @internal
      * @returns Whether this Node is a Scene.
      */
    virtual bool _isScene();

    /**
      * Updates all components.
      * @param time_diff The frame time.
      * @see Component::OnUpdate(double time_diff);
      */
    void _updateAllComponents(double time_diff);

    /**
      * Updates all child nodes.
      * @param time_diff The frame time.
      * @see OnUpdate(double time_diff);
      */
    void _updateAllChildren(double time_diff);

    std::map<QString, std::shared_ptr<Component> > mComponents;   //!< The list of Components.
    QString mName;              //!< The Node name.

private:
    std::map<QString, NodeSP> mChildren;  //!< List of child nodes.
    Ogre::Vector3 mPosition;              //!< The Node position.
    Ogre::Vector3 mScale;                 //!< The Node scale.
    Ogre::Quaternion mRotation;           //!< The Node rotation.
    Node* mParent;                        //!< A pointer to the parent Node.
    bool mIsUpdatingAfterChange;          //!< Whether the node is just in the process of updating all components after a change occurred. This is to prevent infinite stack loops.
    QUuid mId;                            //!< The node's uuid.
    bool mDeathMark;                      //!< Whether the node is marked to be killed. If it's true, the node will be killed when it updates.
    bool mIsEnabled;                      //!< Whether the node is enabled or not.
};

} // namespace dt

#endif
