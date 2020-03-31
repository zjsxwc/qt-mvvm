// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef APPLICATIONMODELS_H
#define APPLICATIONMODELS_H

#include <QString>
#include <memory>

class MaterialModel;
class SampleModel;
class SLDElementModel;
class SLDElementController;

//!  Main class to holds all models of GUI session.

class ApplicationModels
{
public:
    ApplicationModels();
    ~ApplicationModels();

    MaterialModel* materialModel();
    SampleModel* sampleModel();
    SLDElementModel* sldViewModel();
    SLDElementController* sldController();

    void readFromFile(const QString& name);

    void writeToFile(const QString& name);

private:
    struct ApplicationModelsImpl;
    std::unique_ptr<ApplicationModelsImpl> p_impl;
};

#endif //  APPLICATIONMODELS_H
