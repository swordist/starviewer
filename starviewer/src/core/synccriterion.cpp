#include "synccriterion.h"

namespace udg {

SyncCriterion::SyncCriterion()
{
}

SyncCriterion::~SyncCriterion()
{
}

bool SyncCriterion::isCriterionSatisfied(QViewer *viewer1, QViewer *viewer2)
{
    if (viewer1 != 0 && viewer2 != 0)
    {
        return criterionIsMet(viewer1, viewer2);
    }
    else
    {
        return false;
    }
}

} // End namespace udg