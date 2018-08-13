
#pragma once


#include <cppexpose/expose/Object.h>
#include <cppexpose/expose/Var.h>

#include <cppexpose-script/cppexpose-script_api.h>


namespace cppexpose_script
{


/**
*  @brief
*    Example class for dynamic hierarchies
*
*  @remarks
*    This class is an example for reflection objects that
*    create dynamic sub-objects. It can be used to test
*    the cppexpose scripting framework's ability to cope
*    with such dynamic object hierarchies.
*/
class CPPEXPOSE_SCRIPT_API TreeNode : public cppexpose::Object
{
public:
    // Properties
    cppexpose::Var<int> id;


public:
    /**
    *  @brief
    *    Constructor
    */
    TreeNode();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~TreeNode();

    /**
    *  @brief
    *    Get node ID
    *
    *  @return
    *    ID of the node
    */
    int getId() const;

    /**
    *  @brief
    *    Set node ID
    *
    *  @param[in] id
    *    ID of the node
    */
    void setId(const int & id);

    /**
    *  @brief
    *    Expand node
    *
    *  @remarks
    *    Expands the node by creating two sub-nodes 'left' and 'right'.
    *    If the node is already expanded, this function just returns.
    */
    void expand();

    /**
    *  @brief
    *    Collapse node
    *
    *  @remarks
    *    If expanded, the sub-nodes 'left' and 'right' will be deleted and
    *    removed from the node.
    */
    void collapse();

    /**
    *  @brief
    *    Print tree to console
    *
    *  @param[in] indent
    *    Indentation string
    *
    *  @remarks
    *    This prints the id and contents of the tree node and all sub-nodes
    *    to the console.
    */
    void print(const std::string & indent = "");


protected:
    int                       m_id;    ///< ID of the node
    std::unique_ptr<TreeNode> m_left;  ///< Left child node (can be null)
    std::unique_ptr<TreeNode> m_right; ///< Right child node (can be null)
};


} // namespace cppexpose_script
