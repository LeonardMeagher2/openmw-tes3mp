#ifndef OPENCS_VIEW_PAGEDWORLDSPACEWIDGET_H
#define OPENCS_VIEW_PAGEDWORLDSPACEWIDGET_H

#include "../../model/world/cellselection.hpp"

#include "worldspacewidget.hpp"

namespace CSVRender
{
    class PagedWorldspaceWidget : public WorldspaceWidget
    {
            Q_OBJECT

            CSMWorld::CellSelection mSelection;

        private:

            void dropEvent(QDropEvent* event);

            std::pair<int, int> getCoordinatesFromId(const std::string& record) const;

        public:

            PagedWorldspaceWidget (QWidget *parent, CSMDoc::Document& document);
            ///< \note Sets the cell area selection to an invalid value to indicate that currently
            /// no cells are displayed. The cells to be displayed will be specified later through
            /// hint system.

            void useViewHint (const std::string& hint);

            void setCellSelection (const CSMWorld::CellSelection& selection);

            virtual void handleDrop(const std::vector<CSMWorld::UniversalId>& data);

        signals:

            void cellSelectionChanged (const CSMWorld::CellSelection& selection);

            void interiorCellsDropped(const std::vector<CSMWorld::UniversalId>& data);
    };
}

#endif
