// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_ITEMCATALOGUE_H
#define MVVM_ITEMCATALOGUE_H

#include "mvvm_global.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace ModelView
{

class SessionItem;

//! Catalogue for item constructions.

class CORE_EXPORT ItemCatalogue
{
public:
    ItemCatalogue();
    ~ItemCatalogue();

    ItemCatalogue(const ItemCatalogue& other);
    ItemCatalogue& operator=(const ItemCatalogue& other);

    template <typename T> void add(const std::string& label = {});

    bool contains(const std::string& model_type) const;

    std::unique_ptr<SessionItem> create(const std::string& model_type) const;

    std::vector<std::string> modelTypes() const;
    std::vector<std::string> labels() const;

    int itemCount() const;

    void merge(const ItemCatalogue& other);

private:
    using factory_func_t = std::function<SessionItem*()>;
    void add(const std::string& model_type, factory_func_t func, const std::string& label);
    std::unique_ptr<class ItemCataloguePrivate> p_impl;
};

template <typename T> void ItemCatalogue::add(const std::string& label)
{
    T x;
    add(x.modelType(), []() { return new T(); }, label);
}

} // namespace ModelView

#endif // MVVM_ITEMCATALOGUE_H
