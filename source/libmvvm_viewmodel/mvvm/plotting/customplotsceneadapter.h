// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_CUSTOMPLOTSCENEADAPTER_H
#define MVVM_PLOTTING_CUSTOMPLOTSCENEADAPTER_H

#include <mvvm/plotting/sceneadapterinterface.h>

class QCustomPlot;

namespace ModelView
{

/*!
@class CustomPlotSceneAdapter
@brief Converts QGraphicsScene coordinates in the coordinates of local system of QCustomPlot
and vice versa.
*/

class CORE_EXPORT CustomPlotSceneAdapter : public SceneAdapterInterface
{
public:
    explicit CustomPlotSceneAdapter(QCustomPlot* custom_plot);
    ~CustomPlotSceneAdapter() override;

    double toSceneX(double customplot_x) const override;

    double toSceneY(double customplot_y) const override;

    double fromSceneX(double scene_x) const override;

    double fromSceneY(double scene_y) const override;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_CUSTOMPLOTSCENEADAPTER_H
