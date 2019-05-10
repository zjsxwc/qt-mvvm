// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_REMOVEITEMCOMMAND_H
#define MVVM_REMOVEITEMCOMMAND_H

#include "abstractitemcommand.h"
#include "path.h"
#include <memory>

class QJsonObject;

namespace ModelView
{

class SessionModel;
class SessionItem;

//! Command for unddo/redo framework to remove item from a model using child's tag and row.

class CORE_EXPORT RemoveItemCommand : public AbstractItemCommand
{
public:
    using result_t = bool;

    RemoveItemCommand(SessionItem* parent, std::string tag, int row);
    ~RemoveItemCommand() override;

    void undo() override;
    void redo() override;

    result_t result() const;

private:
    Path m_parent_path;
    std::string m_tag;
    int m_row;
    std::unique_ptr<QJsonObject> m_child_backup;
    SessionModel* m_model;
    result_t m_result;
};

} // namespace ModelView

#endif // MVVM_REMOVEITEMCOMMAND_H