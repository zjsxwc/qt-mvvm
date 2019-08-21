// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "MaterialPropertyController.h"
#include "LayerItems.h"
#include "MaterialModel.h"
#include "SampleModel.h"
#include "externalproperty.h"
#include "modelmapper.h"
#include "modelutils.h"

using namespace ModelView;

MaterialPropertyController::MaterialPropertyController(MaterialModel* material_model,
                                                       SampleModel* sample_model)
    : m_material_model(material_model), m_sample_model(sample_model)
{
    connect_material_model();
    update_all();
}

MaterialPropertyController::~MaterialPropertyController()
{
    if (m_material_model)
        m_material_model->mapper()->unsubscribe(this);
}

//! Connect with signals of MaterialModel.

void MaterialPropertyController::connect_material_model()
{
    auto on_data_change = [this](SessionItem*, int) { update_all(); };
    m_material_model->mapper()->setOnDataChange(on_data_change, this);

    auto on_row_removed = [this](SessionItem*, std::string, int) { update_all(); };
    m_material_model->mapper()->setOnRowRemoved(on_row_removed, this);

    auto on_model_destroyed = [this](SessionModel*) { m_material_model = nullptr; };
    m_material_model->mapper()->setOnModelDestroyed(on_model_destroyed, this);
}

//! Updates all material properties in LayerItems to get new material colors and labels.

void MaterialPropertyController::update_all()
{
    auto layers = Utils::FindItems<LayerItem>(m_sample_model);
    for (auto layer : Utils::FindItems<LayerItem>(m_sample_model)) {
        auto property =
            layer->property(LayerItem::P_MATERIAL).value<ModelView::ExternalProperty>();
        auto updated = m_material_model->material_property(property.identifier());
        if (property != updated)
            layer->setItemValue(LayerItem::P_MATERIAL, QVariant::fromValue(updated));
    }
}
